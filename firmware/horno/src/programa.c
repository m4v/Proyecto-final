/*
 * programa.c
 *
 *  Created on: 8 de nov. de 2016
 *      Author: Elián Hanisch, Gastón Riera y Rodrigo Oliver
 *
 *  Implementación de la máquina de estados del programa.
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
#include "teclado.h"

static uint32_t flecha_posicion;

void Horno_programa_actualizar(void)
{
	switch(horno_programa.estado) {
	case INICIO:
		/* deshabilitamos la carga de datos */
		horno_teclado_deshabilitar_carga_datos=true;
		/* borramos la última flecha */
		Horno_grafico_flecha_datos(horno_teclado_linea_datos, true,horno_teclado_deshabilitar_carga_datos);
		/* activar todo y empezar a calentar */
		Horno_control_referencia(horno_programa.temperatura_secado);
		Horno_control_activar(true);
		Horno_pwm_activar(true);
		/* calcular el tiempo restante
		 * FIXME para el calculo usa la pendiente de calentamiento 0.8 pero
		 * debería usar la que esté configurada */
		horno_programa.tiempo_total = horno_programa.tiempo_secado
									+ horno_programa.tiempo_coccion
									+ (horno_programa.temperatura_coccion - horno_programa.temperatura_secado)/0.8
									+ horno_programa.temperatura_secado / 0.3333;
		horno_programa.tiempo_programa_inicio = horno_adc.valor_n;
		Horno_grafico_programa(true,
				horno_programa.pendiente_calentamiento,
				horno_programa.tiempo_secado,
				horno_programa.tiempo_coccion,
				horno_programa.temperatura_secado,
				horno_programa.temperatura_coccion
				);
		horno_programa.estado = ESPERAR_TSECADO;
		DEBUGOUT("ESPERAR_TSECADO\n");
		break;
	case ESPERAR_TSECADO:
		/* pendiente inicial de temperatura.
		 * esperar hasta alcanzar la temperatura de secado */
		if (horno_adc.temperatura > (horno_programa.temperatura_secado))
		{
			horno_programa.tiempo_inicio = horno_adc.valor_n;
			horno_programa.estado = SECADO;
			DEBUGOUT("SECADO\n");
		} else {
			/* actualizamos la flecha */
			Horno_grafico_posicion_CLR_flecha(flecha_posicion);
			int pasos_rampa = horno_programa.temperatura_secado/7;
			flecha_posicion = horno_adc.temperatura/pasos_rampa;
			Horno_grafico_posicion_flecha(flecha_posicion);
		}
		break;
	case SECADO:
		Horno_motor_subir_tiempo(horno_programa.tiempo_secado);
		/* recalcular el tiempo restante */
		horno_programa.tiempo_total = horno_programa.tiempo_secado
									+ horno_programa.tiempo_coccion
									+ (horno_programa.temperatura_coccion - horno_programa.temperatura_secado)/0.8;
		horno_programa.tiempo_programa_inicio = horno_adc.valor_n;
		horno_programa.estado = ESPERAR_CIERRE;
		DEBUGOUT("ESPERAR_CIERRE\n");
		break;
	case ESPERAR_CIERRE:
		/* esperar a que se cierre el horno */
		if (!horno_motor.activo)
		{
			/* llegó al fin de carrera */
			horno_programa.estado = CALENTAMIENTO;
			DEBUGOUT("CALENTAMIENTO\n");
		}
		/* actualizamos la flecha */
		if (flecha_posicion < 18) {
			Horno_grafico_posicion_CLR_flecha(flecha_posicion);
			int pasos = horno_programa.tiempo_secado/12;
			flecha_posicion = (horno_adc.valor_n - horno_programa.tiempo_programa_inicio)/pasos + 7;
			Horno_grafico_posicion_flecha(flecha_posicion);
		}
		break;
	case CALENTAMIENTO:
		/* configurar la nueva temperatura */
		Horno_control_referencia(horno_programa.temperatura_coccion);
		/* recalcular el tiempo restante */
		horno_programa.tiempo_total = horno_programa.tiempo_coccion
									+ (horno_programa.temperatura_coccion - horno_programa.temperatura_secado)/0.8;
		horno_programa.tiempo_programa_inicio = horno_adc.valor_n;
		horno_programa.estado = ESPERAR_TCOCCION;
		DEBUGOUT("ESPERAR_TCOCCION\n");
		break;
	case ESPERAR_TCOCCION:
		/* segunda pendiente de temperatura.
		 * esperar hasta alcanzar la temp. de cocción */
		if (horno_adc.temperatura > (horno_programa.temperatura_coccion))
		{
			/* recalcular el tiempo restante */
			horno_programa.tiempo_total = horno_programa.tiempo_coccion;
			horno_programa.tiempo_programa_inicio = horno_adc.valor_n;

			horno_programa.estado = COCCION;
			horno_programa.tiempo_inicio = horno_adc.valor_n;
			DEBUGOUT("COCCION\n");
		}
		else
		{
			/* actualizamos la flecha */
			Horno_grafico_posicion_CLR_flecha(flecha_posicion);
			int paso_rampa = (horno_programa.temperatura_coccion - horno_programa.temperatura_secado)/8;
			flecha_posicion = (horno_adc.temperatura - horno_programa.temperatura_secado)/paso_rampa + 18;
			Horno_grafico_posicion_flecha(flecha_posicion);
		}
		break;
	case COCCION:
		/* esperar el tiempo programado */
		if (horno_programa.tiempo_coccion < (horno_adc.valor_n - horno_programa.tiempo_inicio))
		{
			horno_programa.estado = FIN_PROGRAMA;
			DEBUGOUT("FIN_PROGRAMA\n");
		} else {
			/* actualizamos la flecha */
			Horno_grafico_posicion_CLR_flecha(flecha_posicion);
			int pasos_flecha = horno_programa.tiempo_coccion/12;
			flecha_posicion = (horno_adc.valor_n - horno_programa.tiempo_programa_inicio)/pasos_flecha + 26;
			Horno_grafico_posicion_flecha(flecha_posicion);
		}
		break;
	case FIN_PROGRAMA:
		/* detenemos y abrimos la puerta */
		Horno_pwm_activar(false);
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
		/* limpiamos la pantalla */
		Horno_grafico_posicion_CLR_flecha(flecha_posicion);
		Horno_grafico_programa(false,
						horno_programa.pendiente_calentamiento,
						horno_programa.tiempo_secado,
						horno_programa.tiempo_coccion,
						horno_programa.temperatura_secado,
						horno_programa.temperatura_coccion
						);
		horno_programa.estado = HACER_NADA;
		DEBUGOUT("HACER_NADA\n");
		break;
	case HACER_NADA:
		/* habilitamos la carga de datos */
		horno_teclado_deshabilitar_carga_datos=false;
		break;
	}

	if (horno_programa.estado != HACER_NADA) {
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

	horno_programa.estado = INICIO;
	DEBUGOUT("INICIO\n");
}

/* @brief: 	Carga/actualiza los datos del programa
 * @param:	horno_ingreso_datos:	linea a la que ingresamos datos
 * 			dato:					valor a poner en las lineas de datos
 * 			estado:					true: funcionando el programa;
 * 									false: programa apagado
 */
void Horno_programa_carga_datos(HORNO_LINEA_T horno_ingreso_datos, uint32_t dato, bool habilitado){
	if(!habilitado){
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
	}


}
