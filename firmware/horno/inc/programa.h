/*
 * programa.h
 *
 *  Created on: 8 de nov. de 2016
 *      Author: Elián Hanisch, Gastón Riera y Rodrigo Oliver
 */

#ifndef PROGRAMA_H_
#define PROGRAMA_H_

/* estados del programa */
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


/* parámetros del programa */
typedef struct {
	HORNO_ESTADO_T estado;
	uint32_t temperatura_secado;
	uint32_t temperatura_coccion;
	uint32_t tiempo_secado;
	uint32_t tiempo_coccion;
	uint32_t tiempo_inicio;
	uint32_t tiempo_total;
	uint32_t tiempo_programa_inicio;
	float pendiente_calentamiento;
} HORNO_PROGRAMA_T;

/* tipo de parámetro */
typedef enum {
	PENDIENTE_CALENTAMIENTO,
	TIEMPO_SECADO,
	TIEMPO_COCCION,
	TEMPERATURA_SECADO,
	TEMPERATURA_COCCION
} HORNO_LINEA_T;


HORNO_PROGRAMA_T horno_programa;
HORNO_LINEA_T horno_ingreso_datos;

void Horno_programa_inicio(void);
void Horno_programa_actualizar(void);
void Horno_programa_carga_datos(HORNO_LINEA_T horno_ingreso_datos, uint32_t dato, bool habilitado);
#endif /* PROGRAMA_H_ */
