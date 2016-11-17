/*
 * control.h
 *
 *  Created on: 23 de oct. de 2016
 *
 */

#ifndef CONTROL_H_
#define CONTROL_H_

/* estructura con valores del lazo de control*/
typedef struct{
	bool activo;            // si el control PI está activo
	float referencia;	    // valor de temperatura de referencia
	float referencia_cond;  // referencia condicionada
	float entrada;          // valor de la entrada del PI
	float entrada_1;        // valor de la entrada del PI una muestra anterior
	float salida;           // valor de la salida del PI
	float salida_1;         // valor de la salida del PI una muestra anterior
} HORNO_CONTROL_T;

HORNO_CONTROL_T horno_control;

void Horno_control_pi(float entrada);
void Horno_control_referencia(float ref);
void Horno_control_activar(bool activar);

#endif /* CONTROL_H_ */
