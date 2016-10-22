/*
 * adc.c
 *
 *  Created on: 9 de ago. de 2016
 *      Author: Gastón Riera, Elián Hanisch y Rodrigo Oliver
 */

#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif

#include "adc.h"

#define ADC_SIZE 4096		//tamaño del ADC
#define ADC_REF  3.3		//tension de referencia de ADC
#define TH_GAIN  80.2 		//ganancia de la etapa de termocupla
#define LM_GAIN  6.65		//ganancia de la etapa de lm
#define TH_SEG1  1228		//limite del primer segmento de linealizacion de termocupla(0-300°C), expresado en niveles de ADC
#define TH_SEG2  2869		//limite del segundo segmento (300-700°C)
#define TH_SEG3  4096		//limite del tercero (700-1000°C)

float a1=-0.007245, b1=0.15911, c1=23.6212, d1=1.0999; 		//coeficientes de polinomios de linealizacion
float a2=0.00252, b2=-0.164398, c2=27.02517, d2=-10.04204;	// a.x^3+b.x^2+c.x+d
float a3=0.078896, b3=19.13545, c3=75.8309;					// a.x^2+b.x+d
float a4=16.09, b4=-3.429325;	//coeficientes de lm35, a4.x+b


void horno_th_line(void){
	if (horno_adc.th_valor<1229){
		horno_th_lineseg1();
	}else if (horno_adc.th_valor>TH_SEG1 && horno_adc.th_valor<TH_SEG2){
		horno_th_lineseg2();
	}else if(horno_adc.th_valor>TH_SEG3 && horno_adc.th_valor<TH_SEG3){
		horno_th_lineseg3();
	}
}

void Horno_th_lineseg1(void){
		float temp=horno_adc.th_valor_mv;
		horno_adc.th_valor_c= a1*temp*temp*temp + b1*temp*temp + c1*temp + d1;
				}
void Horno_th_lineseg2(void){
		float temp=horno_adc.th_valor_mv;
		horno_adc.th_valor_c= a2*temp*temp*temp + b2*temp*temp + c2*temp + d2;
}
void Horno_th_lineseg3(void){
		float temp=horno_adc.th_valor_mv;
		horno_adc.th_valor_c= a3*temp*temp + b3*temp + c3;
}

void Horno_th_adctomv(void){
		horno_adc.th_valor_mv= horno_adc.th_valor*ADC_REF/(ADC_SIZE*TH_GAIN);
}

void Horno_lm_line(void){
		horno_adc.lm_valor_v=horno_adc.lm_valor*ADC_REF/(ADC_SIZE*LM_GAIN);
		horno_adc.lm_valor_c=a4*horno_adc.lm_valor_v+b4;
}

