#!/usr/bin/gnuplot

set term pngcairo enhanced solid size 1280,720 fontscale 2

set datafile separator ","
set decimalsign ","

set grid
#set rmargin 10
#set lmargin 1
#set tmargin 1
#set bmargin 0.5
set xlabel "Tiempo [minutos]"
set ylabel "Tensión [V]"

dv = 3.3/4096 # LSB
tm = 0.01     # periodo de muestreo
g = 81        # ganancia


set ytics nomirror
set y2label "Temperatura [°C]"
set y2tics

datos_2 = "../captura_continua_28-Sep-2016.csv"
datos_3 = "../captura_continua_29-Sep-2016_20:00:26.csv"

set xrange [0:125]
set yrange [0:2.268]
set y2range [0:700]

set output "horno_ensayos_2_y_3.png"
set title "Ensayos del horno"
set key bottom right

# los datos ya estan escalados
plot datos_2 using ($1/60):($2) title "escalon 110V - abierto" with points pt 7 lc rgb "red", \
     datos_3 using ($1/60):($2) title "escalon 50V - cerrado" with points pt 7 lc rgb "blue", \
