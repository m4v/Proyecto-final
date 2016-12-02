#!/usr/bin/gnuplot

set term pngcairo enhanced solid size 1280,720 font 'Verdana,25'

set datafile separator ","
set decimalsign ","
set border linecolor rgb 'black' linetype 1 linewidth 2
set grid lw 2 lc rgb 'black'
set key bottom right

# grosor de las curvas
LW = 2

datos = "../datos_ajuste_modelo_GS.csv"

set xrange [0:*]
set yrange [0:*]

set output "horno_informe_control_1.png"
unset title

set multiplot layout 2, 1

set lmargin 7
set bmargin 0.5
set tmargin 1.5

unset xlabel
set xtics format ""
set ylabel "Temp. [°C]" offset 1

plot datos using ($1/60):($3) title "temperatura" with lines lw LW

set bmargin 2.5
set tmargin 0.5

set xlabel "Tiempo [minutos]" offset 0,0.5
set xtics format "%.0f"
set ylabel "Ciclo de T. [%]" offset 1
#set ytics 0,20,100
set yrange [0:100]

plot datos using ($1/60):($2) title "ciclo de trabajo" with lines lw LW

unset multiplot

set tmargin 1.5
set bmargin 2.5
set yrange [0:*]
set output "horno_informe_control_2.png"
set xlabel "Tiempo [minutos]"
set ylabel "Temperatura [°C]"


plot datos using ($1/60):($3) title "ensayo" with lines lw LW lc rgb "blue", \
     ""    using ($1/60):($4) title "modelo" with lines lw LW lc rgb "red"


valid_1 = "../datos_validacion_modelo_GS_1.csv"
valid_2 = "../datos_validacion_modelo_GS_2.csv"
valid_3 = "../datos_validacion_modelo_GS_3.csv"
valid_4 = "../datos_validacion_modelo_GS_4.csv"

set output "horno_informe_control_3.png"

set multiplot layout 2,2

set tmargin 0.5
set bmargin 2
set lmargin 4.5
set rmargin 1

unset xlabel
unset ylabel

plot valid_1 using ($1/60):($3) title "ensayo" with lines lw LW lc rgb "blue", \
"" using ($1/60):($4) title "modelo" with lines lw LW lc rgb "red"


plot valid_2 using ($1/60):($3) title "ensayo" with lines lw LW lc rgb "blue", \
"" using ($1/60):($4) title "modelo" with lines lw LW lc rgb "red"

plot valid_3 using ($1/60):($3) title "ensayo" with lines lw LW lc rgb "blue", \
"" using ($1/60):($4) title "modelo" with lines lw LW lc rgb "red"

plot valid_4 using ($1/60):($3) title "ensayo" with lines lw LW lc rgb "blue", \
"" using ($1/60):($4) title "modelo" with lines lw LW lc rgb "red"

unset multiplot

datos = "../datos_ajuste_modelo_GC.csv"

set tmargin 1.5
set bmargin 2.5
set lmargin -1
set rmargin -1
set yrange [*:*]
set output "horno_informe_control_4.png"
set xlabel "Tiempo [minutos]" offset 0,0.5
set ylabel "Temperatura [°C]"

plot datos using ($1/60):($3) title "ensayo" with lines lw LW lc rgb "blue", \
     ""    using ($1/60):($4) title "modelo" with lines lw LW lc rgb "red"


valid_1 = "../datos_validacion_modelo_GC_1.csv"

set output "horno_informe_control_5.png"

plot valid_1 using ($1/60):($3) title "ensayo" with lines lw LW lc rgb "blue", \
     ""    using ($1/60):($4) title "modelo" with lines lw LW lc rgb "red"

datos = "../simulacion_alta_temperatura_1.csv"
set output "horno_informe_control_6.png"
set multiplot

set size 1,1
set origin 0,0
set key top left
unset grid

set xrange [0:25]

plot datos using ($1/60):($2) title "referencia" with lines lw LW dashtype "--", \
     ""    using ($1/60):($3) title "simulación" with lines lw LW lc rgb "blue", \
     ""    using ($1/60):($4) title "ensayo" with lines lw LW lc rgb "red"
# zoom
unset xlabel
unset ylabel
unset key
set size 0.5,0.6
set origin 0.45,0.1
set xrange [16:25]
set yrange [995:1005]
set xtics 15,2,25
set grid

replot

unset multiplot

datos = "../simulacion_alta_temperatura_2.csv"
set output "horno_informe_control_7.png"
set multiplot

set size 1,1
set origin 0,0
unset grid
set key top left
set yrange [*:*]
set xrange [0:20]
set xtics autofreq
set xlabel "Tiempo [minutos]" offset 0,0.5
set ylabel "Temperatura [°C]"

plot datos using ($1/60):($2) title "referencia" with lines lw LW dashtype "--", \
     ""    using ($1/60):($3) title "simulación" with lines lw LW lc rgb "blue", \
     ""    using ($1/60):($4) title "ensayo" with lines lw LW lc rgb "red"
# zoom
unset xlabel
unset ylabel
unset key
set size 0.5,0.6
set origin 0.45,0.1
set xrange [12:20]
set yrange [795:808]
set xtics 0,2,25
set grid

replot
unset multiplot

datos = "../simulacion_baja_temperatura_2.csv"
set output "horno_informe_control_8.png"
set multiplot

set size 1,1
set origin 0,0
unset grid
set key top left
set yrange [*:*]
set xrange [0:21]
set xtics autofreq
set xlabel "Tiempo [minutos]" offset 0,0.5
set ylabel "Temperatura [°C]"

plot datos using ($1/60):(200) title "referencia" with lines lw LW dashtype "--", \
     ""    using ($1/60):($3) title "temperatura" with lines lw LW lc rgb "red", \
     ""    using ($1/60):($2) title "simulación" with lines lw LW lc rgb "blue"

# zoom
unset xlabel
unset ylabel
unset key
set size 0.5,0.6
set origin 0.45,0.1
set xrange [11:21]
set yrange [195:203]
set xtics 0,2,25
set ytics 0,2,210
set grid

replot

unset multiplot

set size 1,1
set origin 0,0
set xlabel "Tiempo [minutos]" offset 0,0.5
set ylabel "Temperatura [°C]"
set xrange [0:*]
set yrange [0:*]
set xtics autofreq
set ytics autofreq
set key bottom right

set output "horno_informe_control_9.png"
datos = "../simulacion_baja_temperatura_1.csv"

plot datos using ($1/60):($2) title "C_s(s) con ref. cond. y anti-windup" with lines lw LW, \
     ""    using ($1/60):($3) title "control PI con ref. cond." with lines lw LW, \
     ""    using ($1/60):($4) title "control PI solamente" with lines lw LW

c = 3.24e-3
datos_escalon = "../captura_continua_04-Oct-2016_151634.csv"
datos_pi = "../captura_PI_01-Nov-2016_173732.csv"

set xlabel "Tiempo [horas]" offset 0,0.5
set xrange [0:5]
set yrange [0:1000]
set xtics autofreq
set ytics autofreq
set xtics add ("{/Symbol t}" 0.85)
set ytics add ("T_{max}" 951)

set output "horno_informe_control_10.png"
set key bottom right

# respuesta a un escalón
f(x) = A/c*(1 - exp(-a*(x*3600 - t0)))

set arrow from 0,0 to 0.85,951 nohead lw LW dashtype "--" lc rgb "blue"
set arrow from 0.85,951 to 0.85,0 nohead lw LW dashtype "--" lc rgb "blue"

plot datos_escalon using ($1/3600):($2/c) title "temperatura" with lines lw LW lc rgb "red", \
A=3.0821, a=1/3070.87, t0=90.34, f(x) title "ajuste" with lines lw LW lc rgb "black", \
     951 notitle with lines dashtype "--" lw LW lc rgb "blue"

unset arrow

set output "horno_informe_control_11.png"
set xlabel "Tiempo [minutos]" offset 0,0.5
set xrange [0:*] 
set yrange [0:1020]
set xtics autofreq
set ytics autofreq

plot datos_pi using (($1 - 450)/60):($5) title "referencia" with lines dashtype "--" lw LW lc rgb "blue", \
     datos_pi using (($1 - 450)/60):($2) title "temperatura" with lines lw LW lc rgb "red"

set output "horno_informe_control_12.png"
unset key

set object 1 rect from graph 0,0 to grap 1,0.34 front fc rgb "light-blue" fillstyle transparent solid 0.7
set object 2 rect from graph 0,0.34 to grap 1,1 front fc rgb "light-red" fillstyle transparent solid 0.7
set label "modelo de baja temperatura (secado)\nC_s(s) y G_s(s)" at graph 0.5, 0.17 center front font "Sans,25"
set label "modelo de alta temperatura (curado)\nC_c(s) y G_c(s)" at graph 0.5, 0.67 center front font "Sans,25"
set ytics add (350)
unset xlabel
set xtics format ""

plot datos_pi using (($1 - 450)/60):($5) title "referencia" with lines dashtype "--" lw LW lc rgb "blue", \
     datos_pi using (($1 - 450)/60):($2) title "temperatura" with lines lw LW lc rgb "red"

unset object 1
unset object 2
unset label

set output "horno_informe_control_13.png"

set xrange [0:15]
set yrange [0:250]
set xtics autofreq format "%.0f"
set ytics autofreq
set xlabel "Tiempo [minutos]" offset 0,0.5
set key

plot 200 title "referencia" with lines dashtype "--" lw LW, \
     x > 10 ? 200 : x*20 title "ref. condicionada" with lines lw LW
