/*
 * grafico.c
 *
 *  Created on: 22 de oct. de 2016
 *      Author: m4v
 */

#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif

#include "320240.h"
#include "grafico.h"

/* estructura para guardar bloques de 32x42 píxeles */
typedef struct {
	uint32_t linea[42];
} BLOQUE42_T;

const BLOQUE42_T HORNO_DIGITO[] = {
	{{ /* número 0*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00003E00,
		 0x0000FF80, 0x0003FFE0, 0x0003E3E0, 0x000780F0, 0x000780F0, 0x000F0078, 0x000F0078,
		 0x000F0078, 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C,
		 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C, 0x000F0078, 0x000F0078,
		 0x000F0078, 0x000780F0, 0x000780F0, 0x0003E3E0, 0x0003FFE0, 0x0000FF80, 0x00003E00,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 1*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		 0x0000FE00, 0x000FFE00, 0x000FFE00, 0x000F1E00, 0x00001E00, 0x00001E00, 0x00001E00,
		 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00,
		 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00,
		 0x00001E00, 0x00001E00, 0x00001E00, 0x00001E00, 0x0007FFF8, 0x0007FFF8, 0x0007FFF8,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 2*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0001FC00,
		 0x000FFF00, 0x001FFFC0, 0x001F07E0, 0x001803E0, 0x001001F0, 0x000000F0, 0x000000F0,
		 0x000000F0, 0x000000F0, 0x000000F0, 0x000001E0, 0x000001E0, 0x000003C0, 0x000007C0,
		 0x00000F80, 0x00001F00, 0x00001F00, 0x00003E00, 0x00007C00, 0x0000F800, 0x0001F000,
		 0x0003E000, 0x0007C000, 0x000FC000, 0x001F8000, 0x001FFFF0, 0x001FFFF0, 0x001FFFF0,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 3*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0003FE00,
		 0x000FFF80, 0x000FFFC0, 0x000C07E0, 0x000001E0, 0x000001F0, 0x000000F0, 0x000000F0,
		 0x000000F0, 0x000000F0, 0x000000E0, 0x000001E0, 0x000003C0, 0x0000FF80, 0x0000FF00,
		 0x0000FFC0, 0x000003E0, 0x000000F0, 0x000000F8, 0x00000078, 0x00000078, 0x00000078,
		 0x00000078, 0x000000F8, 0x001001F0, 0x001C03F0, 0x001FFFE0, 0x001FFF80, 0x0007FE00,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 4*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		 0x000007C0, 0x00000FC0, 0x00000FC0, 0x00001FC0, 0x00003FC0, 0x00003BC0, 0x000073C0,
		 0x0000F3C0, 0x0000E3C0, 0x0001C3C0, 0x0001C3C0, 0x000383C0, 0x000703C0, 0x000703C0,
		 0x000E03C0, 0x001E03C0, 0x001C03C0, 0x003803C0, 0x003FFFFC, 0x003FFFFC, 0x003FFFFC,
		 0x000003C0, 0x000003C0, 0x000003C0, 0x000003C0, 0x000003C0, 0x000003C0, 0x000003C0,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 5*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		 0x000FFFE0, 0x000FFFE0, 0x000FFFE0, 0x000F0000, 0x000F0000, 0x000F0000, 0x000F0000,
		 0x000F0000, 0x000F0000, 0x000F0000, 0x000FFE00, 0x000FFF80, 0x000FFFC0, 0x000C07E0,
		 0x000001F0, 0x000000F0, 0x000000F8, 0x00000078, 0x00000078, 0x00000078, 0x00000078,
		 0x000000F8, 0x000000F0, 0x001001F0, 0x001C07E0, 0x001FFFC0, 0x001FFF80, 0x0007FC00,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 6*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00001FC0,
		 0x00007FF0, 0x0001FFF0, 0x0003F030, 0x0003C000, 0x00078000, 0x00078000, 0x000F0000,
		 0x000F0000, 0x000F0000, 0x001E1F00, 0x001E7FC0, 0x001EFFF0, 0x001FC1F0, 0x001F80F8,
		 0x001F0078, 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C, 0x000E003C, 0x000E003C,
		 0x000F007C, 0x00070078, 0x000780F8, 0x0003C1F0, 0x0001FFE0, 0x0000FFC0, 0x00003F00,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 7*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		 0x001FFFF8, 0x001FFFF8, 0x001FFFF8, 0x000000F0, 0x000000F0, 0x000001F0, 0x000001E0,
		 0x000001E0, 0x000003C0, 0x000003C0, 0x000007C0, 0x00000780, 0x00000780, 0x00000F80,
		 0x00000F00, 0x00000F00, 0x00001F00, 0x00001E00, 0x00001E00, 0x00003C00, 0x00003C00,
		 0x00007C00, 0x00007800, 0x00007800, 0x0000F800, 0x0000F000, 0x0000F000, 0x0001E000,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 8*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00007F00,
		 0x0001FFC0, 0x0003FFE0, 0x0007C1F0, 0x000780F0, 0x000F0078, 0x000F0078, 0x000F0078,
		 0x000F0078, 0x000F0078, 0x00070070, 0x000780F0, 0x0003C1E0, 0x0001FFC0, 0x0000FF80,
		 0x0003FFE0, 0x0007C1F0, 0x000F0078, 0x000F0078, 0x001E003C, 0x001E003C, 0x001E003C,
		 0x001E003C, 0x001F007C, 0x000F0078, 0x000FC1F8, 0x0007FFF0, 0x0003FFE0, 0x00007F00,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	}},
	{{ /* número 9*/
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00007E00,
		 0x0001FF80, 0x0003FFC0, 0x0007C1E0, 0x000F80F0, 0x000F0070, 0x001F0078, 0x001E0038,
		 0x001E0038, 0x001E003C, 0x001E003C, 0x001E003C, 0x001E003C, 0x000F007C, 0x000F80FC,
		 0x0007C1FC, 0x0007FFBC, 0x0001FF3C, 0x00007C3C, 0x00000078, 0x00000078, 0x00000078,
		 0x000000F0, 0x000000F0, 0x000001E0, 0x000607E0, 0x0007FFC0, 0x0007FF00, 0x0001FC00,
		 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	}}
};

/*
 * @brief grafica un número de 24x42 pixeles
 * @param x: posición X en pixels
 * @param y: posición Y en pixels
 * @param num: dígito de 0 a 9
 */
void Horno_grafico_digito(uint32_t x, uint32_t y, uint32_t num) {
	BLOQUE42_T bloque = HORNO_DIGITO[num];
	for (uint32_t i=0; i < 42; i++) {
		Set_graphic_position(x/8, y+i);
		uint32_t linea = bloque.linea[i];
		for (uint32_t p=3; p>0;p--) { // p cuenta para atrás para no deformar el gráfico
			/* separo los 32 bits en bloques de 8 */
			uint8_t byte = (linea & (0xFF<<((p-1)*8)))>>((p-1)*8);
			Command_Write(MEM_WRITE);
			Parameter_Write(byte);
		}
	}
}
