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

#define PERIODO_MUESTREO 100 // muestreo del ADC en ms

/* PERIODO_PROMEDIO se puede cambiar, pero muchas partes del programa
 * aprovecha que se obtiene una muestra por segundo para medir el tiempo,
 * sobretodo para la ejecución del programa.
 */
#define PERIODO_PROMEDIO 1   // muestreo total en seg (tiempo promediando)
#define PWM_PERIODO 1800     // periodo del PWM en ms

void Horno_muestra_Handler(float temperatura);

#endif /* HORNO_H_ */
