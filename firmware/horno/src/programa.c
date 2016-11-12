/*
 * programa.c
 *
 *  Created on: 8 de nov. de 2016
 *      Author: m4v
 */

#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif

#include "programa.h"
#include "pwm.h"
#include "adc.h"
#include "control.h"
#include "motor.h"
#include "grafico.h"

#define TIEMPO_PROGRAMA (horno_adc.valor_n - horno_programa.tiempo_inicio)

void Horno_programa_actualizar(void)
{
	switch(horno_estado) {
	case INICIO:
		/* activar todo y empezar a calentar */
		Horno_control_referencia(horno_programa.temperatura_secado);
		Horno_control_activar(true);
		Horno_pwm_inicio();
		/* calcular el tiempo restante */
		horno_programa.tiempo_total = horno_programa.tiempo_secado
									+ horno_programa.tiempo_coccion
									+ (horno_programa.temperatura_coccion - horno_programa.temperatura_secado)/0.8
									+ horno_programa.temperatura_secado / 0.3333;
		horno_programa.tiempo_programa_inicio = horno_adc.valor_n;
		horno_estado = ESPERAR_TSECADO;
		DEBUGOUT("ESPERAR_TSECADO\n");
		break;
	case ESPERAR_TSECADO:
		/* pendiente inicial de temperatura.
		 * esperar hasta alcanzar la temperatura de secado */
		if (horno_adc.temperatura > (horno_programa.temperatura_secado - 10))
		{
			horno_programa.tiempo_inicio = horno_adc.valor_n;
			horno_estado = SECADO;
			DEBUGOUT("SECADO\n");
		}
		break;
	case SECADO:
		Horno_motor_subir_tiempo(horno_programa.tiempo_secado);
		/* recalcular el tiempo restante */
		horno_programa.tiempo_total = horno_programa.tiempo_secado
									+ horno_programa.tiempo_coccion
									+ (horno_programa.temperatura_coccion - horno_programa.temperatura_secado)/0.8;
		horno_programa.tiempo_programa_inicio = horno_adc.valor_n;

		horno_estado = ESPERAR_CIERRE;
		DEBUGOUT("ESPERAR_CIERRE\n");
		break;
	case ESPERAR_CIERRE:
		/* esperar a que se cierre el horno */
		if (!horno_motor.activo)
		{
			/* llegó al fin de carrera */
			horno_estado = CALENTAMIENTO;
			DEBUGOUT("CALENTAMIENTO\n");
		}
		break;
	case CALENTAMIENTO:
		/* configurar la nueva temperatura */
		Horno_control_referencia(horno_programa.temperatura_coccion);
		/* recalcular el tiempo restante */
		horno_programa.tiempo_total = horno_programa.tiempo_coccion
									+ (horno_programa.temperatura_coccion - horno_programa.temperatura_secado)/0.8;
		horno_programa.tiempo_programa_inicio = horno_adc.valor_n;

		horno_estado = ESPERAR_TCOCCION;
		DEBUGOUT("ESPERAR_TCOCCION\n");
		break;
	case ESPERAR_TCOCCION:
		/* segunda pendiente de temperatura.
		 * esperar hasta alcanzar la temp. de cocción */
		if (horno_adc.temperatura > (horno_programa.temperatura_coccion - 10))
		{
			/* recalcular el tiempo restante */
			horno_programa.tiempo_total = horno_programa.tiempo_coccion;
			horno_programa.tiempo_programa_inicio = horno_adc.valor_n;

			horno_estado = COCCION;
			horno_programa.tiempo_inicio = horno_adc.valor_n;
			DEBUGOUT("COCCION\n");
		}
		break;
	case COCCION:
		/* esperar el tiempo programado */
		if (horno_programa.tiempo_coccion < (horno_adc.valor_n - horno_programa.tiempo_inicio))
		{
			horno_estado = FIN_PROGRAMA;
			DEBUGOUT("FIN_PROGRAMA\n");
		}
		break;
	case FIN_PROGRAMA:
		/* detenemos todo y abrimos la puerta */
		Horno_pwm_parar();
		Horno_control_activar(false);
		Horno_motor_bajar();
		/* limpiar los 2 puntos */
		Horno_grafico_CLR_dos_puntos();
		/* escribir FIN */
		uint32_t pos_m[2]={295, 268};
		uint32_t pos_h[2]={235, 210};
	   	Horno_grafico_CLR_digito(pos_m[1],75);
	   	Horno_grafico_CLR_digito(pos_m[0],75);
	   	Horno_grafico_CLR_digito(pos_h[1],75);
	   	Horno_grafico_CLR_digito(pos_h[0],75);
		Horno_grafico_FIN(); // Ponemos la palabra FIN
		horno_estado = HACER_NADA;
		DEBUGOUT("HACER_NADA\n");
		break;
	case HACER_NADA:
		break;
	}

	if (horno_estado != HACER_NADA) {
		/* Pone los dos puntos intermitentes del tiempo */
		if(horno_adc.valor_n & 1){
			Horno_grafico_CLR_dos_puntos();
		} else {
			Horno_grafico_dos_puntos();
		}
		int32_t tiempo = horno_programa.tiempo_total
				        - horno_adc.valor_n
				        + horno_programa.tiempo_programa_inicio;
		Horno_grafico_tiempo(tiempo > 0 ? tiempo : 0);
	}


}

void Horno_programa_inicio(void) {
	horno_programa.temperatura_coccion = 800;
	horno_programa.temperatura_secado = 200;
	horno_programa.tiempo_secado = 600;
	horno_programa.tiempo_coccion = 600;
	horno_programa.pendiente_calentamiento = 0.8;

	horno_estado = INICIO;
	DEBUGOUT("INICIO\n");
}

/* dato: valor a poner en las lineas de datos
 * estado:	true: funcionando el programa;
 * 			false: programa apagado
 */
//void Horno_programa_carga_datos(int horno_ingreso_datos, uint32_t dato, bool estado){
void Horno_programa_carga_datos(int horno_ingreso_datos, uint32_t dato){
//	if(!estado==true){
		switch(horno_ingreso_datos)	{
		case PENDIENTE_MAX:
			Horno_grafico_datos_pendiente(dato);
			horno_programa.pendiente_calentamiento = dato;
			break;
		case TIEMPO_SECADO:
			Horno_grafico_datos_tiempo_secado(dato); // En este tenemos que definir qué variable le asignamos
			horno_programa.tiempo_secado = dato;
			break;
		case TIEMPO_COCCION:
			Horno_grafico_datos_tiempo_coccion(dato);
			horno_programa.tiempo_coccion = dato;
			break;
		case TEMPERATURA_SECADO:
			Horno_grafico_datos_temperatura_secado(dato);
			horno_programa.temperatura_secado = dato;
			break;
		case TEMPERATURA_COCCION:
			Horno_grafico_datos_temperatura_coccion(dato);
			horno_programa.temperatura_coccion = dato;
			break;
		}
//	}


}
