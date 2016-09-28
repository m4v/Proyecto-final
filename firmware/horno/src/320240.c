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

/* Defines */

/* mapeo de pines */
#define SET_CS  Chip_GPIO_SetPinState(LPC_GPIO, 0,  4, true)
#define CLR_CS  Chip_GPIO_SetPinState(LPC_GPIO, 0,  4, false)
#define SET_A0  Chip_GPIO_SetPinState(LPC_GPIO, 0,  5, true)
#define CLR_A0  Chip_GPIO_SetPinState(LPC_GPIO, 0,  5, false)
#define SET_WR  Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, true)
#define CLR_WR  Chip_GPIO_SetPinState(LPC_GPIO, 0, 11, false)
#define SET_RD  Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true)
#define CLR_RD  Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, false)
#define SET_RST Chip_GPIO_SetPinState(LPC_GPIO, 2, 12, true)
#define CLR_RST Chip_GPIO_SetPinState(LPC_GPIO, 2, 12, false)
/* Datos D[7:0] P2.0:P2.7 */

/* comandos */
#define SYSTEM_SET  0x40
#define MEM_WRITE   0x42
#define MEM_READ    0x43
#define SCROLL      0x44
#define CSR_WRITE   0x46
#define CSR_READ    0x47
#define DISPLAY_OFF 0x58
#define DISPLAY_ON  0x59
#define HDOT_SCR    0x5A
#define OVERLAY     0x5B
#define CSR_FORM    0x5D
#define CSR_DIR_R   0x4C
#define CSR_DIR_L   0x4D
#define CSR_DIR_U   0x4E
#define CSR_DIR_D   0x4F
#define GRAYSCALE   0x60

#define LCD_DELAY 40 /* retraso usado para comunicarse con la pantalla */


/* activo la pata de reset del display */
void Display_Reset(void)
{
	CLR_RST;
	Horno_udelay(1e3);
	SET_RST;
	Horno_udelay(3e3);
}

/* escribir un byte en el bus de datos */
void Data_Write(uint8_t pmtr)
{
	uint32_t port = Chip_GPIO_GetPortValue(LPC_GPIO, 2);
	/* limpio los 8 bits del puerto y cambio sus datos */
	port &= ~0xFF;
	port |= pmtr;
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
	int str_length=0;
	str_length=strlen(str);
	for(int i=0; i<str_length;i++){
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

/* Fijamos las coordenadas para comenzar a escribir en el layer gráfico.
 * Configurado para el 2do layer es 0x1000.
 *
 * Acá hay que poner la dirección en un define
*/
void Set_graphic_position(uint32_t x, uint32_t y){
	uint32_t address=(0x1000 + (y * 40) + x);
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

/* Función de rodri, pendiente de comentarios */
//void Inc_put_pixel(uint32_t x,uint32_t y){
//	Set_graphic_position(x/8,y);
//	int temp= (7-(x%8));
//	Command_Write(MEM_WRITE);
//	Parameter_Write(0xFF<<temp);
//}

/* Hace un rectánculo de las dimensiones indicadas, comenzando en el (0,0) */
void Put_rectangle(uint32_t width, uint32_t height){
/*
	Command_Write(CSR_WRITE); // Ponemos el cursor en el comienzo del 2do layer <- Capa GRAFICA!
	Parameter_Write(0x00); //P1 -- LSB
	Parameter_Write(0x10); //P2 -- MSB
//	Command_Write(MEM_WRITE); // Avisamos que vamos a escribir
	int x = width;
	int y = height;

	for(int j=0;j<x;j++){
		Command_Write(MEM_WRITE);
		Parameter_Write(0xFF);}
	for (int i=1; i<y; i++){
		// Incremento una posición en y
		Set_graphic_position(0,i);
				Command_Write(MEM_WRITE);
				Parameter_Write(0x80);
		Set_graphic_position(x*8,i);
				Command_Write(MEM_WRITE);
				Parameter_Write(0x01);
	}
	Set_graphic_position(0,y);
	for(int j=0;j<x;j++){

		Command_Write(MEM_WRITE);
		Parameter_Write(0xFF);}
*/
	for(int i=0;i<width;i++){	Put_pixel(i,0);}		// Arista superior
	for(int j=0;j<height;j++){	Put_pixel(0,j);}		// Arista izquierda
	for(int j=0;j<height;j++){	Put_pixel(width,j);}	// Arista derecha
	for(int i=0;i<width;i++){	Put_pixel(i,height);}	// Arista inferior
}

/* Rellena rectángulo. Lo mismo que crear un cuadrado */
void Fill_rectangle(uint32_t width, uint32_t height){
	// acá iria donde acomodamos la dirección
	Set_graphic_position(width/8,height);
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

/* Curva de trabajo estática con el recuadro*/
void static_curve_wsqare(){
	/* Esto pone la curva*/
	for (int i=0;i<50;i++){
			/*primer rampa       --desde x0=10 y0=230 hasta x1=83 y1=181*/
			/*segunda rampa      --desde x0=150 y0=181 hasta x1=223 y1=132*/
			if (i>=46){
				Put_line_waddr(10,230,i,-i,97);			/* Constante 1*/
				Put_line_waddr(150,181,1.5*i,-i,90);	/* Constante 2*/
			}
			else{
				Put_line_waddr(10,230,i,-i,8);
				Put_line_waddr(150,180,1.5*i,-i,8);
			}

		}
	/* Esto pone el recuadro */
	int x0=0,y0=120;
	for (int i=y0;i<=239;i++){
		if(i==y0||i==239){
			Put_line_waddr(x0,y0,0,i-y0,320);
		}
		Put_pixel(x0,i+1);
		Put_pixel(319,i+1);
		Put_line_waddr(x0,y0,0,i,1);
		Put_line_waddr(310,y0,0,i,1);
	}
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

/* Con esta funcion jugamos y testeamos el display */
void Horno_Display_Test(void)
{

	/* Curva de trabajo estática*/
	static_curve_wsqare();



/* Esto escribe el string prueba de en cascada y luego en ascendente*/
//	char prueba[]="Hola MUNDO";
//	for(int i=0;i<30;i++){
//	Set_text_position(i,i);
//	Put_string(prueba);
//	Horno_udelay(50e3);
//	}
//
//	//	 clear data in first layer
//		Command_Write(CSR_WRITE); // Ponemos el cursor en el comienzo del 1er layer
//		Parameter_Write(0x00); //P1 -- LSB
//		Parameter_Write(0x00); //P2 -- MSB
//		Fill_text_layer(0x00);
//
//	for(int i=30;i>=0;i--){
//	Set_text_position((-i+30),(i-1));
//	Put_string(prueba);
//	Horno_udelay(50e3);
//	}


/*Con esto hacemos un gusanito de 8 pixels de largo*/
//		int j=0;
//	for (int k=0;k<240;k++){
//		for(int i=0;i<320;i++){
//			j++;
//			if((j-1)%8==0){Clr_pixel(i-1,k);}
//			Inc_put_pixel(i,k);
//			Horno_udelay(500e2);
//	}}

/* Escribir toda la pantalla con líneas de letras consecutivas.*/
//	Command_Write(MEM_WRITE);
//	for(int k=0; k<30; k++) {
//    	char c='A';
//	for(int i=0; i<40; i++) {
//    	Parameter_Write(c);
//    	c++;
////    	Horno_udelay(500e3);   } //medio segundo
//    }	}



}
