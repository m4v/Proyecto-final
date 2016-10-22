typedef struct {
	uint32_t th_suma;			// suma accumulada del valor del AD (para hacer el promedio)
	uint32_t th_cantidad;       // cantidad de valores sumados
	uint16_t th_valor;          // valor del AD promediado
	uint32_t lm_suma;
	uint32_t lm_cantidad;
	uint16_t lm_valor;
	uint32_t valor_n;           // número del último valor obtenido
	float    th_valor_mv;
	float    th_valor_c;
	float    lm_valor_v;
	float 	 lm_valor_c;
} HORNO_PROMEDIO_T;

static HORNO_PROMEDIO_T horno_adc;

void Horno_th_lineseg1(void);
void Horno_th_lineseg2(void);
void Horno_th_lineseg3(void);
void Horno_th_adctomv(void);
void Horno_lm_line(void);
