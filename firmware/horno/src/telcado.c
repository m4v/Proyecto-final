#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif

#include "delay.h"
#include "320240.h"

#define _LPC_TIMER         LPC_TIMER0
#define _TIMER_IRQn        TIMER0_IRQn
#define _SYSCTL_PCLK_TIMER SYSCTL_PCLK_TIMER0
#define _TIMER_IRQHandler  TIMER0_IRQHandler

#define DEBOUNCE_COUNT 10

/* defines para manejar las filas */
#define SET_FILA1  Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, true)
#define SET_FILA2  Chip_GPIO_SetPinState(LPC_GPIO, 0, 8, true)
#define SET_FILA3  Chip_GPIO_SetPinState(LPC_GPIO, 0, 7, true)
#define SET_FILA4  Chip_GPIO_SetPinState(LPC_GPIO, 0, 6, true)
#define CLR_FILA1  Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, false)
#define CLR_FILA2  Chip_GPIO_SetPinState(LPC_GPIO, 0, 8, false)
#define CLR_FILA3  Chip_GPIO_SetPinState(LPC_GPIO, 0, 7, false)
#define CLR_FILA4  Chip_GPIO_SetPinState(LPC_GPIO, 0, 6, false)

/* defines para leer las filas/columnas */
#define FILA1 Chip_GPIO_GetPinState(LPC_GPIO, 0,  9)
#define FILA2 Chip_GPIO_GetPinState(LPC_GPIO, 0,  8)
#define FILA3 Chip_GPIO_GetPinState(LPC_GPIO, 0,  7)
#define FILA4 Chip_GPIO_GetPinState(LPC_GPIO, 0,  6)
#define COL1  Chip_GPIO_GetPinState(LPC_GPIO, 0,  2)
#define COL2  Chip_GPIO_GetPinState(LPC_GPIO, 0, 21)
#define COL3  Chip_GPIO_GetPinState(LPC_GPIO, 0, 24)
#define COL4  Chip_GPIO_GetPinState(LPC_GPIO, 0, 25)

/* bits de las columnas */
#define BCOL1 1<<2
#define BCOL2 1<<21
#define BCOL3 1<<24
#define BCOL4 1<<25
#define GETCOL1(port) (port & BCOL1)
#define GETCOL2(port) (port & BCOL2)
#define GETCOL3(port) (port & BCOL3)
#define GETCOL4(port) (port & BCOL4)


static uint32_t tecla[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
};

static uint32_t counter;

//void Horno_teclado_marcha(void){
//	/* poner todos los contadores a cero */
//	Chip_TIMER_Reset(_LPC_TIMER);
//	/* obtener la cantidad de ciclos por milisegundo */
//	uint32_t ticks = Chip_Clock_GetPeripheralClockRate(_SYSCTL_PCLK_TIMER) ;
//	ticks=ticks/1e6;
//	Chip_TIMER_SetMatch(_LPC_TIMER, 1, ticks);
//	Chip_TIMER_Enable(_LPC_TIMER);
//}


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

void TECLAE_Handler(void) {
	DEBUGOUT("*");
}

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

void EINT3_IRQHandler(void) {
	NVIC_DisableIRQ(EINT3_IRQn);
	if (Chip_GPIOINT_IsIntPending(LPC_GPIOINT, 0)) {
		uint32_t pint = Chip_GPIOINT_GetStatusRising(LPC_GPIOINT, 0);
		if (GETCOL1(pint)) {
			Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, 0, BCOL1);
			Horno_udelay(10);
			if (COL1) {
				COLUMN1_Handler();
				while(COL1) {};
				Horno_udelay(1e3);
			}
		}
		if (GETCOL2(pint)) {
			Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, 0, BCOL2);
			Horno_udelay(10);
			if (COL2) {
				COLUMN2_Handler();
				while(COL2) {};
				Horno_udelay(1e3);
			}
		}
		if (GETCOL3(pint)) {
			Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, 0, BCOL3);
			Horno_udelay(10);
			if (COL3) {
				COLUMN3_Handler();
				while(COL3) {};
				Horno_udelay(1e3);
			}
		}
		if (GETCOL4(pint)) {
			Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, 0, BCOL4);
			Horno_udelay(10);
			if (COL4) {
				COLUMN4_Handler();
				while(COL4) {};
				Horno_udelay(1e3);
			}
		}
	}
	NVIC_ClearPendingIRQ(EINT3_IRQn);
	NVIC_EnableIRQ(EINT3_IRQn);
}

void Horno_teclado_init(void) {
	/* configurar interrupciones del GPIO */
	Chip_GPIOINT_Init(LPC_GPIOINT);
	Chip_GPIOINT_SetIntRising(LPC_GPIOINT, 0, BCOL1|BCOL2|BCOL3|BCOL4);

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

//
//void Horno_tecla(void){
//	for(int i=0; i<11; i++){
//		if(KEYA1==1){
//
//				if(KEYB5==1){
//						if(KEYB5==1){
//							teclado[1][1]++;
//								}
//							}
//				else if (KEYB6==1){
//						if(KEYB6==1){
//							teclado[1][2]++;
//								}
//							}
//				else if (KEYB7==1){
//						if(KEYB7==1){
//							teclado[1][3]++;
//									}
//							}
//				else if (KEYB8==1){
//							if(KEYB8==1){
//								teclado[1][4]++;
//										}
//									}
//
//						}
//		}
//		else if(KEYA2==1){
//						if(KEYA2==1){
//								if(KEYB5==1){
//										if(KEYB5==1){
//											teclado[2][1]++;
//												}
//											}
//								else if(KEYB6==1){
//										if(KEYB6==1){
//											teclado[2][2]++;
//													}
//												}
//								else if(KEYB7==1){
//										if(KEYB7==1){
//											teclado[2][3]++;
//													}
//												}
//								else if(KEYB7==1){
//										if(KEYB7==1){
//											teclado[2][4]++;
//													}
//												}
//								}
//			}
//			else if(KEYA3==1){
//						if(KEYA3==1){
//								 if(KEYB5==1){
//								 		 	 if(KEYB5==1){
//											teclado[3][1]++;
//								 	 	 	 	 	 }
//								 	 	 	 	 }
//								 if(KEYB6==1){
//								 		 	 if(KEYB6==1){
//													teclado[3][2]++;
//								 		 	 	 	 	 }
//								 	 	 	 	 }
//								 if(KEYB7==1){
//								 		 	 if(KEYB7==1){
//													teclado[3][3]++;
//								 		 	 	 	 	 }
//								 	 	 	 	 	 }
//								 if(KEYB7==1){
//											 if(KEYB8==1){
//													teclado[3][4]++;
//													 	 }
//								                     }
//								 	 	 	 }
//								}
//
//	}

void Horno_tecla(void){
	SET_FILA1;
	CLR_FILA2;
	CLR_FILA3;
	CLR_FILA4;
	//Horno_udelay(1000);
	int i = 0;
	/* tecla 1 */
	if(COL1 == true) {
		tecla[1][1]++;
		if (tecla[1][1] > DEBOUNCE_COUNT) {
			TECLA1_Handler();
			tecla[1][1] = 0;
		}
		i = 1;
	} else {
		tecla[1][1] = 0;
	}
	/* tecla 2 */
	if (COL2 == true){
		i = 1;
		tecla[1][2]++;
		if (tecla[1][2] > DEBOUNCE_COUNT)
		{
			TECLA2_Handler();
			tecla[1][2] = 0;
		}
	} else {
		tecla[1][2] = 0;
	}
	/* tecla 3 */
	if (COL3 == true){
		i = 1;
		tecla[1][3]++;
		if (tecla[1][3] > DEBOUNCE_COUNT)
		{
			TECLA3_Handler();
			tecla[1][3] = 0;
		}
	} else {
		tecla[1][3] = 0;
	}
	/* tecla A */
	if (COL4 == true){
		i = 1;
		tecla[1][4]++;
		if (tecla[1][4] > DEBOUNCE_COUNT)
		{
			TECLAA_Handler();
			tecla[1][4] = 0;
		}
	} else {
		tecla[1][4] = 0;
	}

//	if (i == 0) {
//		DEBUGOUT(" ");
//	}
//	KEYA1DOWN;
//	KEYA2UP;
//	KEYA3DOWN;
//	KEYA4DOWN;
//	if(KEYB5==1){
//		DEBUGOUT("\r\n 4\r\n");
//		return 0;
//			//teclado[2][1]++;
//		}else if(KEYB6==1){
//			DEBUGOUT("\r\n 5\r\n");
//			//teclado[2][2]++;
//			return 0;
//		}else if(KEYB7==1){
//			DEBUGOUT("\r\n 6\r\n");
//			return 0;
//			//teclado[2][3]++;
//		}else if(KEYB8){
//			DEBUGOUT("\r\n B\r\n");
//			return 0;
//			//teclado[2][4]++;
//		}
//	KEYA1DOWN;
//	KEYA2DOWN;
//	KEYA3UP;
//	KEYA4DOWN;
//	if(KEYB5==1){
//			DEBUGOUT("\r\n 7\r\n");
//			return 0;
//				//teclado[3][1]++;
//			}else if(KEYB6==1){
//			DEBUGOUT("\r\n 8\r\n");
//			return 0;
//			//teclado[3][2]++;
//			}else if(KEYB7==1){
//			DEBUGOUT("\r\n 9\r\n");
//			return 0;
//				//teclado[3][3]++;
//			}else if(KEYB8){
//			DEBUGOUT("\r\n C\r\n");
//			return 0;
//			//teclado[3][4]++;
//			}
//	KEYA1DOWN;
//	KEYA2DOWN;
//	KEYA3DOWN;
//	KEYA4UP;
//	if(KEYB5==1){
//				DEBUGOUT("\r\n *\r\n");
//				return 0;
//					//teclado[4][1]++;
//				}else if(KEYB6==1){
//				DEBUGOUT("\r\n 0\r\n");
//				return 0;
//					//teclado[4][2]++;
//				}else if(KEYB7==1){
//				DEBUGOUT("\r\n #\r\n");
//				return 0;
//					//teclado[4][3]++;
//				}else if(KEYB8){
//				DEBUGOUT("\r\n D\r\n");
//				return 0;
//					//teclado[4][4]++;
//				}
}

//void Horno_tecla_check(void){
//	for( int j=1;j<5;j++){
//		for (int k=1;k<5;k++){
//			if(teclado[j][k]==10){
//						DEBUGOUT("\r\n en teclado:",teclado[j][k]);
//
//							}
//					}
//			}
//}
void _TIMER_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(_LPC_TIMER, 1)) {
		/* limpiar la interrupción */
		Chip_TIMER_ClearMatch(_LPC_TIMER, 1);
		/* rotar la fila */
		switch(counter & 0b11) {
		case 0:
			SET_FILA1;
			CLR_FILA2;
			CLR_FILA3;
			CLR_FILA4;
			break;
		case 1:
			CLR_FILA1;
			SET_FILA2;
			CLR_FILA3;
			CLR_FILA4;
			break;
		case 2:
			CLR_FILA1;
			CLR_FILA2;
			SET_FILA3;
			CLR_FILA4;
			break;
		case 3:
			CLR_FILA1;
			CLR_FILA2;
			CLR_FILA3;
			SET_FILA4;
			break;
		}
		counter++;
	}
}
