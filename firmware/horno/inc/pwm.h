/*
 * pwm.h
 *
 *  Created on: 21 de oct. de 2016
 *      Author: m4v
 */

#ifndef PWM_H_
#define PWM_H_

typedef struct {
	bool activo;
	uint32_t periodo;
	float dc;
} HORNO_PWM_T;

void Horno_pwm_init(void);
void Horno_pwm_periodo(uint32_t ms);
void Horno_pwm_ciclo(float dc);
void Horno_pwm_inicio(void);
void Horno_pwm_parar(void);

HORNO_PWM_T horno_pwm;

#endif /* PWM_H_ */
