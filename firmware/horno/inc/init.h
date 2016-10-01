/*
 * init.h
 *
 *  Created on: 31/5/2016
 *      Author: Elián Hanisch, Gastón Riera y Rodrigo Oliver
 */

#ifndef INIT_H_
#define INIT_H_

typedef struct {
	uint32_t pingrp:3;
	uint32_t pinnum:5;
	uint32_t output:1;
} GPIO_DIR_T;

typedef struct {
	uint32_t puerto:3;
	uint32_t pin:5;
} PUERTO_T;

#define ADC_TH   ADC_CH0     // ADC termocupla
#define ADC_LM35 ADC_CH6     // ADC LM35
#define PERIODO_MUESTREO 100 // muestreo del ADC en ms

void Horno_Init (void);

#endif /* INIT_H_ */
