/*
 * delay.h
 *
 *  Created on: 27 de ago. de 2016
 *      Author: m4v
 */

#ifndef ADC_H
#define ADC_H

#include "board.h"

#define NUM_MUESTRAS_ADC (1000*PERIODO_PROMEDIO/PERIODO_MUESTREO)

typedef struct {
	bool     salida_uart;       // si imprime los datos del AD al UART
	uint32_t th_suma;			// suma accumulada del valor del AD (para hacer el promedio)
	uint16_t th_valor;          // valor del AD promediado
	uint32_t lm_suma;			// lo mismo para lm
	uint16_t lm_valor;
	uint32_t suma_cantidad;     // cantidad de valores sumados
	uint32_t valor_n;           // número del último valor obtenido
	float    th_temperatura;	// valor de temperatura de termocupla actual en gr C
	float 	 lm_temperatura;
	float 	 temperatura;		// valor de temperatura actual en gr C
} HORNO_PROMEDIO_T;

HORNO_PROMEDIO_T horno_adc;

void Horno_adc_muestreo(void);
void Horno_adc_init(void);

#endif /* ADC_H_ */
