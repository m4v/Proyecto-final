/*
 * motor.h
 *
 *  Created on: 31/5/2016
 *      Author: Elián Hanisch, Gastón Riera y Rodrigo Oliver
 */

#ifndef MOTOR_H_
#define MOTOR_H_

void Horno_motor_paso(uint32_t paso);
void Horno_motor_init(void);
void Horno_motor_detener(void);
void Horno_motor_marcha(uint32_t periodo);
void Horno_motor_ascender(bool ascender);

#endif /* MOTOR_H_ */
