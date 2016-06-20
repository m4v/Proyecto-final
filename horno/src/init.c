/*
 * init.c
 *
 *  Created on: 31/5/2016
 *      Author: m4v
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

/* Pin muxing configuration */
static const PINMUX_GRP_T pinmux[] = {
	/* pines para motor paso a paso */
	{2,   6,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   7,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   8,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,  10,  IOCON_MODE_INACT | IOCON_FUNC0},
	/* pines para control del motor */
	{2,  11,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,  12,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   5,  IOCON_MODE_INACT | IOCON_FUNC0},

};

/* Pin GPIO configuration */
static const GPIO_DIR_T gpiodir[] = {
	/* pines del motor como salidas */
	{2,  6, true},
	{2,  7, true},
	{2,  8, true},
	{2, 10, true},
	/* pines de control del motor como entradas */
	{2,  11, false},
	{2,  12, false},
	{2,  5, false},
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
}

