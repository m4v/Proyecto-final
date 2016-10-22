#!/usr/bin/gnuplot

set term pngcairo enhanced solid size 1280,720 fontscale 2

set datafile separator ","
set decimalsign ","

set grid
set rmargin 10
#set lmargin 1
set tmargin 1
set bmargin 0.5

set output "grafico_circuito_continua.png"
set nokey

dv = 3.3/4096
m = 0.006 # altura de eje Y es 2m

datos_lm35 = "lm35_1.csv"
mean_lm35 = 1.7134
st_lm35 = 0.0026786

datos_lm35_circuito = "lm35_circuito.csv"
mean_lm35_circuito = 1.8285
st_lm35_circuito = 0.0011675

datos_pilaAA2 = "pila_AA_sin_proto_2.csv"
mean_pilaAA2 = 1.5729
st_pilaAA2 = 0.0016863

set label "Valor\nmedio" at character 2,18
set label "Dispersión\n4{/Symbol s}" at character 55,18
set xtics format ""
set ytics format "%.2fV"


set multiplot
set size 1, 1./3

set tmargin 2
set origin 0, 2./3
mean = mean_lm35
st = st_lm35
set yrange [mean-m:mean+m]
set ytics ("" mean-2*st, mean, "" mean+2*st) out
set arrow from 1025,mean-2*st to 1025,mean+2*st heads filled
set label "10,7mV\n13 LSB" at 1040,mean
set title "Amp. LM35 en placa perforada" offset 0, -1 
plot datos_lm35 using ($1/0.1):($2*dv) with points pt 7 lc rgb "purple"

set tmargin 1
set origin 0, 0
mean = mean_lm35_circuito
st = st_lm35_circuito
set yrange [mean-m:mean+m]
set ytics ("" mean-2*st, mean, "" mean+2*st) out
set arrow from 1025,mean-2*st to 1025,mean+2*st heads filled
set label "4,7mV\n6 LSB" at 1040,mean
set title "Amp. LM35 en PCB"
plot datos_lm35_circuito using ($1):($2*dv) with points pt 7 lc rgb "red"

set origin 0, 1./3
mean = mean_pilaAA2
st = st_pilaAA2
set yrange [mean-m:mean+m]
set ytics ("" mean-2*st, mean, "" mean+2*st) out
set arrow from 1025,mean-2*st to 1025,mean+2*st heads filled
set label "6,7mV\n8 LSB" at 1040,mean
set title "pila AA con cable corto"
plot datos_pilaAA2 using 1:($2*dv) with points pt 7 lc rgb "purple"

unset multiplot
