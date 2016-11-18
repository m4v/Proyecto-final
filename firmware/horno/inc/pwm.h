/*
 * pwm.h
 *
 *  Created on: 21 de oct. de 2016
 *      Author: m4v
 */

#ifndef PWM_H_
#define PWM_H_

typedef struct {
	bool activo;         // si el PWM está activo
	uint32_t periodo;    // periodo del PWM en ms
	float dc;            // ciclo de trabajo (de 0.0 a 1.0)
} HORNO_PWM_T;

void Horno_pwm_init(void);
void Horno_pwm_periodo(uint32_t ms);
void Horno_pwm_ciclo(float dc);
void Horno_pwm_activar(bool estado);

HORNO_PWM_T horno_pwm;

#endif /* PWM_H_ */
