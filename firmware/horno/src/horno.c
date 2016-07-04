/*
===============================================================================
 Name        : horno.c
 Author      : Elián Hanisch, Gastón Riera y Rodrigo Oliver
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

static int32_t contador;
static int32_t pasos;
static int32_t paso_inc = 0;

/* mensaje de inicio para mandar por el UART */
static char mensaje_inicio[] = "\r\nProyecto Final Horno Dental\r\n";
static char mensaje_menu[] = "La tecla 'c' inicia el ADC, 'x' lo detiene.\r\n";

void SysTick_Handler(void)
{
	contador++;
	if ((contador % 4) == 0) {
		/* divido por 4 para que no parpadeé tan rápido el led */
		Board_LED_Toggle(0);
	}
	if (paso_inc == 0) {
		/* no queremos dejar el motor clavado con una bobina siempre encendida */
		Horno_MotorApagar();
	} else {
		pasos += paso_inc;
		Horno_MotorPaso(pasos);
	}
}

int main(void) {
	uint8_t charUART;
    uint16_t dataADC;

	int adc_enable = 0;

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

    /* SystemCoreClock es 96Mhz
     * SysTick_Config usa el argumento para cargar un contador decreciente
     * que cuando llega a cero genera una interrupción. El contador es de
     * 24bits.
     */
    SysTick_Config(SystemCoreClock / 40); // 40 interrupciones por segundo
    Horno_Init();

    DEBUGOUT(mensaje_inicio);

    // Force the counter to be placed into memory
    volatile static int i = 0;
    // Enter an infinite loop, just incrementing a counter

	DEBUGOUT(mensaje_menu);
    while(1) {
    	charUART = DEBUGIN();
    	if (charUART == 'c') {
    		adc_enable = 1;
    	} else if (charUART == 'x') {
    		DEBUGOUT("ADC detenido.\r\n");
    		DEBUGOUT(mensaje_menu);
    		adc_enable = 0;
    	}
    	if (adc_enable) {
    		Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
			/* Waiting for A/D conversion complete */
			while (Chip_ADC_ReadStatus(LPC_ADC, ADC_CHANNEL, ADC_DR_DONE_STAT) != SET) {}
			/* Read ADC value */
			Chip_ADC_ReadValue(LPC_ADC, ADC_CHANNEL, &dataADC);
			/* Print ADC value */
			volatile uint32_t j;
			j = 5000000;
			DEBUGOUT("ADC value is : 0x%04x\r\n", dataADC);
			/* Delay */
			while (j--) {}
    	}
    }
    return 0;
}
