/*
 * grafico.h
 *
 *  Created on: 22 de oct. de 2016
 *      Author: m4v
 */

#ifndef GRAFICO_H_
#define GRAFICO_H_


#define Horno_grafico_datos_pendiente(dato)				Horno_grafico_datos(14,4,dato)
#define Horno_grafico_datos_tiempo_secado(dato)			Horno_grafico_datos(14,6,dato)
#define Horno_grafico_datos_tiempo_coccion(dato)		Horno_grafico_datos(14,8,dato)
#define Horno_grafico_datos_temperatura_secado(dato)	Horno_grafico_datos(14,10,dato)
#define Horno_grafico_datos_temperatura_coccion(dato)	Horno_grafico_datos(14,12,dato)
#define Horno_grafico_datos_PI_referencia(dato)			Horno_grafico_datos(14,10,dato)

int Horno_pos_y_flecha[39];

void Horno_grafico_digito(uint32_t x, uint32_t y, uint32_t num);

void Horno_grafico_CLR_digito(uint32_t x, uint32_t y);

void Horno_grafico_flecha(uint32_t x, uint32_t y);
void Horno_grafico_CLR_flecha(uint32_t x, uint32_t y);
void Horno_grafico_posicion_flecha(uint32_t estado);
void Horno_grafico_posicion_CLR_flecha(uint32_t estado);

void Horno_grafico_entero(uint32_t y, uint32_t dato);
void Horno_grafico_temperatura(uint32_t temp);
void Horno_grafico_tiempo(uint32_t tiempo);

void Horno_grafico_datos(uint32_t x, uint32_t y, uint32_t dato);

void Horno_grafico_programa(bool estado, uint32_t P_calentamiento, uint32_t T_secado, uint32_t T_coccion, uint32_t t_secado, uint32_t t_coccion);
void Horno_grafico_datos_pwm( bool activo, uint32_t periodo, float dc, float referencia);

void Horno_grafico_pwm_encendido(bool activo);
void Horno_grafico_pwm_periodo(uint32_t periodo);
void Horno_grafico_pwm_ciclo(float dc);
void Horno_grafico_control_referencia(float ref);

void Horno_grafico_dos_puntos(uint32_t x, uint32_t y);
void Horno_grafico_CLR_dos_puntos(uint32_t x, uint32_t y);
void Horno_grafico_FIN();


#endif /* GRAFICO_H_ */
