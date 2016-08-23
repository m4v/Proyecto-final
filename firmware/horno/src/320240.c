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
 * /CS and /RES		P0.4
 * A0				P0.5
 * /RD				P0.10
 * /WR				P0.11
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
	//Chip_GPIO_SetPinState(LPC_GPIO, 2, 12, true);// /Res active in LOW
	//delayUS(10);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 4, true); // /CS=HIGH
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 5, true); // A0=HIGH
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true); // RD=HIGH
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, true); // WR=HIGH
	delayUS(2000);


	// start
	// supply on
	// system set
	Command_Write(0x40); //C
	Parameter_Write(0x30); // 0x30 //P1  -- D5=D4=1 usually HIGH. D3=0->single panel. D0=1 CGROM->internal character(5x7) generator, resto todo LOW
	Parameter_Write(0x87); //P2 -- D7=1 MOD usually HIGH. D[3-0]= Horizontal size -1. Ahora está en 7, Tamano horiz=8
	Parameter_Write(0x07); //P3 -- D[3-0]= Vertical size -1. Ahora en 7, tamano vert=8
	Parameter_Write(0x27); // 0x27  //P4 -- Character Bytes per Row. D[7-0]=([C/R]x bpp)-1. Ahora está en C/R=40
	Parameter_Write(0x2F); // 0x49 //P5 -- Total Character Bytes per Row. D[7-0]=[C/R]+1. Ahora está en 73
	Parameter_Write(0xEF); // 0xEF //P6 -- Frame Height. D[7-0]=Frame height in lines-1. Cantidad de líneas: P6=(240-1). Esta es la altura del display.
	Parameter_Write(0x28); // 0x28 //P7 -- P8P7 habla de la cantidad de direcciones horizontales. El datasheet habla de 128 con el display de 512, pero considerando una pantalla virtual extra.Para nosotros(sin pantalla virtual) (320/8)=40=0x0028 (P8=0x00,P7=0x28).
	Parameter_Write(0x00); // 0x00 //P8
	//SCROLL
	Command_Write(0x44); //C
	Parameter_Write(0x00); //P1
	Parameter_Write(0x00); //P2
	Parameter_Write(0x30); //REG[0Dh] bits 7-0 = screen block 1 size in number of lines - 1 --0x30 //P3
	Parameter_Write(0x00); //P4
	Parameter_Write(0x10); //P5
	Parameter_Write(0x30); //P6 -- Igual que P3
	Parameter_Write(0x00); //P7
	Parameter_Write(0x04); //P8
	// Estos no me sirven porque configuré single panel
	Parameter_Write(0x00); //P9
	Parameter_Write(0x30); //P10

	//Hdot SCR
	Command_Write(0x5A); //C
	Parameter_Write(0x00); //P1 -- Set Horizontal pixel shiflt to zero
	//OVLAY
	Command_Write(0x5B); //C
	Parameter_Write(0x01); //P1	-- D[1-0]: layer composition method, D[1-0]=0b01; EXOR
	// DISP OFF
	Command_Write(0x58); //C -- Disp OFF
	Parameter_Write(0x14); //0x56 //P1
	// clear data in first layer
	int i;

	/*Command_Write(0x42); //C -- Le aviso que voy a escribir
	for (i=0;i<(40*30);i++){
		Parameter_Write(0x20); // fill first screen layer memory with 0x20 (space char)
		}
	//clear data in second layer
	Command_Write(0x42);  //C -- Le aviso que voy a escribir
	for (i=0;i<(40*30);i++){
		Parameter_Write(0x00); // Fill second screen layer memory with 0x00 (blank data)
		}
	*/
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
	Parameter_Write(0x14); //0x00 //P1
	// CSR DIR.
	Command_Write(0x4C); //C -- Set cursor shift direction to right.

	// MWRITE
	Command_Write(0x42);
	// Acá terminamos y dejamos listo para escribir

	/*
	Parameter_Write(0x20); // ' '
	Parameter_Write(0x45); // E
	Parameter_Write(0x50); // P
	Parameter_Write(0x53); // S
	Parameter_Write(0x4F); // O
	Parameter_Write(0x4E); // N
	 */

	char c='A';
    while(c<100) {
    	//Parameter_Write(c);
    	Parameter_Write(c);
    	c++;
      }


}

/* */
void Parameter_Write(uint32_t pmtr)
{
	Chip_GPIO_SetPortValue(LPC_GPIO, 2, pmtr);

	Chip_GPIO_SetPinState(LPC_GPIO, 0, 4, false); // /CS=LOW
	//delayUS(1000);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, false);// WR=LOW
	delayUS(1000);

	Chip_GPIO_SetPinState(LPC_GPIO, 0, 5, false);// A0=LOW
	//Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true);// RD=HIGH
	//Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, false);// WR=LOW
	delayUS(1000);

	Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, true);// WR=HIGH
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 4, true); // /CS=HIGH
	//Chip_GPIO_SetPinState(LPC_GPIO, 0, 5, true);// A0=LOW
	delayUS(1000);
}

void Command_Write(uint32_t cmd)
{
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 5, true); // Send Command

	Chip_GPIO_SetPortValue(LPC_GPIO, 2, cmd); // equivalente de FIOPIN2 = cmd;

	Chip_GPIO_SetPinState(LPC_GPIO, 0, 4, false); // /CS=LOW
	delayUS(1000);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, false);// WR=LOW
	delayUS(1000);

	Board_LED_Set(0, true);
	delayUS(1000);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 4, true); // /CS=HIGH
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, true);// WR=HIGH
	Board_LED_Set(0, false);
	delayUS(1000);
}

void delayUS(unsigned int us)
{
	int i,x;
	//clock @96MHz
	//us=us*96; //96 ciclos equivale a 1 us
	for(i=0;i<(us*96); i++)
	{
		x++;
	}
}




