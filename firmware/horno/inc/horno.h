/*
 * horno.h
 *
 *  Created on: 31/5/2016
 *      Author: Elián Hanisch, Gastón Riera y Rodrigo Oliver
 */

#ifndef HORNO_H_
#define HORNO_H_

typedef struct {
	uint32_t pingrp:3;
	uint32_t pinnum:5;
	uint32_t output:1;
} GPIO_DIR_T;

#define ADC_TH   ADC_CH0     // ADC termocupla
#define ADC_LM35 ADC_CH6     // ADC LM35
#define PERIODO_MUESTREO 100 // muestreo del ADC en ms
#define PERIODO_PROMEDIO 1   // muestreo total en seg (tiempo promediando)
#define PWM_PERIODO 1800     // periodo del PWM en ms

void Horno_muestra_Handler(float temperatura);

#endif /* HORNO_H_ */
