/*
 * 320240.c
 *
 *  Created on: 9 de ago. de 2016
 *      Author: Gastón Riera, Elián Hanisch y Rodrigo Oliver
 */

#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif

#include "320240.h"
/*  Datos
 * Comandos control
 * CS#		P0.4
 * A0		P0.5
 * RD0#		P0.10
 * WR0#		P0.11
 * WAIT#	P2.11
 * RESET#	P2.12
 */

/* Datos D[7:0] P2.0:P2.7 */

/* Defines */

// #define

/* Cada vez que le mandamos algo al display, hay que ponerle una configuración particular. Esto lo hacemos con una función
 * que sellamará: Command_Write.
 *
 * Una vez que mandamos el comando, procedemos a escribir los registros. Esto lo haceoms con la función: Parameter_Write.
 *
 * La escritura de una letra, en modo caracter, es lo misma misma operación que escribir un registro.
 */

/*Declaro las funciones */
void Display_Init(void);
void Parameter_Write(uint32_t x);
void Command_Write(uint32_t x);
void delayUS(unsigned int us);


/* Main */
void Display_Init(void)
{
	// A esta altura ya están todos los pines correspondientes como salida.
	// Los pines de WAIT y RES los dejo en bajo por HARD.
	// 15.1.2 Initialization example. Pág 103, controlador

	// start
	// supply on
	// system set
	Command_Write(0x40); //C
	Parameter_Write(0x30); //P1  -- D5=D4=1 usually HIGH. D3=0->single panel. D0=1 CGROM->internal character(5x7) generator, resto todo LOW
	Parameter_Write(0x87); //P2 -- D7=1 MOD usually HIGH. D[3-0]= Horizontal size -1. Ahora está en 7, Tamano horiz=8
	Parameter_Write(0x07); //P3 -- D[3-0]= Vertical size -1. Ahora en 7, tamano vert=8
	Parameter_Write(0x27); //P4 -- Character Bytes per Row. D[7-0]=([C/R]x bpp)-1. Ahora está en C/R=40
	Parameter_Write(0x49); //P5 -- Total Character Bytes per Row. D[7-0]=[C/R]+1. Ahora está en 73
	Parameter_Write(0xEF); //P6 -- Frame Height. D[7-0]=Frame height in lines-1. Cantidad de líneas: P6=(240-1). Esta es la altura del display.
	Parameter_Write(0x40); //P7 -- P8P7 habla de la cantidad de direcciones horizontales. El datasheet habla de 128, será que va acá 320=0x140 (P8=0x01,P7=0x40)?
	Parameter_Write(0x01); //P8

	//SCROLL
	Command_Write(0x44); //C
	Parameter_Write(0x00); //P1
	Parameter_Write(0x00); //P2
	Parameter_Write(0x40); //P3
	Parameter_Write(0x00); //P4
	Parameter_Write(0x10); //P5
	Parameter_Write(0x40); //P6
	Parameter_Write(0x00); //P7
	Parameter_Write(0x04); //P8
	// Estos no me sirven porque configuré single panel
	//Parameter_Write(0x00); //P9
	//Parameter_Write(0x40); //P10

	//Hdot SCR
	Command_Write(0x5A); //C
	Parameter_Write(0x00); //P1 -- Set Horizontal pixel shiflt to zero
	//OVLAY
	Command_Write(0x5B); //C
	Parameter_Write(0x01); //P1	-- D[1-0]: layer composition method, D[1-0]=0b01; EXOR
	// DISP OFF
	Command_Write(0x58); //C -- Disp OFF
	Parameter_Write(0x56); //P1
	// clear data in first layer
	int i;
	for (i=0;i<(40*30);i++){
		Parameter_Write(0x20); // fill first screen layer memory with 0x20 (space char)
		}
	//clear data in second layer
	for (i=0;i<(40*30);i++){
	Parameter_Write(0x00); // Fill second screen layer memory with 0x00 (blank data)
		}
	// CSRW
	Command_Write(0x46); //C
	Parameter_Write(0x00); //P1 -- Set cursor to star of the first screen block.
	Parameter_Write(0x00); //P2
	// CSR FORM
	Command_Write(0x5D); //C
	Parameter_Write(0x04); //P1 -- Horizontal cursor size=5px
	Parameter_Write(0x86); //P2 -- Vertical cursor size=7px
	//DISP ON
	Command_Write(0x59); //C -- Disp ON
	Parameter_Write(0x00); //P1
	// CSR DIR.
	Command_Write(0x4C); //C -- Set cursor shift direction to right.

	// Acá terminamos y dejamos listo para escribir
	char c='A';
    while(1) {
    	for (i=0;i<100;i++){
    		Parameter_Write(c);
    		c++;
        	}
    }


}

/* */
void Parameter_Write(uint32_t pmtr)
{
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 5, false);// A0=LOW
	delayUS(10);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true);// RD=HIGH
	delayUS(10);
	Chip_GPIO_SetPortValue(LPC_GPIO, 2, pmtr);
	delayUS(10);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, false);// WR=LOW
	delayUS(20);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, true);// WR=HIGH
	//delayUS(20);
}

void Command_Write(uint32_t cmd)
{
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 5, true);// A0=HIGH
	delayUS(10);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true);// RD=HIGH
	delayUS(10);
	Chip_GPIO_SetPortValue(LPC_GPIO, 2, cmd); // equivalente de FIOPIN2 = cmd;
	delayUS(10);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, false);// WR=LOW -- equivalente de FIOPIN0 &= ~(1<<11);
	delayUS(10);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, true);// WR=HIGH
	delayUS(20);
}

void delayUS(unsigned int us)
{
	int i,x;
	//clock @96MHz
	us=us*96; //96 ciclos equivale a 1 us
	for(i=0;i<(us*96); i++)
	{
		x++;
	}
}




