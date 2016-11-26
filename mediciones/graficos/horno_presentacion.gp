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

# grosor de las curvas
LW = 3

dv = 3.3/4096 # LSB
tm = 0.01     # periodo de muestreo
g = 81        # ganancia
c = 3.24e-3

datos_escalon = "../captura_continua_04-Oct-2016_151634.csv"
datos_pi = "../captura_PI_01-Nov-2016_173732.csv"

set xrange [0:5]
set yrange [0:1000]

set output "horno_presentacion_escalon.png"
set title "Respuesta al escalón de 91V"
set key bottom right

# respuesta a un escalón
f(x) = A/c*(1 - exp(-a*(x*3600 - t0)))

plot A=3.0821, a=1/3070.87, t0=90.34, f(x) title "T_{max}=951°C {/Symbol t}=51 minutos" with lines lw 18 lc rgb "grey", \
     datos_escalon using ($1/3600):($2/c) title "temperatura" with lines lw LW lc rgb "blue"

set output "horno_presentacion_pi.png"
set title "Ensayo de un PI"
set xlabel "Tiempo [minutos]"
set xrange [0:*] 
set yrange [0:1020]

plot datos_pi using (($1 - 450)/60):($5) title "referencia" with lines dashtype "--" lw LW lc rgb "blue", \
     datos_pi using (($1 - 450)/60):($2) title "temperatura" with lines lw LW lc rgb "red"

set output "horno_presentacion_pi_1.png"


set object 1 rect from graph 0,0 to grap 1,0.34 front fc rgb "light-blue" fillstyle transparent solid 0.7
set object 2 rect from graph 0,0.34 to grap 1,1 front fc rgb "light-red" fillstyle transparent solid 0.7
set label "baja temperatura" at graph 0.5, 0.17 center front font "Sans,15"
set label "alta temperatura" at graph 0.5, 0.67 center front font "Sans,15"

plot datos_pi using (($1 - 450)/60):($5) title "referencia" with lines dashtype "--" lw LW lc rgb "blue", \
     datos_pi using (($1 - 450)/60):($2) title "temperatura" with lines lw LW lc rgb "red"

unset object 1
unset object 2
unset label

# ----
 
set output "horno_presentacion_programa_1.png"
set title "Ensayo del controlador (1000 °C)"
datos = "../captura_programa_15-Nov-2016_173219.csv"
t0 = 95

set arrow from 0,32 to 9.3,200 dashtype "--" lw LW lc rgb "black" nohead

plot datos using (($1 - t0)/60):($1 < 600 ? 200 : $9) title "referencia" with lines dashtype "--" lw LW lc rgb "blue", \
     datos using (($1 - t0)/60):($2) title "temperatura" with lines lw LW lc rgb "red", \

unset arrow

set output "horno_presentacion_programa_2.png"
set multiplot

# gráfico grande
set size 1,1
set origin 0,0
unset grid

set arrow from 15,230 to 15,340 filled
set arrow from 40,970 to 40,830 filled

set object 1 rectangle center screen 0.355,0.55 size screen 0.36,0.3 front fc rgb "white" fs solid border rgb "white"
set object 1 rectangle center screen 0.765,0.55 size screen 0.36,0.3 front fc rgb "white" fs solid border rgb "white"

plot datos using (($1 - t0)/60):($1 < 600 ? 200 : $9) title "referencia" with lines dashtype "--" lw LW lc rgb "blue", \
     datos using (($1 - t0)/60):($2) title "temperatura" with lines lw LW lc rgb "red"


# zoom en secado
set size 0.45,0.4
set origin 0.13,0.35
set xrange [11:21]
set yrange [196:202]
set xlabel ""
set ylabel ""
set title ""
set nokey
set grid lw 2 lc rgb "black"
set ytics 0,2,1020
unset xtics
unset arrow
unset object 1

plot datos using (($1 - t0)/60):(200) title "referencia" with lines dashtype "--" lw LW lc rgb "blue", \
     "" using (($1 - t0)/60):($2) title "temperatura" with lines lw LW lc rgb "red"

# zoom en coccion
set size 0.45,0.4
set origin 0.54,0.35
set xrange [37.5:47.5]
set yrange [996:1003]

plot datos using (($1 - t0)/60):(1000) title "referencia" with lines dashtype "--" lw LW lc rgb "blue", \
     "" using (($1 - t0)/60):($2) title "temperatura" with lines lw LW lc rgb "red"

unset multiplot

# --

datos = "../captura_programa_10-Nov-2016_152524.csv"
t0 = 39

set output "horno_presentacion_programa_3.png"
set multiplot

# gráfico grande
set size 1,1
set origin 0,0
unset grid
set ytics autofreq
set xtics
set xrange [0:50]
set yrange [0:850]
set xlabel "Tiempo [minutos]"
set ylabel "Temperatura [°C]"
set title "Ensayo del controlador (800 °C)"
set key bottom right

set arrow from 15,230 to 15,340 filled
set arrow from 35,770 to 35,630 filled

set object 1 rectangle center screen 0.355,0.55 size screen 0.36,0.3 front fc rgb "white" fs solid border rgb "white"
set object 1 rectangle center screen 0.6,0.55 size screen 0.05,0.3 front fc rgb "white" fs solid border rgb "white"

plot datos using (($1 - t0)/60):($1 < 600 ? 200 : $9) title "referencia" with lines dashtype "--" lw LW lc rgb "blue", \
     datos using (($1 - t0)/60):($2) title "temperatura" with lines lw LW lc rgb "red"


# zoom en secado
set size 0.45,0.4
set origin 0.13,0.35
set xrange [11:21]
set yrange [196:202]
set xlabel ""
set ylabel ""
set title ""
set nokey
set grid lw 2 lc rgb "black"
set ytics 0,2,1020
unset xtics
unset arrow
unset object 1

plot datos using (($1 - t0)/60):(200) title "referencia" with lines dashtype "--" lw LW lc rgb "blue", \
     "" using (($1 - t0)/60):($2) title "temperatura" with lines lw LW lc rgb "red"

# zoom en coccion
set size 0.45,0.4
set origin 0.54,0.35
set xrange [33:43]
set ytics 0,4,1020
set yrange [796:808]

plot datos using (($1 - t0)/60):(800) title "referencia" with lines dashtype "--" lw LW lc rgb "blue", \
     "" using (($1 - t0)/60):($2) title "temperatura" with lines lw LW lc rgb "red"

unset multiplot

# --

datos = "../captura_programa_11-Nov-2016_175802.csv"
t0 = 528

set output "horno_presentacion_programa_4.png"
set title "Ensayo del controlador (primer ensayo con display)"

set size 1,1
set origin 0,0
set grid
set ytics autofreq
set xtics
set xrange [0:*]
set yrange [0:1050]
set xlabel "Tiempo [minutos]"
set ylabel "Temperatura [°C]"
set key bottom right

plot datos using (($1 - t0)/60):(($1 - t0) < 600 ? 200 : $9) title "referencia" with lines dashtype "--" lw LW lc rgb "blue", \
     datos using (($1 - t0)/60):($2) title "temperatura" with lines lw LW lc rgb "red"


set output "horno_presentacion_coccion.png"
set title "Cocción de una pieza cerámica"

datos = "../captura_coccion_23-Nov-2016_130902.csv"
t0 = 41

set multiplot title "Cocción de una pieza cerámica" layout 2,1

unset key
unset title
unset xlabel
set xrange [0:32]

set rmargin 1
set lmargin 8
set tmargin 0.5
set bmargin 0.5
set xtics format ""
set ylabel "Temp. [°C]" offset 1

plot datos using (($1 - t0)/60):($9) title "referencia" with lines dashtype "--" lw 3 lc rgb "blue", \
     "" using (($1 - t0)/60):($2) title "temperatura" with lines lw 3 lc rgb "red"

set xlabel "Tiempo [minutos]"
set ylabel "Ciclo de T. [%]" offset 0
set yrange [*:*]
set ytics -40,40,180
set xtics format "%.0f"

set tmargin 0
set bmargin 3

plot datos using (($1 - t0)/60):($1 > 1793 ? 0 : $7) title "salida PI" with lines lw 3 lc rgb "red", \
     "" using (($1 - t0)/60):($8) title "salida PI (saturada)" with lines lw 3 lc rgb "blue"

unset multiplot
