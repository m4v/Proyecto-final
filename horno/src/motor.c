/*
 * motor.c
 *
 *  Created on: 31/5/2016
 *      Author: m4v
 *
 *  Funciones para controlar el motor paso a paso.
 *
 */

#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif

#include "motor.h"


void Horno_MotorPaso(uint32_t pasos) {
	switch(pasos % 4) {
	case 0:
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 6, true);
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 7, false);
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 8, false);
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 10, false);
		break;
	case 1:
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 6, false);
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 7, true);
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 8, false);
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 10, false);
		break;
	case 2:
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 6, false);
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 7, false);
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 8, true);
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 10, false);
		break;
	case 3:
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 6, false);
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 7, false);
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 8, false);
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 10, true);
		break;
	}
}

void Horno_MotorApagar(void){
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 6, false);
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 7, false);
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 8, false);
	Chip_GPIO_SetPinState(LPC_GPIO, 2, 10, false);
}
