#!/usr/bin/gnuplot

set term pngcairo enhanced solid size 1280,720 fontscale 2

set datafile separator ","
set decimalsign ","

set grid
#set rmargin 10
#set lmargin 1
#set tmargin 1
#set bmargin 0.5
set xlabel "Tiempo [horas]"
set ylabel "Temperatura [°C]"

dv = 3.3/4096 # LSB
tm = 0.01     # periodo de muestreo
g = 81        # ganancia
c = 3.24e-3

datos_2 = "../captura_continua_28-Sep-2016.csv"
datos_3 = "../captura_continua_29-Sep-2016_200026.csv"
datos_4 = "../captura_continua_30-Sep-2016_193235.csv"
datos_5 = "../captura_continua_04-Oct-2016_151634.csv"

set xrange [0:5]
set yrange [0:1000]

set output "horno_presentacion_respuestas.png"
set title "Respuestas del horno"
unset key

# respuesta a un escalón
f(x) = A/c*(1 - exp(-a*(x*3600 - t0)))

plot datos_3 using ($1/3600):($2/c) notitle with points pt 7 lc rgb "blue", \
     datos_4 using ($1/3600):($2/c) notitle with points pt 7 lc rgb "red", \
     datos_5 using ($1/3600):($2/c) notitle with points pt 7 lc rgb "web-green", \
     A=1.5946, a=1/5221.85, t0=70.52, f(x) notitle with lines lw 3 lc rgb "blue", \
     A=2.8363, a=1/3185.88, t0=95.12, f(x) notitle with lines lw 3 lc rgb "red", \
     A=3.0821, a=1/3070.87, t0=90.34, f(x) notitle with lines lw 3 lc rgb "web-green", \
     datos_2 using ($1/3600):($2/c) title "escalón 110V - horno abierto" with points pt 7 lc rgb "orange", \
     A=2.2212, a=1/1292.15, t0=77.5, f(x) title "E_{max}=2,22V {/Symbol t}=22 min" with lines lc rgb "orange" lw 3
