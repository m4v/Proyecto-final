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



#define ADC_CHANNEL ADC_TH  // canal de captura del comando 'm'
#define NUM_MUESTRAS_CAPTURA 100
#define NUM_MUESTRAS_ADC 1000*PERIODO_PROMEDIO/PERIODO_MUESTREO
bool adc_enabled = false;
bool adc_continue = false;
uint16_t muestras[NUM_MUESTRAS_CAPTURA];


typedef struct {
	uint32_t th_suma;			// suma accumulada del valor del AD (para hacer el promedio)
	uint32_t th_cantidad;       // cantidad de valores sumados
	uint16_t th_valor;          // valor del AD promediado
	uint32_t lm_suma;			// lo mismo para lm
	uint32_t lm_cantidad;
	uint16_t lm_valor;
	uint32_t valor_n;           // número del último valor obtenido
	float    th_valor_mv;		// valor del temperatura de termocupla actual en mv
	float    th_temperatura;		// valor de temperatura de termocupla actual en gr C
	float    lm_valor_v;		// mismo para lm
	float 	 lm_temperatura;
	float 	 temperatura;			// valor de temperatura actual en gr C
} HORNO_PROMEDIO_T;

HORNO_PROMEDIO_T horno_adc;

void Horno_th_lineseg1(void);
void Horno_th_lineseg2(void);
void Horno_th_lineseg3(void);
void Horno_th_adctomv(void);
void Horno_lm_line(void);


#endif /* ADC_H_ */
