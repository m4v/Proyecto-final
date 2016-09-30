#!/usr/bin/gnuplot

set term pngcairo enhanced solid size 1280,720 fontscale 2

set datafile separator ","
set decimalsign ","

set grid
#set rmargin 10
#set lmargin 1
#set tmargin 1
#set bmargin 0.5
set xlabel "Tiempo [s]"
set ylabel "Tensión [mV]"
set nokey

dv = 3.3/4096 # LSB
tm = 0.01     # periodo de muestreo
g = 81        # ganancia

datos_1 = "th_circuito_1.csv"
datos_2 = "th_circuito_3.csv"

set output "grafico_circuito_termocupla_1.png"
set title "Tensión de termocupla J (bajo una llama)"
plot datos_1 using ($1*tm):($2*dv/g*1000) with points pt 7 lc rgb "red"

set output "grafico_circuito_termocupla_2.png"
set title "Tensión de termocupla J (enfriado natural)"
plot datos_2 using ($1*tm):($2*dv/g*1000) with points pt 7 lc rgb "red"

