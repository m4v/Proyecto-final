#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif

#include "delay.h"

#define _LPC_TIMER         LPC_TIMER0
#define _TIMER_IRQn        TIMER0_IRQn
#define _SYSCTL_PCLK_TIMER SYSCTL_PCLK_TIMER0
#define _TIMER_IRQHandler  TIMER0_IRQHandler

/* bits del P0 para las columnas */
#define bCOL1 2
#define bCOL2 21
#define bCOL3 24
#define bCOL4 25
/* bits del P0 para las filas */
#define bFILA1 9
#define bFILA2 8
#define bFILA3 7
#define bFILA4 6

#define GETCOL1(num) (num & (1<<bCOL1))
#define GETCOL2(num) (num & (1<<bCOL2))
#define GETCOL3(num) (num & (1<<bCOL3))
#define GETCOL4(num) (num & (1<<bCOL4))
#define GETFILA1(num) (num & (1<<bFILA1))
#define GETFILA2(num) (num & (1<<bFILA2))
#define GETFILA3(num) (num & (1<<bFILA3))
#define GETFILA4(num) (num & (1<<bFILA4))

/* defines para manejar las filas */
#define SET_FILA1(value) Chip_GPIO_SetPinState(LPC_GPIO, 0, bFILA1, value)
#define SET_FILA2(value) Chip_GPIO_SetPinState(LPC_GPIO, 0, bFILA2, value)
#define SET_FILA3(value) Chip_GPIO_SetPinState(LPC_GPIO, 0, bFILA3, value)
#define SET_FILA4(value) Chip_GPIO_SetPinState(LPC_GPIO, 0, bFILA4, value)

/* defines para leer las filas/columnas */
#define FILA1 GETFILA1(Chip_GPIO_GetPortValue(LPC_GPIO, 0))
#define FILA2 GETFILA2(Chip_GPIO_GetPortValue(LPC_GPIO, 0))
#define FILA3 GETFILA3(Chip_GPIO_GetPortValue(LPC_GPIO, 0))
#define FILA4 GETFILA4(Chip_GPIO_GetPortValue(LPC_GPIO, 0))
#define COL1  GETCOL1(Chip_GPIO_GetPortValue(LPC_GPIO, 0))
#define COL2  GETCOL2(Chip_GPIO_GetPortValue(LPC_GPIO, 0))
#define COL3  GETCOL3(Chip_GPIO_GetPortValue(LPC_GPIO, 0))
#define COL4  GETCOL4(Chip_GPIO_GetPortValue(LPC_GPIO, 0))

static uint32_t counter;

void TECLA1_Handler(void) {
	DEBUGOUT("1");
}

void TECLA2_Handler(void) {
	DEBUGOUT("2");
}

void TECLA3_Handler(void) {
	DEBUGOUT("3");
}

void TECLA4_Handler(void) {
	DEBUGOUT("4");
}

void TECLA5_Handler(void) {
	DEBUGOUT("5");
}

void TECLA6_Handler(void) {
	DEBUGOUT("6");
}

void TECLA7_Handler(void) {
	DEBUGOUT("7");
}

void TECLA8_Handler(void) {
	DEBUGOUT("8");
}

void TECLA9_Handler(void) {
	DEBUGOUT("9");
}

void TECLA0_Handler(void) {
	DEBUGOUT("0");
}

void TECLAA_Handler(void) {
	DEBUGOUT("A");
}

void TECLAB_Handler(void) {
	DEBUGOUT("B");
}

void TECLAC_Handler(void) {
	DEBUGOUT("C");
}

void TECLAD_Handler(void) {
	DEBUGOUT("D");
}

/* tecla asterisco */
void TECLAE_Handler(void) {
	DEBUGOUT("*");
}

/* tecla numeral */
void TECLAF_Handler(void) {
	DEBUGOUT("\n");
}

void COLUMN1_Handler(void) {
	     if (FILA1) { TECLA1_Handler(); }
	else if (FILA2) { TECLA4_Handler(); }
	else if (FILA3) { TECLA7_Handler(); }
	else if (FILA4) { TECLAE_Handler(); }
}

void COLUMN2_Handler(void) {
	     if (FILA1) { TECLA2_Handler(); }
	else if (FILA2) { TECLA5_Handler(); }
	else if (FILA3) { TECLA8_Handler(); }
	else if (FILA4) { TECLA0_Handler(); }
}

void COLUMN3_Handler(void) {
	     if (FILA1) { TECLA3_Handler(); }
	else if (FILA2) { TECLA6_Handler(); }
	else if (FILA3) { TECLA9_Handler(); }
	else if (FILA4) { TECLAF_Handler(); }

}

void COLUMN4_Handler(void) {
	     if (FILA1) { TECLAA_Handler(); }
	else if (FILA2) { TECLAB_Handler(); }
	else if (FILA3) { TECLAC_Handler(); }
	else if (FILA4) { TECLAD_Handler(); }
}

/* interrupción del GPIO, cuando detecta un flanco ascendiente */
void EINT3_IRQHandler(void) {
	if (Chip_GPIOINT_IsIntPending(LPC_GPIOINT, 0)) {
		uint32_t pint = Chip_GPIOINT_GetStatusRising(LPC_GPIOINT, 0);
		if (GETCOL1(pint)) {
			/* columna 1, limpio la interrupción */
			Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, 0, 1<<bCOL1);
			Horno_udelay(1e3); // dejo pasar los rebotes
			if (COL1) {
				/* el boton está apretado */
				COLUMN1_Handler();
				/* espero a que se suelte el boton */
				while(COL1) { Horno_udelay(100); };
				Horno_udelay(1e3); // dejo pasar los rebotes
			}
		}
		if (GETCOL2(pint)) {
			Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, 0, 1<<bCOL2);
			Horno_udelay(1e3);
			if (COL2) {
				COLUMN2_Handler();
				while(COL2) { Horno_udelay(100); };
				Horno_udelay(1e3);
			}
		}
		if (GETCOL3(pint)) {
			Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, 0, 1<<bCOL3);
			Horno_udelay(1e3);
			if (COL3) {
				COLUMN3_Handler();
				while(COL3) { Horno_udelay(100); };
				Horno_udelay(1e3);
			}
		}
		if (GETCOL4(pint)) {
			Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, 0, 1<<bCOL4);
			Horno_udelay(1e3);
			if (COL4) {
				COLUMN4_Handler();
				while(COL4) { Horno_udelay(100); };
				Horno_udelay(1e3);
			}
		}
	}
	NVIC_ClearPendingIRQ(EINT3_IRQn);
}

/* la interrupcion del timer rota las filas */
void _TIMER_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(_LPC_TIMER, 1)) {
		/* limpiar la interrupción */
		Chip_TIMER_ClearMatch(_LPC_TIMER, 1);
		/* rotar la fila */
		switch(counter & 0b11) {
		case 0:
			SET_FILA1(true);
			SET_FILA2(false);
			SET_FILA3(false);
			SET_FILA4(false);
			break;
		case 1:
			SET_FILA1(false);
			SET_FILA2(true);
			SET_FILA3(false);
			SET_FILA4(false);
			break;
		case 2:
			SET_FILA1(false);
			SET_FILA2(false);
			SET_FILA3(true);
			SET_FILA4(false);
			break;
		case 3:
			SET_FILA1(false);
			SET_FILA2(false);
			SET_FILA3(false);
			SET_FILA4(true);
			break;
		}
		counter++;
	}
}

void Horno_teclado_init(void) {
	/* configurar interrupciones del GPIO */
	Chip_GPIOINT_Init(LPC_GPIOINT);
	Chip_GPIOINT_SetIntRising(LPC_GPIOINT, 0, (1<<bCOL1)|(1<<bCOL2)|(1<<bCOL3)|(1<<bCOL4));

	/* configurar timer */
	Chip_TIMER_Init(_LPC_TIMER); // activa el clock del timer
	/* obtener la cantidad de ciclos por milisegundo */
	uint32_t ticks = Chip_Clock_GetPeripheralClockRate(_SYSCTL_PCLK_TIMER) / 1e3;
	Chip_TIMER_Reset(_LPC_TIMER);
	Chip_TIMER_SetMatch(_LPC_TIMER, 1, 10*ticks);
	/* Cuando el timer alcanza el valor en el match register, queremos una
	 * interrupción y que el timer se reinicie. */
	Chip_TIMER_MatchEnableInt(_LPC_TIMER, 1);
	Chip_TIMER_ResetOnMatchEnable(_LPC_TIMER, 1);
	Chip_TIMER_Enable(_LPC_TIMER);

	/* bajar la prioridad de EINT3 así se puede usar Horno_udelay mientras se
	 * atiende esa interrupción. */
	NVIC_SetPriority(EINT3_IRQn, 10);
	/* asegurar que la prioridad del _TIMER no es mayor que la de EINT3 para
	 * que no rote filas mientras se espera que se suelte una tecla. */
	NVIC_SetPriority(_TIMER_IRQn, 20);

	/* habilitar interrupciones */
	NVIC_ClearPendingIRQ(EINT3_IRQn);
	NVIC_EnableIRQ(EINT3_IRQn);
	Chip_TIMER_ClearMatch(_LPC_TIMER, 1);
	NVIC_ClearPendingIRQ(_TIMER_IRQn);
	NVIC_EnableIRQ(_TIMER_IRQn);
}
