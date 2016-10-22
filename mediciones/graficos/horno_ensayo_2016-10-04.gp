#!/usr/bin/gnuplot

set term pngcairo enhanced solid size 1280,720 fontscale 1

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

datos_1 = "../captura_continua_04-Oct-2016_15:16:34.csv" # calentamiento
datos_2 = "../captura_continua_04-Oct-2016_18:50:57.csv" # enfriamiento

set xrange [0:540]
set yrange [0:3.24]
set y2range [0:1000]

set output "horno_ensayo_2016-10-04.png"
set title "Ensayo del horno - 04/10/2016"
set key bottom right

# respuesta a un escalón
f(x) = A*(1 - exp(-a*(x*60 - t0)))

plot datos_1 using ($1/60):($2) title "escalón 91V" with points pt 7 lc rgb "blue", \
     datos_2 using (($1+18123)/60):($2) notitle with points pt 7 lc rgb "blue", \
     datos_1 using ($1/60):3 title "tensión LM35 (temperatura no a escala)" with points pt 7 lc rgb "red", \
     datos_2 using (($1+18123)/60):3 notitle with points pt 7 lc rgb "red", \
     A=3.0821, a=1/3070.87, t0=90.34, f(x) title "E_{max}=3,08V {/Symbol t}=51 min" with lines lw 3 lc rgb "dark-grey"

