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
#define _LPC_TIMER LPC_TIMER1
#define _TIMER_IRQn TIMER1_IRQn
#define _SYSCTL_PCLK_TIMER SYSCTL_PCLK_TIMER1

#define PASOS 200 // pasos por vuelta

#define MOTOR_P0(estado) Chip_GPIO_SetPinState(LPC_GPIO, 0, 30, estado);
#define MOTOR_P1(estado) Chip_GPIO_SetPinState(LPC_GPIO, 0,  4, estado);
#define MOTOR_P2(estado) Chip_GPIO_SetPinState(LPC_GPIO, 0,  5, estado);
#define MOTOR_P3(estado) Chip_GPIO_SetPinState(LPC_GPIO, 0, 29, estado);

static uint32_t motor_paso;
static int32_t motor_incremento = 1;
static uint32_t motor_periodo;
static uint32_t ticks;

/*
 * @brief traduce el número de paso actual a la sequencia correspondiente
 * @param paso: número de paso
 */

void Horno_motor_paso(uint32_t paso) {
	switch(paso % 4) {
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
	/* poner todos los contadores a cero */
	Chip_TIMER_Reset(_LPC_TIMER);
	/* sacar el tiempo por paso */
	uint32_t ms = time_ms / PASOS;
	/* configuramos la cantidad de ciclos a esperar y activamos el timer */
	Chip_TIMER_SetMatch(_LPC_TIMER, 1, ms * ticks);
	Chip_TIMER_Enable(_LPC_TIMER);
}

/*
 * @brief Cambia el sentido del motor
 * @param ascender: true o false
 */

void Horno_motor_ascender(bool ascender) {
	if (ascender) {
		motor_incremento = 1;
	} else {
		motor_incremento = -1;
	}
}

/*
 * @brief	Handle interrupt from 32-bit timer
 */

void TIMER1_IRQHandler(void)
{
	/* limpiar la interrupción */
	if (Chip_TIMER_MatchPending(_LPC_TIMER, 1)) {
		Chip_TIMER_ClearMatch(_LPC_TIMER, 1);
		Board_LED_Toggle(0);
		motor_paso += motor_incremento;
		Horno_motor_paso(motor_paso);
	}
}

/*
 * @brief  Inicialización de los periféricos para manejar el motor.
 */

void Horno_motor_init(void) {
	/* obtener el clock que utiliza el timer */
	uint32_t timer_clock = Chip_Clock_GetPeripheralClockRate(_SYSCTL_PCLK_TIMER);
	ticks = timer_clock / 1e3; // cantidad de ciclos por milisegundo.

	/* configurar timer */
	Chip_TIMER_Init(_LPC_TIMER); // activa el clock del timer
	/* Cuando el timer alcanza el valor en el match register, queremos una
	 * interrupción y que el timer se reinicie. */
	Chip_TIMER_MatchEnableInt(_LPC_TIMER, 1);
	Chip_TIMER_ResetOnMatchEnable(_LPC_TIMER, 1);

	/* Enable timer interrupt */
	NVIC_ClearPendingIRQ(_TIMER_IRQn); // TODO: ver que hace esto y si es necesario.
	NVIC_EnableIRQ(_TIMER_IRQn);
}
