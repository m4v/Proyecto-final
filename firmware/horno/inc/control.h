/*
 * control.h
 *
 *  Created on: 23 de oct. de 2016
 *      Author: Nico
 */

#ifndef CONTROL_H_
#define CONTROL_H_

/* estructura con valores del lazo de control*/
typedef struct{
	float Err;			// valor de error (ref - out)
	float PI_I;			// valor de termino integrador
	float PI_K;			// valor de termino proporcional
	float temp_set;		// valor de temperatura de referencia (entrada al lazo de control)
	float PI_Out;		// valor de control -  esto es lo que traducir en ciclos de pwm
} HORNO_CONTROL;

static HORNO_CONTROL horno_control;

/* estructura con valores de PI discreto */
typedef struct{
	float K;
	float Ti;
	float I;
} HORNO_PI;

static HORNO_PI horno_pi;


void Horno_PI(void);
void Horno_control_pi(void);
void Horno_control_p(void);

#endif /* CONTROL_H_ */