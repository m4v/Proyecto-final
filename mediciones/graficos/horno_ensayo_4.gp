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
datos_4 = "../captura_continua_30-Sep-2016_19:32:35.csv"

set xrange [0:180]
set yrange [0:3.24]
set y2range [0:1000]

set output "horno_ensayos_con_ajuste_2.png"
set title "Ensayo del horno con puerta abierta"
set key bottom right

# respuesta a un escalón

f(x) = A*(1 - exp(-a*(x*60 - t0)))

plot datos_2 using ($1/60):($2) title "escalón 110V" with points pt 7 lc rgb "red", \
     A=2.2212, a=1/1292.1559, t0=77.5, f(x) title "Tmax=2,22V Tau=22 min" with lines lc rgb "blue"

