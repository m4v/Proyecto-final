/*
 * init.c
 *
 *  Created on: 31/5/2016
 *      Author: Elián Hanisch, Gastón Riera y Rodrigo Oliver
 *
 *  Funciones de inicialización del programa del horno
 *
 */

#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif

#include "init.h"
#include "delay.h"
#include "320240.h"
#include "motor.h"
#include "pwm.h"
#include "adc.h"
#include "teclado.h"

static ADC_CLOCK_SETUP_T ADCSetup;

/*
 * Pin muxing configuration
 * IOCON_MODE_INACT deshabilita las resistencias de pull-up/pull-down
 */
static const PINMUX_GRP_T pinmux[] = {
	/* pines para motor paso a paso */
	{0,  30,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,   4,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,   5,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,  29,  IOCON_MODE_INACT | IOCON_FUNC0},
	/* pines P0.0 y P0.1 reservados para la comunicación UART */
	{0,   0,  IOCON_MODE_INACT | IOCON_FUNC2},
	{0,   1,  IOCON_MODE_INACT | IOCON_FUNC2},
	/* pines del ADC */
	{0,  23,  IOCON_MODE_INACT | IOCON_FUNC1}, // Termocupla
	{0,   3,  IOCON_MODE_INACT | IOCON_FUNC2}, // LM35
	/* PWM
	 * Lo utilizamos como GPIO con R de pull-down, desde pwm.c se cambia a IOCON_FUNC1
	 * cuando es necesario. */
	{2,   0,  IOCON_MODE_PULLDOWN | IOCON_FUNC0},
	/* pines del display */
	{2,  11,  IOCON_MODE_INACT | IOCON_FUNC0}, // /CS
	{2,   1,  IOCON_MODE_INACT | IOCON_FUNC0}, // A0
	{0,  10,  IOCON_MODE_INACT | IOCON_FUNC0}, // /RD
	{0,  11,  IOCON_MODE_INACT | IOCON_FUNC0}, // /WR
	{2,  12,  IOCON_MODE_INACT | IOCON_FUNC0}, // /RES
	/* D[0-7] display */
	{2,   2,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   3,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   4,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   5,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   6,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   7,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   8,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,  10,  IOCON_MODE_INACT | IOCON_FUNC0},
	/*Pines del teclado */
	/* filas */
	{0,  9,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,  8,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,  7,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,  6,  IOCON_MODE_INACT | IOCON_FUNC0},
	/* columnas, entradas con R de pull-down para reducir el ruido cuando
	 * estan en alta impedancia.
	 * ATENCION pines P0.27 a P0.30 no admiten R de pull-up/down.
	 * tabla 89 del manual de usuario del LPC1769 */
	{0,   2,  IOCON_MODE_PULLDOWN | IOCON_FUNC0},
	{0,  21,  IOCON_MODE_PULLDOWN | IOCON_FUNC0},
	{0,  24,  IOCON_MODE_PULLDOWN | IOCON_FUNC0},
	{0,  25,  IOCON_MODE_PULLDOWN | IOCON_FUNC0},

	/* LED */
	{0,  22,  IOCON_MODE_INACT | IOCON_FUNC0},
};

/* Pin GPIO configuration */
static const GPIO_DIR_T gpiodir[] = {
	/* pines del motor como salidas */
	{0, 30, true},
	{0,  4, true},
	{0,  5, true},
	{0, 29, true},
	/* pines de datos display como salida*/
	{2, 11, true}, // /CS
	{2,  1, true}, // A0
	{0, 10, true}, // /RD
	{0, 11, true}, // /WR
	{2, 12, true}, // /RES
	/* D[0-7] display */
	{2,  2, true},
	{2,  3, true},
	{2,  4, true},
	{2,  5, true},
	{2,  6, true},
	{2,  7, true},
	{2,  8, true},
	{2, 10, true},
	/*Pines del teclado */
	/* filas */
	{0,  9, true},
	{0,  8, true},
	{0,  7, true},
	{0,  6, true},
	/* columnas como entradas */
	{0,  2, false},
	{0, 21, false},
	{0, 24, false},
	{0, 25, false},
	/* LED */
	{0, 22, true},
};

/*
 * Inicializa las direcciones del GPIO
 */
void GPIO_SetDirections(const GPIO_DIR_T *pinArray, uint32_t arrayLength)
{
	uint32_t ix;

	for (ix = 0; ix < arrayLength; ix++ ) {
		Chip_GPIO_SetPinDIR(LPC_GPIO, pinArray[ix].pingrp, pinArray[ix].pinnum, pinArray[ix].output);
	}
}

void Horno_systick_init(uint32_t ms)
{
	/*
	 * SystemCoreClock es 96Mhz
	 * SysTick_Config usa el argumento para cargar un contador decreciente
	 * que cuando llega a cero genera una interrupción.
	 */
	uint32_t ticks = SystemCoreClock / 1000;
	ticks *= ms;
	/* el contador es de 24 bits, no deberíamos superar ese valor */
	if (0xFFFFFF < ticks) {
		ticks = 0xFFFFFF;
	}
	SysTick_Config(ticks);
}

void SysTick_Handler(void) {
	Horno_adc_muestreo ();
}

/*
 * Función de inicialización del horno.
 * Se llama al principio del main
 */
void Horno_Init (void) {
	/* configurar puertos */
	Chip_IOCON_SetPinMuxing(LPC_IOCON, pinmux, sizeof(pinmux) / sizeof(PINMUX_GRP_T));
	GPIO_SetDirections(gpiodir, sizeof(gpiodir) / sizeof(GPIO_DIR_T));

	/* Habilitar el timer para hacer retrasos */
	Horno_delay_timer_Init();

	Horno_Display_Init();

	/* ADC Init */
	Chip_ADC_Init(LPC_ADC, &ADCSetup);
	Chip_ADC_EnableChannel(LPC_ADC, ADC_TH, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC, ADC_LM35, ENABLE);
	Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE); // habilitar conversión continua

	/*
	 * Las interrupciones del SysTick son para muestrear con el ADC.
	 */
	Horno_systick_init(PERIODO_MUESTREO);

	Horno_teclado_init();
	Horno_motor_init();
	Horno_pwm_init();
}

