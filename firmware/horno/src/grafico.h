/*
 * grafico.h
 *
 *  Created on: 22 de oct. de 2016
 *      Author: m4v
 */

#ifndef GRAFICO_H_
#define GRAFICO_H_

#define Horno_grafico_temperatura(temp) Horno_grafico_entero(20, temp)
//#define Horno_grafico_tiempo(tiemp) Horno_grafico_entero(75, tiemp)


#define Horno_grafico_datos_pendiente(dato)				Horno_grafico_datos(14,4,dato)
#define Horno_grafico_datos_temperatura_ascenso(dato)	Horno_grafico_datos(14,6,dato)
#define Horno_grafico_datos_tiempo_coccion(dato)		Horno_grafico_datos(14,8,dato)
#define Horno_grafico_datos_temperatura_secado(dato)	Horno_grafico_datos(14,10,dato)
#define Horno_grafico_datos_temperatura_coccion(dato)	Horno_grafico_datos(14,12,dato)


void Horno_grafico_digito(uint32_t x, uint32_t y, uint32_t num);

void Horno_grafico_CLR_digito(uint32_t x, uint32_t y);

void Horno_grafico_flecha(uint32_t x, uint32_t y);

void Horno_grafico_CLR_flecha(uint32_t x, uint32_t y);

void Horno_grafico_entero(uint32_t y, uint32_t dato);

void Horno_grafico_datos(uint32_t x, uint32_t y, uint32_t dato);

#endif /* GRAFICO_H_ */
