#!/usr/bin/gnuplot

#set term cairolatex monochrome
set term pngcairo enhanced solid size 1280,720 fontscale 2

set datafile separator ","

set grid
#set key bottom right
#set grid ytics ls 1 lw 1 lc rgb "black"
#set grid xtics ls 1 lw 1 lc rgb "black"

set title "Mediciones con conversor AD"
set ylabel "Tensión [V]"
set xlabel "Muestras"
set output "grafico_adc.png"
set yrange [1.52:1.82]
#set xrange [0:20]

set key opaque box

dv = 3.3/4096

datos_lm35 = "lm35_1.csv"
datos_pila = "data_pila4.csv"
datos_pilaAA = "pila_AA_1.csv"

plot \
     datos_lm35 using ($1/0.1):($2*dv) title "Amp. LM35 {/Symbol D}V = 10,7mV (13 niveles)" with points pt 7, \
     datos_pilaAA using ($1/0.1):($2*dv) title "pila AA {/Symbol D}V = 32mV (40 niveles)" with points pt 7, \
     datos_pila using ($1/0.1):($2*dv) title "pila botón {/Symbol D}V = 9,7mV (12 niveles)" with points pt 7, \

datos_termo = "amplificador_termocupla.csv"
datos_pilaAA1 = "pila_AA_sin_proto_1.csv"
datos_pilaAA2 = "pila_AA_sin_proto_2.csv"

set title "Mediciones con conversor AD (sin protoboard)"
set yrange [1.56:1.58]
set output "grafico_adc2.png"
plot \
     datos_pilaAA1 using 1:($2*dv) title "pila AA cable largo - {/Symbol D}V = 9,6mV (12 niveles)" with points pt 7, \
     datos_pilaAA2 using 1:($2*dv) title "pila AA cable corto - {/Symbol D}V = 6,7mV (8 niveles)" with points pt 7, \

set title "Mediciones con conversor AD (sin protoboard)"
set yrange [*:*]
set output "grafico_adc3.png"
plot \
     datos_termo using 1:($2*dv) title "Amp. termocupla {/Symbol D}V = 9mV (11 niveles)" with points pt 7
