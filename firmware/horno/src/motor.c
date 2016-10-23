/*
 * motor.c
 *
 *  Created on: 31/5/2016
 *      Author: Elián Hanisch, Gastón Riera y Rodrigo Oliver
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

/* usar el TIMER1 para hacer los retrasos */
#define _LPC_TIMER         LPC_TIMER1
#define _TIMER_IRQn        TIMER1_IRQn
#define _SYSCTL_PCLK_TIMER SYSCTL_PCLK_TIMER1

#define PASOS 200 // pasos por vuelta

#define MOTOR_P0(estado) Chip_GPIO_SetPinState(LPC_GPIO, 0, 30, estado);
#define MOTOR_P1(estado) Chip_GPIO_SetPinState(LPC_GPIO, 0,  4, estado);
#define MOTOR_P2(estado) Chip_GPIO_SetPinState(LPC_GPIO, 0,  5, estado);
#define MOTOR_P3(estado) Chip_GPIO_SetPinState(LPC_GPIO, 0, 29, estado);

/*
 * @brief traduce el número de paso actual a la sequencia correspondiente
 * @param paso: número de paso
 */

void Horno_motor_paso(uint32_t paso) {
	switch(paso & 0b11) {
	case 0:
		MOTOR_P0(true);
		MOTOR_P1(false);
		MOTOR_P2(false);
		MOTOR_P3(false);
		break;
	case 1:
		MOTOR_P0(false);
		MOTOR_P1(true);
		MOTOR_P2(false);
		MOTOR_P3(false);
		break;
	case 2:
		MOTOR_P0(false);
		MOTOR_P1(false);
		MOTOR_P2(true);
		MOTOR_P3(false);
		break;
	case 3:
		MOTOR_P0(false);
		MOTOR_P1(false);
		MOTOR_P2(false);
		MOTOR_P3(true);
		break;
	}
}

/*
 * @brief detiene el motor
 */

void Horno_motor_detener(void){
	MOTOR_P0(false);
	MOTOR_P1(false);
	MOTOR_P2(false);
	MOTOR_P3(false);
	Chip_TIMER_Disable(_LPC_TIMER);
}

/*
 * @brief enciende el motor a una velocidad específica
 * @param time_ms: milisegundos por vuelta
 */

void Horno_motor_marcha(uint32_t time_ms)
{
	/* más rápido no gira */
	if (time_ms < 2000) {
		time_ms = 2000;
	}
	horno_motor.periodo = time_ms;
	/* poner todos los contadores a cero */
	Chip_TIMER_Reset(_LPC_TIMER);

	/* obtener la cantidad de ciclos por milisegundo */
	uint32_t ticks = Chip_Clock_GetPeripheralClockRate(_SYSCTL_PCLK_TIMER) / 1e3;
	/* sacar los ciclos por cada paso */
	ticks = time_ms * ticks / PASOS;
	/* configuramos la cantidad de ciclos a esperar y activamos el timer */
	Chip_TIMER_SetMatch(_LPC_TIMER, 1, ticks);
	Chip_TIMER_Enable(_LPC_TIMER);
}

/*
 * @brief Cambia el sentido del motor
 * @param ascender: true o false
 */

void Horno_motor_ascender(bool ascender) {
	horno_motor.ascender = ascender;
}

/*
 * @brief	Handle interrupt from 32-bit timer
 */

void TIMER1_IRQHandler(void)
{
	/* limpiar la interrupción */
	if (Chip_TIMER_MatchPending(_LPC_TIMER, 1)) {
		Chip_TIMER_ClearMatch(_LPC_TIMER, 1);
		if (horno_motor.ascender) {
			horno_motor.num_paso += 1;
		} else {
			horno_motor.num_paso -= 1;
		}
		Horno_motor_paso(horno_motor.num_paso);
	}
}

/*
 * @brief  Inicialización de los periféricos para manejar el motor.
 */

void Horno_motor_init(void) {
	/* configurar timer */
	Chip_TIMER_Init(_LPC_TIMER); // activa el clock del timer
	/* Cuando el timer alcanza el valor en el match register, queremos una
	 * interrupción y que el timer se reinicie. */
	Chip_TIMER_MatchEnableInt(_LPC_TIMER, 1);
	Chip_TIMER_ResetOnMatchEnable(_LPC_TIMER, 1);

	/* Enable timer interrupt */
	NVIC_ClearPendingIRQ(_TIMER_IRQn);
	NVIC_EnableIRQ(_TIMER_IRQn);

	horno_motor.periodo = 2000;
}
