/*
 * 320240.h
 *
 *  Created on: 9 de ago. de 2016
 *      Author: Gastón Riera, Elián Hanisch y Rodrigo Oliver
 */

#ifndef D320240_H_
#define D320240_H_

void Display_Reset(void);
void Data_Write(uint8_t dato);
void Parameter_Write(uint8_t pmtr);
void Command_Write(uint8_t cmd);
void Put_string(char str[]);
void Fill_text_layer(uint8_t value);
void Fill_graphic_layer(uint8_t value);
void Set_text_position(uint32_t x, uint32_t y);
void Set_graphic_position(uint32_t x, uint32_t y);
void Put_pixel(uint32_t x, uint32_t y);
void Clr_pixel(uint32_t x, uint32_t y);
void Put_line_waddr(int x0, uint32_t y0, uint32_t x, uint32_t y, uint32_t largo);
void Clear_line_waddr(int x0, uint32_t y0, uint32_t x, uint32_t y, uint32_t largo);
void Horno_320240_recuadros(void);
void Put_string_waddr(int x, int y, char *str);
void Horno_320240_clear2d_layer(void);
void Horno_Display_Init(void);
void Horno_Display_static(void);


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
