/*
 * control.c
 *
 *  Created on: 23 de oct. de 2016
 *      Author: Nico
 */

/* valores del PI */
#define KP 5.23			// constante proporcional
#define KI 9.9e-5		// constante integrador
#define TS 0.1			// periodo de muestreo

#include "control.h"
#include "adc.h"
#include "pwm.h"



/*
 * @brief se define PI discreto
 *
 * PI= Kp + Ki * Ts
 */
void Horno_PI(void){
	horno_pi.Kp= KP;
	horno_pi.Ki= KI*TS;
}

/*
 * @brief Lazo de control PI
 */
void Horno_control_pi(void){
	horno_control.Err= horno_control.temp_set - horno_adc.temperatura ; // calculo de error
	horno_control.PI_K= horno_pi.Kp*horno_control.Err;				// calculo de termino proporcional
	horno_control.PI_I= horno_pi.Ki*horno_control.Err;				// calculo de termino integrador
	horno_control.PI_Out= horno_control.PI_K + horno_control.PI_I;	// calculo de salida de PI
}
/*
 * @brief Lazo de control P
 */
void Horno_control_p(void){
	horno_control.Err= horno_control.temp_set - horno_adc.temperatura; // calculo de error
	horno_control.PI_Out= horno_pi.Kp*horno_control.Err;			   // calculo de termino proporcional
}


