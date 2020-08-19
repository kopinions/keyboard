EESchema Schematic File Version 4
LIBS:connector-cache
EELAYER 29 0
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
L Connector_Generic_MountingPin:Conn_01x02_MountingPin J4
U 1 1 5EB63D84
P 4600 3700
F 0 "J4" V 4476 3780 50  0000 L CNN
F 1 "BAT_OUTPUT" V 4567 3780 50  0000 L CNN
F 2 "Connector_JST:JST_PH_S2B-PH-SM4-TB_1x02-1MP_P2.00mm_Horizontal" H 4600 3700 50  0001 C CNN
F 3 "~" H 4600 3700 50  0001 C CNN
	1    4600 3700
	0    -1   1    0   
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5EB63647
P 4300 3100
F 0 "SW1" V 4346 3052 50  0000 R CNN
F 1 "SW_Push" V 4255 3052 50  0000 R CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H9.5mm" H 4300 3300 50  0001 C CNN
F 3 "~" H 4300 3300 50  0001 C CNN
	1    4300 3100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4700 3500 4900 3500
Wire Wire Line
	4900 3700 4900 3500
Connection ~ 4900 3500
Wire Wire Line
	4900 3500 4950 3500
Wire Wire Line
	4950 2800 4950 3500
Wire Wire Line
	4300 2900 4300 2800
$Comp
L Device:Battery_Cell BT1
U 1 1 5F351599
P 4600 2800
F 0 "BT1" V 4855 2850 50  0000 C CNN
F 1 "Battery_Cell" V 4764 2850 50  0000 C CNN
F 2 "Battery:Battery_Panasonic_CR1025-VSK_Vertical_CircularHoles" V 4600 2860 50  0001 C CNN
F 3 "~" V 4600 2860 50  0001 C CNN
	1    4600 2800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4300 2800 4400 2800
Wire Wire Line
	4700 2800 4950 2800
Wire Wire Line
	4300 3300 4300 3500
Wire Wire Line
	4300 3500 4600 3500
$EndSCHEMATC
