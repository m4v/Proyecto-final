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
Title "Conexión LPCXpresso LPC1769"
Date "2016-09-11"
Rev "2"
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
F 1 "LPC1769" H 5650 2300 50  0000 C CNN
F 2 "Horno:Pin_Header_LPCXpresso_LPC1769" H 5400 3700 50  0001 C CNN
F 3 "" H 5400 3700 50  0000 C CNN
	1    5850 3700
	1    0    0    -1  
$EndComp
Text HLabel 4300 3800 0    60   Input ~ 0
AD_TERMOCUPLA
Text HLabel 4300 4500 0    60   Input ~ 0
AD_LM35
Wire Wire Line
	5100 3800 4300 3800
Text Notes 5350 2000 0    60   ~ 0
Sócalo de conexión de la placa de\ndesarrollo LPCXpresso LPC1769
Text HLabel 7100 3800 2    60   Output ~ 0
PWM
Wire Wire Line
	6600 3800 7100 3800
Text HLabel 7100 3200 2    60   Output ~ 0
S1
Text HLabel 7100 3400 2    60   Output ~ 0
S2
Text HLabel 7100 3500 2    60   Output ~ 0
S3
Text HLabel 7100 3300 2    60   Output ~ 0
S4
Wire Wire Line
	5100 4800 4300 4800
Wire Wire Line
	5100 4700 4300 4700
Text HLabel 7100 4000 2    60   BiDi ~ 0
D0
Text HLabel 7100 4100 2    60   BiDi ~ 0
D1
Text HLabel 7100 4200 2    60   BiDi ~ 0
D2
Text HLabel 7100 4300 2    60   BiDi ~ 0
D3
Text HLabel 7100 4400 2    60   BiDi ~ 0
D4
Text HLabel 7100 4500 2    60   BiDi ~ 0
D5
Text HLabel 7100 4600 2    60   BiDi ~ 0
D6
Text HLabel 7100 4700 2    60   BiDi ~ 0
D7
Wire Wire Line
	6600 3900 7100 3900
Wire Wire Line
	7100 4000 6600 4000
Wire Wire Line
	6600 4100 7100 4100
Wire Wire Line
	7100 4200 6600 4200
Wire Wire Line
	6600 4300 7100 4300
Wire Wire Line
	7100 4400 6600 4400
Wire Wire Line
	6600 4500 7100 4500
Wire Wire Line
	7100 4600 6600 4600
Text HLabel 7100 3900 2    60   Output ~ 0
A0
Text HLabel 7100 3600 2    60   Output ~ 0
RD
Text HLabel 7100 3700 2    60   Output ~ 0
WR
Wire Wire Line
	7100 4700 6600 4700
Wire Wire Line
	7100 4800 6600 4800
Wire Wire Line
	6600 4900 7100 4900
Text HLabel 7100 4800 2    60   Output ~ 0
CS
Wire Wire Line
	7100 3700 6600 3700
$Comp
L CONN_01X03 P8
U 1 1 57C92591
P 3100 3300
F 0 "P8" H 3100 3500 50  0000 C CNN
F 1 "UART" V 3200 3300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 3100 3300 50  0001 C CNN
F 3 "" H 3100 3300 50  0000 C CNN
	1    3100 3300
	-1   0    0    1   
$EndComp
Wire Wire Line
	3300 3400 3400 3400
Wire Wire Line
	3400 3400 3400 3500
$Comp
L GNDD #PWR045
U 1 1 57C92697
P 3400 3500
F 0 "#PWR045" H 3400 3250 50  0001 C CNN
F 1 "GNDD" H 3400 3350 50  0000 C CNN
F 2 "" H 3400 3500 50  0000 C CNN
F 3 "" H 3400 3500 50  0000 C CNN
	1    3400 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 4500 5100 4500
Wire Wire Line
	5100 3600 4300 3600
Wire Wire Line
	4300 3500 5100 3500
Wire Wire Line
	5100 3400 4300 3400
Wire Wire Line
	3300 3300 5100 3300
Wire Wire Line
	3300 3200 5100 3200
Wire Wire Line
	4300 3100 5100 3100
Wire Wire Line
	4300 3000 5100 3000
Wire Wire Line
	4300 2800 5100 2800
Wire Wire Line
	5100 2900 4300 2900
$Comp
L SW_PUSH SW1
U 1 1 57C95D09
P 3850 1800
F 0 "SW1" H 4000 1910 50  0000 C CNN
F 1 "RST" H 3850 1720 50  0000 C CNN
F 2 "Buttons_Switches_ThroughHole:SW_PUSH_6mm" H 3850 1800 50  0001 C CNN
F 3 "" H 3850 1800 50  0000 C CNN
	1    3850 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 1800 4400 1800
Wire Wire Line
	4400 1800 4400 2700
Wire Wire Line
	4400 2700 5100 2700
$Comp
L GNDD #PWR046
U 1 1 57C95D64
P 3550 1950
F 0 "#PWR046" H 3550 1700 50  0001 C CNN
F 1 "GNDD" H 3550 1800 50  0000 C CNN
F 2 "" H 3550 1950 50  0000 C CNN
F 3 "" H 3550 1950 50  0000 C CNN
	1    3550 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 1950 3550 1800
Wire Wire Line
	5100 4900 4300 4900
Wire Wire Line
	5100 5000 4300 5000
$Comp
L +5V #PWR047
U 1 1 57C9FF7B
P 4850 2200
F 0 "#PWR047" H 4850 2050 50  0001 C CNN
F 1 "+5V" H 4850 2340 50  0000 C CNN
F 2 "" H 4850 2200 50  0000 C CNN
F 3 "" H 4850 2200 50  0000 C CNN
	1    4850 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2200 4850 2500
Wire Wire Line
	4850 2500 5100 2500
NoConn ~ 5100 2600
NoConn ~ 6600 2800
NoConn ~ 6600 2900
NoConn ~ 6600 3000
NoConn ~ 6600 3100
Wire Wire Line
	6600 3200 7100 3200
Wire Wire Line
	7100 3300 6600 3300
Wire Wire Line
	7100 3400 6600 3400
Wire Wire Line
	7100 3500 6600 3500
Text Label 4300 5000 0    60   ~ 0
GPIO0
Text Label 4300 4900 0    60   ~ 0
GPIO1
Text Label 4300 4800 0    60   ~ 0
GPIO2
Text Label 4300 4700 0    60   ~ 0
GPIO3
Text Label 4300 4200 0    60   ~ 0
GPIO4
Text Label 4300 4100 0    60   ~ 0
GPIO5
Text Label 4300 4000 0    60   ~ 0
GPIO6
Text Label 4300 3600 0    60   ~ 0
GPIO7
Text Label 4300 3500 0    60   ~ 0
GPIO8
Text Label 4300 3400 0    60   ~ 0
GPIO9
Text Label 4300 3100 0    60   ~ 0
GPIO10
$Comp
L CONN_02X12 P9
U 1 1 57CA19E6
P 8800 2600
F 0 "P9" H 8800 3250 50  0000 C CNN
F 1 "GPIO" V 8800 2600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x12" H 8800 1400 50  0001 C CNN
F 3 "" H 8800 1400 50  0000 C CNN
	1    8800 2600
	1    0    0    -1  
$EndComp
Text Label 8200 2150 0    60   ~ 0
GPIO0
Wire Wire Line
	8200 2150 8550 2150
Wire Wire Line
	8550 2250 8200 2250
Wire Wire Line
	8200 2350 8550 2350
Wire Wire Line
	8200 2450 8550 2450
Wire Wire Line
	8200 2550 8550 2550
Wire Wire Line
	8200 2650 8550 2650
Wire Wire Line
	8550 2750 8200 2750
Wire Wire Line
	9400 2750 9050 2750
Wire Wire Line
	9400 2650 9050 2650
Wire Wire Line
	9050 2550 9400 2550
Wire Wire Line
	9400 2450 9050 2450
Wire Wire Line
	9400 2350 9050 2350
Wire Wire Line
	9400 2250 9050 2250
Wire Wire Line
	9400 2150 9050 2150
Text Label 8200 2250 0    60   ~ 0
GPIO2
Text Label 8200 2350 0    60   ~ 0
GPIO4
Text Label 8200 2450 0    60   ~ 0
GPIO6
Text Label 8200 2550 0    60   ~ 0
GPIO8
Text Label 8200 2650 0    60   ~ 0
GPIO10
Text Label 8200 2750 0    60   ~ 0
GPIO12
Text Label 9400 2150 2    60   ~ 0
GPIO1
Text Label 9400 2250 2    60   ~ 0
GPIO3
Text Label 9400 2350 2    60   ~ 0
GPIO5
Text Label 9400 2450 2    60   ~ 0
GPIO7
Text Label 9400 2550 2    60   ~ 0
GPIO9
Text Label 9400 2650 2    60   ~ 0
GPIO11
Text Label 9400 2750 2    60   ~ 0
GPIO13
$Comp
L GNDD #PWR048
U 1 1 57CA27ED
P 7800 2050
F 0 "#PWR048" H 7800 1800 50  0001 C CNN
F 1 "GNDD" H 7800 1900 50  0000 C CNN
F 2 "" H 7800 2050 50  0000 C CNN
F 3 "" H 7800 2050 50  0000 C CNN
	1    7800 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 2050 8550 2050
$Comp
L +3.3V #PWR049
U 1 1 57CA2D56
P 6850 2250
F 0 "#PWR049" H 6850 2100 50  0001 C CNN
F 1 "+3.3V" H 6850 2390 50  0000 C CNN
F 2 "" H 6850 2250 50  0000 C CNN
F 3 "" H 6850 2250 50  0000 C CNN
	1    6850 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 2250 6850 2400
Wire Wire Line
	6850 2400 6600 2400
$Comp
L +3.3V #PWR050
U 1 1 57CA2DC6
P 9050 1750
F 0 "#PWR050" H 9050 1600 50  0001 C CNN
F 1 "+3.3V" H 9050 1890 50  0000 C CNN
F 2 "" H 9050 1750 50  0000 C CNN
F 3 "" H 9050 1750 50  0000 C CNN
	1    9050 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 1750 9050 2050
Text Notes 8700 3800 0    60   ~ 0
Puertos de propósito general\naún sin aplicación.
Text Notes 2750 3000 0    60   ~ 0
Comunicación\nUART
$Comp
L GNDD #PWR051
U 1 1 57CD952B
P 4700 2400
F 0 "#PWR051" H 4700 2150 50  0001 C CNN
F 1 "GNDD" H 4700 2250 50  0000 C CNN
F 2 "" H 4700 2400 50  0000 C CNN
F 3 "" H 4700 2400 50  0000 C CNN
	1    4700 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 2400 4700 2400
Wire Wire Line
	6600 5000 7200 5000
Wire Wire Line
	6900 5000 6900 5300
$Comp
L GND #PWR052
U 1 1 57CDC8E9
P 6900 5300
F 0 "#PWR052" H 6900 5050 50  0001 C CNN
F 1 "GND" H 6900 5150 50  0000 C CNN
F 2 "" H 6900 5300 50  0000 C CNN
F 3 "" H 6900 5300 50  0000 C CNN
	1    6900 5300
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR053
U 1 1 57CF04C1
P 7200 5300
F 0 "#PWR053" H 7200 5050 50  0001 C CNN
F 1 "GNDA" H 7200 5150 50  0000 C CNN
F 2 "" H 7200 5300 50  0000 C CNN
F 3 "" H 7200 5300 50  0000 C CNN
	1    7200 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 5000 7200 5300
Connection ~ 6900 5000
Text HLabel 7100 4900 2    60   Output ~ 0
RST
Wire Wire Line
	7100 3600 6600 3600
Wire Wire Line
	5100 4000 4300 4000
Wire Wire Line
	5100 4100 4300 4100
Wire Wire Line
	5100 4200 4300 4200
Text Label 4300 3000 0    60   ~ 0
GPIO11
Text Label 4300 2900 0    60   ~ 0
GPIO12
Text Label 4300 2800 0    60   ~ 0
GPIO13
NoConn ~ 5100 4600
NoConn ~ 5100 4400
NoConn ~ 5100 4300
NoConn ~ 5100 3900
NoConn ~ 5100 3700
$Comp
L GNDD #PWR054
U 1 1 57D4E6A6
P 8300 3400
F 0 "#PWR054" H 8300 3150 50  0001 C CNN
F 1 "GNDD" H 8300 3250 50  0000 C CNN
F 2 "" H 8300 3400 50  0000 C CNN
F 3 "" H 8300 3400 50  0000 C CNN
	1    8300 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 3400 8300 3050
Wire Wire Line
	8300 3050 8550 3050
Wire Wire Line
	8550 3150 8300 3150
Connection ~ 8300 3150
$Comp
L GNDD #PWR055
U 1 1 57D4E7B5
P 9300 3400
F 0 "#PWR055" H 9300 3150 50  0001 C CNN
F 1 "GNDD" H 9300 3250 50  0000 C CNN
F 2 "" H 9300 3400 50  0000 C CNN
F 3 "" H 9300 3400 50  0000 C CNN
	1    9300 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 3400 9300 3050
Wire Wire Line
	9300 3050 9050 3050
Wire Wire Line
	9050 3150 9300 3150
Connection ~ 9300 3150
$Comp
L +5V #PWR056
U 1 1 57D4E97D
P 9600 2750
F 0 "#PWR056" H 9600 2600 50  0001 C CNN
F 1 "+5V" H 9600 2890 50  0000 C CNN
F 2 "" H 9600 2750 50  0000 C CNN
F 3 "" H 9600 2750 50  0000 C CNN
	1    9600 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 2750 9600 2950
Wire Wire Line
	9600 2950 9050 2950
Wire Wire Line
	9050 2850 9600 2850
Connection ~ 9600 2850
NoConn ~ 8550 2850
NoConn ~ 8550 2950
$EndSCHEMATC
