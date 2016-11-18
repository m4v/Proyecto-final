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
#include "320240.h"
#include "fuentes.h"
#include "programa.h"
#include "teclado.h"

#include <stdlib.h>



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
		Command_Write(MEM_WRITE);
		for (uint32_t p=3; p>0;p--) { // p cuenta para atrás para no deformar el gráfico
			/* separo los 32 bits en bloques de 8 */
			uint8_t byte = (linea & (0xFF<<((p-1)*8)))>>((p-1)*8);
			Parameter_Write(byte);
		}
	}
}

void Horno_grafico_CLR_digito(uint32_t x, uint32_t y) {
	for (uint32_t i=0; i < 42; i++) {
		Set_graphic_position(x/8, y+i);
		Command_Write(MEM_WRITE);
		for (uint32_t p=3; p>0;p--) { // p cuenta para atrás para no deformar el gráfico
			Parameter_Write(0x00);
		}
	}
}

/*
 * @brief Grafica temperatura formato "xxxxºC"
 * @param y: posición Y en pixels
 * @param dato: numero entre 0 y 9999
 */
void Horno_grafico_entero(uint32_t y, uint32_t dato){
	uint32_t pos[4]={270, 245, 220, 195};
	uint32_t numero=dato;
	/* Borramos los digitos */
	Horno_grafico_CLR_digito(pos[0], y);
	Horno_grafico_CLR_digito(pos[1], y);
	Horno_grafico_CLR_digito(pos[2], y);
	Horno_grafico_CLR_digito(pos[3], y);

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
			/* Escribimos los digitos */
			int temp=numero%10;
	   		Horno_grafico_digito(pos[i], y, temp);
	   		i++;
	   		numero=numero/10;
			}
		}
   	Horno_grafico_digito(295,20,10);
	}


/*
 * @brief Grafica el tiempo en formato HH:MM
 * @param y: posición Y en pixels
 * @param segundos
 */
void Horno_grafico_entero_tiempo(uint32_t y, uint32_t segundos){
	uint32_t pos_m[2]={295, 268};
	uint32_t pos_h[2]={235, 210};
	uint32_t horas, minutos;
	horas=segundos/3600;
	minutos=(segundos%3600)/60;

	if ((horas>99) || (segundos<0)){ // Condiciones de error
	   	Horno_grafico_digito(pos_h[1], y, 9);
	   	Horno_grafico_digito(pos_h[0], y, 9);
	   	Horno_grafico_digito(pos_m[1], y, 9);
	   	Horno_grafico_digito(pos_m[0], y, 9);
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
	Horno_grafico_flecha(estado, horno_pos_y_flecha[estado]);
}

void Horno_grafico_posicion_CLR_flecha(uint32_t estado){
	Horno_grafico_CLR_flecha(estado, horno_pos_y_flecha[estado]);
}

/*
 * @brief borra la flecha siguiendo la gráfica
 * @param estado: momento en que está el programa (de 0 a 39 estados)
 */
void Horno_grafico_posicion_flecha_CLR(uint32_t estado){
	Horno_grafico_CLR_flecha(estado, horno_pos_y_flecha[estado]);
}

/*
 * @brief pone los dos puntos del gráfico del tiempo
 * @param x: posición X de a pixels
 * @param y: posición Y de a pixels
 */
void Horno_grafico_dos_puntos(void){
	uint32_t x, y;
	x=260;
	y=75;
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
void Horno_grafico_CLR_dos_puntos(void) {
	uint32_t x, y;
	x=260;
	y=75;
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
	uint32_t pos[3]={268, 244, 220};
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

void Horno_grafico_programa(bool deshabilitar, uint32_t P_calentamiento, uint32_t T_secado, uint32_t T_coccion, uint32_t t_secado, uint32_t t_coccion){
	uint8_t pos_unit = 21;

	Put_string_waddr(1,1,"DATOS del PROGRAMA");
	Put_string_waddr(1,2,"==================");

	Put_string_waddr(1,4,"Pendi. Calent.:");
	Horno_grafico_datos_pendiente(P_calentamiento);
	Put_string_waddr(pos_unit-2,4,"`C/m");
	Put_string_waddr(1,6,"Tiempo Secado :");
	Horno_grafico_datos_tiempo_secado(T_secado); // En este tenemos que definir qué variable le asignamos
	Put_string_waddr(pos_unit+1,6,"m");
	Put_string_waddr(1,8,"Tiempo Coccion:");
	Horno_grafico_datos_tiempo_coccion(T_coccion);
	Put_string_waddr(pos_unit+1,8,"m");
	Put_string_waddr(1,10,"Tempe. Secado :");
	Horno_grafico_datos_temperatura_secado(t_secado);
	Put_string_waddr(pos_unit,10,"`C");
	Put_string_waddr(1,12,"Tempe. Coccion:");
	Horno_grafico_datos_temperatura_coccion(t_coccion);
	Put_string_waddr(pos_unit,12,"`C");

	Put_string_waddr(1,14,"ESTADO:");
	/* Hasta 14 caracteres puede ser el estado */
	if(!deshabilitar){
		Put_string_waddr(9,14,"              ");
		Put_string_waddr(9,14,"       APAGADO");
		Horno_grafico_CLR_curva();
		}
	else{
		Put_string_waddr(9,14,"              ");
		Put_string_waddr(9,14,"     ENCENDIDO");
		Horno_grafico_curva();
	}

}

/*
 * @brief pone datos en de temperatura actual en ºC
 * @param temp: temperatura a mostrar.
 */
void Horno_grafico_temperatura(uint32_t temp){
	Put_string_waddr(24,1,"TEMPERATURA: ");
	Horno_grafico_entero(20,temp);
}

/*
 * @brief pone datos en de tiempo restante
 * @param tiempo: numero en minutos a graficar.
 */
void Horno_grafico_tiempo(uint32_t tiempo){
	Put_string_waddr(24,8,"TIEMPO RESTANTE: ");
	Horno_grafico_entero_tiempo(75,tiempo);
}


void Horno_grafico_control_referencia(float ref){
	Put_string_waddr(1,10,"Ref. PI:");
	Put_string_waddr(14,10,"    ");
	Horno_grafico_datos_PI_referencia(ref);
	Put_string_waddr(18,10,"`C");
}

void Horno_grafico_curva(void){
	/* Esto pone la curva*/
		/*primer rampa       --desde x0=0 y0=229 hasta x1=83 y1=181*/
	for (int i=0; i<59; i++){
		Put_line_waddr(1,239,i,-i,8);
		}
	for (int i=0;i<49;i++){
			/*segunda rampa      --desde x0=150 y0=181 hasta x1=223 y1=132*/
			if (i>=45){
				Put_line_waddr(11,229,i,-i,99);			/* Constante 1*/
				Put_line_waddr(150,181,1.5*i,-i,97);	/* Constante 2*/
			}
			else{
				Put_line_waddr(150,181,1.5*i,-i,8);
			}
		}
}

void Horno_grafico_CLR_curva(void){
	/* Esto pone la curva*/
		/*primer rampa       --desde x0=0 y0=229 hasta x1=83 y1=181*/
	for (int i=0; i<59; i++){
		Clear_line_waddr(1,239,i,-i,8);
		}
	for (int i=0;i<49;i++){
			/*segunda rampa      --desde x0=150 y0=181 hasta x1=223 y1=132*/
			if (i>=45){
				Clear_line_waddr(11,229,i,-i,99);			/* Constante 1*/
				Clear_line_waddr(150,181,1.5*i,-i,97);	/* Constante 2*/
			}
			else{
				Clear_line_waddr(150,181,1.5*i,-i,8);
			}
		}
}

void Horno_grafico_flecha_datos(int linea, bool borrar, bool habilitado){
	uint32_t x=16;
	uint32_t y=4;
	y+=2*linea;
	// Fijamos el comienzo del 1er layer
	Command_Write(CSR_WRITE);
	Parameter_Write(0x00);
	Parameter_Write(0x00);
	// Fijamos la posición del cursor
	Set_text_position(x,y);
	Command_Write(MEM_WRITE);
	if(!borrar && !habilitado){
	Parameter_Write(0x7E);
	} else {
		Parameter_Write(0x20);
	}
}

/*
 * @brief grafica la pantalla de inicio
 */

void Horno_grafico_pantalla(void) {
	Set_graphic_position(0, 0);
	Command_Write(MEM_WRITE);
	for (uint32_t i=0; i < (sizeof(pantalla_inicio)/sizeof(uint32_t)); i++) {
		uint32_t linea = pantalla_inicio[i];
		for (uint32_t p=4; p>0;p--) { // p cuenta para atrás para no deformar el gráfico
			/* separo los 32 bits en bloques de 8 */
			uint8_t byte = (linea & (0xFF<<((p-1)*8)))>>((p-1)*8);
			Parameter_Write(byte);
		}
	}
}
