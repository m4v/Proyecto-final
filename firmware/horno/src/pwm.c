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

void PWM1_IRQHandler(void){
	if (Chip_PWM_MatchPending(LPC_PWM1, 0)) {
		Chip_PWM_ClearMatch(LPC_PWM1, 0);
		Board_LED_Set(0, true);
	} else if (Chip_PWM_MatchPending(LPC_PWM1, 1)) {
		Chip_PWM_ClearMatch(LPC_PWM1, 1);
		Board_LED_Set(0, false);
	}
	NVIC_ClearPendingIRQ(PWM1_IRQn);
}

void Horno_pwm_init(void) {
	Chip_PWM_SetControlMode(LPC_PWM1, 1, PWM_SINGLE_EDGE_CONTROL_MODE, PWM_OUT_ENABLED);

	Chip_PWM_SetMatch(LPC_PWM1, 0, 24e6);
	Chip_PWM_SetMatch(LPC_PWM1, 1, 12e6);
	Chip_PWM_LatchEnable(LPC_PWM1, 0, PWM_OUT_ENABLED);
	Chip_PWM_LatchEnable(LPC_PWM1, 1, PWM_OUT_ENABLED);

	Chip_PWM_ResetOnMatchEnable(LPC_PWM1, 0);
	Chip_PWM_Init(LPC_PWM1);
	Chip_PWM_Enable(LPC_PWM1);

	//Chip_PWM_MatchEnableInt(LPC_PWM1, 0);
	//Chip_PWM_MatchEnableInt(LPC_PWM1, 1);
	//NVIC_EnableIRQ(PWM1_IRQn);
}
