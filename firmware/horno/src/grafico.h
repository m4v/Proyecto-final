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


void Horno_grafico_digito(uint32_t x, uint32_t y, uint32_t num);

void Horno_grafico_CLR_digito(uint32_t x, uint32_t y);

void Horno_grafico_flecha(uint32_t x, uint32_t y);

void Horno_grafico_CLR_flecha(uint32_t x, uint32_t y);

void Horno_grafico_entero(uint32_t y, uint32_t dato);

#endif /* GRAFICO_H_ */
