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
#define _TIMER_IRQHandler  TIMER1_IRQHandler

#define PASOS_VUELTA 200     // pasos por vuelta
#define DISTANCIA_VUELTAS 56 // cantidad de vueltas del motor para cerrar la plataforma

/* tiempos mínimos (en ms) que puede tardar el motor en hacer una vuelta cuando sube y
 * baja la plataforma. Tiempos menores (mayor velocidad) hace que el motor patine */
#define PERIODO_MIN_SUBIDA 2000
#define PERIODO_MIN_BAJADA 1000

#define MOTOR_P0(estado) Chip_GPIO_SetPinState(LPC_GPIO, 0, 30, estado);
#define MOTOR_P1(estado) Chip_GPIO_SetPinState(LPC_GPIO, 0,  4, estado);
#define MOTOR_P2(estado) Chip_GPIO_SetPinState(LPC_GPIO, 0,  5, estado);
#define MOTOR_P3(estado) Chip_GPIO_SetPinState(LPC_GPIO, 0, 29, estado);

#define FIN_CARRERA Chip_GPIO_GetPinState(LPC_GPIO, 0, 26)

/*
 * @brief traduce el número de paso actual a la sequencia correspondiente
 * @param paso: número de paso
 */

void Horno_motor_paso(uint32_t paso) {
	switch(paso & 0b11) {
	case 0:
		MOTOR_P0(true);
		MOTOR_P3(false);
		break;
	case 1:
		MOTOR_P0(false);
		MOTOR_P1(true);
		break;
	case 2:
		MOTOR_P1(false);
		MOTOR_P2(true);
		break;
	case 3:
		MOTOR_P2(false);
		MOTOR_P3(true);
		break;
	}

	/* si se activa el fin de carrera detenemos el motor solamente si al menos
	 * ya hizo una vuelta.
	 */
	if (FIN_CARRERA && (horno_motor.cantidad_pasos > PASOS_VUELTA)) {
		Horno_motor_detener();
	}
	horno_motor.cantidad_pasos++;
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
	horno_motor.activo = false;
}

/*
 * @brief enciende el motor a una velocidad específica
 * @param time_ms: milisegundos por vuelta
 */

void Horno_motor_marcha(uint32_t time_ms)
{
	horno_motor.cantidad_pasos = 0;
	horno_motor.periodo = time_ms;
	/* poner todos los contadores a cero */
	Chip_TIMER_Reset(_LPC_TIMER);

	/* obtener la cantidad de ciclos por milisegundo */
	uint32_t ticks = Chip_Clock_GetPeripheralClockRate(_SYSCTL_PCLK_TIMER) / 1e3;
	/* sacar los ciclos por cada paso */
	ticks = time_ms * ticks / PASOS_VUELTA;
	/* configuramos la cantidad de ciclos a esperar y activamos el timer */
	Chip_TIMER_SetMatch(_LPC_TIMER, 1, ticks);
	Chip_TIMER_Enable(_LPC_TIMER);
	horno_motor.activo = true;
}

/*
 * @brief Cambia el sentido del motor
 * @param ascender: true o false
 */

void Horno_motor_ascender(bool ascender) {
	horno_motor.ascender = ascender;
}

/*
 * @brief Sube la plataforma a la máxima velocidad posible.
 */

void Horno_motor_subir(void) {
	horno_motor.ascender = true;
	Horno_motor_marcha(PERIODO_MIN_SUBIDA);
}

/*
 * @brief Sube la plataforma para cerrar en el tiempo indicado
 * @param tiempo: Tiempo que debería tardar en cerrar la plataforma (segundos).
 */

void Horno_motor_subir_tiempo(uint32_t tiempo) {
	horno_motor.ascender = true;

	uint32_t periodo = 1000*tiempo/DISTANCIA_VUELTAS;

	if (periodo < PERIODO_MIN_SUBIDA) {
		periodo = PERIODO_MIN_SUBIDA;
	}

	Horno_motor_marcha(periodo);
}

/*
 * @brief Baja la plataforma a la máxima velocidad posible.
 */
void Horno_motor_bajar(void) {
	horno_motor.ascender = false;
	Horno_motor_marcha(PERIODO_MIN_BAJADA);
}

/*
 * @brief	Handle interrupt from 32-bit timer
 */

void _TIMER_IRQHandler(void)
{
	/* limpiar la interrupción */
	if (Chip_TIMER_MatchPending(_LPC_TIMER, 1)) {
		Chip_TIMER_ClearMatch(_LPC_TIMER, 1);
		if (horno_motor.ascender) {
			horno_motor.secuencia -= 1;
		} else {
			horno_motor.secuencia += 1;
		}
		Horno_motor_paso(horno_motor.secuencia);
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

	horno_motor.periodo = PERIODO_MIN_SUBIDA;
}
