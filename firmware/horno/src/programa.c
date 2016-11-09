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

void Horno_programa_actualizar(void)
{
	switch(horno_estado) {
	case INICIO:
		/* activar todo y empezar a calentar */
		Horno_control_referencia(horno_programa.temperatura_secado);
		Horno_control_activar(true);
		Horno_pwm_inicio();
		horno_estado = ESPERAR_TSECADO;
		DEBUGOUT("ESPERAR_TSECADO\n");
		break;
	case ESPERAR_TSECADO:
		/* pendiente inicial de temperatura.
		 * esperar hasta alcanzar la temperatura de secado */
		if (horno_adc.temperatura > (horno_programa.temperatura_secado - 10)) {
			horno_programa.tiempo_inicio = horno_adc.valor_n;
			horno_estado = SECADO;
			DEBUGOUT("SECADO\n");
		}
		break;
	case SECADO:
		/* esperar el tiempo programado */
		if (horno_programa.tiempo_secado < (horno_adc.valor_n - horno_programa.tiempo_inicio)) {
			Horno_motor_ascender(true);
			Horno_motor_marcha(3000);
			horno_estado = ESPERAR_CIERRE;
			DEBUGOUT("ESPERAR_CIERRE\n");
		}
		break;
	case ESPERAR_CIERRE:
		/* esperar a que se cierre el horno */
		if (!horno_motor.activo) {
			/* llegó al fin de carrera */
			horno_estado = CALENTAMIENTO;
			DEBUGOUT("CALENTAMIENTO\n");
		}
		break;
	case CALENTAMIENTO:
		/* configurar la nueva temperatura */
		Horno_control_referencia(horno_programa.temperatura_coccion);
		horno_estado = ESPERAR_TCOCCION;
		DEBUGOUT("ESPERAR_TCOCCION\n");
		break;
	case ESPERAR_TCOCCION:
		/* segunda pendiente de temperatura.
		 * esperar hasta alcanzar la temp. de cocción */
		if (horno_adc.temperatura > (horno_programa.temperatura_coccion - 10)) {
			horno_estado = COCCION;
			horno_programa.tiempo_inicio = horno_adc.valor_n;
			DEBUGOUT("COCCION\n");
		}
		break;
	case COCCION:
		/* esperar el tiempo programado */
		if (horno_programa.tiempo_coccion < (horno_adc.valor_n - horno_programa.tiempo_inicio)) {
			horno_estado = FIN_PROGRAMA;
			DEBUGOUT("FIN_PROGRAMA\n");
		}
		break;
	case FIN_PROGRAMA:
		/* detenemos todo y abrimos la puerta */
		Horno_pwm_parar();
		Horno_control_activar(false);
		Horno_motor_ascender(false);
		Horno_motor_marcha(3000);
		horno_estado = HACER_NADA;
		DEBUGOUT("HACER_NADA\n");
		break;
	case HACER_NADA:
		break;
	}
}

void Horno_programa_inicio(void) {
	horno_programa.temperatura_coccion = 800;
	horno_programa.temperatura_secado = 200;
	horno_programa.tiempo_secado = 500;
	horno_programa.tiempo_coccion = 500;
	horno_programa.pendiente_calentamiento = 0.8;

	horno_estado = INICIO;
	DEBUGOUT("INICIO\n");
}
