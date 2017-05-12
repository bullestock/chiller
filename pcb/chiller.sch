EESchema Schematic File Version 2
LIBS:chiller-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:tinkerforge
LIBS:arduino
LIBS:maxim
LIBS:relays
LIBS:chiller-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LCD-20X4 U2
U 1 1 582F6D65
P 9100 2200
F 0 "U2" H 9100 3100 60  0000 C CNN
F 1 "LCD-20X4" H 9150 1350 60  0000 C CNN
F 2 "" H 9100 2200 60  0000 C CNN
F 3 "" H 9100 2200 60  0000 C CNN
	1    9100 2200
	1    0    0    -1  
$EndComp
$Comp
L ARDUINO_PRO_MINI_5V IC1
U 1 1 582F6DE8
P 7500 2450
F 0 "IC1" H 7950 3250 60  0000 C CNN
F 1 "ARDUINO NANO" V 7500 2600 60  0000 C CNN
F 2 "" H 7500 2450 60  0000 C CNN
F 3 "" H 7500 2450 60  0000 C CNN
	1    7500 2450
	1    0    0    1   
$EndComp
Wire Wire Line
	8300 2450 8950 2450
Wire Wire Line
	8950 2550 8300 2550
Wire Wire Line
	8300 2650 8950 2650
Wire Wire Line
	8950 2750 8300 2750
Wire Wire Line
	8500 1100 8700 1100
Wire Wire Line
	8700 1100 8700 1650
Wire Wire Line
	8700 1650 8950 1650
$Comp
L GND #PWR16
U 1 1 582F6EE9
P 8350 1350
F 0 "#PWR16" H 8350 1100 50  0001 C CNN
F 1 "GND" H 8350 1200 50  0000 C CNN
F 2 "" H 8350 1350 50  0000 C CNN
F 3 "" H 8350 1350 50  0000 C CNN
	1    8350 1350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR15
U 1 1 582F6F03
P 8350 850
F 0 "#PWR15" H 8350 700 50  0001 C CNN
F 1 "+5V" H 8350 990 50  0000 C CNN
F 2 "" H 8350 850 50  0000 C CNN
F 3 "" H 8350 850 50  0000 C CNN
	1    8350 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 850  8350 950 
Wire Wire Line
	8350 1250 8350 1350
Wire Wire Line
	6150 900  8800 900 
Wire Wire Line
	8800 900  8800 2850
Wire Wire Line
	8800 1550 8950 1550
Connection ~ 8350 900 
Wire Wire Line
	8350 1300 8900 1300
Wire Wire Line
	8900 1300 8900 1850
Wire Wire Line
	8900 1450 8950 1450
Connection ~ 8350 1300
Wire Wire Line
	8950 1750 8550 1750
Wire Wire Line
	8550 1750 8550 2850
Wire Wire Line
	8550 2850 8300 2850
Wire Wire Line
	8300 2350 8650 2350
Wire Wire Line
	8650 2350 8650 1950
Wire Wire Line
	8650 1950 8950 1950
Wire Wire Line
	8900 1850 8950 1850
Connection ~ 8900 1450
NoConn ~ 8950 2050
NoConn ~ 8950 2150
NoConn ~ 8950 2250
NoConn ~ 8950 2350
Wire Wire Line
	8800 2850 8950 2850
Connection ~ 8800 1550
$Comp
L GND #PWR17
U 1 1 582F70AB
P 8800 3150
F 0 "#PWR17" H 8800 2900 50  0001 C CNN
F 1 "GND" H 8800 3000 50  0000 C CNN
F 2 "" H 8800 3150 50  0000 C CNN
F 3 "" H 8800 3150 50  0000 C CNN
	1    8800 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 3150 8800 2950
Wire Wire Line
	8450 2950 8950 2950
NoConn ~ 7250 1500
NoConn ~ 7350 1500
NoConn ~ 7450 1500
NoConn ~ 7550 1500
NoConn ~ 7650 1500
NoConn ~ 7750 1500
NoConn ~ 8300 2050
Wire Wire Line
	8300 2150 8450 2150
Wire Wire Line
	8450 2150 8450 2950
Connection ~ 8800 2950
Wire Wire Line
	6150 900  6150 2150
Wire Wire Line
	6150 2150 6650 2150
NoConn ~ 6650 2050
NoConn ~ 6650 1850
$Comp
L GND #PWR12
U 1 1 582F7183
P 6300 1950
F 0 "#PWR12" H 6300 1700 50  0001 C CNN
F 1 "GND" H 6300 1800 50  0000 C CNN
F 2 "" H 6300 1950 50  0000 C CNN
F 3 "" H 6300 1950 50  0000 C CNN
	1    6300 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 1950 6650 1950
$Comp
L GND #PWR9
U 1 1 582F736C
P 5200 4350
F 0 "#PWR9" H 5200 4100 50  0001 C CNN
F 1 "GND" H 5200 4200 50  0000 C CNN
F 2 "" H 5200 4350 50  0000 C CNN
F 3 "" H 5200 4350 50  0000 C CNN
	1    5200 4350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR6
U 1 1 582F738A
P 3650 1950
F 0 "#PWR6" H 3650 1800 50  0001 C CNN
F 1 "+5V" H 3650 2090 50  0000 C CNN
F 2 "" H 3650 1950 50  0000 C CNN
F 3 "" H 3650 1950 50  0000 C CNN
	1    3650 1950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5400 1950 5400 3950
Wire Wire Line
	5400 3150 4500 3150
Wire Wire Line
	4500 2400 5400 2400
Connection ~ 5400 2400
Wire Wire Line
	4500 2600 5800 2600
Wire Wire Line
	4500 3350 5200 3350
Connection ~ 5200 3350
Wire Wire Line
	5200 4150 4500 4150
Connection ~ 5200 4150
Wire Wire Line
	5400 3950 4500 3950
Connection ~ 5400 3150
Wire Wire Line
	8300 2250 8400 2250
Wire Wire Line
	8300 2950 8300 3700
Wire Wire Line
	8300 3700 5550 3700
Wire Wire Line
	5550 3700 5550 3250
Wire Wire Line
	5550 3250 4500 3250
Wire Wire Line
	6650 2950 5550 2950
Wire Wire Line
	5550 2950 5550 2500
Wire Wire Line
	5550 2500 4500 2500
$Comp
L 7805 U1
U 1 1 582F7821
P 4800 1250
F 0 "U1" H 4950 1054 50  0000 C CNN
F 1 "7805" H 4800 1450 50  0000 C CNN
F 2 "" H 4800 1250 50  0000 C CNN
F 3 "" H 4800 1250 50  0000 C CNN
	1    4800 1250
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR10
U 1 1 582F78C5
P 5700 1350
F 0 "#PWR10" H 5700 1200 50  0001 C CNN
F 1 "+5V" H 5700 1490 50  0000 C CNN
F 2 "" H 5700 1350 50  0000 C CNN
F 3 "" H 5700 1350 50  0000 C CNN
	1    5700 1350
	-1   0    0    1   
$EndComp
Wire Wire Line
	5200 1200 5700 1200
Wire Wire Line
	5700 1200 5700 1350
$Comp
L GND #PWR8
U 1 1 582F7929
P 4800 1650
F 0 "#PWR8" H 4800 1400 50  0001 C CNN
F 1 "GND" H 4800 1500 50  0000 C CNN
F 2 "" H 4800 1650 50  0000 C CNN
F 3 "" H 4800 1650 50  0000 C CNN
	1    4800 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 1500 4800 1650
$Comp
L CONN_01X02 P1
U 1 1 582F798F
P 3700 1250
F 0 "P1" H 3700 1400 50  0000 C CNN
F 1 "CONN_01X02" V 3800 1250 50  0000 C CNN
F 2 "" H 3700 1250 50  0000 C CNN
F 3 "" H 3700 1250 50  0000 C CNN
	1    3700 1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 1300 3900 1600
Wire Wire Line
	3900 1600 5250 1600
Connection ~ 4800 1600
Wire Wire Line
	3900 1200 4400 1200
$Comp
L CP C1
U 1 1 582F7A72
P 4250 1400
F 0 "C1" H 4275 1500 50  0000 L CNN
F 1 "10u" H 4275 1300 50  0000 L CNN
F 2 "" H 4288 1250 50  0000 C CNN
F 3 "" H 4250 1400 50  0000 C CNN
	1    4250 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 1050 4250 1250
Connection ~ 4250 1200
Wire Wire Line
	4250 1550 4250 1600
Connection ~ 4250 1600
$Comp
L C C2
U 1 1 582F7BB5
P 5250 1400
F 0 "C2" H 5275 1500 50  0000 L CNN
F 1 "100n" H 5275 1300 50  0000 L CNN
F 2 "" H 5288 1250 50  0000 C CNN
F 3 "" H 5250 1400 50  0000 C CNN
	1    5250 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 1200 5250 1250
Connection ~ 5250 1200
Wire Wire Line
	5250 1600 5250 1550
$Comp
L CONN_01X02 J7
U 1 1 58D195B3
P 3350 4750
F 0 "J7" H 3350 4900 50  0000 C CNN
F 1 "CONN_01X02" V 3450 4750 50  0000 C CNN
F 2 "" H 3350 4750 50  0001 C CNN
F 3 "" H 3350 4750 50  0001 C CNN
	1    3350 4750
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 J4
U 1 1 58D1963E
P 4300 2500
F 0 "J4" H 4300 2700 50  0000 C CNN
F 1 "CONN_01X03" V 4400 2500 50  0000 C CNN
F 2 "" H 4300 2500 50  0001 C CNN
F 3 "" H 4300 2500 50  0001 C CNN
	1    4300 2500
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 J5
U 1 1 58D196A3
P 4300 3250
F 0 "J5" H 4300 3450 50  0000 C CNN
F 1 "CONN_01X03" V 4400 3250 50  0000 C CNN
F 2 "" H 4300 3250 50  0001 C CNN
F 3 "" H 4300 3250 50  0001 C CNN
	1    4300 3250
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 J6
U 1 1 58D196DC
P 4300 4050
F 0 "J6" H 4300 4250 50  0000 C CNN
F 1 "CONN_01X03" V 4400 4050 50  0000 C CNN
F 2 "" H 4300 4050 50  0001 C CNN
F 3 "" H 4300 4050 50  0001 C CNN
	1    4300 4050
	-1   0    0    1   
$EndComp
Text Notes 3700 2400 0    60   ~ 0
TEMP1
Text Notes 3700 3050 0    60   ~ 0
TEMP2
Text Notes 3700 3800 0    60   ~ 0
FLOW
Text Notes 2950 4800 0    60   ~ 0
SSR
$Comp
L Buzzer BZ1
U 1 1 58D2E5F1
P 5550 6350
F 0 "BZ1" H 5700 6400 50  0000 L CNN
F 1 "Buzzer" H 5700 6300 50  0000 L CNN
F 2 "" V 5525 6450 50  0001 C CNN
F 3 "" V 5525 6450 50  0001 C CNN
	1    5550 6350
	-1   0    0    1   
$EndComp
$Comp
L RM50-xx21 RL1
U 1 1 58D2E664
P 7800 4400
F 0 "RL1" H 8250 4550 50  0000 L CNN
F 1 "RM50-xx21" H 8250 4450 50  0000 L CNN
F 2 "" H 7800 4400 50  0001 C CNN
F 3 "" H 7800 4400 50  0001 C CNN
	1    7800 4400
	1    0    0    -1  
$EndComp
$Comp
L POT_TRIM RV1
U 1 1 58D2E732
P 8350 1100
F 0 "RV1" V 8175 1100 50  0000 C CNN
F 1 "10K" V 8250 1100 50  0000 C CNN
F 2 "" H 8350 1100 50  0001 C CNN
F 3 "" H 8350 1100 50  0001 C CNN
	1    8350 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 5200 6150 5200
Wire Wire Line
	6150 5200 6150 2850
Wire Wire Line
	6150 2850 6650 2850
NoConn ~ 6650 2650
$Comp
L BC547 Q1
U 1 1 58D2E8F5
P 7500 5000
F 0 "Q1" H 7700 5075 50  0000 L CNN
F 1 "BC547" H 7700 5000 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 7700 4925 50  0001 L CIN
F 3 "" H 7500 5000 50  0001 L CNN
	1    7500 5000
	1    0    0    -1  
$EndComp
$Comp
L DIODE D1
U 1 1 58D2E9AA
P 7050 4400
F 0 "D1" H 7050 4500 40  0000 C CNN
F 1 "1N4148" H 7050 4300 40  0000 C CNN
F 2 "" H 7050 4400 60  0000 C CNN
F 3 "" H 7050 4400 60  0000 C CNN
	1    7050 4400
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 58D2EA0D
P 6850 5000
F 0 "R2" V 6930 5000 50  0000 C CNN
F 1 "1K" V 6850 5000 50  0000 C CNN
F 2 "" V 6780 5000 50  0001 C CNN
F 3 "" H 6850 5000 50  0001 C CNN
	1    6850 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	6650 2750 6350 2750
Wire Wire Line
	6350 2750 6350 5000
Wire Wire Line
	6350 5000 6700 5000
Wire Wire Line
	7000 5000 7300 5000
$Comp
L GND #PWR14
U 1 1 58D2EBAA
P 7600 5300
F 0 "#PWR14" H 7600 5050 50  0001 C CNN
F 1 "GND" H 7600 5150 50  0000 C CNN
F 2 "" H 7600 5300 50  0001 C CNN
F 3 "" H 7600 5300 50  0001 C CNN
	1    7600 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 5300 7600 5200
Wire Wire Line
	7600 4700 7600 4800
Wire Wire Line
	7050 4600 7050 4750
Wire Wire Line
	7050 4750 7600 4750
Connection ~ 7600 4750
$Comp
L +5V #PWR13
U 1 1 58D2ED2E
P 6950 4000
F 0 "#PWR13" H 6950 3850 50  0001 C CNN
F 1 "+5V" H 6950 4140 50  0000 C CNN
F 2 "" H 6950 4000 50  0001 C CNN
F 3 "" H 6950 4000 50  0001 C CNN
	1    6950 4000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6950 4000 7600 4000
Wire Wire Line
	7050 4000 7050 4200
Wire Wire Line
	7600 4000 7600 4100
Connection ~ 7050 4000
$Comp
L CONN_01X02 J8
U 1 1 58D2EE7D
P 9150 4450
F 0 "J8" H 9150 4600 50  0000 C CNN
F 1 "CONN_01X02" V 9250 4450 50  0000 C CNN
F 2 "" H 9150 4450 50  0001 C CNN
F 3 "" H 9150 4450 50  0001 C CNN
	1    9150 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 4100 8100 4050
Wire Wire Line
	8100 4050 8800 4050
Wire Wire Line
	8800 4050 8800 4400
Wire Wire Line
	8800 4400 8950 4400
Wire Wire Line
	8950 4500 8800 4500
Wire Wire Line
	8800 4500 8800 4800
Wire Wire Line
	8800 4800 8000 4800
Wire Wire Line
	8000 4800 8000 4700
Text Notes 9350 4500 0    60   ~ 0
LASERSAUR
$Comp
L R R1
U 1 1 58D2F17F
P 4100 1950
F 0 "R1" V 4180 1950 50  0000 C CNN
F 1 "100" V 4100 1950 50  0000 C CNN
F 2 "" V 4030 1950 50  0001 C CNN
F 3 "" H 4100 1950 50  0001 C CNN
	1    4100 1950
	0    1    1    0   
$EndComp
$Comp
L C C3
U 1 1 58D2F1CA
P 5800 2200
F 0 "C3" H 5825 2300 50  0000 L CNN
F 1 "100n" H 5825 2100 50  0000 L CNN
F 2 "" H 5838 2050 50  0001 C CNN
F 3 "" H 5800 2200 50  0001 C CNN
	1    5800 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2600 5800 2350
Connection ~ 5200 2600
Wire Wire Line
	5800 1950 5800 2050
Wire Wire Line
	4250 1950 5800 1950
Connection ~ 5400 1950
Wire Wire Line
	3650 1950 3950 1950
$Comp
L CONN_01X02 J2
U 1 1 58D2FE93
P 3400 6400
F 0 "J2" H 3400 6550 50  0000 C CNN
F 1 "CONN_01X02" V 3500 6400 50  0000 C CNN
F 2 "" H 3400 6400 50  0001 C CNN
F 3 "" H 3400 6400 50  0001 C CNN
	1    3400 6400
	-1   0    0    1   
$EndComp
Text Notes 3000 6400 0    60   ~ 0
FAN
$Comp
L CONN_01X02 J3
U 1 1 58D2FF09
P 1700 4600
F 0 "J3" H 1700 4750 50  0000 C CNN
F 1 "CONN_01X02" V 1800 4600 50  0000 C CNN
F 2 "" H 1700 4600 50  0001 C CNN
F 3 "" H 1700 4600 50  0001 C CNN
	1    1700 4600
	-1   0    0    1   
$EndComp
Text Notes 1150 4650 0    60   ~ 0
PUMP
$Comp
L +12V #PWR7
U 1 1 58D301A3
P 4250 1050
F 0 "#PWR7" H 4250 900 50  0001 C CNN
F 1 "+12V" H 4250 1190 50  0000 C CNN
F 2 "" H 4250 1050 50  0001 C CNN
F 3 "" H 4250 1050 50  0001 C CNN
	1    4250 1050
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR5
U 1 1 58D30293
P 2000 4450
F 0 "#PWR5" H 2000 4300 50  0001 C CNN
F 1 "+12V" H 2000 4590 50  0000 C CNN
F 2 "" H 2000 4450 50  0001 C CNN
F 3 "" H 2000 4450 50  0001 C CNN
	1    2000 4450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 58D303D0
P 2000 4800
F 0 "#PWR3" H 2000 4550 50  0001 C CNN
F 1 "GND" H 2000 4650 50  0000 C CNN
F 2 "" H 2000 4800 50  0001 C CNN
F 3 "" H 2000 4800 50  0001 C CNN
	1    2000 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 4650 2000 4800
Wire Wire Line
	1900 4650 2000 4650
Wire Wire Line
	6650 2550 5900 2550
Wire Wire Line
	5900 2550 5900 6250
Wire Wire Line
	5900 6250 5650 6250
$Comp
L GND #PWR11
U 1 1 58D42121
P 5900 6550
F 0 "#PWR11" H 5900 6300 50  0001 C CNN
F 1 "GND" H 5900 6400 50  0000 C CNN
F 2 "" H 5900 6550 50  0001 C CNN
F 3 "" H 5900 6550 50  0001 C CNN
	1    5900 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 6450 5900 6450
Wire Wire Line
	5900 6450 5900 6550
Text GLabel 8300 1850 2    47   Input ~ 0
TX
Text GLabel 8300 1950 2    47   Input ~ 0
RX
Text Notes 1150 2500 0    60   ~ 0
SERIAL
$Comp
L GND #PWR4
U 1 1 58D6F63A
P 2100 2750
F 0 "#PWR4" H 2100 2500 50  0001 C CNN
F 1 "GND" H 2100 2600 50  0000 C CNN
F 2 "" H 2100 2750 50  0001 C CNN
F 3 "" H 2100 2750 50  0001 C CNN
	1    2100 2750
	1    0    0    -1  
$EndComp
Text GLabel 2250 2400 2    47   Input ~ 0
RX
$Comp
L CONN_01X03 J1
U 1 1 58D6F6BD
P 1600 2400
F 0 "J1" H 1600 2600 50  0000 C CNN
F 1 "CONN_01X03" V 1700 2400 50  0000 C CNN
F 2 "" H 1600 2400 50  0001 C CNN
F 3 "" H 1600 2400 50  0001 C CNN
	1    1600 2400
	-1   0    0    1   
$EndComp
Text GLabel 2250 2300 2    47   Input ~ 0
TX
Wire Wire Line
	1800 2300 2250 2300
Wire Wire Line
	2250 2400 1800 2400
Wire Wire Line
	1800 2500 2100 2500
Wire Wire Line
	2100 2500 2100 2750
$Comp
L PWR_FLAG #FLG1
U 1 1 58D6F982
P 1400 6350
F 0 "#FLG1" H 1400 6425 50  0001 C CNN
F 1 "PWR_FLAG" H 1400 6500 50  0000 C CNN
F 2 "" H 1400 6350 50  0001 C CNN
F 3 "" H 1400 6350 50  0001 C CNN
	1    1400 6350
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG2
U 1 1 58D6F9C2
P 1950 6350
F 0 "#FLG2" H 1950 6425 50  0001 C CNN
F 1 "PWR_FLAG" H 1950 6500 50  0000 C CNN
F 2 "" H 1950 6350 50  0001 C CNN
F 3 "" H 1950 6350 50  0001 C CNN
	1    1950 6350
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR1
U 1 1 58D6FA70
P 1400 6550
F 0 "#PWR1" H 1400 6400 50  0001 C CNN
F 1 "+12V" H 1400 6690 50  0000 C CNN
F 2 "" H 1400 6550 50  0001 C CNN
F 3 "" H 1400 6550 50  0001 C CNN
	1    1400 6550
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR2
U 1 1 58D6FAB0
P 1950 6550
F 0 "#PWR2" H 1950 6300 50  0001 C CNN
F 1 "GND" H 1950 6400 50  0000 C CNN
F 2 "" H 1950 6550 50  0001 C CNN
F 3 "" H 1950 6550 50  0001 C CNN
	1    1950 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 6550 1950 6350
Wire Wire Line
	1400 6350 1400 6550
Wire Wire Line
	4500 4050 5550 4050
Wire Wire Line
	5550 4050 5550 3800
Wire Wire Line
	5550 3800 8400 3800
Wire Wire Line
	8400 3800 8400 2250
$Comp
L R R4
U 1 1 58DAACB2
P 4950 2200
F 0 "R4" V 5030 2200 50  0000 C CNN
F 1 "4K7" V 4950 2200 50  0000 C CNN
F 2 "" V 4880 2200 50  0001 C CNN
F 3 "" H 4950 2200 50  0001 C CNN
	1    4950 2200
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 58DAAD09
P 4700 2200
F 0 "R3" V 4780 2200 50  0000 C CNN
F 1 "4K7" V 4700 2200 50  0000 C CNN
F 2 "" V 4630 2200 50  0001 C CNN
F 3 "" H 4700 2200 50  0001 C CNN
	1    4700 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 1950 4700 2050
Connection ~ 4700 1950
Wire Wire Line
	4700 2350 4700 2500
Connection ~ 4700 2500
Wire Wire Line
	4950 2350 4950 3250
Connection ~ 4950 3250
Wire Wire Line
	4950 1950 4950 2050
Connection ~ 4950 1950
$Comp
L MOSFET_N_CH Q?
U 1 1 59162D17
P 3800 5200
F 0 "Q?" H 4100 5250 50  0000 R CNN
F 1 "IRF530N" H 4350 5150 50  0000 R CNN
F 2 "" H 4000 5300 50  0000 C CNN
F 3 "" H 3800 5200 50  0000 C CNN
	1    3800 5200
	-1   0    0    -1  
$EndComp
$Comp
L +12V #PWR?
U 1 1 59162F37
P 3700 4500
F 0 "#PWR?" H 3700 4350 50  0001 C CNN
F 1 "+12V" H 3700 4640 50  0000 C CNN
F 2 "" H 3700 4500 50  0001 C CNN
F 3 "" H 3700 4500 50  0001 C CNN
	1    3700 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 4500 3700 4700
Wire Wire Line
	3700 4700 3550 4700
Wire Wire Line
	3550 4800 3700 4800
Wire Wire Line
	3700 4800 3700 5000
$Comp
L GND #PWR?
U 1 1 591630EF
P 3700 5500
F 0 "#PWR?" H 3700 5250 50  0001 C CNN
F 1 "GND" H 3700 5350 50  0000 C CNN
F 2 "" H 3700 5500 50  0001 C CNN
F 3 "" H 3700 5500 50  0001 C CNN
	1    3700 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 5500 3700 5400
Wire Wire Line
	5200 2600 5200 4350
Wire Wire Line
	1900 4550 2000 4550
Wire Wire Line
	2000 4550 2000 4450
$Comp
L MOSFET_N_CH Q?
U 1 1 591638EA
P 3800 6800
F 0 "Q?" H 4100 6850 50  0000 R CNN
F 1 "IRF530N" H 4500 6750 50  0000 R CNN
F 2 "" H 4000 6900 50  0000 C CNN
F 3 "" H 3800 6800 50  0000 C CNN
	1    3800 6800
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59163A75
P 3700 7250
F 0 "#PWR?" H 3700 7000 50  0001 C CNN
F 1 "GND" H 3700 7100 50  0000 C CNN
F 2 "" H 3700 7250 50  0001 C CNN
F 3 "" H 3700 7250 50  0001 C CNN
	1    3700 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 6450 3700 6450
Wire Wire Line
	3700 6450 3700 6600
Wire Wire Line
	3700 7000 3700 7250
$Comp
L +12V #PWR?
U 1 1 59163CEF
P 3700 6250
F 0 "#PWR?" H 3700 6100 50  0001 C CNN
F 1 "+12V" H 3700 6390 50  0000 C CNN
F 2 "" H 3700 6250 50  0001 C CNN
F 3 "" H 3700 6250 50  0001 C CNN
	1    3700 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 6250 3700 6350
Wire Wire Line
	3700 6350 3600 6350
Wire Wire Line
	6650 2450 6050 2450
Wire Wire Line
	6050 2450 6050 5000
Wire Wire Line
	6050 5000 4450 5000
Wire Wire Line
	4450 5000 4450 6800
Wire Wire Line
	4450 6800 4000 6800
$EndSCHEMATC
