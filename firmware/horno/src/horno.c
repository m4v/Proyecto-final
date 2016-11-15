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
#include "horno.h"
#include "motor.h"
#include "320240.h"
#include "grafico.h"
#include "delay.h"
#include "pwm.h"
#include "adc.h"
#include "control.h"
#include "programa.h"
#include "teclado.h"

/* mensaje de inicio para mandar por el UART */
static const char mensaje_inicio[] =
		"\r\n"
		"Proyecto Final 2016 - Horno Dental\r\n"
		"==================================\r\n"
		"\r\n";
static const char mensaje_menu[] =
		"Controles UART:\r\n"
		" 'c' mostrar/ocultar datos del ADC y PWM.\r\n"
		" 'i' para poner en marcha el motor.\r\n"
		" 'p' para detener el motor.\r\n"
		" '+' para aumentar la velocidad del motor.\r\n"
		" '-' para disminuir la velocidad del motor.\r\n"
		" 'l' para cambiar el sentido de giro.\r\n"
		" 'M' para iniciar/detener el programa.\r\n"
		" 'L' para activar el control PI.\r\n"
		" 'P' para activar el PWM\r\n."
		" 'S' para configurar la referencia del PI\r\n."
		" 'D' para configurar el ciclo de trabajo del PWM\r\n."
		"\r\n"
		"Teclado:\r\n"
		" A inicia el programa de cocción.\r\n"
		" B detiene el programa de cocción.\r\n"
		" C sube el cursor.\r\n"
		" D baja el cursor.\r\n"
		" # ingresar dato.\r\n"
		" * retroceso.\r\n";

/*
 * Pin muxing configuration
 * IOCON_MODE_INACT deshabilita las resistencias de pull-up/pull-down
 */
static const PINMUX_GRP_T pinmux[] = {
	/* pines para motor paso a paso */
	{0,  30,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,   4,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,   5,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,  29,  IOCON_MODE_INACT | IOCON_FUNC0},
	/* pines P0.0 y P0.1 reservados para la comunicación UART */
	{0,   0,  IOCON_MODE_INACT | IOCON_FUNC2},
	{0,   1,  IOCON_MODE_INACT | IOCON_FUNC2},
	/* pines del ADC */
	{0,  23,  IOCON_MODE_INACT | IOCON_FUNC1}, // Termocupla
	{0,   3,  IOCON_MODE_INACT | IOCON_FUNC2}, // LM35
	/* PWM
	 * Lo utilizamos como GPIO con R de pull-down, desde pwm.c se cambia a IOCON_FUNC1
	 * cuando es necesario. */
	{2,   0,  IOCON_MODE_PULLDOWN | IOCON_FUNC0},
	/* pines del display */
	{2,  11,  IOCON_MODE_INACT | IOCON_FUNC0}, // /CS
	{2,   1,  IOCON_MODE_INACT | IOCON_FUNC0}, // A0
	{0,  10,  IOCON_MODE_INACT | IOCON_FUNC0}, // /RD
	{0,  11,  IOCON_MODE_INACT | IOCON_FUNC0}, // /WR
	{2,  12,  IOCON_MODE_INACT | IOCON_FUNC0}, // /RES
	/* D[0-7] display */
	{2,   2,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   3,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   4,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   5,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   6,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   7,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,   8,  IOCON_MODE_INACT | IOCON_FUNC0},
	{2,  10,  IOCON_MODE_INACT | IOCON_FUNC0},
	/*Pines del teclado */
	/* filas */
	{0,  9,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,  8,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,  7,  IOCON_MODE_INACT | IOCON_FUNC0},
	{0,  6,  IOCON_MODE_INACT | IOCON_FUNC0},
	/* columnas, entradas con R de pull-down para reducir el ruido cuando
	 * estan en alta impedancia.
	 * ATENCION pines P0.27 a P0.30 no admiten R de pull-up/down.
	 * tabla 89 del manual de usuario del LPC1769 */
	{0,   2,  IOCON_MODE_PULLDOWN | IOCON_FUNC0},
	{0,  21,  IOCON_MODE_PULLDOWN | IOCON_FUNC0},
	{0,  24,  IOCON_MODE_PULLDOWN | IOCON_FUNC0},
	{0,  25,  IOCON_MODE_PULLDOWN | IOCON_FUNC0},
	/* pin del fin de carrera */
	{0,  26,  IOCON_MODE_PULLDOWN | IOCON_FUNC0},
	/* LED de la placa LPCXpresso */
	{0,  22,  IOCON_MODE_INACT | IOCON_FUNC0},
};

/* Pin GPIO configuration */
static const GPIO_DIR_T gpiodir[] = {
	/* pines del motor como salidas */
	{0, 30, true},
	{0,  4, true},
	{0,  5, true},
	{0, 29, true},
	/* pines de datos display como salida*/
	{2, 11, true}, // /CS
	{2,  1, true}, // A0
	{0, 10, true}, // /RD
	{0, 11, true}, // /WR
	{2, 12, true}, // /RES
	/* D[0-7] display */
	{2,  2, true},
	{2,  3, true},
	{2,  4, true},
	{2,  5, true},
	{2,  6, true},
	{2,  7, true},
	{2,  8, true},
	{2, 10, true},
	/*Pines del teclado */
	/* filas */
	{0,  9, true},
	{0,  8, true},
	{0,  7, true},
	{0,  6, true},
	/* columnas como entradas */
	{0,  2, false},
	{0, 21, false},
	{0, 24, false},
	{0, 25, false},
	/* LED */
	{0, 22, true},
	/* pin del fin de carrera */
	{0, 26, false},
};

/*
 * Inicializa las direcciones del GPIO
 */
void GPIO_SetDirections(const GPIO_DIR_T *pinArray, uint32_t arrayLength)
{
	uint32_t ix;

	for (ix = 0; ix < arrayLength; ix++ ) {
		Chip_GPIO_SetPinDIR(LPC_GPIO, pinArray[ix].pingrp, pinArray[ix].pinnum, pinArray[ix].output);
	}
}

void Horno_systick_init(uint32_t ms)
{
	/*
	 * SystemCoreClock es 96Mhz
	 * SysTick_Config usa el argumento para cargar un contador decreciente
	 * que cuando llega a cero genera una interrupción.
	 */
	uint32_t ticks = SystemCoreClock / 1000;
	ticks *= ms;
	/* el contador es de 24 bits, no deberíamos superar ese valor */
	if (0xFFFFFF < ticks) {
		ticks = 0xFFFFFF;
	}
	SysTick_Config(ticks);
}

/* en cada interrupción del systick vemos el resultado en el AD */
void SysTick_Handler(void) {
	Horno_adc_muestreo ();
}

/*
 * @brief Esta función se ejecuta cada vez que se obtiene una nueva muestra de
 *        temperatura, y aquí se procesa.
 * @param temperatura: Temperatura en grados celsius
 */
void Horno_muestra_Handler(float temperatura) {
	/* actualizar la pantalla */
	Horno_grafico_temperatura((uint32_t)temperatura);
	/* actualizar la máquina de estados */
	Horno_programa_actualizar();

	if (horno_pwm.activo) {
		Horno_control_pi(temperatura);
	}

	if (horno_adc.salida_uart) {
		DEBUGOUT("%d, %.2f, %.2f, %.2f, %d, %d, %.4f, %.2f, %.2f, %.2f, %.2f\r\n",
				horno_adc.valor_n,
				horno_adc.temperatura,
				horno_adc.th_temperatura,
				horno_adc.lm_temperatura,
				horno_adc.th_valor,
				horno_adc.lm_valor,
				horno_pwm.activo ? horno_pwm.dc : 0,
				horno_control.referencia,
				horno_control.referencia_cond,
				horno_control.entrada,
				horno_control.salida);
	}
}

/*
 * Función de inicialización del horno.
 */
void Horno_Init (void) {
	/* inicializar la máquina de estados */
	horno_estado = HACER_NADA;

	/* configurar puertos */
	Chip_IOCON_SetPinMuxing(LPC_IOCON, pinmux, sizeof(pinmux) / sizeof(PINMUX_GRP_T));
	GPIO_SetDirections(gpiodir, sizeof(gpiodir) / sizeof(GPIO_DIR_T));

	/* Habilitar el timer para hacer retrasos */
	Horno_delay_timer_Init();
	Horno_Display_Init();
    Horno_grafico_pantalla(); // pantalla de inicio
    Horno_udelay(10e6);
    Horno_320240_clean2d_layer(); // Limpiamos la pantalla que tiene el gráfico de inicio.

	Horno_adc_init();
	/* Las interrupciones del SysTick son para muestrear con el ADC. */
	Horno_systick_init(PERIODO_MUESTREO);
	Horno_teclado_init();
	Horno_motor_init();
	Horno_pwm_init();

	horno_teclado_deshabilitar_carga_datos=true;
}

int main(void) {

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
	uint8_t charUART;

    DEBUGOUT(mensaje_inicio);

    Horno_Init();
   	Horno_Display_Test();
   	Board_LED_Set(0,true); // apagar el led

   	DEBUGOUT(mensaje_menu);

   	/* Bucle principal
   	 *
   	 * el bucle principal no hace nada, más que manejar los comandos y la
   	 * salida del UART, que son puramente para hacer ensayos.
   	 */
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
    		Horno_motor_marcha(horno_motor.periodo + 100);
    		DEBUGOUT("Motor periodo %dms\n", horno_motor.periodo);
    		break;
    	case '-':
    		Horno_motor_marcha(horno_motor.periodo - 100);
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
    		DEBUGOUT("PI activo: %d\n", horno_control.activo);
    		break;
    	case 'D':
			DEBUGOUT("Ingrese ciclo de trabajo: ");
			uint32_t dc = 0;
			while(1) {
				uint8_t c = DEBUGIN();
				if (((c > 47) && (c < 58)) || (c == '\n')) {
					DEBUGOUT("%c", c);
					if (c == '\n') {
						break;
					}
					dc = (dc*10) + c - 48;
				}
			}
			DEBUGOUT("Valor ingresado: %d\n", dc);
			Horno_pwm_ciclo((float)dc/100);
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
    	case 'M':
    		if (horno_estado == HACER_NADA) {
    			Horno_programa_inicio();
    		} else {
    			horno_estado = FIN_PROGRAMA;
    		}
    		break;
    	}
    }
    return 0;
}
