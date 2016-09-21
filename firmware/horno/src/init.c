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

static ADC_CLOCK_SETUP_T ADCSetup;

/* Pin muxing configuration */
static const PINMUX_GRP_T pinmux[] = {
	/* pines para motor paso a paso */
	{0,   6,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,   7,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,   8,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,   9,  IOCON_MODE_INACT | IOCON_FUNC0},
	/* pines P0.0 y P0.1 reservados para la comunicación UART */
	{0,   0,  IOCON_FUNC2},
	{0,   1,  IOCON_FUNC2},
	/* pines para control del motor */
	{0,  18,  IOCON_MODE_INACT | IOCON_FUNC0},
	/* pin del ADC */
	{0,  23,  IOCON_MODE_INACT | IOCON_FUNC1},
	/* pines del display */
	{0,   4,  IOCON_MODE_INACT | IOCON_FUNC0}, // /CS
	{0,   5,  IOCON_MODE_INACT | IOCON_FUNC0}, // A0
	{0,  10,  IOCON_MODE_INACT | IOCON_FUNC0}, // /RD
	{0,  11,  IOCON_MODE_INACT | IOCON_FUNC0}, // /WR
	{2,  12,  IOCON_MODE_INACT | IOCON_FUNC0}, // /RES
	/* D[0-7] display */
	{2,   0,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   1,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   2,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   3,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   4,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   5,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   6,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   7,  IOCON_MODE_INACT | IOCON_FUNC0},
};

/* Pin GPIO configuration */
static const GPIO_DIR_T gpiodir[] = {
	//  Los pines del motor los mudé al costado izquierdo. Y todos consecutivos
	/* pines del motor como salidas */
	{0,  6, true},
	{0,  7, true},
	{0,  8, true},
	{0,  9, true},
	/* pines de control del motor como entradas */
	{0,  0, false},
	{0,  1, false},
	{0,  18,  false},
	/* pines de datos display como salida*/
	{0,  4, true}, // /CS
	{0,  5, true}, // A0
	{0,  10, true}, // /RD
	{0,  11, true}, // /WR
	{2,  12, true}, // /RES
	/* D[0-7] display */
	{2,  0, true},
	{2,  1, true},
	{2,  2, true},
	{2,  3, true},
	{2,  4, true},
	{2,  5, true},
	{2,  6, true},
	{2,  7, true},
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

/*
 * Función de inicialización del horno.
 * Se llama al principio del main
 */
void Horno_Init (void) {
	Chip_IOCON_SetPinMuxing(LPC_IOCON, pinmux, sizeof(pinmux) / sizeof(PINMUX_GRP_T));

	GPIO_SetDirections(gpiodir, sizeof(gpiodir) / sizeof(GPIO_DIR_T));

	/* Habilitar el timer para hacer retrasos */
	Horno_delay_timer_Init();

	Horno_Display_Init();

	/* ADC Init */
	Chip_ADC_Init(LPC_ADC, &ADCSetup);
	Chip_ADC_EnableChannel(LPC_ADC, ADC_CHANNEL, ENABLE);
	/* Enable ADC Interrupt */
	Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CHANNEL, ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);

	uint8_t div = 0xFF;
	uint32_t cr = LPC_ADC->CR & (~ADC_SAMPLE_RATE_CONFIG_MASK);
	cr |= ADC_CR_CLKDIV(div);
	LPC_ADC->CR = cr;
}

