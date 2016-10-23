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
#define _TIMER_IRQHandler   TIMER0_IRQHandler

#define DEBOUNCE_COUNT 10

#define SET_FILA1  Chip_GPIO_SetPinState(LPC_GPIO, 1, 30, true)
#define SET_FILA2  Chip_GPIO_SetPinState(LPC_GPIO, 1, 31, true)
#define SET_FILA3  Chip_GPIO_SetPinState(LPC_GPIO, 0,  2, true)
#define SET_FILA4  Chip_GPIO_SetPinState(LPC_GPIO, 0,  3, true)
#define CLR_FILA1  Chip_GPIO_SetPinState(LPC_GPIO, 1, 30, false)
#define CLR_FILA2  Chip_GPIO_SetPinState(LPC_GPIO, 1, 31, false)
#define CLR_FILA3  Chip_GPIO_SetPinState(LPC_GPIO, 0,  2, false)
#define CLR_FILA4  Chip_GPIO_SetPinState(LPC_GPIO, 0,  3, false)

#define COL1 Chip_GPIO_GetPinState(LPC_GPIO, 0, 21)
#define COL2 Chip_GPIO_GetPinState(LPC_GPIO, 0, 27)
#define COL3 Chip_GPIO_GetPinState(LPC_GPIO, 0, 28)
#define COL4 Chip_GPIO_GetPinState(LPC_GPIO, 2, 13)

static uint32_t tecla[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
};


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

void TECLAA_Handler(void) {
	DEBUGOUT("A");
}

void Horno_teclado_init(void) {
	/* configurar timer */
	Chip_TIMER_Init(_LPC_TIMER); // activa el clock del timer
	/* obtener la cantidad de ciclos por milisegundo */
	uint32_t ticks = Chip_Clock_GetPeripheralClockRate(_SYSCTL_PCLK_TIMER) / 1e3;
	Chip_TIMER_Reset(_LPC_TIMER);
	Chip_TIMER_SetMatch(_LPC_TIMER, 1, ticks);
	/* Cuando el timer alcanza el valor en el match register, queremos una
	 * interrupción y que el timer se reinicie. */
	Chip_TIMER_MatchEnableInt(_LPC_TIMER, 1);
	Chip_TIMER_ResetOnMatchEnable(_LPC_TIMER, 1);
	Chip_TIMER_Enable(_LPC_TIMER);

	/* Enable timer interrupt */
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
	/* limpiar la interrupción */
	if (Chip_TIMER_MatchPending(_LPC_TIMER, 1)) {
		Chip_TIMER_ClearMatch(_LPC_TIMER, 1);
		Horno_tecla();
	//	Horno_tecla_check();
	}
}
