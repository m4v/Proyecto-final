#!/usr/bin/gnuplot

set term pngcairo enhanced solid size 1280,720 fontscale 1

set datafile separator ","
set decimalsign ","

set grid
#set rmargin 10
#set lmargin 1
#set tmargin 1
#set bmargin 0.5

datos_1 = "../osciloscopio_PWM_WA000007.CSV"
# las puntas estaba mal en x1 cuando eran x10
datos_2 = "../osciloscopio_PWM_WA000001.CSV"
datos_3 = "../osciloscopio_PWM_WA000002.CSV"

set output "horno_pwm1.png"

set xlabel "Tiempo [seg]"
set ylabel "Corriente [mA]"
set xrange [0:3]
set yrange [-5:30]


plot datos_2 using ($4+2):($5/22*10000) title "corriente optoacoplador" with lines lc rgb "blue"

set output "horno_pwm2.png"
plot datos_3 using ($4+1.2):($5/22*10000) title "corriente optoacoplador" with lines lc rgb "blue"

set xlabel "Tiempo [mseg]"
set ylabel "Tensión [V]"
set y2label "Corriente [mA]"
set ytics nomirror
set y2tics
set xrange [0:8]
set yrange [-0.1:0.8]
set y2range [-4.54:36.36]

set output "horno_pwm3.png"

plot datos_1 using ($4*1000+4):($5/22*1000) title "corriente optoacoplador" axes x1y2 with lines lc rgb "blue", \
     '' using ($4*1000+4):($6) title "tensión de base" with lines lc rgb "red"
