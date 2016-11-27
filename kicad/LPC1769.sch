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
Sheet 4 5
Title "Conexión LPCXpresso LPC1769"
Date "2016-11-26"
Rev "3"
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
Text HLabel 4300 4500 0    60   Input ~ 0
AD_LM35
Text Notes 5350 2000 0    60   ~ 0
Sócalo de conexión de la placa de\ndesarrollo LPCXpresso LPC1769
Text HLabel 7100 3800 2    60   Output ~ 0
PWM
Text HLabel 7100 3200 2    60   Output ~ 0
S1
Text HLabel 7100 3400 2    60   Output ~ 0
S2
Text HLabel 7100 3500 2    60   Output ~ 0
S3
Text HLabel 7100 3300 2    60   Output ~ 0
S4
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
Text HLabel 7100 3900 2    60   Output ~ 0
A0
Text HLabel 7100 3600 2    60   Output ~ 0
RD
Text HLabel 7100 3700 2    60   Output ~ 0
WR
Text HLabel 7100 4800 2    60   Output ~ 0
CS
$Comp
L CONN_01X03 P8
U 1 1 57C92591
P 1400 3300
F 0 "P8" H 1400 3500 50  0000 C CNN
F 1 "UART" V 1500 3300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 1400 3300 50  0001 C CNN
F 3 "" H 1400 3300 50  0000 C CNN
	1    1400 3300
	-1   0    0    1   
$EndComp
$Comp
L GNDD #PWR46
U 1 1 57C92697
P 1700 3500
F 0 "#PWR46" H 1700 3250 50  0001 C CNN
F 1 "GNDD" H 1700 3350 50  0000 C CNN
F 2 "" H 1700 3500 50  0000 C CNN
F 3 "" H 1700 3500 50  0000 C CNN
	1    1700 3500
	1    0    0    -1  
$EndComp
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
$Comp
L GNDD #PWR47
U 1 1 57C95D64
P 3550 1950
F 0 "#PWR47" H 3550 1700 50  0001 C CNN
F 1 "GNDD" H 3550 1800 50  0000 C CNN
F 2 "" H 3550 1950 50  0000 C CNN
F 3 "" H 3550 1950 50  0000 C CNN
	1    3550 1950
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR49
U 1 1 57C9FF7B
P 4850 2200
F 0 "#PWR49" H 4850 2050 50  0001 C CNN
F 1 "+5V" H 4850 2340 50  0000 C CNN
F 2 "" H 4850 2200 50  0000 C CNN
F 3 "" H 4850 2200 50  0000 C CNN
	1    4850 2200
	1    0    0    -1  
$EndComp
NoConn ~ 5100 2600
NoConn ~ 6600 2800
NoConn ~ 6600 2900
NoConn ~ 6600 3000
NoConn ~ 6600 3100
$Comp
L +3.3V #PWR50
U 1 1 57CA2D56
P 6850 2250
F 0 "#PWR50" H 6850 2100 50  0001 C CNN
F 1 "+3.3V" H 6850 2390 50  0000 C CNN
F 2 "" H 6850 2250 50  0000 C CNN
F 3 "" H 6850 2250 50  0000 C CNN
	1    6850 2250
	1    0    0    -1  
$EndComp
Text Notes 1350 3050 0    60   ~ 0
Comunicación\nUART
$Comp
L GNDD #PWR48
U 1 1 57CD952B
P 4700 2400
F 0 "#PWR48" H 4700 2150 50  0001 C CNN
F 1 "GNDD" H 4700 2250 50  0000 C CNN
F 2 "" H 4700 2400 50  0000 C CNN
F 3 "" H 4700 2400 50  0000 C CNN
	1    4700 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR51
U 1 1 57CDC8E9
P 6900 5300
F 0 "#PWR51" H 6900 5050 50  0001 C CNN
F 1 "GND" H 6900 5150 50  0000 C CNN
F 2 "" H 6900 5300 50  0000 C CNN
F 3 "" H 6900 5300 50  0000 C CNN
	1    6900 5300
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR52
U 1 1 57CF04C1
P 7200 5300
F 0 "#PWR52" H 7200 5050 50  0001 C CNN
F 1 "GNDA" H 7200 5150 50  0000 C CNN
F 2 "" H 7200 5300 50  0000 C CNN
F 3 "" H 7200 5300 50  0000 C CNN
	1    7200 5300
	1    0    0    -1  
$EndComp
Text HLabel 4300 3800 0    60   Input ~ 0
AD_TERMOCUPLA
Text HLabel 4300 3100 0    60   Output ~ 0
KEY_F4
Text HLabel 4300 3000 0    60   Output ~ 0
KEY_F3
Text HLabel 4300 2900 0    60   Output ~ 0
KEY_F2
Text HLabel 4300 2800 0    60   Output ~ 0
KEY_F1
Text HLabel 4300 4600 0    60   Input ~ 0
KEY_C2
Text HLabel 4300 4400 0    60   Input ~ 0
KEY_C1
Text HLabel 4300 4100 0    60   Input ~ 0
FIN_CARRERA
Text HLabel 4300 4000 0    60   Input ~ 0
KEY_C4
Text HLabel 4300 3900 0    60   Input ~ 0
KEY_C3
Wire Wire Line
	5100 3800 4300 3800
Wire Wire Line
	6600 3800 7100 3800
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
Wire Wire Line
	7100 4700 6600 4700
Wire Wire Line
	7100 4800 6600 4800
Wire Wire Line
	7100 3700 6600 3700
Wire Wire Line
	1600 3400 1700 3400
Wire Wire Line
	1700 3400 1700 3500
Wire Wire Line
	4300 4500 5100 4500
Wire Wire Line
	4300 3100 5100 3100
Wire Wire Line
	4300 3000 5100 3000
Wire Wire Line
	4300 2800 5100 2800
Wire Wire Line
	5100 2900 4300 2900
Wire Wire Line
	4150 1800 4400 1800
Wire Wire Line
	4400 1800 4400 2700
Wire Wire Line
	4400 2700 5100 2700
Wire Wire Line
	3550 1950 3550 1800
Wire Wire Line
	4850 2200 4850 2500
Wire Wire Line
	4850 2500 5100 2500
Wire Wire Line
	6600 3200 7100 3200
Wire Wire Line
	7100 3300 6600 3300
Wire Wire Line
	7100 3400 6600 3400
Wire Wire Line
	7100 3500 6600 3500
Wire Wire Line
	6850 2250 6850 2400
Wire Wire Line
	6850 2400 6600 2400
Wire Wire Line
	5100 2400 4700 2400
Wire Wire Line
	6600 5000 7200 5000
Wire Wire Line
	6900 5000 6900 5300
Wire Wire Line
	7200 5000 7200 5300
Connection ~ 6900 5000
Wire Wire Line
	7100 3600 6600 3600
Wire Wire Line
	5100 4000 4300 4000
Wire Wire Line
	5100 4100 4300 4100
Wire Wire Line
	5100 3900 4300 3900
Wire Wire Line
	5100 4400 4300 4400
Wire Wire Line
	5100 4600 4300 4600
NoConn ~ 5100 3400
NoConn ~ 5100 3500
NoConn ~ 5100 3600
NoConn ~ 5100 3700
NoConn ~ 5100 4200
NoConn ~ 5100 4300
NoConn ~ 5100 4700
NoConn ~ 5100 4800
NoConn ~ 5100 4900
NoConn ~ 5100 5000
Wire Wire Line
	5100 3200 4300 3200
Wire Wire Line
	4300 3300 5100 3300
Text Label 4300 3200 0    60   ~ 0
UART_TX
Text Label 4300 3300 0    60   ~ 0
UART_RX
Text Label 2000 3200 2    60   ~ 0
UART_TX
Text Label 2000 3300 2    60   ~ 0
UART_RX
Wire Wire Line
	1600 3200 2000 3200
Wire Wire Line
	2000 3300 1600 3300
NoConn ~ 6600 4900
$Comp
L BC547 Q2
U 1 1 583A29DB
P 8850 2400
F 0 "Q2" H 9050 2475 50  0000 L CNN
F 1 "BC547" H 9050 2400 50  0000 L CNN
F 2 "TO-92" H 9050 2325 50  0001 L CIN
F 3 "" H 8850 2400 50  0000 L CNN
	1    8850 2400
	1    0    0    -1  
$EndComp
$Comp
L R R13
U 1 1 583A2A40
P 8950 1900
F 0 "R13" V 9030 1900 50  0000 C CNN
F 1 "220" V 8950 1900 50  0000 C CNN
F 2 "" V 8880 1900 50  0000 C CNN
F 3 "" H 8950 1900 50  0000 C CNN
	1    8950 1900
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 583A2AB1
P 8950 1350
F 0 "D1" H 8950 1450 50  0000 C CNN
F 1 "LED" H 8950 1250 50  0000 C CNN
F 2 "" H 8950 1350 50  0000 C CNN
F 3 "" H 8950 1350 50  0000 C CNN
	1    8950 1350
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR53
U 1 1 583A2AF6
P 8950 1000
F 0 "#PWR53" H 8950 850 50  0001 C CNN
F 1 "+5V" H 8950 1140 50  0000 C CNN
F 2 "" H 8950 1000 50  0000 C CNN
F 3 "" H 8950 1000 50  0000 C CNN
	1    8950 1000
	1    0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 583A35FD
P 8200 2400
F 0 "R12" V 8280 2400 50  0000 C CNN
F 1 "10k" V 8200 2400 50  0000 C CNN
F 2 "" V 8130 2400 50  0000 C CNN
F 3 "" H 8200 2400 50  0000 C CNN
	1    8200 2400
	0    1    1    0   
$EndComp
$Comp
L GND #PWR54
U 1 1 583A3630
P 8950 3000
F 0 "#PWR54" H 8950 2750 50  0001 C CNN
F 1 "GND" H 8950 2850 50  0000 C CNN
F 2 "" H 8950 3000 50  0000 C CNN
F 3 "" H 8950 3000 50  0000 C CNN
	1    8950 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 3000 8950 2600
Wire Wire Line
	8950 2200 8950 2050
Wire Wire Line
	8950 1750 8950 1550
Wire Wire Line
	8950 1000 8950 1150
Wire Wire Line
	8650 2400 8350 2400
Wire Wire Line
	8050 2400 7050 2400
Wire Wire Line
	7050 2400 7050 3800
Connection ~ 7050 3800
Text Notes 9050 2700 0    60   ~ 0
Indicador del PWM
$EndSCHEMATC
