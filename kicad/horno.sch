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
Sheet 1 5
Title "Esquemático jerárquico"
Date "2016-08-27"
Rev "1"
Comp "Elián Hanisch - Rodrigo Oliver - Gastón Riera"
Comment1 "Cátedra de Proyecto Final"
Comment2 "Ingeniería Electrónica"
Comment3 "Universidad Nacional de La Plata"
Comment4 "Sistema de control digital para un horno de prótesis dentales"
$EndDescr
$Sheet
S 4300 2400 1150 3600
U 57C1B180
F0 "LPC1769" 60
F1 "LPC1769.sch" 60
F2 "AD0" I L 4300 3850 60 
F3 "AD1" I L 4300 3950 60 
F4 "PWM" O R 5450 3300 60 
F5 "S1" O R 5450 5050 60 
F6 "S2" O R 5450 5150 60 
F7 "S3" O R 5450 5250 60 
F8 "S4" O R 5450 5350 60 
F9 "GND" I R 5450 5900 60 
F10 "D0" B L 4300 4700 60 
F11 "D1" B L 4300 4800 60 
F12 "D2" B L 4300 4900 60 
F13 "D3" B L 4300 5000 60 
F14 "D4" B L 4300 5100 60 
F15 "D5" B L 4300 5200 60 
F16 "D6" B L 4300 5300 60 
F17 "D7" B L 4300 5400 60 
F18 "A0" O L 4300 5500 60 
F19 "RD" O L 4300 5600 60 
F20 "WD" O L 4300 5700 60 
F21 "CS" O L 4300 5800 60 
$EndSheet
$Sheet
S 2100 3700 1400 850 
U 57C2159A
F0 "LM35" 60
F1 "AmpLM35.sch" 60
F2 "+5V" I L 2100 3800 60 
F3 "-5V" I L 2100 3900 60 
F4 "GND" I L 2100 4450 60 
F5 "LM35_OUT" O R 3500 3950 60 
$EndSheet
$Sheet
S 2100 2700 1400 750 
U 57C52EB8
F0 "Termocupla" 60
F1 "AmpTermocupla.sch" 60
F2 "TERMOCUPLA_OUT" O R 3500 2800 60 
F3 "+5V" I L 2100 2800 60 
F4 "-5V" I L 2100 2900 60 
F5 "GND" I L 2100 3350 60 
$EndSheet
$Sheet
S 6300 4550 1100 1450
U 57C5E497
F0 "Motor paso a paso" 60
F1 "motorPP.sch" 60
F2 "S1" I L 6300 5050 60 
F3 "S2" I L 6300 5150 60 
F4 "S3" I L 6300 5250 60 
F5 "S4" I L 6300 5350 60 
$EndSheet
$Comp
L R R9
U 1 1 57C663FD
P 6000 3300
F 0 "R9" V 6080 3300 50  0000 C CNN
F 1 "R" V 6000 3300 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 5930 3300 50  0001 C CNN
F 3 "" H 6000 3300 50  0000 C CNN
	1    6000 3300
	0    1    1    0   
$EndComp
$Comp
L BC547 Q1
U 1 1 57C67500
P 6600 3300
F 0 "Q1" H 6800 3375 50  0000 L CNN
F 1 "BC547" H 6800 3300 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Narrow_Oval" H 6800 3225 50  0001 L CIN
F 3 "" H 6600 3300 50  0000 L CNN
	1    6600 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 57C67CA4
P 6700 3650
F 0 "#PWR01" H 6700 3400 50  0001 C CNN
F 1 "GND" H 6700 3500 50  0001 C CNN
F 2 "" H 6700 3650 50  0000 C CNN
F 3 "" H 6700 3650 50  0000 C CNN
	1    6700 3650
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P4
U 1 1 57C6822B
P 6950 2650
F 0 "P4" H 6950 2800 50  0000 C CNN
F 1 "CONN_01X02" V 7050 2650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 6950 2650 50  0001 C CNN
F 3 "" H 6950 2650 50  0000 C CNN
	1    6950 2650
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR02
U 1 1 57C682C4
P 6700 2300
F 0 "#PWR02" H 6700 2150 50  0001 C CNN
F 1 "+5V" H 6700 2440 50  0000 C CNN
F 2 "" H 6700 2300 50  0000 C CNN
F 3 "" H 6700 2300 50  0000 C CNN
	1    6700 2300
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X11 P7
U 1 1 57C3EF67
P 2350 6650
F 0 "P7" H 2350 7250 50  0000 C CNN
F 1 "CONN_02X11" V 2350 6650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x11" H 2350 5450 50  0001 C CNN
F 3 "" H 2350 5450 50  0000 C CNN
	1    2350 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3950 4300 3950
Wire Wire Line
	3500 2800 3850 2800
Wire Wire Line
	3850 2800 3850 3850
Wire Wire Line
	3850 3850 4300 3850
Wire Wire Line
	5450 3300 5850 3300
Wire Wire Line
	6150 3300 6400 3300
Wire Wire Line
	6700 3500 6700 3650
Wire Wire Line
	6700 2300 6700 2600
Wire Wire Line
	6700 2700 6700 3100
Wire Wire Line
	6700 2600 6750 2600
Wire Wire Line
	6750 2700 6700 2700
Wire Wire Line
	5450 5050 6300 5050
Wire Wire Line
	5450 5150 6300 5150
Wire Wire Line
	6300 5250 5450 5250
Wire Wire Line
	5450 5350 6300 5350
Wire Wire Line
	4300 4700 3650 4700
Wire Wire Line
	4300 4800 3650 4800
Wire Wire Line
	4300 4900 3650 4900
Wire Wire Line
	4300 5000 3650 5000
Wire Wire Line
	4300 5100 3650 5100
Text Label 3650 4700 0    60   ~ 0
LCD_D0
Text Label 3650 4800 0    60   ~ 0
LCD_D1
Text Label 3650 4900 0    60   ~ 0
LCD_D2
Text Label 3650 5000 0    60   ~ 0
LCD_D3
Text Label 3650 5100 0    60   ~ 0
LCD_D4
Wire Wire Line
	4300 5200 3650 5200
Wire Wire Line
	4300 5300 3650 5300
Wire Wire Line
	4300 5400 3650 5400
Text Label 3650 5200 0    60   ~ 0
LCD_D5
Text Label 3650 5300 0    60   ~ 0
LCD_D6
Text Label 3650 5400 0    60   ~ 0
LCD_D7
Wire Wire Line
	2100 6450 1650 6450
Text Label 1650 6450 0    60   ~ 0
LCD_D0
Wire Wire Line
	2100 6550 1650 6550
Wire Wire Line
	2100 6650 1650 6650
Wire Wire Line
	2100 6750 1650 6750
Wire Wire Line
	2600 6450 3050 6450
Text Label 3050 6450 2    60   ~ 0
LCD_D1
Wire Wire Line
	2600 6550 3050 6550
Wire Wire Line
	2600 6650 3050 6650
Wire Wire Line
	2600 6750 3050 6750
Text Label 3050 6550 2    60   ~ 0
LCD_D3
Text Label 3050 6650 2    60   ~ 0
LCD_D5
Text Label 3050 6750 2    60   ~ 0
LCD_D7
Text Label 1650 6550 0    60   ~ 0
LCD_D2
Text Label 1650 6650 0    60   ~ 0
LCD_D4
Text Label 1650 6750 0    60   ~ 0
LCD_D6
$EndSCHEMATC
