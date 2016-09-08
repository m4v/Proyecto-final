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

#include "delay.h"
#include "320240.h"

/* Defines */

/* mapeo de pines */
#define SET_CS Chip_GPIO_SetPinState(LPC_GPIO, 0, 4, true)
#define CLR_CS Chip_GPIO_SetPinState(LPC_GPIO, 0, 4, false)
#define SET_A0 Chip_GPIO_SetPinState(LPC_GPIO, 0, 5, true)
#define CLR_A0 Chip_GPIO_SetPinState(LPC_GPIO, 0, 5, false)
#define SET_WR Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, true)
#define CLR_WR Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, false)
#define SET_RD Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true)
#define CLR_RD Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, false)
#define SET_RST Chip_GPIO_SetPinState(LPC_GPIO, 2, 12, true)
#define CLR_RST Chip_GPIO_SetPinState(LPC_GPIO, 2, 12, false)

/* Datos D[7:0] P2.0:P2.7 */



/*Declaro las funciones */
void Parameter_Write(unsigned char x);
void Command_Write(unsigned char x);
void Clear_text_layer(unsigned char x);

char CTL=0x00;
/* Main */
void Display_Init(void)
{
	CLR_CS;
	SET_RD;
	SET_WR;
	/* reseteamos el display y esperamos a que se estabilice */
	CLR_RST;
	Horno_udelay(1e3);
	SET_RST;
	Horno_udelay(3e3);

	// start
	// supply on
	// system set
	Command_Write(0x40); //C
	Parameter_Write(0x30); // 0x30 //P1  -- D5=D4=1 usually HIGH. D3=0->single panel. D0=1 CGROM->internal character(5x7) generator, resto todo LOW
	Parameter_Write(0x87); //P2 -- D7=1 MOD usually HIGH. D[3-0]= Horizontal size -1. Ahora está en 7, Tamano horiz=8
	Parameter_Write(0x07); //P3 -- D[3-0]= Vertical size -1. Ahora en 7, tamano vert=8
	Parameter_Write(0x27); // 38 P4 -- Character Bytes per Row. D[7-0]=([C/R]x bpp)-1. Ahora está en C/R=40
	Parameter_Write(0x42); // 40 P5 -- Total Character Bytes per Row. D[7-0]=[TC/R]+1. Ahora está en 73
	Parameter_Write(0xEF); //P6 -- Frame Height. D[7-0]=Frame height in lines-1. Cantidad de líneas: P6=(240-1). Esta es la altura del display.
	Parameter_Write(0x28); // 48 //P7 -- P8P7 habla de la cantidad de direcciones horizontales. El datasheet habla de 128 con el display de 512, pero considerando una pantalla virtual extra.Para nosotros(sin pantalla virtual) (320/8)=40=0x0028 (P8=0x00,P7=0x28).
	Parameter_Write(0x00); //P8
	//SCROLL
	Command_Write(0x44); //C
	Parameter_Write(0x00); //P1
	Parameter_Write(0x00); //P2
	Parameter_Write(0xEF); // 28 //P3 -- REG[0Dh] bits 7-0 = screen block 1 size in number of lines - 1
	Parameter_Write(0x00); // 00 //P4 -- Second screen block start address
	Parameter_Write(0x10); // 00 //P5
	Parameter_Write(0xEF); // 00 //P6 -- Igual que P3
	Parameter_Write(0x00); // 00 //P7 -- Third screen block start address
	Parameter_Write(0x04); //P8
	Parameter_Write(0x00); //P9 -- Fourth screen block start address
	Parameter_Write(0x30); //P10 xz
	//Hdot SCR
	Command_Write(0x5A); //C
	Parameter_Write(0x00); //P1 -- Set Horizontal pixel shift to zero
	//OVLAY
	Command_Write(0x5B); //C
	Parameter_Write(0x01); //P1	-- D[1-0]: layer composition method, D[1-0]=0b01; EXOR
	// DISP OFF
//	Command_Write(0x58); //C -- Disp OFF
//	Parameter_Write(0x06); //P1

//	 clear data in first layer
	Command_Write(0x46); // Ponemos el cursor en el comienzo del 1er layer
	Parameter_Write(0x00); //P1 -- LSB
	Parameter_Write(0x00); //P2 -- MSB
	Clear_text_layer(0x00);

	//clear data in 2nd display memory page
//	Command_Write(0x46); // Ponemos el cursor en el comienzo del 2do layer
//	Parameter_Write(0x00); //P1 -- LSB
//	Parameter_Write(0x04); //P2 -- MSB
//	Clear_text_layer(0x00);

	//clear data in 3rd display memory page
	Command_Write(0x46); // Ponemos el cursor en el comienzo del 2do layer
	Parameter_Write(0x00); //P1 -- LSB
	Parameter_Write(0x10); //P2 -- MSB
	Clear_graphic_layer(0x00);
//	CTL++;

	// CSRW
	Command_Write(0x46); //C
	Parameter_Write(0x00); //P1 -- Set cursor to star of the first screen block.
	Parameter_Write(0x00); //P2
	// CSR FORM
	Command_Write(0x5D); //C
	Parameter_Write(0x07); //P1 -- Horizontal cursor size=5px
	Parameter_Write(0x87); //P2 -- Vertical cursor size=7px
	//DISP ON
	Command_Write(0x59); //C -- Disp ON
	Parameter_Write(0x16);
	// CSR DIR.
	Command_Write(0x4C); //C -- Set cursor shift direction to right.
	// MWRITE
	Command_Write(0x42);
	// Acá terminamos y dejamos listo para escribir


    for(int k=0; k<30; k++) {
    	char c='A';
	for(int i=0; i<40; i++) {
    	Parameter_Write(c);
    	c++;
//    	Horno_udelay(500e3);
    }
    }
}
/*
 * Escribir 8 bits en el bus de datos
 */
void Data_Write(uint8_t pmtr)
{
	uint32_t port = Chip_GPIO_GetPortValue(LPC_GPIO, 2);
	/* limpio los 8 bits del puerto y cambio sus datos */
	port &= ~0xFF;
	port |= pmtr;
	Chip_GPIO_SetPortValue(LPC_GPIO, 2, port);
}

/* */
void Parameter_Write(unsigned char pmtr)
{
	// Datos
	Data_Write(pmtr);

	// Control
	CLR_CS;
	CLR_A0;
	CLR_WR;
	SET_RD;
	Horno_udelay(100); // esperar 2 ms
	SET_WR;
	SET_CS;
	Horno_udelay(100); // esperar 2 ms
}

void Command_Write(unsigned char cmd)
{
	// Datos
	Data_Write(cmd);

	// Control
	CLR_CS;
	SET_A0;
	CLR_WR;
	SET_RD;
	Horno_udelay(100); // esperar 2 ms

	Board_LED_Set(0, false);
	Horno_udelay(100); // esperar 2 ms
	SET_WR;
	SET_CS;
	Board_LED_Set(0, true);
	Horno_udelay(100); // esperar 2 ms
}

void Clear_text_layer(unsigned char x){
	int i;
	Command_Write(0x42);
	for(i=0;i<1200;i++){
		Parameter_Write(x);
	}

}

void Clear_graphic_layer(unsigned char x){
	int i;
	Command_Write(0x42);
	for(i=0;i<((0x28)*240);i++){
		Parameter_Write(x);
	}
}


