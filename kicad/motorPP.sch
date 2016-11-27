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
Sheet 5 5
Title "Driver del motor paso a paso"
Date "2016-08-28"
Rev "3"
Comp "Elián Hanisch - Rodrigo Oliver - Gastón Riera"
Comment1 "Cátedra de Proyecto Final"
Comment2 "Ingeniería Electrónica"
Comment3 "Universidad Nacional de La Plata"
Comment4 "Sistema de control digital para un horno de prótesis dentales"
$EndDescr
$Comp
L L293D U5
U 1 1 57C5E503
P 5950 3900
F 0 "U5" H 5550 4800 50  0000 L BNN
F 1 "L293D" H 5550 2900 50  0000 L BNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 5950 4050 50  0001 C CNN
F 3 "" H 5950 3900 60  0001 C CNN
	1    5950 3900
	1    0    0    -1  
$EndComp
Text HLabel 2450 3600 0    60   Input ~ 0
S1
Text HLabel 2450 3700 0    60   Input ~ 0
S2
Text HLabel 2450 3800 0    60   Input ~ 0
S3
Text HLabel 2450 3900 0    60   Input ~ 0
S4
$Comp
L CONN_01X05 P6
U 1 1 57C5E7CF
P 10000 3700
F 0 "P6" H 10000 4000 50  0000 C CNN
F 1 "Motor" V 10100 3700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x05" H 10000 3700 50  0001 C CNN
F 3 "" H 10000 3700 50  0000 C CNN
	1    10000 3700
	1    0    0    1   
$EndComp
$Comp
L GND #PWR63
U 1 1 57C5E8F6
P 9450 3900
F 0 "#PWR63" H 9450 3650 50  0001 C CNN
F 1 "GND" H 9450 3750 50  0000 C CNN
F 2 "" H 9450 3900 50  0000 C CNN
F 3 "" H 9450 3900 50  0000 C CNN
	1    9450 3900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR62
U 1 1 57C5EB75
P 7350 4150
F 0 "#PWR62" H 7350 3900 50  0001 C CNN
F 1 "GND" H 7350 4000 50  0000 C CNN
F 2 "" H 7350 4150 50  0000 C CNN
F 3 "" H 7350 4150 50  0000 C CNN
	1    7350 4150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR55
U 1 1 57C5EC02
P 4350 4150
F 0 "#PWR55" H 4350 3900 50  0001 C CNN
F 1 "GND" H 4350 4000 50  0000 C CNN
F 2 "" H 4350 4150 50  0000 C CNN
F 3 "" H 4350 4150 50  0000 C CNN
	1    4350 4150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR60
U 1 1 57C5EEC1
P 7200 2800
F 0 "#PWR60" H 7200 2650 50  0001 C CNN
F 1 "+5V" H 7200 2940 50  0000 C CNN
F 2 "" H 7200 2800 50  0000 C CNN
F 3 "" H 7200 2800 50  0000 C CNN
	1    7200 2800
	1    0    0    -1  
$EndComp
$Comp
L C_Small C14
U 1 1 57C5F150
P 7200 3400
F 0 "C14" H 7210 3470 50  0000 L CNN
F 1 "0,1uF" H 7210 3320 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 7200 3400 50  0001 C CNN
F 3 "" H 7200 3400 50  0000 C CNN
	1    7200 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR61
U 1 1 57C5F1E5
P 7200 3500
F 0 "#PWR61" H 7200 3250 50  0001 C CNN
F 1 "GND" H 7200 3350 50  0000 C CNN
F 2 "" H 7200 3500 50  0000 C CNN
F 3 "" H 7200 3500 50  0000 C CNN
	1    7200 3500
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR56
U 1 1 57C5F2BE
P 4650 4450
F 0 "#PWR56" H 4650 4300 50  0001 C CNN
F 1 "+24V" H 4650 4590 50  0000 C CNN
F 2 "" H 4650 4450 50  0000 C CNN
F 3 "" H 4650 4450 50  0000 C CNN
	1    4650 4450
	1    0    0    -1  
$EndComp
$Comp
L CP_Small C13
U 1 1 57C5F33D
P 4650 4750
F 0 "C13" H 4660 4820 50  0000 L CNN
F 1 "1uF" H 4660 4670 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L6_P2.5" H 4650 4750 50  0001 C CNN
F 3 "" H 4650 4750 50  0000 C CNN
	1    4650 4750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR57
U 1 1 57C5F38E
P 4650 4850
F 0 "#PWR57" H 4650 4600 50  0001 C CNN
F 1 "GND" H 4650 4700 50  0000 C CNN
F 2 "" H 4650 4850 50  0000 C CNN
F 3 "" H 4650 4850 50  0000 C CNN
	1    4650 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 3900 9800 3900
Wire Wire Line
	7350 4150 7350 3800
Wire Wire Line
	7350 3800 6550 3800
Wire Wire Line
	6550 4000 7350 4000
Connection ~ 7350 4000
Wire Wire Line
	4350 4150 4350 3800
Connection ~ 4350 4000
Wire Wire Line
	6550 3200 7200 3200
Wire Wire Line
	7200 2800 7200 3300
Wire Wire Line
	4650 4600 5350 4600
Wire Wire Line
	4650 4450 4650 4650
Wire Wire Line
	5100 4400 5350 4400
Wire Wire Line
	5100 4200 5350 4200
Connection ~ 4650 4600
Wire Wire Line
	4350 3800 5350 3800
Wire Wire Line
	5350 4000 4350 4000
Connection ~ 7200 3200
Wire Wire Line
	7050 4600 6550 4600
Wire Wire Line
	5350 2900 5350 3200
$Comp
L CONN_01X02 P5
U 1 1 57C6A8B7
P 10000 2250
F 0 "P5" H 10000 2400 50  0000 C CNN
F 1 "24V" V 10100 2250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 10000 2250 50  0001 C CNN
F 3 "" H 10000 2250 50  0000 C CNN
	1    10000 2250
	1    0    0    1   
$EndComp
$Comp
L +24V #PWR64
U 1 1 57C6A907
P 9700 1850
F 0 "#PWR64" H 9700 1700 50  0001 C CNN
F 1 "+24V" H 9700 1990 50  0000 C CNN
F 2 "" H 9700 1850 50  0000 C CNN
F 3 "" H 9700 1850 50  0000 C CNN
	1    9700 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 1850 9700 2200
Wire Wire Line
	9700 2200 9800 2200
$Comp
L GND #PWR65
U 1 1 57C6A966
P 9700 2550
F 0 "#PWR65" H 9700 2300 50  0001 C CNN
F 1 "GND" H 9700 2400 50  0000 C CNN
F 2 "" H 9700 2550 50  0000 C CNN
F 3 "" H 9700 2550 50  0000 C CNN
	1    9700 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 2550 9700 2300
Wire Wire Line
	9700 2300 9800 2300
Text Label 3050 3600 2    60   ~ 0
IN1
Text Label 3050 3700 2    60   ~ 0
IN2
Text Label 3050 3800 2    60   ~ 0
IN3
Text Label 3050 3900 2    60   ~ 0
IN4
Wire Wire Line
	2450 3600 3050 3600
Wire Wire Line
	3050 3700 2450 3700
Wire Wire Line
	2450 3800 3050 3800
Wire Wire Line
	3050 3900 2450 3900
Text Label 5100 3400 0    60   ~ 0
IN1
Text Label 5100 4400 0    60   ~ 0
IN2
Text Label 5100 3600 0    60   ~ 0
OUT1
Text Label 5100 4200 0    60   ~ 0
OUT2
Wire Wire Line
	5100 3400 5350 3400
Wire Wire Line
	5350 3600 5100 3600
Text Label 9250 3800 0    60   ~ 0
OUT1
Text Label 9250 3700 0    60   ~ 0
OUT2
Text Label 9250 3600 0    60   ~ 0
OUT3
Text Label 9250 3500 0    60   ~ 0
OUT4
Wire Wire Line
	9250 3500 9800 3500
Wire Wire Line
	9800 3600 9250 3600
Wire Wire Line
	9250 3700 9800 3700
Wire Wire Line
	9800 3800 9250 3800
$Comp
L +5V #PWR58
U 1 1 57C4777C
P 5350 2900
F 0 "#PWR58" H 5350 2750 50  0001 C CNN
F 1 "+5V" H 5350 3040 50  0000 C CNN
F 2 "" H 5350 2900 50  0000 C CNN
F 3 "" H 5350 2900 50  0000 C CNN
	1    5350 2900
	1    0    0    -1  
$EndComp
Text Label 6800 3600 2    60   ~ 0
OUT4
Wire Wire Line
	6800 3600 6550 3600
Text Label 6800 4200 2    60   ~ 0
OUT3
Text Label 6800 4400 2    60   ~ 0
IN3
Text Label 6800 3400 2    60   ~ 0
IN4
Wire Wire Line
	6800 3400 6550 3400
Wire Wire Line
	6550 4200 6800 4200
Wire Wire Line
	6550 4400 6800 4400
$Comp
L +5V #PWR59
U 1 1 57C47990
P 7050 4500
F 0 "#PWR59" H 7050 4350 50  0001 C CNN
F 1 "+5V" H 7050 4640 50  0000 C CNN
F 2 "" H 7050 4500 50  0000 C CNN
F 3 "" H 7050 4500 50  0000 C CNN
	1    7050 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 4500 7050 4600
Text Notes 9800 4300 0    60   ~ 0
Conector al \nmotor paso a paso
$EndSCHEMATC
