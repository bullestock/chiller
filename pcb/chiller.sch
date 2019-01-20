EESchema Schematic File Version 4
LIBS:chiller-cache
EELAYER 26 0
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
L tinkerforge:LCD-20X4 J9
U 1 1 582F6D65
P 9100 2200
F 0 "J9" H 9100 3100 60  0000 C CNN
F 1 "LCD-20X4" H 9150 1350 60  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x16_P2.54mm_Vertical" H 9100 2200 60  0001 C CNN
F 3 "" H 9100 2200 60  0000 C CNN
	1    9100 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 1100 8700 1100
Wire Wire Line
	8700 1100 8700 1650
Wire Wire Line
	8700 1650 8950 1650
$Comp
L power:GND #PWR016
U 1 1 582F6EE9
P 8350 1350
F 0 "#PWR016" H 8350 1100 50  0001 C CNN
F 1 "GND" H 8350 1200 50  0000 C CNN
F 2 "" H 8350 1350 50  0000 C CNN
F 3 "" H 8350 1350 50  0000 C CNN
	1    8350 1350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR015
U 1 1 582F6F03
P 8350 850
F 0 "#PWR015" H 8350 700 50  0001 C CNN
F 1 "+5V" H 8350 990 50  0000 C CNN
F 2 "" H 8350 850 50  0000 C CNN
F 3 "" H 8350 850 50  0000 C CNN
	1    8350 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 850  8350 900 
Wire Wire Line
	8350 1250 8350 1300
Wire Wire Line
	8800 900  8800 1550
Wire Wire Line
	8800 1550 8950 1550
Connection ~ 8350 900 
Wire Wire Line
	8350 1300 8900 1300
Wire Wire Line
	8900 1300 8900 1450
Wire Wire Line
	8900 1450 8950 1450
Connection ~ 8350 1300
Wire Wire Line
	8950 1750 8550 1750
Wire Wire Line
	8550 1750 8550 2850
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
L power:GND #PWR017
U 1 1 582F70AB
P 8800 3150
F 0 "#PWR017" H 8800 2900 50  0001 C CNN
F 1 "GND" H 8800 3000 50  0000 C CNN
F 2 "" H 8800 3150 50  0000 C CNN
F 3 "" H 8800 3150 50  0000 C CNN
	1    8800 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 3150 8800 2950
$Comp
L power:GND #PWR012
U 1 1 582F7183
P 7300 3700
F 0 "#PWR012" H 7300 3450 50  0001 C CNN
F 1 "GND" H 7300 3550 50  0000 C CNN
F 2 "" H 7300 3700 50  0000 C CNN
F 3 "" H 7300 3700 50  0000 C CNN
	1    7300 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 582F736C
P 5200 4350
F 0 "#PWR09" H 5200 4100 50  0001 C CNN
F 1 "GND" H 5200 4200 50  0000 C CNN
F 2 "" H 5200 4350 50  0000 C CNN
F 3 "" H 5200 4350 50  0000 C CNN
	1    5200 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR06
U 1 1 582F738A
P 3650 1950
F 0 "#PWR06" H 3650 1800 50  0001 C CNN
F 1 "+5V" H 3650 2090 50  0000 C CNN
F 2 "" H 3650 1950 50  0000 C CNN
F 3 "" H 3650 1950 50  0000 C CNN
	1    3650 1950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5400 1950 5400 2400
Wire Wire Line
	5400 3150 4500 3150
Wire Wire Line
	4500 2400 5400 2400
Connection ~ 5400 2400
Wire Wire Line
	4500 2600 5200 2600
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
	5550 3250 4950 3250
Wire Wire Line
	5550 2500 4700 2500
$Comp
L chiller-rescue:7805 U1
U 1 1 582F7821
P 4800 1250
F 0 "U1" H 4950 1054 50  0000 C CNN
F 1 "78M05" H 4800 1450 50  0000 C CNN
F 2 "modules:DPAK-3" H 4800 1250 50  0001 C CNN
F 3 "" H 4800 1250 50  0000 C CNN
	1    4800 1250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 582F78C5
P 5700 1350
F 0 "#PWR010" H 5700 1200 50  0001 C CNN
F 1 "+5V" H 5700 1490 50  0000 C CNN
F 2 "" H 5700 1350 50  0000 C CNN
F 3 "" H 5700 1350 50  0000 C CNN
	1    5700 1350
	-1   0    0    1   
$EndComp
Wire Wire Line
	5200 1200 5250 1200
Wire Wire Line
	5700 1200 5700 1350
$Comp
L power:GND #PWR08
U 1 1 582F7929
P 4800 1650
F 0 "#PWR08" H 4800 1400 50  0001 C CNN
F 1 "GND" H 4800 1500 50  0000 C CNN
F 2 "" H 4800 1650 50  0000 C CNN
F 3 "" H 4800 1650 50  0000 C CNN
	1    4800 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 1500 4800 1600
$Comp
L tinkerforge:CONN_01X02 J11
U 1 1 582F798F
P 3700 1250
F 0 "J11" H 3700 1400 50  0000 C CNN
F 1 "CONN_01X02" V 3800 1250 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B02B-XH-A_1x02_P2.50mm_Vertical" H 3700 1250 50  0001 C CNN
F 3 "" H 3700 1250 50  0000 C CNN
	1    3700 1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 1300 3900 1600
Wire Wire Line
	3900 1600 4250 1600
Connection ~ 4800 1600
Wire Wire Line
	3900 1200 4250 1200
$Comp
L chiller-rescue:CP C1
U 1 1 582F7A72
P 4250 1400
F 0 "C1" H 4275 1500 50  0000 L CNN
F 1 "10u" H 4275 1300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4288 1250 50  0001 C CNN
F 3 "" H 4250 1400 50  0000 C CNN
	1    4250 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 1050 4250 1200
Connection ~ 4250 1200
Wire Wire Line
	4250 1550 4250 1600
Connection ~ 4250 1600
$Comp
L chiller-rescue:C C2
U 1 1 582F7BB5
P 5250 1400
F 0 "C2" H 5275 1500 50  0000 L CNN
F 1 "100n" H 5275 1300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5288 1250 50  0001 C CNN
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
L tinkerforge:CONN_01X02 J6
U 1 1 58D195B3
P 3350 4750
F 0 "J6" H 3350 4900 50  0000 C CNN
F 1 "CONN_01X02" V 3450 4750 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B02B-XH-A_1x02_P2.50mm_Vertical" H 3350 4750 50  0001 C CNN
F 3 "" H 3350 4750 50  0001 C CNN
	1    3350 4750
	-1   0    0    1   
$EndComp
$Comp
L chiller-rescue:CONN_01X03 J1
U 1 1 58D1963E
P 4300 2500
F 0 "J1" H 4300 2700 50  0000 C CNN
F 1 "CONN_01X03" V 4400 2500 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B03B-XH-A_1x03_P2.50mm_Vertical" H 4300 2500 50  0001 C CNN
F 3 "" H 4300 2500 50  0001 C CNN
	1    4300 2500
	-1   0    0    1   
$EndComp
$Comp
L chiller-rescue:CONN_01X03 J2
U 1 1 58D196A3
P 4300 3250
F 0 "J2" H 4300 3450 50  0000 C CNN
F 1 "CONN_01X03" V 4400 3250 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B03B-XH-A_1x03_P2.50mm_Vertical" H 4300 3250 50  0001 C CNN
F 3 "" H 4300 3250 50  0001 C CNN
	1    4300 3250
	-1   0    0    1   
$EndComp
$Comp
L chiller-rescue:CONN_01X03 J3
U 1 1 58D196DC
P 4300 4050
F 0 "J3" H 4300 4250 50  0000 C CNN
F 1 "CONN_01X03" V 4400 4050 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B03B-XH-A_1x03_P2.50mm_Vertical" H 4300 4050 50  0001 C CNN
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
L chiller-rescue:POT_TRIM RV1
U 1 1 58D2E732
P 8350 1100
F 0 "RV1" V 8175 1100 50  0000 C CNN
F 1 "10K" V 8250 1100 50  0000 C CNN
F 2 "Potentiometer_SMD:Potentiometer_Vishay_TS53YL_Vertical" H 8350 1100 50  0001 C CNN
F 3 "" H 8350 1100 50  0001 C CNN
	1    8350 1100
	1    0    0    -1  
$EndComp
$Comp
L chiller-rescue:R R10
U 1 1 58D2EA0D
P 6850 5000
F 0 "R10" V 6930 5000 50  0000 C CNN
F 1 "1K" V 6850 5000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6780 5000 50  0001 C CNN
F 3 "" H 6850 5000 50  0001 C CNN
	1    6850 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	6350 5000 6700 5000
Wire Wire Line
	7000 5000 7150 5000
$Comp
L power:GND #PWR014
U 1 1 58D2EBAA
P 7600 5500
F 0 "#PWR014" H 7600 5250 50  0001 C CNN
F 1 "GND" H 7600 5350 50  0000 C CNN
F 2 "" H 7600 5500 50  0001 C CNN
F 3 "" H 7600 5500 50  0001 C CNN
	1    7600 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 4700 7600 4750
Connection ~ 7600 4750
$Comp
L power:+5V #PWR013
U 1 1 58D2ED2E
P 6950 4000
F 0 "#PWR013" H 6950 3850 50  0001 C CNN
F 1 "+5V" H 6950 4140 50  0000 C CNN
F 2 "" H 6950 4000 50  0001 C CNN
F 3 "" H 6950 4000 50  0001 C CNN
	1    6950 4000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6950 4000 7050 4000
Wire Wire Line
	7600 4000 7600 4100
Connection ~ 7050 4000
$Comp
L tinkerforge:CONN_01X02 J8
U 1 1 58D2EE7D
P 9150 4450
F 0 "J8" H 9150 4600 50  0000 C CNN
F 1 "CONN_01X02" V 9250 4450 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B02B-XH-A_1x02_P2.50mm_Vertical" H 9150 4450 50  0001 C CNN
F 3 "" H 9150 4450 50  0001 C CNN
	1    9150 4450
	1    0    0    1   
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
Ready
$Comp
L chiller-rescue:R R1
U 1 1 58D2F17F
P 4100 1950
F 0 "R1" V 4180 1950 50  0000 C CNN
F 1 "100" V 4100 1950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4030 1950 50  0001 C CNN
F 3 "" H 4100 1950 50  0001 C CNN
	1    4100 1950
	0    1    1    0   
$EndComp
$Comp
L chiller-rescue:C C3
U 1 1 58D2F1CA
P 5650 1950
F 0 "C3" H 5675 2050 50  0000 L CNN
F 1 "100n" H 5675 1850 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5688 1800 50  0001 C CNN
F 3 "" H 5650 1950 50  0001 C CNN
	1    5650 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	4250 1950 4700 1950
Wire Wire Line
	3650 1950 3950 1950
$Comp
L tinkerforge:CONN_01X02 J7
U 1 1 58D2FE93
P 3400 6400
F 0 "J7" H 3400 6550 50  0000 C CNN
F 1 "CONN_01X02" V 3500 6400 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B02B-XH-A_1x02_P2.50mm_Vertical" H 3400 6400 50  0001 C CNN
F 3 "" H 3400 6400 50  0001 C CNN
	1    3400 6400
	-1   0    0    1   
$EndComp
Text Notes 3000 6400 0    60   ~ 0
FAN
$Comp
L tinkerforge:CONN_01X02 J4
U 1 1 58D2FF09
P 1200 4900
F 0 "J4" H 1200 5050 50  0000 C CNN
F 1 "CONN_01X02" V 1300 4900 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B02B-XH-A_1x02_P2.50mm_Vertical" H 1200 4900 50  0001 C CNN
F 3 "" H 1200 4900 50  0001 C CNN
	1    1200 4900
	-1   0    0    1   
$EndComp
Text Notes 650  4950 0    60   ~ 0
PUMP
$Comp
L power:+12V #PWR07
U 1 1 58D301A3
P 4250 1050
F 0 "#PWR07" H 4250 900 50  0001 C CNN
F 1 "+12V" H 4250 1190 50  0000 C CNN
F 2 "" H 4250 1050 50  0001 C CNN
F 3 "" H 4250 1050 50  0001 C CNN
	1    4250 1050
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR05
U 1 1 58D30293
P 1500 4750
F 0 "#PWR05" H 1500 4600 50  0001 C CNN
F 1 "+12V" H 1500 4890 50  0000 C CNN
F 2 "" H 1500 4750 50  0001 C CNN
F 3 "" H 1500 4750 50  0001 C CNN
	1    1500 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 58D303D0
P 1500 5100
F 0 "#PWR03" H 1500 4850 50  0001 C CNN
F 1 "GND" H 1500 4950 50  0000 C CNN
F 2 "" H 1500 5100 50  0001 C CNN
F 3 "" H 1500 5100 50  0001 C CNN
	1    1500 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 4950 1500 5100
Wire Wire Line
	1400 4950 1500 4950
Text Notes 750  3800 0    60   ~ 0
SERIAL
$Comp
L power:GND #PWR04
U 1 1 58D6F63A
P 1700 4050
F 0 "#PWR04" H 1700 3800 50  0001 C CNN
F 1 "GND" H 1700 3900 50  0000 C CNN
F 2 "" H 1700 4050 50  0001 C CNN
F 3 "" H 1700 4050 50  0001 C CNN
	1    1700 4050
	1    0    0    -1  
$EndComp
Text GLabel 1850 3700 2    47   Input ~ 0
RX
$Comp
L chiller-rescue:CONN_01X03 J10
U 1 1 58D6F6BD
P 1200 3700
F 0 "J10" H 1200 3900 50  0000 C CNN
F 1 "CONN_01X03" V 1300 3700 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B03B-XH-A_1x03_P2.50mm_Vertical" H 1200 3700 50  0001 C CNN
F 3 "" H 1200 3700 50  0001 C CNN
	1    1200 3700
	-1   0    0    1   
$EndComp
Text GLabel 1850 3600 2    47   Input ~ 0
TX
Wire Wire Line
	1400 3600 1850 3600
Wire Wire Line
	1850 3700 1400 3700
Wire Wire Line
	1400 3800 1700 3800
Wire Wire Line
	1700 3800 1700 4050
$Comp
L power:PWR_FLAG #FLG01
U 1 1 58D6F982
P 9900 3350
F 0 "#FLG01" H 9900 3425 50  0001 C CNN
F 1 "PWR_FLAG" H 9900 3500 50  0000 C CNN
F 2 "" H 9900 3350 50  0001 C CNN
F 3 "" H 9900 3350 50  0001 C CNN
	1    9900 3350
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 58D6F9C2
P 10450 3350
F 0 "#FLG02" H 10450 3425 50  0001 C CNN
F 1 "PWR_FLAG" H 10450 3500 50  0000 C CNN
F 2 "" H 10450 3350 50  0001 C CNN
F 3 "" H 10450 3350 50  0001 C CNN
	1    10450 3350
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR01
U 1 1 58D6FA70
P 9900 3550
F 0 "#PWR01" H 9900 3400 50  0001 C CNN
F 1 "+12V" H 9900 3690 50  0000 C CNN
F 2 "" H 9900 3550 50  0001 C CNN
F 3 "" H 9900 3550 50  0001 C CNN
	1    9900 3550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 58D6FAB0
P 10450 3550
F 0 "#PWR02" H 10450 3300 50  0001 C CNN
F 1 "GND" H 10450 3400 50  0000 C CNN
F 2 "" H 10450 3550 50  0001 C CNN
F 3 "" H 10450 3550 50  0001 C CNN
	1    10450 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 3550 10450 3350
Wire Wire Line
	9900 3350 9900 3550
Wire Wire Line
	4500 4050 5550 4050
$Comp
L chiller-rescue:R R3
U 1 1 58DAACB2
P 4950 2200
F 0 "R3" V 5030 2200 50  0000 C CNN
F 1 "4K7" V 4950 2200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4880 2200 50  0001 C CNN
F 3 "" H 4950 2200 50  0001 C CNN
	1    4950 2200
	1    0    0    -1  
$EndComp
$Comp
L chiller-rescue:R R2
U 1 1 58DAAD09
P 4700 2200
F 0 "R2" V 4780 2200 50  0000 C CNN
F 1 "4K7" V 4700 2200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4630 2200 50  0001 C CNN
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
L power:+12V #PWR0101
U 1 1 59162F37
P 3700 4500
F 0 "#PWR0101" H 3700 4350 50  0001 C CNN
F 1 "+12V" H 3700 4640 50  0000 C CNN
F 2 "" H 3700 4500 50  0001 C CNN
F 3 "" H 3700 4500 50  0001 C CNN
	1    3700 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 4700 3550 4700
Wire Wire Line
	3550 4800 3700 4800
$Comp
L power:GND #PWR0102
U 1 1 591630EF
P 3700 5650
F 0 "#PWR0102" H 3700 5400 50  0001 C CNN
F 1 "GND" H 3700 5500 50  0000 C CNN
F 2 "" H 3700 5650 50  0001 C CNN
F 3 "" H 3700 5650 50  0001 C CNN
	1    3700 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2600 5200 3350
Wire Wire Line
	1400 4850 1500 4850
Wire Wire Line
	1500 4850 1500 4750
$Comp
L power:GND #PWR0103
U 1 1 59163A75
P 3700 7250
F 0 "#PWR0103" H 3700 7000 50  0001 C CNN
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
	3700 7000 3700 7200
$Comp
L power:+12V #PWR0104
U 1 1 59163CEF
P 3700 6150
F 0 "#PWR0104" H 3700 6000 50  0001 C CNN
F 1 "+12V" H 3700 6290 50  0000 C CNN
F 2 "" H 3700 6150 50  0001 C CNN
F 3 "" H 3700 6150 50  0001 C CNN
	1    3700 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 6350 3600 6350
Wire Wire Line
	8350 900  8350 950 
Wire Wire Line
	8350 900  8800 900 
Wire Wire Line
	8350 1300 8350 1350
Wire Wire Line
	8900 1450 8900 1850
Wire Wire Line
	8800 1550 8800 2850
Wire Wire Line
	8800 2950 8950 2950
Wire Wire Line
	5400 2400 5400 3150
Wire Wire Line
	5200 3350 5200 4150
Wire Wire Line
	5200 4150 5200 4350
Wire Wire Line
	5400 3150 5400 3950
Wire Wire Line
	4800 1600 4800 1650
Wire Wire Line
	4800 1600 5250 1600
Wire Wire Line
	4250 1200 4400 1200
Wire Wire Line
	4250 1200 4250 1250
Wire Wire Line
	4250 1600 4800 1600
Wire Wire Line
	5250 1200 5700 1200
Wire Wire Line
	7600 4750 7600 4800
Wire Wire Line
	7050 4000 7200 4000
Wire Wire Line
	4700 1950 4950 1950
Wire Wire Line
	4700 2500 4500 2500
Wire Wire Line
	4950 3250 4500 3250
Wire Wire Line
	4950 1950 5400 1950
$Comp
L chiller-rescue:R R4
U 1 1 5BC8327A
P 2100 6800
F 0 "R4" V 1893 6800 50  0000 C CNN
F 1 "1K" V 1984 6800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2030 6800 50  0001 C CNN
F 3 "" H 2100 6800 50  0001 C CNN
	1    2100 6800
	0    -1   1    0   
$EndComp
$Comp
L tinkerforge:CONN_01X02 J5
U 1 1 5BC833D9
P 1200 6400
F 0 "J5" H 1278 6441 50  0000 L CNN
F 1 "CONN_01X02" H 1278 6350 50  0000 L CNN
F 2 "Connector_JST:JST_XH_B02B-XH-A_1x02_P2.50mm_Vertical" H 1200 6300 50  0001 C CNN
F 3 "" H 1200 6300 50  0000 C CNN
	1    1200 6400
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0105
U 1 1 5BC834F2
P 1550 6150
F 0 "#PWR0105" H 1550 6000 50  0001 C CNN
F 1 "+5V" H 1565 6323 50  0000 C CNN
F 2 "" H 1550 6150 50  0001 C CNN
F 3 "" H 1550 6150 50  0001 C CNN
	1    1550 6150
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5BC836B3
P 1550 7250
F 0 "#PWR0106" H 1550 7000 50  0001 C CNN
F 1 "GND" H 1555 7077 50  0000 C CNN
F 2 "" H 1550 7250 50  0001 C CNN
F 3 "" H 1550 7250 50  0001 C CNN
	1    1550 7250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1550 6150 1550 6350
Wire Wire Line
	1550 6350 1400 6350
Wire Wire Line
	1400 6450 1550 6450
Text Notes 1000 6250 2    60   ~ 0
BUZZER
$Comp
L Diode:BAT54C D1
U 1 1 5BCA2F25
P 6850 4450
F 0 "D1" V 6896 4538 50  0000 L CNN
F 1 "BAT54" V 6805 4538 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6925 4575 50  0001 L CNN
F 3 "http://www.diodes.com/_files/datasheets/ds11005.pdf" H 6770 4450 50  0001 C CNN
	1    6850 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6850 4750 7600 4750
Wire Wire Line
	7050 4000 7050 4450
$Comp
L Transistor_FET:BSS138 Q2
U 1 1 5BCBCC06
P 3800 5200
F 0 "Q2" H 4006 5154 50  0000 L CNN
F 1 "BSS138" H 4006 5245 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4000 5125 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 3800 5200 50  0001 L CNN
	1    3800 5200
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSP129 Q3
U 1 1 5BCBCF68
P 3800 6800
F 0 "Q3" H 4006 6846 50  0000 L CNN
F 1 "ZXMN4A06G" H 4006 6755 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4000 6725 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/Infineon-BSP129-DS-v01_42-en.pdf?fileId=db3a30433c1a8752013c1fc296d2395f" H 3800 6800 50  0001 L CNN
	1    3800 6800
	-1   0    0    -1  
$EndComp
$Comp
L tinkerforge:CONN_01X02 J12
U 1 1 5BC912CA
P 950 2050
F 0 "J12" H 869 1775 50  0000 C CNN
F 1 "CONN_01X02" H 869 1866 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B02B-XH-A_1x02_P2.50mm_Vertical" H 950 1950 50  0001 C CNN
F 3 "" H 950 1950 50  0000 C CNN
	1    950  2050
	-1   0    0    1   
$EndComp
Text Notes 600  2400 0    60   ~ 0
CURRENT\nSENSE
$Comp
L chiller-rescue:C C5
U 1 1 5BC9E84C
P 7200 4300
F 0 "C5" H 7100 4500 50  0000 L CNN
F 1 "10u" H 7250 4500 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7238 4150 50  0001 C CNN
F 3 "" H 7200 4300 50  0001 C CNN
	1    7200 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5BC9EA8B
P 7200 4500
F 0 "#PWR0107" H 7200 4250 50  0001 C CNN
F 1 "GND" H 7205 4327 50  0000 C CNN
F 2 "" H 7200 4500 50  0001 C CNN
F 3 "" H 7200 4500 50  0001 C CNN
	1    7200 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 4450 7200 4500
Wire Wire Line
	7200 4150 7200 4000
Connection ~ 7200 4000
Wire Wire Line
	7200 4000 7600 4000
$Comp
L MCU_Module:Arduino_Nano_v3.x U2
U 1 1 5BCA896C
P 7350 2650
F 0 "U2" H 7350 2650 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 8200 2900 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 7500 1700 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 7350 1650 50  0001 C CNN
	1    7350 2650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7850 2450 8950 2450
Wire Wire Line
	7850 2550 8950 2550
Wire Wire Line
	7850 2650 8950 2650
Wire Wire Line
	7850 2750 8950 2750
Wire Wire Line
	7850 2850 8550 2850
Text GLabel 7950 2950 2    60   Input ~ 0
D9
Wire Wire Line
	7950 2950 7850 2950
Text GLabel 5550 3250 2    60   Input ~ 0
D9
Wire Wire Line
	7250 3650 7250 3700
Wire Wire Line
	7250 3700 7300 3700
Wire Wire Line
	7350 3700 7350 3650
Connection ~ 7300 3700
Wire Wire Line
	7300 3700 7350 3700
Text GLabel 8100 3050 2    60   Input ~ 0
D10
Wire Wire Line
	7850 3050 8100 3050
Text GLabel 5550 2500 2    60   Input ~ 0
D10
Text GLabel 5550 4050 2    60   Input ~ 0
D2
Text GLabel 7900 2250 2    60   Input ~ 0
D2
Wire Wire Line
	7900 2250 7850 2250
Wire Wire Line
	7850 2350 8650 2350
Text GLabel 7900 1850 1    60   Input ~ 0
RX
Text GLabel 8050 1850 1    60   Input ~ 0
TX
Wire Wire Line
	8050 1850 8050 2150
Wire Wire Line
	8050 2150 7850 2150
Wire Wire Line
	7850 2050 7900 2050
Wire Wire Line
	7900 2050 7900 1850
Text GLabel 7850 3150 2    60   Input ~ 0
D11
Text GLabel 8100 3250 2    60   Input ~ 0
D12
Wire Wire Line
	8100 3250 7850 3250
NoConn ~ 7850 3350
NoConn ~ 6850 2950
NoConn ~ 6850 3050
NoConn ~ 6850 3150
NoConn ~ 6850 3250
NoConn ~ 6850 3350
NoConn ~ 6850 2050
NoConn ~ 6850 2150
NoConn ~ 7250 1650
NoConn ~ 7450 1650
$Comp
L chiller-rescue:C C4
U 1 1 5BD50FC7
P 7350 1350
F 0 "C4" V 7098 1350 50  0000 C CNN
F 1 "100n" V 7189 1350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7388 1200 50  0001 C CNN
F 3 "" H 7350 1350 50  0001 C CNN
	1    7350 1350
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 5BD510BB
P 7000 1350
F 0 "#PWR0108" H 7000 1200 50  0001 C CNN
F 1 "+5V" V 7015 1478 50  0000 L CNN
F 2 "" H 7000 1350 50  0001 C CNN
F 3 "" H 7000 1350 50  0001 C CNN
	1    7000 1350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7150 1650 7150 1350
Wire Wire Line
	7150 1350 7000 1350
Wire Wire Line
	7200 1350 7150 1350
Connection ~ 7150 1350
$Comp
L power:GND #PWR0109
U 1 1 5BD5CB7B
P 7650 1450
F 0 "#PWR0109" H 7650 1200 50  0001 C CNN
F 1 "GND" H 7655 1277 50  0000 C CNN
F 2 "" H 7650 1450 50  0001 C CNN
F 3 "" H 7650 1450 50  0001 C CNN
	1    7650 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 1450 7650 1350
Wire Wire Line
	7650 1350 7500 1350
Text GLabel 6600 2650 0    60   Input ~ 0
A0
Text GLabel 6800 2750 0    60   Input ~ 0
A1
Wire Wire Line
	6800 2750 6850 2750
Wire Wire Line
	6850 2650 6600 2650
$Comp
L power:GND #PWR0110
U 1 1 5BD6EE20
P 5900 2050
F 0 "#PWR0110" H 5900 1800 50  0001 C CNN
F 1 "GND" H 5905 1877 50  0000 C CNN
F 2 "" H 5900 2050 50  0001 C CNN
F 3 "" H 5900 2050 50  0001 C CNN
	1    5900 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 2050 5900 1950
Wire Wire Line
	5900 1950 5800 1950
Wire Wire Line
	5500 1950 5400 1950
Connection ~ 5400 1950
$Comp
L chiller-rescue:R R6
U 1 1 5BD7FD27
P 4200 5200
F 0 "R6" V 4407 5200 50  0000 C CNN
F 1 "1K" V 4316 5200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4130 5200 50  0001 C CNN
F 3 "" H 4200 5200 50  0001 C CNN
	1    4200 5200
	0    -1   -1   0   
$EndComp
$Comp
L chiller-rescue:R R7
U 1 1 5BD7FE26
P 4450 5400
F 0 "R7" H 4520 5446 50  0000 L CNN
F 1 "10K" H 4520 5355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4380 5400 50  0001 C CNN
F 3 "" H 4450 5400 50  0001 C CNN
	1    4450 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 5400 3700 5600
Wire Wire Line
	4450 5550 4450 5600
Wire Wire Line
	4450 5600 3700 5600
Connection ~ 3700 5600
Wire Wire Line
	3700 5600 3700 5650
Wire Wire Line
	4000 5200 4050 5200
Wire Wire Line
	4350 5200 4450 5200
Wire Wire Line
	4450 5200 4450 5250
Text GLabel 4600 5200 2    60   Input ~ 0
D11
Wire Wire Line
	4600 5200 4450 5200
Connection ~ 4450 5200
$Comp
L chiller-rescue:R R8
U 1 1 5BDA36EC
P 4200 6800
F 0 "R8" V 3993 6800 50  0000 C CNN
F 1 "1K" V 4084 6800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4130 6800 50  0001 C CNN
F 3 "" H 4200 6800 50  0001 C CNN
	1    4200 6800
	0    1    1    0   
$EndComp
$Comp
L chiller-rescue:R R9
U 1 1 5BDA37A7
P 4450 7000
F 0 "R9" H 4520 7046 50  0000 L CNN
F 1 "10K" H 4520 6955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4380 7000 50  0001 C CNN
F 3 "" H 4450 7000 50  0001 C CNN
	1    4450 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 7150 4450 7200
Wire Wire Line
	4450 7200 3700 7200
Connection ~ 3700 7200
Wire Wire Line
	3700 7200 3700 7250
Wire Wire Line
	4000 6800 4050 6800
Wire Wire Line
	4350 6800 4450 6800
Wire Wire Line
	4450 6800 4450 6850
Text GLabel 4600 6800 2    60   Input ~ 0
A1
Wire Wire Line
	4600 6800 4450 6800
Connection ~ 4450 6800
$Comp
L Transistor_FET:BSS138 Q4
U 1 1 5BDBD580
P 7500 5000
F 0 "Q4" H 7705 5046 50  0000 L CNN
F 1 "BSS138" H 7705 4955 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7700 4925 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 7500 5000 50  0001 L CNN
	1    7500 5000
	1    0    0    -1  
$EndComp
$Comp
L chiller-rescue:R R11
U 1 1 5BDBD62A
P 7150 5250
F 0 "R11" H 7220 5296 50  0000 L CNN
F 1 "10K" H 7220 5205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7080 5250 50  0001 C CNN
F 3 "" H 7150 5250 50  0001 C CNN
	1    7150 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 5450 7150 5450
Wire Wire Line
	7150 5450 7150 5400
Wire Wire Line
	7600 5200 7600 5450
Connection ~ 7600 5450
Wire Wire Line
	7150 5000 7150 5100
Connection ~ 7150 5000
Wire Wire Line
	7150 5000 7300 5000
Wire Wire Line
	7600 5450 7600 5500
Text GLabel 6350 5000 0    60   Input ~ 0
D12
NoConn ~ 6850 2450
$Comp
L Transistor_FET:BSS138 Q1
U 1 1 5BDD9CE1
P 1650 6800
F 0 "Q1" H 1856 6846 50  0000 L CNN
F 1 "BSS138" H 1856 6755 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 1850 6725 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 1650 6800 50  0001 L CNN
	1    1650 6800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1550 6450 1550 6600
Wire Wire Line
	1550 7000 1550 7200
$Comp
L chiller-rescue:R R5
U 1 1 5BE21940
P 2350 7000
F 0 "R5" H 2420 7046 50  0000 L CNN
F 1 "10K" H 2420 6955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2280 7000 50  0001 C CNN
F 3 "" H 2350 7000 50  0001 C CNN
	1    2350 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 7150 2350 7200
Wire Wire Line
	2350 7200 1550 7200
Connection ~ 1550 7200
Wire Wire Line
	1550 7200 1550 7250
Wire Wire Line
	1950 6800 1850 6800
Wire Wire Line
	2250 6800 2350 6800
Wire Wire Line
	2350 6800 2350 6850
Text GLabel 2500 6800 2    60   Input ~ 0
A0
Wire Wire Line
	2500 6800 2350 6800
Connection ~ 2350 6800
$Comp
L tinkerforge:D D2
U 1 1 5BE4C9BC
P 3850 6400
F 0 "D2" V 3804 6478 50  0000 L CNN
F 1 "SS34" V 3895 6478 50  0000 L CNN
F 2 "Diode_SMD:D_SMC" H 3850 6400 50  0001 C CNN
F 3 "" H 3850 6400 50  0000 C CNN
	1    3850 6400
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 6550 3850 6600
Wire Wire Line
	3850 6600 3700 6600
Connection ~ 3700 6600
Wire Wire Line
	3700 6150 3700 6200
Wire Wire Line
	3700 6200 3850 6200
Wire Wire Line
	3850 6200 3850 6250
Connection ~ 3700 6200
Wire Wire Line
	3700 6200 3700 6350
Wire Wire Line
	3700 4800 3700 5000
$Comp
L chiller-rescue:R R12
U 1 1 5BEA684A
P 1700 2350
F 0 "R12" H 1770 2396 50  0000 L CNN
F 1 "10K" H 1770 2305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1630 2350 50  0001 C CNN
F 3 "" H 1700 2350 50  0001 C CNN
	1    1700 2350
	1    0    0    -1  
$EndComp
$Comp
L chiller-rescue:R R13
U 1 1 5BEA6921
P 1700 2750
F 0 "R13" H 1770 2796 50  0000 L CNN
F 1 "10K" H 1770 2705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1630 2750 50  0001 C CNN
F 3 "" H 1700 2750 50  0001 C CNN
	1    1700 2750
	1    0    0    -1  
$EndComp
$Comp
L chiller-rescue:C C6
U 1 1 5BEA6AB7
P 1300 2750
F 0 "C6" H 1415 2796 50  0000 L CNN
F 1 "10u" H 1415 2705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1338 2600 50  0001 C CNN
F 3 "" H 1300 2750 50  0001 C CNN
	1    1300 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5BEA6B79
P 1700 3000
F 0 "#PWR0111" H 1700 2750 50  0001 C CNN
F 1 "GND" H 1705 2827 50  0000 C CNN
F 2 "" H 1700 3000 50  0001 C CNN
F 3 "" H 1700 3000 50  0001 C CNN
	1    1700 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2900 1700 2950
Wire Wire Line
	1300 2900 1300 2950
Wire Wire Line
	1300 2950 1700 2950
Connection ~ 1700 2950
Wire Wire Line
	1700 2950 1700 3000
Wire Wire Line
	1700 2500 1700 2550
Connection ~ 1700 2550
Wire Wire Line
	1700 2550 1700 2600
Wire Wire Line
	1300 2550 1300 2600
Text GLabel 1850 2000 2    60   Input ~ 0
A2
Wire Wire Line
	1850 2000 1700 2000
Wire Wire Line
	1700 2000 1700 2200
Connection ~ 1700 2000
Wire Wire Line
	1150 2000 1700 2000
Wire Wire Line
	1300 2550 1700 2550
Wire Wire Line
	1150 2100 1300 2100
Wire Wire Line
	1300 2100 1300 2550
Connection ~ 1300 2550
Text Notes 3550 950  0    60   ~ 0
POWER
Text GLabel 6600 2850 0    60   Input ~ 0
A2
Wire Wire Line
	6600 2850 6850 2850
$Comp
L omron:G6B-1114C-US5DC RL1
U 1 1 5BCAFCFB
P 7800 4400
F 0 "RL1" H 7800 4950 50  0000 L CNN
F 1 "G6B-1114C-US5DC" H 7800 4850 50  0000 L CNN
F 2 "modules:DIL-relay" H 7800 4400 50  0001 C CNN
F 3 "" H 7800 4400 50  0001 C CNN
	1    7800 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 4150 6500 4150
Wire Wire Line
	6500 4150 6500 4750
Wire Wire Line
	6500 4750 6850 4750
Connection ~ 6850 4750
Wire Wire Line
	3700 4500 3700 4700
$EndSCHEMATC
