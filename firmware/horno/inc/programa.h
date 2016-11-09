/*
 * programa.h
 *
 *  Created on: 8 de nov. de 2016
 *      Author: m4v
 */

#ifndef PROGRAMA_H_
#define PROGRAMA_H_

typedef struct {
	uint32_t temperatura_secado;
	uint32_t temperatura_coccion;
	uint32_t tiempo_secado;
	uint32_t tiempo_coccion;
	uint32_t tiempo_inicio;
	float pendiente_calentamiento;
} HORNO_PROGRAMA_T;

typedef enum {
	INICIO,
	ESPERAR_TSECADO,
	SECADO,
	ESPERAR_CIERRE,
	CALENTAMIENTO,
	ESPERAR_TCOCCION,
	COCCION,
	FIN_PROGRAMA,
	HACER_NADA
} HORNO_ESTADO_T;

HORNO_PROGRAMA_T horno_programa;
HORNO_ESTADO_T horno_estado;

void Horno_programa_inicio(void);
void Horno_programa_actualizar(void);

#endif /* PROGRAMA_H_ */
