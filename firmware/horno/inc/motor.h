/*
 * motor.h
 *
 *  Created on: 31/5/2016
 *      Author: Elián Hanisch, Gastón Riera y Rodrigo Oliver
 */

#ifndef MOTOR_H_
#define MOTOR_H_

void Horno_motor_init(void);
void Horno_motor_detener(void);
void Horno_motor_marcha(uint32_t periodo);
void Horno_motor_ascender(bool ascender);
void Horno_motor_subir(void);
void Horno_motor_bajar(void);

typedef struct {
	bool activo;
	uint32_t secuencia;
	uint32_t cantidad_pasos;
	uint32_t periodo;
	bool ascender;
} HORNO_MOTOR_T;

HORNO_MOTOR_T horno_motor;

#endif /* MOTOR_H_ */
