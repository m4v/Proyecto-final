/*
 * control.c
 *
 *  Created on: 23 de oct. de 2016
 *      Author: Nico
 */

#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif

#include "control.h"
#include "pwm.h"
#include "init.h"

/* valores del PI */
#define KP 5.23			    // constante proporcional
#define KI 9.9e-5		    // constante integrador
#define TS PERIODO_PROMEDIO // periodo de muestreo (segundos)

/* constantes del PI discreto, usando la transformación bilineal */
static const float kx = KI*TS*0.5 + KP, kx1 = KI*TS*0.5 - KP;

/*
 * @brief Lazo de control PI
 */
void Horno_control_pi(float entrada) {
	if (!horno_control.activo) {
		return;
	}
	horno_control.entrada = horno_control.referencia - entrada;
	horno_control.salida = horno_control.entrada * kx
						   + horno_control.entrada_1 * kx1
			               + horno_control.salida_1;

	/* Actualizamos el PWM
	 * Dado nuestro modelo de la planta, la salida es en tensión.
	 * Escalamos para que 220V sean 100% del ciclo de trabajo del PWM */
	Horno_pwm_ciclo(horno_control.salida / 220);

	/* actualizamos las muestras anteriores */
	horno_control.entrada_1 = horno_control.entrada;
	horno_control.salida_1 = horno_control.salida;
}

void Horno_control_referencia(float ref)
{
	horno_control.referencia = ref;
}

/*
 * Inicialización de las variables del PI
 */
void Horno_control_activar(bool activar)
{
	if (activar) {
		/* reiniciamos las variables a cero */
		horno_control.entrada = 0;
		horno_control.entrada_1 = 0;
		horno_control.salida = 0;
		horno_control.salida_1 = 0;
	}
	horno_control.activo = activar;
}
