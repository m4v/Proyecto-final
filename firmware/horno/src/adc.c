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
float a4=16.09, b4=-3.429325;								//coeficientes de lm35, a4.x+b

/*
 * @brief Elige polinomio de linealizacion correspondiente para el calculo de temperatura de termocupla
 */
void horno_th_line(void){
	if (horno_adc.th_valor<TH_SEG1){
		Horno_th_lineseg1();
	}else if (horno_adc.th_valor>TH_SEG1 && horno_adc.th_valor<TH_SEG2){
		Horno_th_lineseg2();
	}else if(horno_adc.th_valor>TH_SEG3 && horno_adc.th_valor<TH_SEG3){
		Horno_th_lineseg3();
	}
}

/*
 * @brief Resuelven linealizaciones y obtiene valor de temperatura de termocupla en gr C
 */
void Horno_th_lineseg1(void){
		float temp=horno_adc.th_valor_mv;
		horno_adc.temperatura= a1*temp*temp*temp + b1*temp*temp + c1*temp + d1;
				}
void Horno_th_lineseg2(void){
		float temp=horno_adc.th_valor_mv;
		horno_adc.th_temperatura= a2*temp*temp*temp + b2*temp*temp + c2*temp + d2;
}
void Horno_th_lineseg3(void){
		float temp=horno_adc.th_valor_mv;
		horno_adc.th_temperatura= a3*temp*temp + b3*temp + c3;
}

/*
 * @brief Pasa valores de niveles de ADC a tension en mv
 */
void Horno_th_adctomv(void){
		horno_adc.th_valor_mv= horno_adc.th_valor*ADC_REF/(ADC_SIZE*TH_GAIN);
}

/*
 * @brief Calcula valor de temperatura en C segun valores del ADC
 */
void Horno_lm_line(void){
		horno_adc.lm_valor_v=horno_adc.lm_valor*ADC_REF/(ADC_SIZE*LM_GAIN);
		horno_adc.lm_temperatura=a4*horno_adc.lm_valor_v+b4;
}


/* rutina de interrupción del systick */
void SysTick_Handler(void)
{
	if (adc_enabled) {
		if (!adc_continue) {
			if (horno_adc.valor_n > NUM_MUESTRAS_CAPTURA) {
				adc_enabled = false;
				Board_LED_Set(0, false);
			}
			Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
			if(Chip_ADC_ReadStatus(LPC_ADC, ADC_CHANNEL, ADC_DR_DONE_STAT) == SET) {
				Chip_ADC_ReadValue(LPC_ADC, ADC_CHANNEL, &muestras[horno_adc.valor_n++]);
			}
		} else {
			/* captura continua */
			if(Chip_ADC_ReadStatus(LPC_ADC, ADC_LM35, ADC_DR_DONE_STAT) == SET) {
				uint16_t muestra;
				Chip_ADC_ReadValue(LPC_ADC, ADC_TH, &muestra);
				horno_adc.th_suma += muestra;
				horno_adc.th_cantidad++;
				Chip_ADC_ReadValue(LPC_ADC, ADC_LM35, &muestra);
				horno_adc.lm_suma += muestra;
				horno_adc.lm_cantidad++;
				if (horno_adc.lm_cantidad >= NUM_MUESTRAS_ADC) {
					Board_LED_Toggle(0);
					horno_adc.th_valor = horno_adc.th_suma / horno_adc.th_cantidad;
					horno_adc.lm_valor = horno_adc.lm_suma / horno_adc.lm_cantidad;
					DEBUGOUT("%10d, %4d, %4d\r\n", horno_adc.valor_n,
							                       horno_adc.th_valor,
							                       horno_adc.lm_valor);
					horno_adc.th_suma = 0;
					horno_adc.th_cantidad = 0;
					horno_adc.lm_suma = 0;
					horno_adc.lm_cantidad = 0;
					horno_adc.valor_n++;
				}
			}
		}
	}
}



