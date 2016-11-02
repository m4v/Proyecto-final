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
#include "grafico.h"
#include "delay.h"
#include "pwm.h"
#include "adc.h"
#include "control.h"

/* mensaje de inicio para mandar por el UART */
static char mensaje_inicio[] =
		"\r\n"
		"Proyecto Final Horno Dental\r\n"
		"===========================\r\n"
		"\r\n";
static char mensaje_menu[] =
		"Controles UART:\r\n"
		" 'c' mostrar datos del ADC y PWM.\r\n"
		" 'i' para poner en marcha el motor.\r\n"
		" 'p' para detener el motor.\r\n"
		" '+' para aumentar la velocidad del motor.\r\n"
		" '-' para disminuir la velocidad del motor.\r\n"
		" 'l' para cambiar el sentido de giro.\r\n"
		"Teclado:\r\n"
		" A inicia/detiene el PWM\r\n"
		" C configura el ciclo de trabajo del PWM\r\n"
		" D configura el periodo del PWM\r\n"
		" # enter\r\n"
		" * retroceso\r\n";


int main(void) {
	uint8_t charUART;

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

    DEBUGOUT(mensaje_inicio);
    Horno_Init();
   	Horno_Display_Test();

   	DEBUGOUT(mensaje_menu);

   	/* bucle principal */
   	while(1){
    	charUART = DEBUGIN();
    	switch(charUART) {
    	case 'c':
    		horno_adc.salida_uart = !horno_adc.salida_uart;
    		break;
    	case 'i':
    		Horno_motor_marcha(horno_motor.periodo);
    		DEBUGOUT("Motor encendido - periodo %dms\n", horno_motor.periodo);
    		break;
    	case 'p':
    		Horno_motor_detener();
    		DEBUGOUT("Motor detenido\n");
    		break;
    	case '+':
    		Horno_motor_marcha(horno_motor.periodo + 500);
    		DEBUGOUT("Motor periodo %dms\n", horno_motor.periodo);
    		break;
    	case '-':
    		Horno_motor_marcha(horno_motor.periodo - 500);
    		DEBUGOUT("Motor periodo %dms\n", horno_motor.periodo);
    		break;
    	case 'l':
    		Horno_motor_ascender(!horno_motor.ascender);
    		DEBUGOUT("Motor sentido ascender %d\n", horno_motor.ascender);
    		break;
    	case 'P':
    		if (horno_pwm.activo) {
    			Horno_pwm_parar();
    			DEBUGOUT("PWM inactivo\n");
    		} else {
    			Horno_pwm_inicio();
    			DEBUGOUT("PWM activo\n");
    		}
    		break;
    	case 'L':
    		Horno_control_activar(!horno_control.activo);
//    		if (horno_control.activo) {
//    			Horno_control_referencia(200);
//    		}
    		DEBUGOUT("PI activo: %d\n", horno_control.activo);
    		break;
    	case 'S':
    		DEBUGOUT("Ingrese temperatura de referencia: ");
    		uint32_t ref = 0;
    		while(1) {
    			uint8_t c = DEBUGIN();
    			if (((c > 47) && (c < 58)) || (c == '\n')) {
					DEBUGOUT("%c", c);
					if (c == '\n') {
						break;
					}
					ref = (ref*10) + c - 48;
    			}
    		}
    		DEBUGOUT("Valor ingresado: %d\n", ref);
    		Horno_control_referencia((float)ref);
    		break;
    	case 'R':
    		horno_adc.valor_n = 0;
    		break;
    	case 'h':
    		DEBUGOUT(mensaje_menu);
    		break;
    	}
    }
    return 0;
}
