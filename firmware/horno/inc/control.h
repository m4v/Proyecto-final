/*
 * control.h
 *
 *  Created on: 23 de oct. de 2016
 *      Author: Nico
 */

#ifndef CONTROL_H_
#define CONTROL_H_


typedef struct{
	float Err;
	float PI_I;
	float PI_K;
	float temp_set;
	float PI_Out;
} HORNO_CONTROL;

static HORNO_CONTROL horno_control;

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
