/*
 * grafico.c
 *
 *  Created on: 22 de oct. de 2016
 *      Author: m4v
 */

#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif

#include "320240.h"
#include "grafico.h"
#include "delay.h"
#include "adc.h"

#include <stdlib.h>

/* estructura para guardar bloques de 32x42 píxeles */
typedef struct {
	uint32_t linea[42];
} BLOQUE42_T;


uint8_t flecha[12]= {0xF0,0xF0,0xF0,0xF0,0xF0,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFD};
uint8_t dos_puntos[42] = {
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x1C,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,
		0x1C,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00};

int Horno_pos_y_flecha[39]={
		220,212,204,196,188,180,172,168,
		168,168,168,168,168,168,168,168,
		168,168,168,162,155,150,145,140,
		135,130,125,121,121,121,121,121,
		121,121,121,121,121,121,121};




const BLOQUE42_T HORNO_DIGITO[] = {
	{{ /* número 0*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00003E00,
		 0x0000FF80, 0x0003FFE0, 0x0003E3E0, 0x000780F0, 0x000780F0, 0x000F0078, 0x000F0078,
		 0x000F0078, 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C,
		 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C, 0x000F0078, 0x000F0078,
		 0x000F0078, 0x000780F0, 0x000780F0, 0x0003E3E0, 0x0003FFE0, 0x0000FF80, 0x00003E00,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 1*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		 0x0000FE00, 0x000FFE00, 0x000FFE00, 0x000F1E00, 0x00001E00, 0x00001E00, 0x00001E00,
		 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00,
		 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00,
		 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x0007FFF8, 0x0007FFF8, 0x0007FFF8,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 2*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0001FC00,
		 0x000FFF00, 0x001FFFC0, 0x001F07E0, 0x001803E0, 0x001001F0, 0x000000F0, 0x000000F0,
		 0x000000F0, 0x000000F0, 0x000000F0, 0x000001E0, 0x000001E0, 0x000003C0, 0x000007C0,
		 0x00000F80, 0x00001F00, 0x00001F00, 0x00003E00, 0x00007C00, 0x0000F800, 0x0001F000,
		 0x0003E000, 0x0007C000, 0x000FC000, 0x001F8000, 0x001FFFF0, 0x001FFFF0, 0x001FFFF0,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 3*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0003FE00,
		 0x000FFF80, 0x000FFFC0, 0x000C07E0, 0x000001E0, 0x000001F0, 0x000000F0, 0x000000F0,
		 0x000000F0, 0x000000F0, 0x000000E0, 0x000001E0, 0x000003C0, 0x0000FF80, 0x0000FF00,
		 0x0000FFC0, 0x000003E0, 0x000000F0, 0x000000F8, 0x00000078, 0x00000078, 0x00000078,
		 0x00000078, 0x000000F8, 0x001001F0, 0x001C03F0, 0x001FFFE0, 0x001FFF80, 0x0007FE00,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 4*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		 0x000007C0, 0x00000FC0, 0x00000FC0, 0x00001FC0, 0x00003FC0, 0x00003BC0, 0x000073C0,
		 0x0000F3C0, 0x0000E3C0, 0x0001C3C0, 0x0001C3C0, 0x000383C0, 0x000703C0, 0x000703C0,
		 0x000E03C0, 0x001E03C0, 0x001C03C0, 0x003803C0, 0x003FFFFC, 0x003FFFFC, 0x003FFFFC,
		 0x000003C0, 0x000003C0, 0x000003C0, 0x000003C0, 0x000003C0, 0x000003C0, 0x000003C0,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 5*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		 0x000FFFE0, 0x000FFFE0, 0x000FFFE0, 0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000,
		 0x000F0000, 0x000F0000, 0x000F0000, 0x000FFE00, 0x000FFF80, 0x000FFFC0, 0x000C07E0,
		 0x000001F0, 0x000000F0, 0x000000F8, 0x00000078, 0x00000078, 0x00000078, 0x00000078,
		 0x000000F8, 0x000000F0, 0x001001F0, 0x001C07E0, 0x001FFFC0, 0x001FFF80, 0x0007FC00,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 6*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00001FC0,
		 0x00007FF0, 0x0001FFF0, 0x0003F030, 0x0003C000, 0x00078000, 0x00078000, 0x000F0000,
		 0x000F0000, 0x000F0000, 0x001E1F00, 0x001E7FC0, 0x001EFFF0, 0x001FC1F0, 0x001F80F8,
		 0x001F0078, 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C, 0x000E003C, 0x000E003C,
		 0x000F007C, 0x00070078, 0x000780F8, 0x0003C1F0, 0x0001FFE0, 0x0000FFC0, 0x00003F00,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 7*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		 0x001FFFF8, 0x001FFFF8, 0x001FFFF8, 0x000000F0, 0x000000F0, 0x000001F0, 0x000001E0,
		 0x000001E0, 0x000003C0, 0x000003C0, 0x000007C0, 0x00000780, 0x00000780, 0x00000F80,
		 0x00000F00, 0x00000F00, 0x00001F00, 0x00001E00, 0x00001E00, 0x00003C00, 0x00003C00,
		 0x00007C00, 0x00007800, 0x00007800, 0x0000F800, 0x0000F000, 0x0000F000, 0x0001E000,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 8*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00007F00,
		 0x0001FFC0, 0x0003FFE0, 0x0007C1F0, 0x000780F0, 0x000F0078, 0x000F0078, 0x000F0078,
		 0x000F0078, 0x000F0078, 0x00070070, 0x000780F0, 0x0003C1E0, 0x0001FFC0, 0x0000FF80,
		 0x0003FFE0, 0x0007C1F0, 0x000F0078, 0x000F0078, 0x001E003C, 0x001E003C, 0x001E003C,
		 0x001E003C, 0x001F007C, 0x000F0078, 0x000FC1F8, 0x0007FFF0, 0x0003FFE0, 0x00007F00,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 9*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00007E00,
		 0x0001FF80, 0x0003FFC0, 0x0007C1E0, 0x000F80F0, 0x000F0070, 0x001F0078, 0x001E0038,
		 0x001E0038, 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C, 0x000F007C, 0x000F80FC,
		 0x0007C1FC, 0x0007FFBC, 0x0001FF3C, 0x00007C3C, 0x00000078, 0x00000078, 0x00000078,
		 0x000000F0, 0x000000F0, 0x000001E0, 0x000607E0, 0x0007FFC0, 0x0007FF00, 0x0001FC00,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /*[10] ºC */
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x001C0000, 0x00360000, 0x00220000,
		 0x00360000, 0x001C0000, 0x00001FC0, 0x0000FFF8, 0x0001FFFC, 0x0007F03E, 0x0007C00E,
		 0x000F0006, 0x001F0000, 0x001E0000, 0x001E0000, 0x003C0000, 0x003C0000, 0x003C0000,
		 0x003C0000, 0x003C0000, 0x003C0000, 0x003C0000, 0x003C0000, 0x001E0000, 0x001E0000,
		 0x001F0000, 0x000F0006, 0x0007C00E, 0x0007F03E, 0x0001FFFC, 0x0000FFF8, 0x00001FC0,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /*[11] E */
	     0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	     0x00000000, 0x000FFFF8, 0x000FFFF8, 0x000FFFF8, 0x000F0000, 0x000F0000, 0x000F0000,
	     0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000, 0x000FFFF0, 0x000FFFF0,
	     0x000FFFF0, 0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000,
	     0x000F0000, 0x000F0000, 0x000F0000, 0x000FFFF8, 0x000FFFF8, 0x000FFFF8, 0x00000000,
	     0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /*[12] R */
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		 0x00000000, 0x000FFF00, 0x000FFFC0, 0x000FFFE0, 0x000F01F0, 0x000F00F8, 0x000F0078,
		 0x000F0078, 0x000F0078, 0x000F0078, 0x000F0078, 0x000F00F0, 0x000F01F0, 0x000FFFE0,
		 0x000FFF80, 0x000FFFC0, 0x000F07E0, 0x000F01E0, 0x000F01F0, 0x000F00F8, 0x000F0078,
		 0x000F007C, 0x000F003C, 0x000F003E, 0x000F001F, 0x000F000F, 0x000F000F, 0x00000000,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /*[13] F */
	     0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	     0x00000000, 0x00000000, 0x000FFFE0, 0x000FFFE0, 0x000FFFE0, 0x000F0000, 0x000F0000,
	     0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000, 0x000FFFC0, 0x000FFFC0,
	     0x000FFFC0, 0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000,
	     0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000,
	     0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /*[14] I */
	     0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	     0x00000000, 0x00000000, 0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00,
	     0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00,
	     0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00,
	     0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00, 0x00003C00,
	     0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /*[15] N */
	     0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	     0x00000000, 0x00000000, 0x000FC00E, 0x000FC00E, 0x000FE00E, 0x000FE00E, 0x000FF00E,
	     0x000FF00E, 0x000FF80E, 0x000F780E, 0x000F7C0E, 0x000F3C0E, 0x000F3E0E, 0x000F1F0E,
	     0x000F1F0E, 0x000F0F8E, 0x000F078E, 0x000F07CE, 0x000F03CE, 0x000F03EE, 0x000F01EE,
	     0x000F01FE, 0x000F00FE, 0x000F00FE, 0x000F007E, 0x000F007E, 0x000F003E, 0x000F003E,
	     0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}}
};



/*
 * @brief grafica un número de 24x42 pixeles
 * @param x: posición X en pixels
 * @param y: posición Y en pixels
 * @param num: dígito de 0 a 9
 */
void Horno_grafico_digito(uint32_t x, uint32_t y, uint32_t num) {
	BLOQUE42_T bloque = HORNO_DIGITO[num];
	for (uint32_t i=0; i < 42; i++) {
		Set_graphic_position(x/8, y+i);
		uint32_t linea = bloque.linea[i];
		for (uint32_t p=3; p>0;p--) { // p cuenta para atrás para no deformar el gráfico
			/* separo los 32 bits en bloques de 8 */
			uint8_t byte = (linea & (0xFF<<((p-1)*8)))>>((p-1)*8);
			Command_Write(MEM_WRITE);
			Parameter_Write(byte);
		}
	}
}

void Horno_grafico_CLR_digito(uint32_t x, uint32_t y) {
	for (uint32_t i=0; i < 42; i++) {
		Set_graphic_position(x/8, y+i);
		for (uint32_t p=3; p>0;p--) { // p cuenta para atrás para no deformar el gráfico
			uint8_t byte = 0x00;
			Command_Write(MEM_WRITE);
			Parameter_Write(byte);
		}
	}
}

/*
 * @brief Grafica temperatura formato "xxxxºC"
 * @param y: posición Y en pixels
 * @param dato: numero entre 0 y 9999
 */
void Horno_grafico_entero(uint32_t y, uint32_t dato){
	uint32_t pos[4]={245, 220, 195, 170};
	uint32_t numero=dato;
	if (numero>=9999){
	   	for(int i=0;i<4;i++){
	   		Horno_grafico_digito(pos[i], y, 9);
	   	}
	}
	else if(numero==0){
   		Horno_grafico_digito(pos[0], y, 0);
	}
	else {
		int i=0;
		while(numero!=0)
		{
			int temp=numero%10;
	   		Horno_grafico_digito(pos[i], y, temp);
	   		i++;
	   		numero=numero/10;
			}
		}
   	Horno_grafico_digito(270,20,10);
	}


/*
 * @brief Grafica el tiempo en formato HH:MM
 * @param y: posición Y en pixels
 * @param segundos
 */
void Horno_grafico_entero_tiempo(uint32_t y, uint32_t segundos){
	uint32_t pos_m[2]={275, 248};
	uint32_t pos_h[2]={223, 198};
	uint32_t horas, minutos;
	horas=segundos/3600;
	minutos=(segundos%3600)/60;

	if ((horas>99) || (segundos<0)){ // Condiciones de error
	   	Horno_grafico_digito(pos_h[1], y, 9); 	// E
	   	Horno_grafico_digito(pos_h[0], y, 9); 	// R
	   	Horno_grafico_digito(pos_m[1], y, 9); 	// R
	   	Horno_grafico_digito(pos_m[0], y, 9); 	// R
	}
	else {
		Horno_grafico_digito(pos_h[0], y, horas%10);
		Horno_grafico_digito(pos_h[1], y, horas/10);
		Horno_grafico_digito(pos_m[0], y, minutos%10);
		Horno_grafico_digito(pos_m[1], y, minutos/10);
		}
}


/*
 * @brief grafica flecha de 8x12 px
 * @param x: posición X de a 8 pixels
 * @param y: posición Y en pixels
 */
void Horno_grafico_flecha(uint32_t x, uint32_t y) {
	for (uint32_t i=0; i < 12; i++) {
		Set_graphic_position(x, y+i);
			Command_Write(MEM_WRITE);
			Parameter_Write((~flecha[i]));
	}
}

/*
 * @brief borra flecha de 8x12 px
 * @param x: posición X de a pixels
 * @param y: posición Y en pixels
 */
void Horno_grafico_CLR_flecha(uint32_t x, uint32_t y) {
	for (uint32_t i=0; i < 12; i++) {
		Set_graphic_position(x, y+i);
			Command_Write(MEM_WRITE);
			Parameter_Write(0X00);
	}
}

/*
 * @brief grafica la flecha siguiendo la gráfica
 * @param estado: momento en que está el programa (de 0 a 39 estados)
 */
void Horno_grafico_posicion_flecha(uint32_t estado){
	Horno_grafico_flecha(estado, Horno_pos_y_flecha[estado]);
}

void Horno_grafico_posicion_CLR_flecha(uint32_t estado){
	Horno_grafico_CLR_flecha(estado, Horno_pos_y_flecha[estado]);
}

/*
 * @brief borra la flecha siguiendo la gráfica
 * @param estado: momento en que está el programa (de 0 a 39 estados)
 */
void Horno_grafico_posicion_flecha_CLR(uint32_t estado){
	Horno_grafico_CLR_flecha(estado, Horno_pos_y_flecha[estado]);
}

/*
 * @brief pone los dos puntos del gráfico del tiempo
 * @param x: posición X de a pixels
 * @param y: posición Y de a pixels
 */
void Horno_grafico_dos_puntos(uint32_t x, uint32_t y){
	for (uint32_t i=0; i < 42; i++) {
		Set_graphic_position(x/8, y+i);
			Command_Write(MEM_WRITE);
			Parameter_Write((dos_puntos[i]));
	}
}

/*
 * @brief borra los dos puntos del gráfico del tiempo
 * @param x: posición X de a pixels
 * @param y: posición Y de a pixels
 */
void Horno_grafico_CLR_dos_puntos(uint32_t x, uint32_t y) {
	for (uint32_t i=0; i < 42; i++) {
		Set_graphic_position(x/8, y+i);
			Command_Write(MEM_WRITE);
			Parameter_Write(0X00);
	}
}

/*
 * @brief grafica FIN
 */
void Horno_grafico_FIN(){
	uint32_t pos[3]={248, 224, 200};
	Horno_grafico_digito(pos[2], 75, 13);
	Horno_grafico_digito(pos[1], 75, 14);
	Horno_grafico_digito(pos[0], 75, 15);
}

/*
 * @brief pone el dato ingresado en formato numérico de 4 cifras
 * @param x: posición x en bloque de 8 pixels
 * @param y: posición y en bloque de 8 pixels
 * @param dato: numero a escribir
 */
void Horno_grafico_datos(uint32_t x, uint32_t y, uint32_t dato) {
	uint32_t numero=dato;
	Put_string_waddr(x,y,"    ");
	if (numero >9999){
		Put_string_waddr(x,y,"ERR");
	}
	else{
		char str[4];
		itoa(numero,str,10);

		Put_string_waddr(x,y,str);
	}
}

void Horno_grafico_pwm_encendido(bool activo) {
	Put_string_waddr(1,4,"PWM:");
	if(activo==1){
		Put_string_waddr(14,4,"    ");
		Put_string_waddr(14,4,"ON");
		}
	else if(activo==0){
		Put_string_waddr(14,4,"    ");
		Put_string_waddr(14,4,"OFF");
	}
}

void Horno_grafico_pwm_periodo(uint32_t periodo) {
	Put_string_waddr(1,6,"Periodo:");
	Put_string_waddr(14,6,"    ");
	Horno_grafico_datos_temperatura_ascenso(periodo);
	Put_string_waddr(18,6,"ms");
}

void Horno_grafico_pwm_ciclo(float dc){
	Put_string_waddr(1,8,"C. Trabajo:");
	Put_string_waddr(14,8,"    ");
	Horno_grafico_datos_tiempo_coccion((int)100*(dc));
	Put_string_waddr(18,8,"%");
}

/* Esta funcion pone los datos del programa en la parte izquierda */
void Horno_grafico_datos_pwm( bool activo, uint32_t periodo, float dc, float referencia){
	Put_string_waddr(1,1,"DATOS del PWM");
	Put_string_waddr(1,2,"=============");

	Horno_grafico_pwm_encendido(activo);
	Horno_grafico_pwm_periodo(periodo);
	Horno_grafico_pwm_ciclo(dc);
	Horno_grafico_control_referencia(referencia);
}

void Horno_grafico_programa(bool estado, uint32_t P_calentamiento, uint32_t T_secado, uint32_t T_coccion, uint32_t t_secado, uint32_t t_coccion){

	Put_string_waddr(1,1,"DATOS del PROGRAMA");
	Put_string_waddr(1,2,"==================");

	Put_string_waddr(1,4,"Pendi. Max.:");
	Horno_grafico_datos_pendiente(P_calentamiento);
	Put_string_waddr(18,4,"m/s");
	Put_string_waddr(1,6,"Tiempo Sec.:");
	Horno_grafico_datos_tiempo_secado(T_secado); // En este tenemos que definir qué variable le asignamos
	Put_string_waddr(19,6,"m");
	Put_string_waddr(1,8,"Tiempo Coc.:");
	Horno_grafico_datos_tiempo_coccion(T_coccion);
	Put_string_waddr(19,8,"m");
	Put_string_waddr(1,10,"Tempe. Sec.:");
	Horno_grafico_datos_temperatura_secado(t_secado);
	Put_string_waddr(18,10,"`C");
	Put_string_waddr(1,12,"Tempe. Coc.:");
	Horno_grafico_datos_temperatura_coccion(t_coccion);
	Put_string_waddr(18,12,"`C");

	Put_string_waddr(1,14,"ESTADO:");
	if(estado==1){
		Put_string_waddr(14,14,"   ");
		Put_string_waddr(14,14,"ON");
		}
	else if(estado==0){
		Put_string_waddr(14,14,"   ");
		Put_string_waddr(14,14,"OFF");
	}

}

/*
 * @brief pone datos en de temperatura actual en ºC
 * @param temp: temperatura a mostrar.
 */
void Horno_grafico_temperatura(uint32_t temp){
	Put_string_waddr(21,1,"TEMPERATURA: ");
	Horno_grafico_entero(20,temp);
}

/*
 * @brief pone datos en de tiempo restante
 * @param tiempo: numero en minutos a graficar.
 */
void Horno_grafico_tiempo(uint32_t tiempo){
	Put_string_waddr(21,8,"TIEMPO RESTANTE: ");
	Horno_grafico_entero_tiempo(75,tiempo);
}


void Horno_grafico_control_referencia(float ref){
	Put_string_waddr(1,10,"Ref. PI:");
	Put_string_waddr(14,10,"    ");
	Horno_grafico_datos_PI_referencia(ref);
	Put_string_waddr(18,10,"`C");
}
