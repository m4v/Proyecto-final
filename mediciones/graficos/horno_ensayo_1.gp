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
set nokey

dv = 3.3/4096 # LSB
tm = 0.01     # periodo de muestreo
g = 81        # ganancia


set ytics nomirror
set y2label "Temperatura [°C]"
set y2tics

datos_1 = "../horno_primer_ensayo.csv"
datos_2 = "../captura_continua_28-Sep-2016.csv"
datos_3 = "../captura_continua_29-Sep-2016_20:00:26.csv"

set xrange [0:22]
set yrange [0:1.458]
set y2range [0:450]

set output "horno_ensayo_1.png"
set title "1º ensayo horno - 23/9/2016"
plot datos_1 using ($1*tm/60):($2*dv) with points lc rgb "blue", \
          '' using ($1*tm/60):($2*dv/g/40e-6) with points axes x1y2 pt 7 lc rgb "red"

set xrange [0:125]
set yrange [0:2.268]
set y2range [0:700]

set output "horno_ensayo_2.png"
set title "2º ensayo horno - escalón de 110V, horno abierto - 28/9/2016"

# los datos ya estan escalados
plot datos_2 using ($1/60):($2) with points lc rgb "blue", \
          '' using ($1/60):($2/g/40e-6) with points axes x1y2 pt 7 lc rgb "red"

set xrange [0:95]
set yrange [0:1.134]
set y2range [0:350]

set output "horno_ensayo_3.png"
set title "3º ensayo horno - escalón de 50V, horno cerrado - 29/9/2016"

# los datos ya estan escalados
plot datos_3 using ($1/60):($2) with points lc rgb "blue", \
          '' using ($1/60):($2/g/40e-6) with points axes x1y2 pt 7 lc rgb "red"
