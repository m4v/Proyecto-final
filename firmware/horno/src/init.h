/*
 * init.h
 *
 *  Created on: 31/5/2016
 *      Author: Elián Hanisch, Gastón Riera y Rodrigo Oliver
 */

#ifndef INIT_H_
#define INIT_H_

typedef struct {
	uint32_t pingrp:3;
	uint32_t pinnum:5;
	uint32_t output:1;
} GPIO_DIR_T;

typedef struct {
	uint32_t puerto:3;
	uint32_t pin:5;
} PUERTO_T;

void Horno_Init (void);

#endif /* INIT_H_ */
