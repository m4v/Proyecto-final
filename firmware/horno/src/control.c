/*
 * control.c
 *
 *  Created on: 23 de oct. de 2016
 *      Author: Nico
 */


#define KP 5.23
#define TAO 10098
#define TS 0.1

#include "control.h"
#include "adc.h"
#include "pwm.h"



/*
 * @brief se calcula el PI
 */
void Horno_PI(void){
	horno_pi.K= KP*TS;
	horno_pi.Ti= 3.3*TAO;
	horno_pi.I= TS/horno_pi.Ti;
}

/*
 * @brief Lazo de control PI
 */
void Horno_control_pi(void){
	horno_control.Err= horno_control.temp_set - horno_adc.valor_c ; // calculo de error
	horno_control.PI_K= horno_pi.K*horno_control.Err;				// calculo de termino proporcional
	horno_control.PI_I= horno_pi.I*horno_control.Err;				// calculo de termino integrador
	horno_control.PI_Out= horno_control.PI_K + horno_control.PI_I;	// calculo de salida de PI
}
/*
 * @brief Lazo de control P
 */
void Horno_control_p(void){
	horno_control.Err= horno_control.temp_set - horno_adc.valor_c; // calculo de error
	horno_control.PI_Out= horno_pi.K*horno_control.Err;			   // calculo de termino proporcional
}


