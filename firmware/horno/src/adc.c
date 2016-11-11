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

#include "init.h"
#include "adc.h"
#include "pwm.h"
#include "grafico.h"
#include "control.h"
#include "programa.h"

#define ADC_SIZE 4096		//tamaño del ADC
#define ADC_REF  3.3		//tension de referencia de ADC
#define TH_GAIN  80.7 		//ganancia de la etapa de termocupla
#define LM_GAIN  6.65		//ganancia de la etapa de lm
#define TH_SEG1  1228		//limite del primer segmento de linealizacion de termocupla(0-300°C), expresado en niveles de ADC
#define TH_SEG2  2869		//limite del segundo segmento (300-700°C)
#define TH_SEG3  4096		//limite del tercero (700-1000°C)

#define K_LM ADC_REF/ADC_SIZE // factor de escala del ADC del LM35
#define K_TH ADC_REF/(ADC_SIZE*TH_GAIN*1e-3) // factor de escala del ADC de la termocupla

static const float a1=-0.007245, b1= 0.15911,  c1=23.6212,  d1=  1.0999;   // coeficientes de polinomios de linealizacion
static const float a2= 0.00252,  b2=-0.164398, c2=27.02517, d2=-10.04204;  // a.x^3+b.x^2+c.x+d
static const float a3= 0.078896, b3=19.13545,  c3=75.8309;				   // a.x^2+b.x+d
static const float a4=16.09,     b4=-3.429325;							   // coeficientes de lm35, a4.x+b

static ADC_CLOCK_SETUP_T ADCSetup;

/*
 * @brief Linealizacion para el calculo de temperatura de termocupla
 */
float th_line(float valor) {
	float tension = valor*K_TH;
	if (valor < TH_SEG1) {
		return a1*tension*tension*tension + b1*tension*tension + c1*tension + d1;
	} else if (valor < TH_SEG2) {
		return a2*tension*tension*tension + b2*tension*tension + c2*tension + d2;
	} else {
		return a3*tension*tension + b3*tension + c3;
	}
}

/*
 * @brief Calcula valor de temperatura en C segun valores del ADC
 */
float lm_line(float valor) {
	float tension = valor*K_LM;
	return a4*tension + b4;
}

/*
 * @brief Esta función se ejecuta cada vez que se obtiene una nueva muestra de
 *        temperatura, y aquí se procesa.
 * @param temperatura: Temperatura en grados celsius
 */
void Horno_adc_muestra_Handler(float temperatura) {

	/* actualizar la pantalla */
	Horno_grafico_temperatura((uint32_t)temperatura);
	/* actualizar la máquina de estados */
	Horno_programa_actualizar();

	if (horno_pwm.activo) {
		Horno_control_pi(temperatura);
	}
}

/*
 * @brief Función que muestrea, promedia y calcula la temperatura desde ADC.
 *        Esta función es llamada en cada interrupción del SYSTICK.
 */
void Horno_adc_muestreo(void)
{
	if(Chip_ADC_ReadStatus(LPC_ADC, ADC_LM35, ADC_DR_DONE_STAT) == SET) {
		uint16_t muestra;
		Chip_ADC_ReadValue(LPC_ADC, ADC_TH, &muestra);
		horno_adc.th_suma += muestra;
		Chip_ADC_ReadValue(LPC_ADC, ADC_LM35, &muestra);
		horno_adc.lm_suma += muestra;
		horno_adc.suma_cantidad++;
		if (horno_adc.suma_cantidad >= NUM_MUESTRAS_ADC) {
			/* hacemos el promedio */
			horno_adc.th_valor = horno_adc.th_suma / horno_adc.suma_cantidad;
			horno_adc.lm_valor = horno_adc.lm_suma / horno_adc.suma_cantidad;

			/* linealizamos */
			horno_adc.lm_temperatura = lm_line((float)horno_adc.lm_valor);
			horno_adc.th_temperatura = th_line((float)horno_adc.th_valor);
			horno_adc.temperatura = horno_adc.lm_temperatura + horno_adc.th_temperatura;

			/* utilizamos la muestra */
			Horno_adc_muestra_Handler(horno_adc.temperatura);

			if (horno_adc.salida_uart) {
				DEBUGOUT("%d, %.2f, %.2f, %.2f, %d, %d, %.4f, %.2f, %.2f, %.2f, %.2f\r\n",
						horno_adc.valor_n,
						horno_adc.temperatura,
						horno_adc.th_temperatura,
						horno_adc.lm_temperatura,
						horno_adc.th_valor,
						horno_adc.lm_valor,
						horno_pwm.activo ? horno_pwm.dc : 0,
						horno_control.referencia,
						horno_control.referencia_cond,
						horno_control.entrada,
						horno_control.salida);
			}
			horno_adc.th_suma = 0;
			horno_adc.lm_suma = 0;
			horno_adc.suma_cantidad = 0;
			horno_adc.valor_n++;
		}
	}
}


/*
 * Iniciación del ADC
 */
void Horno_adc_init(void) {
	Chip_ADC_Init(LPC_ADC, &ADCSetup);
	Chip_ADC_EnableChannel(LPC_ADC, ADC_TH, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC, ADC_LM35, ENABLE);
	Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE); // habilitar conversión continua
}



