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

datos_3 = "../captura_continua_29-Sep-2016_200026.csv"
datos_4 = "../captura_continua_30-Sep-2016_193235.csv"
datos_5 = "../captura_continua_04-Oct-2016_151634.csv"

set xrange [0:300]
set yrange [0:3.24]
set y2range [0:1000]

set output "horno_ensayos_con_ajuste.png"
set title "Ensayos del horno con puerta cerrada"
set key bottom right

# respuesta a un escalón
f(x) = A*(1 - exp(-a*(x*60 - t0)))

plot datos_3 using ($1/60):($2) title "escalón 50V" with points pt 7 lc rgb "blue", \
     datos_4 using ($1/60):($2) title "escalón 86V" with points pt 7 lc rgb "red", \
     datos_5 using ($1/60):($2) title "escalón 91V" with points pt 7 lc rgb "web-green", \
     A=1.5946, a=1/5221.85, t0=70.52, f(x) title "E_{max}=1,59V {/Symbol t}=87 min" with lines lw 2 lc rgb "purple", \
     A=2.8363, a=1/3185.88, t0=95.12, f(x) title "E_{max}=2,84V {/Symbol t}=53 min" with lines lw 2 lc rgb "orange", \
     A=3.0821, a=1/3070.87, t0=90.34, f(x) title "E_{max}=3,08V {/Symbol t}=51 min" with lines lw 2 lc rgb "dark-green"

