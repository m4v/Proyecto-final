/*
===============================================================================
 Name        : horno.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

/* includes del proyecto */
#include "init.h"
#include "motor.h"

/* definitions and declarations here */

static int32_t pasos;
static int32_t paso_inc = 0;

void SysTick_Handler(void)
{
	Board_LED_Toggle(0);
	if (paso_inc == 0) {
		/* no queremos dejar el motor clavado con una bobina siempre encendida */
		Horno_MotorApagar();
	} else {
		pasos += paso_inc;
		Horno_MotorPaso(pasos);
	}
}

int main(void) {

#if defined (__USE_LPCOPEN)
#if !defined(NO_BOARD_LIB)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

    /* código del horno empieza aquí */

    SysTick_Config(SystemCoreClock / 40);
    Horno_Init();

    // Force the counter to be placed into memory
    volatile static int i = 0;
    // Enter an infinite loop, just incrementing a counter
    while(1) {

    	/* leer botones para controlar el motor PP */
        bool der = Chip_GPIO_GetPinState(LPC_GPIO, 2, 12);
        bool izq = Chip_GPIO_GetPinState(LPC_GPIO, 2, 11);
        bool parar = Chip_GPIO_GetPinState(LPC_GPIO, 2, 5);
        if (!parar) {
        	paso_inc = 0;
        } else if (!der) {
        	paso_inc = 1;
        } else if (!izq) {
        	paso_inc = -1;
        }
    }
    return 0 ;
}
