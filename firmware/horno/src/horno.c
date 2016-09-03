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
#include "320240.h"

/* definitions and declarations here */
#define NUM_MUESTRAS 1000

static bool adc_enabled = false;
static int32_t pasos;
static int32_t paso_inc = 0;
static uint32_t time_ms = 0;

static int muestras_i = 0;
static uint16_t muestras[NUM_MUESTRAS];

/* mensaje de inicio para mandar por el UART */
static char mensaje_inicio[] = "\r\nProyecto Final Horno Dental\r\n";
static char mensaje_menu[] = "Presione la tecla 'c' iniciar la captura.\r\n";

/* rutina de interrupción del systick */
void SysTick_Handler(void)
{
//	time_ms++;
//	if ((time_ms % 100) == 0) {
//		/* parpadeo de 10hz */
//		Board_LED_Toggle(0);
//	}
//	if (paso_inc == 0) {
//		/* no queremos dejar el motor clavado con una bobina siempre encendida */
//		Horno_MotorApagar();
//	} else {
//		pasos += paso_inc;
//		Horno_MotorPaso(pasos);
//	}

	if (adc_enabled) {
		if (muestras_i > NUM_MUESTRAS) {
			adc_enabled = false;
			Board_LED_Set(0, false);
		}
		Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
	}
}

/* rutina de interrupción del ADC */
void ADC_IRQHandler(void)
{
	Chip_ADC_ReadValue(LPC_ADC, ADC_CHANNEL, &muestras[muestras_i++]);
}

int main(void) {
	uint8_t charUART;
	int i;

#if defined (__USE_LPCOPEN)
#if !defined(NO_BOARD_LIB)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
#endif
#endif

    /* código del horno empieza aquí */

    /* SystemCoreClock es 96Mhz
     * SysTick_Config usa el argumento para cargar un contador decreciente
     * que cuando llega a cero genera una interrupción. El contador es de
     * 24bits.
     */
    //SysTick_Config(SystemCoreClock / 1000); // una interrupción cada 1 ms
    Horno_Init();

    /*
    DEBUGOUT(mensaje_inicio);
   	DEBUGOUT(mensaje_menu);
    while(1) {
    	charUART = DEBUGIN();
    	if (charUART == 'c') {
    		adc_enabled = true;
    		muestras_i = 0;
    		Board_LED_Set(0, true);
    		while(adc_enabled) {}
    		for (i=0; i < NUM_MUESTRAS; i++) {
    			DEBUGOUT("%.1f, %4d\r\n", (float)i/10, muestras[i]); // tiempo en ms
    		}
    		Board_LED_Set(0, false);
    	}
    }
     */

    /* Display */

    Display_Init();

    return 0;
}
