/*
 * pwm.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: m4v
 */

#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif

#include "pwm.h"

#define PWM_PERIODO 500

void PWM1_IRQHandler(void){
	if (Chip_PWM_MatchPending(LPC_PWM1, 1)) {
		/* apagamos el PWM */
		Chip_PWM_ClearMatch(LPC_PWM1, 1);
		Chip_PWM_MatchDisableInt(LPC_PWM1, 1);
		Chip_PWM_Disable(LPC_PWM1);
		NVIC_DisableIRQ(PWM1_IRQn);
	}
	NVIC_ClearPendingIRQ(PWM1_IRQn);
}

/*
 * @brief Inicia el PWM
 */
void Horno_pwm_inicio(void)
{
	Chip_PWM_Enable(LPC_PWM1);
}

/*
 * @brief Detener el PWM. Se asegura que la salida quede en low.
 */
void Horno_pwm_parar(void)
{
	/* activamos la interrupción en MR1 para asegurar apagar el PWM cuando
	 * su salida está en un nivel bajo. */
	Chip_PWM_SetMatch(LPC_PWM1, 1, Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_PWM1) / 1e3);
	Chip_PWM_LatchEnable(LPC_PWM1, 1);
	Chip_PWM_MatchEnableInt(LPC_PWM1, 1);
	NVIC_ClearPendingIRQ(PWM1_IRQn);
	NVIC_EnableIRQ(PWM1_IRQn);
}

/*
 * @brief Configura el período del PWM
 * @param ms tiempo en milisegundos
 */
void Horno_pwm_periodo(uint32_t ms)
{
	horno_pwm.periodo = ms;
	uint32_t ticks = Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_PWM1) / 1e3;
	Chip_PWM_SetMatch(LPC_PWM1, 0, ms*ticks);
	Chip_PWM_LatchEnable(LPC_PWM1, 0);
}

/*
 * @brief Configura el ciclo de trabajo del PWM
 * @param dc ciclo de trabajo, entre 0.0 y 1.0
 */
void Horno_pwm_ciclo(float dc) {
	if (dc > 1) {
		dc = 1;
	} else if (dc < 0) {
		dc = 0;
	}

	horno_pwm.dc = dc;
	uint32_t pd = LPC_PWM1->MR0;
	Chip_PWM_SetMatch(LPC_PWM1, 1, (uint32_t)(pd * dc));
	Chip_PWM_LatchEnable(LPC_PWM1, 1);
}

/*
 * @brief Inicialización del PWM.
 */
void Horno_pwm_init(void) {
	Chip_PWM_SetControlMode(LPC_PWM1, 1, PWM_SINGLE_EDGE_CONTROL_MODE, PWM_OUT_ENABLED);

	Horno_pwm_periodo(PWM_PERIODO);
	Horno_pwm_ciclo(0.5);

	Chip_PWM_ResetOnMatchEnable(LPC_PWM1, 0);
	Chip_PWM_Init(LPC_PWM1);
}
