/*
 * delay.h
 *
 *  Created on: 27 de ago. de 2016
 *      Author: m4v
 */

#ifndef ADC_H
#define ADC_H

#include "board.h"
#include "init.h"

#define NUM_MUESTRAS_ADC 1000*PERIODO_PROMEDIO/PERIODO_MUESTREO

typedef struct {
	bool     salida_uart;       // si imprime los datos del AD al UART
	uint32_t th_suma;			// suma accumulada del valor del AD (para hacer el promedio)
	uint32_t th_cantidad;       // cantidad de valores sumados
	uint16_t th_valor;          // valor del AD promediado
	uint32_t lm_suma;			// lo mismo para lm
	uint32_t lm_cantidad;
	uint16_t lm_valor;
	uint32_t valor_n;           // número del último valor obtenido
	float    th_temperatura;	// valor de temperatura de termocupla actual en gr C
	float 	 lm_temperatura;
	float 	 temperatura;		// valor de temperatura actual en gr C
} HORNO_PROMEDIO_T;

HORNO_PROMEDIO_T horno_adc;

void Horno_adc_muestreo(void);

#endif /* ADC_H_ */
