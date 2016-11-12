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

#include <string.h>
#include "delay.h"
#include "320240.h"
#include "grafico.h"
#include "pwm.h"
#include "control.h"
/* Defines */

#define LAYER2_ADDRESS 0x1000

/* mapeo de pines */
#define SET_CS  Chip_GPIO_SetPinState(LPC_GPIO, 2, 11, true)
#define CLR_CS  Chip_GPIO_SetPinState(LPC_GPIO, 2, 11, false)
#define SET_A0  Chip_GPIO_SetPinState(LPC_GPIO, 2,  1, true)
#define CLR_A0  Chip_GPIO_SetPinState(LPC_GPIO, 2,  1, false)
#define SET_WR  Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, true)
#define CLR_WR  Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, false)
#define SET_RD  Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true)
#define CLR_RD  Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, false)
#define SET_RST Chip_GPIO_SetPinState(LPC_GPIO, 2, 12, true)
#define CLR_RST Chip_GPIO_SetPinState(LPC_GPIO, 2, 12, false)

#define LCD_DELAY 1 /* retraso usado para comunicarse con la pantalla */


/* activo la pata de reset del display */
void Display_Reset(void)
{
	CLR_RST;
	Horno_udelay(1e3);
	SET_RST;
	Horno_udelay(3e3);
}

/* escribir un byte en el bus de datos */
void Data_Write(uint8_t dato)
{
	/*
	 * pines de datos
	 * D0 P2.2
	 * D1 P2.3
	 * D2 P2.4
	 * D3 P2.5
	 * D4 P2.6
	 * D5 P2.7
	 * D6 P2.8
	 * D7 P2.10
	 */
	uint32_t port = Chip_GPIO_GetPortValue(LPC_GPIO, 2);
	/* limpio los 8 bits del puerto y cambio sus datos */
	port &= ~(0b01111111 << 2);
	port &= ~(0b10000000 << 3);
	port |= (dato & 0b01111111) << 2;  // mover bit 0-6 a la posición 2-8
	port |= (dato & 0b10000000) << 3;  // mover bit 7 a la posición 10
	Chip_GPIO_SetPortValue(LPC_GPIO, 2, port);
}

/* escribe parámetros. */
void Parameter_Write(uint8_t pmtr)
{
	Data_Write(pmtr);

	CLR_CS;
	CLR_A0;
	CLR_WR;
	SET_RD;
	Horno_udelay(LCD_DELAY);
	SET_WR;
	SET_CS;
	Horno_udelay(LCD_DELAY);
}

/* escribe comandos, necesarios para la configuración del controlador */
void Command_Write(uint8_t cmd)
{
	Data_Write(cmd);

	CLR_CS;
	SET_A0;
	CLR_WR;
	SET_RD;
	Horno_udelay(LCD_DELAY);
	SET_WR;
	SET_CS;
	Horno_udelay(LCD_DELAY);
}

/* escribe letra por letra, el contenido de una cadena */
void Put_string(char str[]){
	Command_Write(MEM_WRITE);
	for(int i=0; i<strlen(str);i++){
		Parameter_Write(str[i]);
	}
}

/* rellena la capa de texto con el valor de 8bit ingresado
 * 0x00 pone todo en blanco.
 * 0x20 pone todo en blanco, pero le pasamos el caracter espacio.
 */
void Fill_text_layer(uint8_t x){
	int i;
	Command_Write(MEM_WRITE);
	for(i=0;i<(40*30);i++){
		Parameter_Write(x);
	}
}

/* rellena la capa gráfica con el valor de 8bit ingresado
 * 0x00 pone todo en blanco
 */
void Fill_graphic_layer(uint8_t x){
	Command_Write(MEM_WRITE);
	for(int i=0;i<((0x28)*240);i++){
		Parameter_Write(x);
	}
}

/* fijamos una coordenada para comenzar a escribir en el layer de texto
 *
 * Usamos, a mano que la dirección de comienzo de la capa de texto es 0x0000.
 * Acá hay que poner la dirección en un define
 */
void Set_text_position(uint32_t x, uint32_t y){
	uint32_t address;
	address=(y * 40) + x;
	Command_Write(CSR_WRITE);
	Parameter_Write((uint8_t)(address & 0xFF)); // LSB
	Parameter_Write((uint8_t)(address >> 8));   // MSB
}

/*
 * @brief Fijamos las coordenadas para comenzar a escribir en el layer gráfico.
 * @param x: posición x en bytes
 * @param y: posición y en bits
 */
void Set_graphic_position(uint32_t x, uint32_t y){
	uint32_t address=(LAYER2_ADDRESS + (y * 40) + x);
	Command_Write(CSR_WRITE);
	Parameter_Write((uint8_t)(address & 0xFF)); // LSB
	Parameter_Write((uint8_t)(address >> 8));   // MSB
}

/* Pone un pixel en la coordenada indicada */
void Put_pixel(uint32_t x, uint32_t y){
	Set_graphic_position(x/8,y);
	int temp= (7-(x%8));
	Command_Write(MEM_WRITE);
	Parameter_Write(0x01<<temp);
}

/* Limpia la coordenada puntual */
void Clr_pixel(uint32_t x, uint32_t y){
	Set_graphic_position(x/8,y);
	int temp= (7-(x%8));
	Command_Write(MEM_WRITE);
	Parameter_Write(0x00<<temp);
}

/* Pone una línea que comienza en (x,y) y de longitud 'largo' */
void Put_line( int x, uint32_t y, uint32_t largo){
	char pp=(0x80>>(x%8)); // pixel inicial
	int i;
	largo=x+largo;
	for (i=1; i<=(8-x%8); i++){
		Set_graphic_position(x/8,y);
		Command_Write(MEM_WRITE);
		Parameter_Write(pp);
		pp=pp+((0x80>>(x%8))>>(i));
	}
	x=x+i-1;

	for(; x<largo; x++){
		Set_graphic_position(x/8,y);
//		int temp= (7-(t%8));
		Command_Write(MEM_WRITE);
		char p=0x7F;
		char q;
		q=~(p>>(x%8));
		Parameter_Write(q);
	}
}

/* Crea una linea en la posición (x,y) relativa al origen (x0,y0) de longitud 'largo' */
void Put_line_waddr(int x0, uint32_t y0, uint32_t x, uint32_t y, uint32_t largo){
	// quiero darle una direccion base y que de ahí
	x=x0+x;
	y=y0+y;
	char pp=(0x80>>(x%8)); // pixel inicial
	int i;
	largo=x+largo;
	for (i=1; i<=(8-x%8); i++){
		Set_graphic_position(x/8,y);
		Command_Write(MEM_WRITE);
		Parameter_Write(pp);
		pp=pp+((0x80>>(x%8))>>(i));
	}
	x=x+i-1;

	for(; x<(largo); x++){
		Set_graphic_position(x/8,y);
//		int temp= (7-(t%8));
		Command_Write(MEM_WRITE);
		char p=0x7F;
		char q;
		q=~(p>>(x%8));
		Parameter_Write(q);
	}

}

void Clear_line_waddr(int x0, uint32_t y0, uint32_t x, uint32_t y, uint32_t largo){
	// quiero darle una direccion base y que de ahí
	x=x0+x;
	y=y0+y;
	char pp=(0x00>>(x%8));// 0x80  // pixel inicial
	int i;
	largo=x+largo;
	for (i=1; i<=(8-x%8); i++){
		Set_graphic_position(x/8,y);
		Command_Write(MEM_WRITE);
		Parameter_Write(pp);
		pp=pp+((0x00>>(x%8))>>(i)); //0x80
	}
	x=x+i-1;

	for(; x<(largo); x++){
		Set_graphic_position(x/8,y);
//		int temp= (7-(t%8));
		Command_Write(MEM_WRITE);
		char p=0x00; // 0x7F
//		char q;
//		q=~(p>>(x%8));
		Parameter_Write(p);
	}

}

/* Curva de trabajo estática con el recuadro*/
void static_curve_wsqare(){


	/* Esto pone los recuadros */
	Put_line_waddr(0,0,0,0,320); // Linea horizontal al comienzo


	/* Esto pone las lineas verticales en los laterales */
	for (int i=0;i<=119;i++){
			Put_pixel(0,i+1);	// vertical en el costado izquierdo
			Put_pixel(319,i+1);	// vertical en el costado derecho
			Put_pixel(185,i+1);	// vertical en la mitad
		}
	/* Ponemos la 2da linea horizontal después de las verticales
	 * porque sino aparecen huecos */
	Put_line_waddr(0,0,0,120,320); // Linea horizontal en el medio

}

void Put_string_waddr(int x, int y, char *str){
	// Fijamos el comienzo del 1er layer
	Command_Write(CSR_WRITE);
	Parameter_Write(0x00);
	Parameter_Write(0x00);
	// Fijamos la posición del cursor
	Set_text_position(x,y);
	// Ponemos el string
	Put_string(str);
}

/* inicializa el display con una configuración parecida al 15.1.2 Initialization Example (p.103)
 *  del datasheet del controlador
 */
void Horno_Display_Init(void)
{
	CLR_CS;
	SET_RD;
	SET_WR;
	Display_Reset();

	Command_Write(SYSTEM_SET);
	Parameter_Write((1<<5)|(1<<4)|(0<<3)|(0<<2)|(0));
	/*               \      \      \      \      \Character generator select (0=CGROM 1=CGRAM)
	 *                \      \      \      \Character height (0=8p 1=16p)
	 *                 \      \      \Panel drive select (0=single 1=dual)
	 *                  \      \Reserved (must be 1)
	 *                   \Screen origin compensation (1=no compensation)
	 */
	Parameter_Write((1<<7)|(8-1));
	/*               \      \Horizontal character size (pixels)
	 *                \MOD (0=16-line AC drive 1=two-frame AC drive)
	 */
	Parameter_Write(8-1);   // Vertical character size (pixels)
	Parameter_Write(40-1);  // Character bytes per row (C/R*bpp)
	Parameter_Write(66);    // Total character bytes per row (C/R+2 <= TC/R <= 255)
	Parameter_Write(240-1);	// Frame height (la altura del display)

	/* Horizontal address range (AP) */
	Parameter_Write(0x28); // LSB
	Parameter_Write(0x00); // MSB

	//Command_Write(GRAYSCALE);
	//Parameter_Write(0); // bits per pixel (0=1 1=2 3=4)

	Command_Write(SCROLL);
	/* SAD1 0x0000 */
	Parameter_Write(0x00);  // LSB
	Parameter_Write(0x00);  // MSB
	Parameter_Write(240-1); // SL1
	/* SAD2 0x1000 */
	Parameter_Write(0x00);  // LSB
	Parameter_Write(0x10);  // MSB
	Parameter_Write(240-1); // SL2
	/* SAD3 0x0400 */
	Parameter_Write(0x00); // LSB
	Parameter_Write(0x04); // MSB
	/* SAD4 0x3000 */
	Parameter_Write(0x00); // LSB
	Parameter_Write(0x30); // MSB

	Command_Write(HDOT_SCR);
	Parameter_Write(0); // Horizontal pixel scroll

	Command_Write(OVERLAY);
	Parameter_Write((0<<4)|(0<<3)|(0<<2)|(1));
	/*               \      \      \      \Layer composition method (0=OR 1=XOR 2=AND)
	 *                \      \      \Screen block 1 display mode (0=text 1=graphics)
	 *                 \      \Screen block 3 display mode (0=text 1=graphics)
	 *                  \Layer overlay select (0=two layers 1=three layers)
	 */

	/* clear data in first layer */
	Command_Write(CSR_WRITE); // Ponemos el cursor en el comienzo del layer
	Parameter_Write(0x00); //P1 -- LSB
	Parameter_Write(0x00); //P2 -- MSB
	Fill_text_layer(0x00);

	/* clear data in 2nd display memory page */
	Command_Write(CSR_WRITE); // Ponemos el cursor en el comienzo del layer
	Parameter_Write(0x00); //P1 -- LSB
	Parameter_Write(0x10); //P2 -- MSB
	Fill_graphic_layer(0x00);

	/* clear data in 3rd layer */
	Command_Write(CSR_WRITE); // Ponemos el cursor en el comienzo del layer
	Parameter_Write(0x00); //P1 -- LSB
	Parameter_Write(0x04); //P2 -- MSB
	Fill_text_layer(0x00);

	/* clear data in 4th display memory page */
	Command_Write(CSR_WRITE); // Ponemos el cursor en el comienzo del layer
	Parameter_Write(0x00); //P1 -- LSB
	Parameter_Write(0x30); //P2 -- MSB
	Fill_graphic_layer(0x00);

	/* Set cursor to start of the first screen block. */
	Command_Write(CSR_WRITE);
	Parameter_Write(0x00);
	Parameter_Write(0x00);

	/* Set cursor shape */
	Command_Write(CSR_FORM);
	Parameter_Write(8-1); // Horizontal cursor size
	Parameter_Write((1<<7)|(8-1));
	/*               \      \Vertical cursor size
	 *                \Cursor Mode (0=dash 1=block)
	 */

	/* DISPLAY ON */
	Command_Write(DISPLAY_ON);
	Parameter_Write((0 << 6)|(1 << 4)|(1 << 2)|(2));
	 /*              \        \        \        \cursor attributes
	  *               \        \        \SAD1 attributes
	  *                \        \SAD2 attributes
	  *                 \SAD3 attributes
	  */

	Command_Write(CSR_DIR_R); //Set cursor shift direction to right.
}

void Horno_320240_flecha_datos(uint32_t x, uint32_t y){
	// Fijamos el comienzo del 1er layer
	Command_Write(CSR_WRITE);
	Parameter_Write(0x00);
	Parameter_Write(0x00);
	// Fijamos la posición del cursor
	Set_text_position(x,y);
	Command_Write(MEM_WRITE);
	Parameter_Write(0x7E);
}


/* Con esta funcion jugamos y testeamos el display */
void Horno_Display_Test(void){

	static_curve_wsqare();	// Curva de trabajo + recuadros
	Horno_grafico_programa(0, 00, 00, 00, 00, 00);

//	Put_string_waddr(1,16,"A");
//	Horno_320240_flecha_datos(1,16);
}
