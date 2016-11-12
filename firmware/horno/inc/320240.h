/*
void Horno_grafico_curva(void){
 * 320240.c
 *
 *  Created on: 9 de ago. de 2016
 *      Author: Gastón Riera, Elián Hanisch y Rodrigo Oliver
 */

#ifndef D320240_H_
#define D320240_H_

void Horno_Display_Init(void);
void Horno_Display_Test(void);
void Set_graphic_position(uint32_t x, uint32_t y);
void Parameter_Write(uint8_t pmtr);
void Command_Write(uint8_t cmd);
void Put_string_waddr(int x, int y, char *str);
void Put_line_waddr(int x0, uint32_t y0, uint32_t x, uint32_t y, uint32_t largo);
void Clear_line_waddr(int x0, uint32_t y0, uint32_t x, uint32_t y, uint32_t largo);


/* comandos */
#define SYSTEM_SET  0x40
#define MEM_WRITE   0x42
#define MEM_READ    0x43
#define SCROLL      0x44
#define CSR_WRITE   0x46
#define CSR_READ    0x47
#define DISPLAY_OFF 0x58
#define DISPLAY_ON  0x59
#define HDOT_SCR    0x5A
#define OVERLAY     0x5B
#define CSR_FORM    0x5D
#define CSR_DIR_R   0x4C
#define CSR_DIR_L   0x4D
#define CSR_DIR_U   0x4E
#define CSR_DIR_D   0x4F
#define GRAYSCALE   0x60

#endif /* D320240_H_ */
