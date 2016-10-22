# Proyecto Final - Cátedra de Ingeniería Electrónica - 2016

El objetivo de este proyecto es diseñar un sistema de control digital para un horno de prótesis dentales. 

## Estructura de directorios

* firmware/ - Directorio con el programa del horno.
  * horno/ - Código fuente específico del horno.
  * lpc_board_nxp_lpcxpresso_1769/ - Biblioteca de la placa LPCxpresso 1769.
  * lpc_chip_175x_6x/ - Biblioteca del microcontrolador LPC1769.
  * periph_*/ - ejemplos de LPCOpen.
* kicad/ - Archivos del esquemático y PCB
  * datasheet/ - documentación de los integrados utilizados.
  * notas de aplicaciones/ - documentación sobre temas relevantes al proyecto.
  * documentación/ - archivos del horno en formato .pdf. Ej. esquemáticos
* mediciones/ - Archivos .csv con los resultados de mediciones hechas.
  * graficos/ - Gráficos de las mediciones hechas.
* octave/ - scripts de Octave
