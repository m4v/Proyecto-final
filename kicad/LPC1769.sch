EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:memory
LIBS:microcontrollers
LIBS:dsp
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:siliconi
LIBS:opto
LIBS:contrib
LIBS:valves
LIBS:horno
LIBS:sensors
LIBS:stepper drivers
LIBS:horno-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
Title "Conexión LPCXpresso LPC1769"
Date "2016-08-27"
Rev "1"
Comp "Elián Hanisch - Rodrigo Oliver - Gastón Riera"
Comment1 "Cátedra de Proyecto Final"
Comment2 "Ingeniería Electrónica"
Comment3 "Universidad Nacional de La Plata"
Comment4 "Sistema de control digital para un horno de prótesis dentales"
$EndDescr
$Comp
L CONN_LPC1769 P1
U 1 1 57C1DC4C
P 5850 3700
F 0 "P1" H 5400 5100 50  0000 C CNN
F 1 "CONN_LPC1769" H 5650 2300 50  0000 C CNN
F 2 "" H 5400 3700 50  0001 C CNN
F 3 "" H 5400 3700 50  0000 C CNN
	1    5850 3700
	1    0    0    -1  
$EndComp
Text HLabel 7100 5000 2    60   Input ~ 0
GND
Wire Wire Line
	6450 5000 7100 5000
Text HLabel 4300 3800 0    60   Input ~ 0
AD0
Text HLabel 4300 3900 0    60   Input ~ 0
AD1
Wire Wire Line
	4300 3900 5200 3900
Wire Wire Line
	5200 3800 4300 3800
Text Notes 5350 2000 0    60   ~ 0
Sócalo de conexión de la placa de\ndesarrollo LPCXpresso LPC1769
Text HLabel 7100 3800 2    60   Output ~ 0
PWM
Wire Wire Line
	6450 3800 7100 3800
Text HLabel 4300 4600 0    60   Output ~ 0
S1
Text HLabel 4300 4700 0    60   Output ~ 0
S2
Text HLabel 4300 4800 0    60   Output ~ 0
S3
Text HLabel 4300 4900 0    60   Output ~ 0
S4
Wire Wire Line
	5200 4900 4300 4900
Wire Wire Line
	5200 4800 4300 4800
Wire Wire Line
	4300 4600 5200 4600
Wire Wire Line
	5200 4700 4300 4700
Text HLabel 7100 3900 2    60   BiDi ~ 0
D0
Text HLabel 7100 4000 2    60   BiDi ~ 0
D1
Text HLabel 7100 4100 2    60   BiDi ~ 0
D2
Text HLabel 7100 4200 2    60   BiDi ~ 0
D3
Text HLabel 7100 4300 2    60   BiDi ~ 0
D4
Text HLabel 7100 4400 2    60   BiDi ~ 0
D5
Text HLabel 7100 4500 2    60   BiDi ~ 0
D6
Text HLabel 7100 4600 2    60   BiDi ~ 0
D7
Wire Wire Line
	6450 3900 7100 3900
Wire Wire Line
	7100 4000 6450 4000
Wire Wire Line
	6450 4100 7100 4100
Wire Wire Line
	7100 4200 6450 4200
Wire Wire Line
	6450 4300 7100 4300
Wire Wire Line
	7100 4400 6450 4400
Wire Wire Line
	6450 4500 7100 4500
Wire Wire Line
	7100 4600 6450 4600
Text HLabel 7100 4700 2    60   Output ~ 0
A0
Text HLabel 7100 4800 2    60   Output ~ 0
RD
Text HLabel 7100 4900 2    60   Output ~ 0
WD
Wire Wire Line
	7100 4700 6450 4700
Wire Wire Line
	7100 4800 6450 4800
Wire Wire Line
	6450 4900 7100 4900
Text HLabel 7100 3700 2    60   Output ~ 0
CS
Wire Wire Line
	7100 3700 6450 3700
$EndSCHEMATC
