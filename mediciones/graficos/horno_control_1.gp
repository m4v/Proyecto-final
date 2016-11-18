#!/usr/bin/gnuplot

set term pngcairo enhanced size 1280,720 fontscale 1

set datafile separator ","
set decimalsign ","

set grid
#set rmargin 10
#set lmargin 1
#set tmargin 1
#set bmargin 0.5
set xlabel "Tiempo [minutos]"
set ylabel "Temperatura [°C]"

datos_1 = "../captura_programa_11-Nov-2016_175802.csv"
t0_1 = 528

datos_2 = "../captura_programa_10-Nov-2016_152524.csv"
t0_2 = 39

datos_3 = "../captura_programa_09-Nov-2016_195356.csv"
t0_3 = 44

datos_4 = "../captura_programa_09-Nov-2016_145400.csv"
t0_4 = 0

datos_5 = "../captura_programa_15-Nov-2016_173219.csv"
t0_5 = 95

datos_6 = "../captura_programa_17-Nov-2016_180946.csv"
t0_6 = 46

set xrange [0:50]
#set yrange [0:3.24]
#set y2range [0:1000]
set key bottom right

set output "horno_programa_2.png"
set title "Ensayo del programa 10/11 (sin display)"

plot datos_2 using (($1 - t0_2)/60):($2) title "temperatura" with lines lc rgb "red", \
     datos_2 using (($1 - t0_2)/60):($9) title "referencia" with lines lc rgb "blue"

set output "horno_programa_3.png"
set xrange [0:60]
set title "Ensayo del programa 11/11 (con display)"

plot datos_1 using (($1 - t0_1)/60):($2) title "temperatura" with lines lc rgb "red", \
     datos_1 using (($1 - t0_1)/60):($9) title "referencia" with lines lc rgb "blue"

set output "horno_programa_4.png"
set title "Ensayo del programa 15/11 (con display)"
set xrange [0:50]

plot datos_5 using (($1 - t0_5)/60):($2) title "temperatura" with lines lc rgb "red", \
     datos_5 using (($1 - t0_5)/60):($9) title "referencia" with lines dashtype "--" lc rgb "blue"

set output "horno_programa_5.png"
set title "Ensayo del programa 17/11 (con display)"
set xrange [0:50]
plot datos_6 using (($1 - t0_6)/60):($2) title "temperatura" with lines lc rgb "red", \
     datos_6 using (($1 - t0_6)/60):($9) title "referencia" with lines dashtype "--" lc rgb "blue"
