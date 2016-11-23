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
void Horno_motor_subir_tiempo(uint32_t periodo);
void Horno_motor_bajar(void);
void Horno_motor_bajar_tiempo(uint32_t periodo);

typedef struct {
	bool activo;               // si el motor está activo
	uint32_t secuencia;        // el paso actual
	uint32_t cantidad_pasos;   // cantidad de pasos hechos
	uint32_t periodo;          // tiempo que tarda en dar una vuelta (en ms)
	bool ascender;             // subir o bajar la plataforma.
} HORNO_MOTOR_T;

HORNO_MOTOR_T horno_motor;

#endif /* MOTOR_H_ */
