/*
 * delay.c
 *
 *  Created on: 27 de ago. de 2016
 *      Author: Elián Hanisch, Gastón Riera y Rodrigo Oliver
 *
 *  Subrutinas de retraso
 *
 */

#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif

/* usar el TIMER3 para hacer los retrasos */
#define _LPC_TIMER LPC_TIMER3
#define _TIMER_IRQn TIMER3_IRQn
#define _SYSCTL_PCLK_TIMER SYSCTL_PCLK_TIMER3
#define _TIMER_IRQHandler TIMER3_IRQHandler

static bool delay_enabled;
static uint32_t timer_clock;
static uint32_t ticks;

/**
 * @brief	Handle interrupt from 32-bit timer
 * @return	Nothing
 */
void _TIMER_IRQHandler(void)
{
	/* limpiar la interrupción y detener el delay */
	if (Chip_TIMER_MatchPending(_LPC_TIMER, 1)) {
		Chip_TIMER_ClearMatch(_LPC_TIMER, 1);
		delay_enabled = false;
	}
}

/*
 * @brief  función para generar retrasos
 * @param  usec: cantidad de microsegundos
 */
void Horno_udelay(uint32_t usec)
{
	delay_enabled = true;
	/* poner todos los contadores a cero */
	Chip_TIMER_Reset(_LPC_TIMER);

	/* configuramos la cantidad de ciclos a esperar y activamos el timer */
	Chip_TIMER_SetMatch(_LPC_TIMER, 1, usec * ticks);
	Chip_TIMER_Enable(_LPC_TIMER);

	/* Esperamos hasta que llegue la interrupción */
	while (1) {
		__WFI();		if (delay_enabled == false) {
			break;
		}
	}
}

/*
 * @brief  Inicialización del timer que utlizamos para generar retrasos.
 */
void Horno_delay_timer_Init(void) {
	/* obtener el clock que utiliza el timer */
	timer_clock = Chip_Clock_GetPeripheralClockRate(_SYSCTL_PCLK_TIMER);
	ticks = timer_clock / 1e6; // cantidad de ciclos por microsegundo.

	/* configurar timer */
	Chip_TIMER_Init(_LPC_TIMER); // activa el clock del timer
	/* Cuando el timer alcanza el valor en el match register, queremos una
	 * interrupción y que el timer se detenga. */
	Chip_TIMER_MatchEnableInt(_LPC_TIMER, 1);
	Chip_TIMER_StopOnMatchEnable(_LPC_TIMER, 1);

	/* Enable timer interrupt */
	NVIC_ClearPendingIRQ(_TIMER_IRQn);
	NVIC_EnableIRQ(_TIMER_IRQn);
}


