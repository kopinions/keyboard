EESchema Schematic File Version 4
EELAYER 30 0
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
L Diode:1N914 D-1
U 1 1 5E9050C2
P 3600 1450
F 0 "D-1" V 3646 1371 50  0001 R CNN
F 1 "D" V 3555 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 3600 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 3600 1450 50  0001 C CNN
	1    3600 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2900 1600 3600 1600
Connection ~ 3600 1600
Wire Wire Line
	3600 1600 4100 1600
$Comp
L keyboard:SW_SPST SW-7
U 1 1 5E90EDA8
P 4300 1300
F 0 "SW-7" H 4300 1443 50  0001 C CNN
F 1 "SW_SPST" H 4300 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 4300 1300 50  0001 C CNN
F 3 "~" H 4300 1300 50  0001 C CNN
F 4 "KEY" H 4300 1400 50  0000 C CNN "Key"
	1    4300 1300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-7
U 1 1 5E90EDB2
P 4100 1450
F 0 "D-7" V 4146 1371 50  0001 R CNN
F 1 "D" V 4055 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 4100 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 4100 1450 50  0001 C CNN
	1    4100 1450
	0    -1   -1   0   
$EndComp
Connection ~ 4100 1600
Wire Wire Line
	4100 1600 4600 1600
$Comp
L keyboard:SW_SPST SW-13
U 1 1 5E91416B
P 4800 1300
F 0 "SW-13" H 4800 1443 50  0001 C CNN
F 1 "SW_SPST" H 4800 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 4800 1300 50  0001 C CNN
F 3 "~" H 4800 1300 50  0001 C CNN
F 4 "KEY" H 4800 1300 50  0000 C CNN "Key"
	1    4800 1300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-13
U 1 1 5E914171
P 4600 1450
F 0 "D-13" V 4646 1371 50  0001 R CNN
F 1 "D" V 4555 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 4600 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 4600 1450 50  0001 C CNN
	1    4600 1450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-19
U 1 1 5E9148B8
P 5300 1300
F 0 "SW-19" H 5300 1443 50  0001 C CNN
F 1 "SW_SPST" H 5300 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 5300 1300 50  0001 C CNN
F 3 "~" H 5300 1300 50  0001 C CNN
	1    5300 1300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-19
U 1 1 5E9148BE
P 5100 1450
F 0 "D-19" V 5146 1371 50  0001 R CNN
F 1 "D" V 5055 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 5100 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 5100 1450 50  0001 C CNN
	1    5100 1450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-25
U 1 1 5E916405
P 5800 1300
F 0 "SW-25" H 5800 1443 50  0001 C CNN
F 1 "SW_SPST" H 5800 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 5800 1300 50  0001 C CNN
F 3 "~" H 5800 1300 50  0001 C CNN
	1    5800 1300
	1    0    0    -1  
$EndComp
Connection ~ 4600 1600
Wire Wire Line
	4600 1600 5100 1600
Connection ~ 5100 1600
Wire Wire Line
	5100 1600 5600 1600
Connection ~ 5600 1600
Wire Wire Line
	5000 750  5000 1300
Wire Wire Line
	5500 750  5500 1300
Wire Wire Line
	6000 750  6000 1300
Text GLabel 4000 750  0    50   Input ~ 0
COL1
Text GLabel 4500 750  0    50   Input ~ 0
COL2
Text GLabel 5000 750  0    50   Input ~ 0
COL3
Text GLabel 5500 750  0    50   Input ~ 0
COL4
Text GLabel 6000 750  0    50   Input ~ 0
COL5
Text GLabel 6500 750  0    50   Input ~ 0
COL6
Text GLabel 7000 750  0    50   Input ~ 0
COL7
Text GLabel 7500 750  0    50   Input ~ 0
COL8
Text GLabel 2900 1600 0    50   Input ~ 0
ROW1
Text GLabel 8000 750  0    50   Input ~ 0
COL9
Text GLabel 8500 750  0    50   Input ~ 0
COL10
Text GLabel 9000 750  0    50   Input ~ 0
COL11
Text GLabel 9500 750  0    50   Input ~ 0
COL12
Text GLabel 10000 750  0    50   Input ~ 0
COL13
Text GLabel 10500 750  0    50   Input ~ 0
COL14
Text GLabel 11000 750  0    50   Input ~ 0
COL15
Text GLabel 2900 2200 0    50   Input ~ 0
ROW2
Text GLabel 2900 2800 0    50   Input ~ 0
ROW3
Text GLabel 2900 3400 0    50   Input ~ 0
ROW4
Text GLabel 2900 4000 0    50   Input ~ 0
ROW5
Text GLabel 1200 5350 0    50   Input ~ 0
ROW1
Text GLabel 1200 5450 0    50   Input ~ 0
ROW2
Text GLabel 1200 5550 0    50   Input ~ 0
ROW3
Text GLabel 1200 5650 0    50   Input ~ 0
ROW4
Text GLabel 1200 5750 0    50   Input ~ 0
ROW5
Text GLabel 1200 5850 0    50   Input ~ 0
ROW6
Text GLabel 1200 5950 0    50   Input ~ 0
COL1
Text GLabel 1200 6050 0    50   Input ~ 0
COL2
Text GLabel 1200 6150 0    50   Input ~ 0
COL3
Text GLabel 1200 6250 0    50   Input ~ 0
COL4
Text GLabel 1200 6350 0    50   Input ~ 0
COL5
Text GLabel 1200 6450 0    50   Input ~ 0
COL6
Text GLabel 1200 6550 0    50   Input ~ 0
COL7
Text GLabel 1200 6650 0    50   Input ~ 0
COL8
Text GLabel 1200 6750 0    50   Input ~ 0
COL9
Text GLabel 1200 6850 0    50   Input ~ 0
COL10
Text GLabel 1200 6950 0    50   Input ~ 0
COL11
Text GLabel 1200 7050 0    50   Input ~ 0
COL12
Text GLabel 1200 7150 0    50   Input ~ 0
COL13
Text GLabel 1200 7250 0    50   Input ~ 0
COL14
Text GLabel 1700 7250 2    50   Input ~ 0
COL15
$Comp
L Diode:1N914 D-25
U 1 1 5E91640B
P 5600 1450
F 0 "D-25" V 5646 1371 50  0001 R CNN
F 1 "D" V 5555 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 5600 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 5600 1450 50  0001 C CNN
	1    5600 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5600 1600 6100 1600
Wire Wire Line
	6500 750  6500 1300
$Comp
L keyboard:SW_SPST SW-31
U 1 1 5E9D6F85
P 6300 1300
F 0 "SW-31" H 6300 1443 50  0001 C CNN
F 1 "SW_SPST" H 6300 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 6300 1300 50  0001 C CNN
F 3 "~" H 6300 1300 50  0001 C CNN
	1    6300 1300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-30
U 1 1 5E9D6F8B
P 6100 1450
F 0 "D-30" V 6146 1371 50  0001 R CNN
F 1 "D" V 6055 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 6100 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 6100 1450 50  0001 C CNN
	1    6100 1450
	0    -1   -1   0   
$EndComp
Connection ~ 6100 1600
Wire Wire Line
	6100 1600 6600 1600
Wire Wire Line
	2900 2200 3600 2200
Wire Wire Line
	2900 2800 3600 2800
Wire Wire Line
	2900 3400 3600 3400
Wire Wire Line
	2900 4000 3600 4000
Wire Wire Line
	2900 4600 3600 4600
$Comp
L keyboard:SW_SPST SW-36
U 1 1 5EA16B54
P 6800 1300
F 0 "SW-36" H 6800 1450 50  0001 C CNN
F 1 "SW_SPST" H 6800 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 6800 1300 50  0001 C CNN
F 3 "~" H 6800 1300 50  0001 C CNN
	1    6800 1300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-35
U 1 1 5EA16B5E
P 6600 1450
F 0 "D-35" V 6646 1371 50  0001 R CNN
F 1 "D" V 6555 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 6600 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 6600 1450 50  0001 C CNN
	1    6600 1450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-41
U 1 1 5EA16B68
P 7300 1300
F 0 "SW-41" H 7300 1443 50  0001 C CNN
F 1 "SW_SPST" H 7300 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 7300 1300 50  0001 C CNN
F 3 "~" H 7300 1300 50  0001 C CNN
	1    7300 1300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-40
U 1 1 5EA16B72
P 7100 1450
F 0 "D-40" V 7146 1371 50  0001 R CNN
F 1 "D" V 7055 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 7100 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 7100 1450 50  0001 C CNN
	1    7100 1450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-46
U 1 1 5EA16B7C
P 7800 1300
F 0 "SW-46" H 7800 1443 50  0001 C CNN
F 1 "SW_SPST" H 7800 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 7800 1300 50  0001 C CNN
F 3 "~" H 7800 1300 50  0001 C CNN
	1    7800 1300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-45
U 1 1 5EA16B86
P 7600 1450
F 0 "D-45" V 7646 1371 50  0001 R CNN
F 1 "D" V 7555 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 7600 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 7600 1450 50  0001 C CNN
	1    7600 1450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-51
U 1 1 5EA16B90
P 8300 1300
F 0 "SW-51" H 8300 1443 50  0001 C CNN
F 1 "SW_SPST" H 8300 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 8300 1300 50  0001 C CNN
F 3 "~" H 8300 1300 50  0001 C CNN
	1    8300 1300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-50
U 1 1 5EA16B9A
P 8100 1450
F 0 "D-50" V 8146 1371 50  0001 R CNN
F 1 "D" V 8055 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 8100 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 8100 1450 50  0001 C CNN
	1    8100 1450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-56
U 1 1 5EA16BA4
P 8800 1300
F 0 "SW-56" H 8800 1443 50  0001 C CNN
F 1 "SW_SPST" H 8800 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 8800 1300 50  0001 C CNN
F 3 "~" H 8800 1300 50  0001 C CNN
	1    8800 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 750  7000 1300
Wire Wire Line
	7500 750  7500 1300
Wire Wire Line
	8000 750  8000 1300
Wire Wire Line
	8500 750  8500 1300
Wire Wire Line
	9000 750  9000 1300
$Comp
L Diode:1N914 D-55
U 1 1 5EA16BB3
P 8600 1450
F 0 "D-55" V 8646 1371 50  0001 R CNN
F 1 "D" V 8555 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 8600 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 8600 1450 50  0001 C CNN
	1    8600 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9500 750  9500 1300
$Comp
L keyboard:SW_SPST SW-62
U 1 1 5EA16BBE
P 9300 1300
F 0 "SW-62" H 9300 1443 50  0001 C CNN
F 1 "SW_SPST" H 9300 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 9300 1300 50  0001 C CNN
F 3 "~" H 9300 1300 50  0001 C CNN
	1    9300 1300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-61
U 1 1 5EA16BC8
P 9100 1450
F 0 "D-61" V 9146 1371 50  0001 R CNN
F 1 "D" V 9055 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 9100 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9100 1450 50  0001 C CNN
	1    9100 1450
	0    -1   -1   0   
$EndComp
Connection ~ 6600 1600
Wire Wire Line
	6600 1600 7100 1600
Connection ~ 7100 1600
Wire Wire Line
	7100 1600 7600 1600
Connection ~ 7600 1600
Wire Wire Line
	7600 1600 8100 1600
Connection ~ 8100 1600
Wire Wire Line
	8100 1600 8600 1600
Connection ~ 8600 1600
Wire Wire Line
	8600 1600 9100 1600
Connection ~ 9100 1600
Wire Wire Line
	9100 1600 9600 1600
$Comp
L keyboard:SW_SPST SW-68
U 1 1 5EA2C70F
P 9800 1300
F 0 "SW-68" H 9800 1443 50  0001 C CNN
F 1 "SW_SPST" H 9800 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 9800 1300 50  0001 C CNN
F 3 "~" H 9800 1300 50  0001 C CNN
	1    9800 1300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-67
U 1 1 5EA2C719
P 9600 1450
F 0 "D-67" V 9646 1371 50  0001 R CNN
F 1 "D" V 9555 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 9600 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9600 1450 50  0001 C CNN
	1    9600 1450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-74
U 1 1 5EA2C723
P 10300 1300
F 0 "SW-74" H 10300 1443 50  0001 C CNN
F 1 "SW_SPST" H 10300 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 10300 1300 50  0001 C CNN
F 3 "~" H 10300 1300 50  0001 C CNN
	1    10300 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 750  10000 1300
Wire Wire Line
	10500 750  10500 1300
$Comp
L Diode:1N914 D-73
U 1 1 5EA2C72F
P 10100 1450
F 0 "D-73" V 10146 1371 50  0001 R CNN
F 1 "D" V 10055 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 10100 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 10100 1450 50  0001 C CNN
	1    10100 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	11000 750  11000 1300
$Comp
L keyboard:SW_SPST SW-80
U 1 1 5EA2C73A
P 10800 1300
F 0 "SW-80" H 10800 1443 50  0001 C CNN
F 1 "SW_SPST" H 10800 1444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 10800 1300 50  0001 C CNN
F 3 "~" H 10800 1300 50  0001 C CNN
	1    10800 1300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-79
U 1 1 5EA2C744
P 10600 1450
F 0 "D-79" V 10646 1371 50  0001 R CNN
F 1 "D" V 10555 1371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 10600 1275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 10600 1450 50  0001 C CNN
	1    10600 1450
	0    -1   -1   0   
$EndComp
Connection ~ 9600 1600
Wire Wire Line
	9600 1600 10100 1600
Connection ~ 10100 1600
Wire Wire Line
	10100 1600 10600 1600
$Comp
L keyboard:SW_SPST SW-2
U 1 1 5EA32686
P 3800 1900
F 0 "SW-2" H 3800 2050 50  0001 C CNN
F 1 "SW_SPST" H 3800 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 3800 1900 50  0001 C CNN
F 3 "~" H 3800 1900 50  0001 C CNN
F 4 "GARVE" H 3800 1900 50  0001 C CNN "Key"
	1    3800 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-2
U 1 1 5EA32690
P 3600 2050
F 0 "D-2" V 3646 1971 50  0001 R CNN
F 1 "D" V 3555 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 3600 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 3600 2050 50  0001 C CNN
	1    3600 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-8
U 1 1 5EA3269A
P 4300 1900
F 0 "SW-8" H 4300 2043 50  0001 C CNN
F 1 "SW_SPST" H 4300 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 4300 1900 50  0001 C CNN
F 3 "~" H 4300 1900 50  0001 C CNN
	1    4300 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-8
U 1 1 5EA326A4
P 4100 2050
F 0 "D-8" V 4146 1971 50  0001 R CNN
F 1 "D" V 4055 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 4100 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 4100 2050 50  0001 C CNN
	1    4100 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-14
U 1 1 5EA326AE
P 4800 1900
F 0 "SW-14" H 4800 2043 50  0001 C CNN
F 1 "SW_SPST" H 4800 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 4800 1900 50  0001 C CNN
F 3 "~" H 4800 1900 50  0001 C CNN
	1    4800 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-14
U 1 1 5EA326B8
P 4600 2050
F 0 "D-14" V 4646 1971 50  0001 R CNN
F 1 "D" V 4555 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 4600 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 4600 2050 50  0001 C CNN
	1    4600 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-20
U 1 1 5EA326C2
P 5300 1900
F 0 "SW-20" H 5300 2043 50  0001 C CNN
F 1 "SW_SPST" H 5300 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 5300 1900 50  0001 C CNN
F 3 "~" H 5300 1900 50  0001 C CNN
	1    5300 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-20
U 1 1 5EA326CC
P 5100 2050
F 0 "D-20" V 5146 1971 50  0001 R CNN
F 1 "D" V 5055 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 5100 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 5100 2050 50  0001 C CNN
	1    5100 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-26
U 1 1 5EA326D6
P 5800 1900
F 0 "SW-26" H 5800 2043 50  0001 C CNN
F 1 "SW_SPST" H 5800 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 5800 1900 50  0001 C CNN
F 3 "~" H 5800 1900 50  0001 C CNN
	1    5800 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-26
U 1 1 5EA326E5
P 5600 2050
F 0 "D-26" V 5646 1971 50  0001 R CNN
F 1 "D" V 5555 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 5600 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 5600 2050 50  0001 C CNN
	1    5600 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-32
U 1 1 5EA326F0
P 6300 1900
F 0 "SW-32" H 6300 2043 50  0001 C CNN
F 1 "SW_SPST" H 6300 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 6300 1900 50  0001 C CNN
F 3 "~" H 6300 1900 50  0001 C CNN
	1    6300 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-31
U 1 1 5EA326FA
P 6100 2050
F 0 "D-31" V 6146 1971 50  0001 R CNN
F 1 "D" V 6055 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 6100 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 6100 2050 50  0001 C CNN
	1    6100 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-37
U 1 1 5EA32704
P 6800 1900
F 0 "SW-37" H 6800 2050 50  0001 C CNN
F 1 "SW_SPST" H 6800 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 6800 1900 50  0001 C CNN
F 3 "~" H 6800 1900 50  0001 C CNN
	1    6800 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-36
U 1 1 5EA3270E
P 6600 2050
F 0 "D-36" V 6646 1971 50  0001 R CNN
F 1 "D" V 6555 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 6600 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 6600 2050 50  0001 C CNN
	1    6600 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-42
U 1 1 5EA32718
P 7300 1900
F 0 "SW-42" H 7300 2043 50  0001 C CNN
F 1 "SW_SPST" H 7300 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 7300 1900 50  0001 C CNN
F 3 "~" H 7300 1900 50  0001 C CNN
	1    7300 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-41
U 1 1 5EA32722
P 7100 2050
F 0 "D-41" V 7146 1971 50  0001 R CNN
F 1 "D" V 7055 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 7100 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 7100 2050 50  0001 C CNN
	1    7100 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-47
U 1 1 5EA3272C
P 7800 1900
F 0 "SW-47" H 7800 2043 50  0001 C CNN
F 1 "SW_SPST" H 7800 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 7800 1900 50  0001 C CNN
F 3 "~" H 7800 1900 50  0001 C CNN
	1    7800 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-46
U 1 1 5EA32736
P 7600 2050
F 0 "D-46" V 7646 1971 50  0001 R CNN
F 1 "D" V 7555 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 7600 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 7600 2050 50  0001 C CNN
	1    7600 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-52
U 1 1 5EA32740
P 8300 1900
F 0 "SW-52" H 8300 2043 50  0001 C CNN
F 1 "SW_SPST" H 8300 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 8300 1900 50  0001 C CNN
F 3 "~" H 8300 1900 50  0001 C CNN
	1    8300 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-51
U 1 1 5EA3274A
P 8100 2050
F 0 "D-51" V 8146 1971 50  0001 R CNN
F 1 "D" V 8055 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 8100 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 8100 2050 50  0001 C CNN
	1    8100 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-57
U 1 1 5EA32754
P 8800 1900
F 0 "SW-57" H 8800 2043 50  0001 C CNN
F 1 "SW_SPST" H 8800 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 8800 1900 50  0001 C CNN
F 3 "~" H 8800 1900 50  0001 C CNN
	1    8800 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-56
U 1 1 5EA32763
P 8600 2050
F 0 "D-56" V 8646 1971 50  0001 R CNN
F 1 "D" V 8555 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 8600 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 8600 2050 50  0001 C CNN
	1    8600 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-63
U 1 1 5EA3276E
P 9300 1900
F 0 "SW-63" H 9300 2043 50  0001 C CNN
F 1 "SW_SPST" H 9300 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 9300 1900 50  0001 C CNN
F 3 "~" H 9300 1900 50  0001 C CNN
	1    9300 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-62
U 1 1 5EA32778
P 9100 2050
F 0 "D-62" V 9146 1971 50  0001 R CNN
F 1 "D" V 9055 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 9100 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9100 2050 50  0001 C CNN
	1    9100 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-69
U 1 1 5EA32782
P 9800 1900
F 0 "SW-69" H 9800 2043 50  0001 C CNN
F 1 "SW_SPST" H 9800 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 9800 1900 50  0001 C CNN
F 3 "~" H 9800 1900 50  0001 C CNN
	1    9800 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-68
U 1 1 5EA3278C
P 9600 2050
F 0 "D-68" V 9646 1971 50  0001 R CNN
F 1 "D" V 9555 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 9600 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9600 2050 50  0001 C CNN
	1    9600 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-75
U 1 1 5EA32796
P 10300 1900
F 0 "SW-75" H 10300 2043 50  0001 C CNN
F 1 "SW_SPST" H 10300 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_2.00u_Plate" H 10300 1900 50  0001 C CNN
F 3 "~" H 10300 1900 50  0001 C CNN
	1    10300 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-74
U 1 1 5EA327A2
P 10100 2050
F 0 "D-74" V 10146 1971 50  0001 R CNN
F 1 "D" V 10055 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 10100 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 10100 2050 50  0001 C CNN
	1    10100 2050
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-81
U 1 1 5EA327AD
P 10800 1900
F 0 "SW-81" H 10800 2043 50  0001 C CNN
F 1 "SW_SPST" H 10800 2044 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 10800 1900 50  0001 C CNN
F 3 "~" H 10800 1900 50  0001 C CNN
	1    10800 1900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-80
U 1 1 5EA327B7
P 10600 2050
F 0 "D-80" V 10646 1971 50  0001 R CNN
F 1 "D" V 10555 1971 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 10600 1875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 10600 2050 50  0001 C CNN
	1    10600 2050
	0    -1   -1   0   
$EndComp
Connection ~ 11000 1300
Connection ~ 3600 2200
Wire Wire Line
	3600 2200 4100 2200
Connection ~ 4100 2200
Wire Wire Line
	4100 2200 4600 2200
Connection ~ 4600 2200
Wire Wire Line
	4600 2200 5100 2200
Connection ~ 5100 2200
Wire Wire Line
	5100 2200 5600 2200
Connection ~ 5600 2200
Wire Wire Line
	5600 2200 6100 2200
Connection ~ 6100 2200
Wire Wire Line
	6100 2200 6600 2200
Connection ~ 6600 2200
Wire Wire Line
	6600 2200 7100 2200
Connection ~ 7100 2200
Wire Wire Line
	7100 2200 7600 2200
Connection ~ 7600 2200
Wire Wire Line
	7600 2200 8100 2200
Connection ~ 8100 2200
Wire Wire Line
	8100 2200 8600 2200
Connection ~ 8600 2200
Wire Wire Line
	8600 2200 9100 2200
Connection ~ 9100 2200
Wire Wire Line
	9100 2200 9600 2200
Connection ~ 9600 2200
Wire Wire Line
	9600 2200 10100 2200
Connection ~ 10100 2200
Wire Wire Line
	10100 2200 10600 2200
Wire Wire Line
	4000 750  4000 1300
Connection ~ 4000 1300
Wire Wire Line
	4000 1300 4000 1900
Wire Wire Line
	4500 750  4500 1300
Connection ~ 4500 1300
Wire Wire Line
	4500 1300 4500 1900
Wire Wire Line
	5000 1300 5000 1900
Connection ~ 5000 1300
Wire Wire Line
	5500 1300 5500 1900
Connection ~ 5500 1300
Wire Wire Line
	6000 1300 6000 1900
Connection ~ 6000 1300
Wire Wire Line
	6500 1300 6500 1900
Connection ~ 6500 1300
Wire Wire Line
	7000 1300 7000 1900
Connection ~ 7000 1300
Wire Wire Line
	7500 1300 7500 1900
Connection ~ 7500 1300
Wire Wire Line
	8500 1300 8500 1900
Connection ~ 8500 1300
Wire Wire Line
	8000 1300 8000 1900
Connection ~ 8000 1300
Wire Wire Line
	9000 1300 9000 1900
Connection ~ 9000 1300
Wire Wire Line
	9500 1300 9500 1900
Connection ~ 9500 1300
Wire Wire Line
	10000 1300 10000 1900
Connection ~ 10000 1300
Wire Wire Line
	10500 1300 10500 1900
Connection ~ 10500 1300
Wire Wire Line
	11000 1300 11000 1900
$Comp
L keyboard:SW_SPST SW-3
U 1 1 5EA94D27
P 3800 2500
F 0 "SW-3" H 3800 2650 50  0001 C CNN
F 1 "SW_SPST" H 3800 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.50u_Plate" H 3800 2500 50  0001 C CNN
F 3 "~" H 3800 2500 50  0001 C CNN
F 4 "TAB" H 3800 2500 50  0001 C CNN "Key"
	1    3800 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-3
U 1 1 5EA94D31
P 3600 2650
F 0 "D-3" V 3646 2571 50  0001 R CNN
F 1 "D" V 3555 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 3600 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 3600 2650 50  0001 C CNN
	1    3600 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-9
U 1 1 5EA94D3B
P 4300 2500
F 0 "SW-9" H 4300 2643 50  0001 C CNN
F 1 "SW_SPST" H 4300 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 4300 2500 50  0001 C CNN
F 3 "~" H 4300 2500 50  0001 C CNN
	1    4300 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-9
U 1 1 5EA94D45
P 4100 2650
F 0 "D-9" V 4146 2571 50  0001 R CNN
F 1 "D" V 4055 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 4100 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 4100 2650 50  0001 C CNN
	1    4100 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-15
U 1 1 5EA94D4F
P 4800 2500
F 0 "SW-15" H 4800 2643 50  0001 C CNN
F 1 "SW_SPST" H 4800 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 4800 2500 50  0001 C CNN
F 3 "~" H 4800 2500 50  0001 C CNN
F 4 "KEY" H 4800 2600 50  0000 C CNN "Key"
	1    4800 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-15
U 1 1 5EA94D59
P 4600 2650
F 0 "D-15" V 4646 2571 50  0001 R CNN
F 1 "D" V 4555 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 4600 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 4600 2650 50  0001 C CNN
	1    4600 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-21
U 1 1 5EA94D63
P 5300 2500
F 0 "SW-21" H 5300 2643 50  0001 C CNN
F 1 "SW_SPST" H 5300 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 5300 2500 50  0001 C CNN
F 3 "~" H 5300 2500 50  0001 C CNN
	1    5300 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-21
U 1 1 5EA94D6D
P 5100 2650
F 0 "D-21" V 5146 2571 50  0001 R CNN
F 1 "D" V 5055 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 5100 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 5100 2650 50  0001 C CNN
	1    5100 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-27
U 1 1 5EA94D77
P 5800 2500
F 0 "SW-27" H 5800 2643 50  0001 C CNN
F 1 "SW_SPST" H 5800 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 5800 2500 50  0001 C CNN
F 3 "~" H 5800 2500 50  0001 C CNN
	1    5800 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-27
U 1 1 5EA94D81
P 5600 2650
F 0 "D-27" V 5646 2571 50  0001 R CNN
F 1 "D" V 5555 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 5600 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 5600 2650 50  0001 C CNN
	1    5600 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-33
U 1 1 5EA94D8B
P 6300 2500
F 0 "SW-33" H 6300 2643 50  0001 C CNN
F 1 "SW_SPST" H 6300 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 6300 2500 50  0001 C CNN
F 3 "~" H 6300 2500 50  0001 C CNN
	1    6300 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-32
U 1 1 5EA94D95
P 6100 2650
F 0 "D-32" V 6146 2571 50  0001 R CNN
F 1 "D" V 6055 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 6100 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 6100 2650 50  0001 C CNN
	1    6100 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-38
U 1 1 5EA94D9F
P 6800 2500
F 0 "SW-38" H 6800 2650 50  0001 C CNN
F 1 "SW_SPST" H 6800 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 6800 2500 50  0001 C CNN
F 3 "~" H 6800 2500 50  0001 C CNN
	1    6800 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-37
U 1 1 5EA94DA9
P 6600 2650
F 0 "D-37" V 6646 2571 50  0001 R CNN
F 1 "D" V 6555 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 6600 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 6600 2650 50  0001 C CNN
	1    6600 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-43
U 1 1 5EA94DB3
P 7300 2500
F 0 "SW-43" H 7300 2643 50  0001 C CNN
F 1 "SW_SPST" H 7300 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 7300 2500 50  0001 C CNN
F 3 "~" H 7300 2500 50  0001 C CNN
	1    7300 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-42
U 1 1 5EA94DBD
P 7100 2650
F 0 "D-42" V 7146 2571 50  0001 R CNN
F 1 "D" V 7055 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 7100 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 7100 2650 50  0001 C CNN
	1    7100 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-48
U 1 1 5EA94DC7
P 7800 2500
F 0 "SW-48" H 7800 2643 50  0001 C CNN
F 1 "SW_SPST" H 7800 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 7800 2500 50  0001 C CNN
F 3 "~" H 7800 2500 50  0001 C CNN
	1    7800 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-47
U 1 1 5EA94DD1
P 7600 2650
F 0 "D-47" V 7646 2571 50  0001 R CNN
F 1 "D" V 7555 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 7600 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 7600 2650 50  0001 C CNN
	1    7600 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-53
U 1 1 5EA94DDB
P 8300 2500
F 0 "SW-53" H 8300 2643 50  0001 C CNN
F 1 "SW_SPST" H 8300 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 8300 2500 50  0001 C CNN
F 3 "~" H 8300 2500 50  0001 C CNN
	1    8300 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-52
U 1 1 5EA94DE5
P 8100 2650
F 0 "D-52" V 8146 2571 50  0001 R CNN
F 1 "D" V 8055 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 8100 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 8100 2650 50  0001 C CNN
	1    8100 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-58
U 1 1 5EA94DEF
P 8800 2500
F 0 "SW-58" H 8800 2643 50  0001 C CNN
F 1 "SW_SPST" H 8800 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 8800 2500 50  0001 C CNN
F 3 "~" H 8800 2500 50  0001 C CNN
	1    8800 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-57
U 1 1 5EA94DF9
P 8600 2650
F 0 "D-57" V 8646 2571 50  0001 R CNN
F 1 "D" V 8555 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 8600 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 8600 2650 50  0001 C CNN
	1    8600 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-64
U 1 1 5EA94E03
P 9300 2500
F 0 "SW-64" H 9300 2643 50  0001 C CNN
F 1 "SW_SPST" H 9300 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 9300 2500 50  0001 C CNN
F 3 "~" H 9300 2500 50  0001 C CNN
	1    9300 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-63
U 1 1 5EA94E0D
P 9100 2650
F 0 "D-63" V 9146 2571 50  0001 R CNN
F 1 "D" V 9055 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 9100 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9100 2650 50  0001 C CNN
	1    9100 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-70
U 1 1 5EA94E17
P 9800 2500
F 0 "SW-70" H 9800 2643 50  0001 C CNN
F 1 "SW_SPST" H 9800 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 9800 2500 50  0001 C CNN
F 3 "~" H 9800 2500 50  0001 C CNN
	1    9800 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-69
U 1 1 5EA94E21
P 9600 2650
F 0 "D-69" V 9646 2571 50  0001 R CNN
F 1 "D" V 9555 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 9600 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9600 2650 50  0001 C CNN
	1    9600 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-76
U 1 1 5EA94E2B
P 10300 2500
F 0 "SW-76" H 10300 2643 50  0001 C CNN
F 1 "SW_SPST" H 10300 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.50u_Plate" H 10300 2500 50  0001 C CNN
F 3 "~" H 10300 2500 50  0001 C CNN
	1    10300 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-75
U 1 1 5EA94E35
P 10100 2650
F 0 "D-75" V 10146 2571 50  0001 R CNN
F 1 "D" V 10055 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 10100 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 10100 2650 50  0001 C CNN
	1    10100 2650
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-82
U 1 1 5EA94E3F
P 10800 2500
F 0 "SW-82" H 10800 2643 50  0001 C CNN
F 1 "SW_SPST" H 10800 2644 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 10800 2500 50  0001 C CNN
F 3 "~" H 10800 2500 50  0001 C CNN
	1    10800 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-81
U 1 1 5EA94E49
P 10600 2650
F 0 "D-81" V 10646 2571 50  0001 R CNN
F 1 "D" V 10555 2571 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 10600 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 10600 2650 50  0001 C CNN
	1    10600 2650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4000 1900 4000 2500
Wire Wire Line
	4500 1900 4500 2500
Wire Wire Line
	5000 1900 5000 2500
Wire Wire Line
	5500 1900 5500 2500
Wire Wire Line
	6000 1900 6000 2500
Wire Wire Line
	6500 1900 6500 2500
Wire Wire Line
	7000 1900 7000 2500
Wire Wire Line
	7500 1900 7500 2500
Wire Wire Line
	8500 1900 8500 2500
Wire Wire Line
	8000 1900 8000 2500
Wire Wire Line
	9000 1900 9000 2500
Wire Wire Line
	9500 1900 9500 2500
Wire Wire Line
	10000 1900 10000 2500
Wire Wire Line
	10500 1900 10500 2500
Wire Wire Line
	11000 1900 11000 2500
Connection ~ 3600 2800
Wire Wire Line
	3600 2800 4100 2800
Connection ~ 4000 1900
Connection ~ 4100 2800
Wire Wire Line
	4100 2800 4600 2800
Connection ~ 4500 1900
Connection ~ 4600 2800
Wire Wire Line
	4600 2800 5100 2800
Connection ~ 5000 1900
Connection ~ 5100 2800
Wire Wire Line
	5100 2800 5600 2800
Connection ~ 5500 1900
Connection ~ 5600 2800
Wire Wire Line
	5600 2800 6100 2800
Connection ~ 6000 1900
Connection ~ 6100 2800
Wire Wire Line
	6100 2800 6600 2800
Connection ~ 6500 1900
Connection ~ 6600 2800
Wire Wire Line
	6600 2800 7100 2800
Connection ~ 7000 1900
Connection ~ 7100 2800
Wire Wire Line
	7100 2800 7600 2800
Connection ~ 7500 1900
Connection ~ 7600 2800
Wire Wire Line
	7600 2800 8100 2800
Connection ~ 8000 1900
Connection ~ 8100 2800
Wire Wire Line
	8100 2800 8600 2800
Connection ~ 8500 1900
Connection ~ 8600 2800
Wire Wire Line
	8600 2800 9100 2800
Connection ~ 9000 1900
Connection ~ 9100 2800
Wire Wire Line
	9100 2800 9600 2800
Connection ~ 9500 1900
Connection ~ 9600 2800
Wire Wire Line
	9600 2800 10100 2800
Connection ~ 10000 1900
Connection ~ 10100 2800
Wire Wire Line
	10100 2800 10600 2800
Connection ~ 10500 1900
Connection ~ 11000 1900
$Comp
L keyboard:SW_SPST SW-4
U 1 1 5EAB0A21
P 3800 3100
F 0 "SW-4" H 3800 3250 50  0001 C CNN
F 1 "SW_SPST" H 3800 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.75u_Plate" H 3800 3100 50  0001 C CNN
F 3 "~" H 3800 3100 50  0001 C CNN
	1    3800 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-4
U 1 1 5EAB0A2B
P 3600 3250
F 0 "D-4" V 3646 3171 50  0001 R CNN
F 1 "D" V 3555 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 3600 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 3600 3250 50  0001 C CNN
	1    3600 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-10
U 1 1 5EAB0A35
P 4300 3100
F 0 "SW-10" H 4300 3243 50  0001 C CNN
F 1 "SW_SPST" H 4300 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 4300 3100 50  0001 C CNN
F 3 "~" H 4300 3100 50  0001 C CNN
	1    4300 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-10
U 1 1 5EAB0A3F
P 4100 3250
F 0 "D-10" V 4146 3171 50  0001 R CNN
F 1 "D" V 4055 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 4100 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 4100 3250 50  0001 C CNN
	1    4100 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-16
U 1 1 5EAB0A49
P 4800 3100
F 0 "SW-16" H 4800 3243 50  0001 C CNN
F 1 "SW_SPST" H 4800 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 4800 3100 50  0001 C CNN
F 3 "~" H 4800 3100 50  0001 C CNN
	1    4800 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-16
U 1 1 5EAB0A53
P 4600 3250
F 0 "D-16" V 4646 3171 50  0001 R CNN
F 1 "D" V 4555 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 4600 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 4600 3250 50  0001 C CNN
	1    4600 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-22
U 1 1 5EAB0A5D
P 5300 3100
F 0 "SW-22" H 5300 3243 50  0001 C CNN
F 1 "SW_SPST" H 5300 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 5300 3100 50  0001 C CNN
F 3 "~" H 5300 3100 50  0001 C CNN
	1    5300 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-22
U 1 1 5EAB0A67
P 5100 3250
F 0 "D-22" V 5146 3171 50  0001 R CNN
F 1 "D" V 5055 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 5100 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 5100 3250 50  0001 C CNN
	1    5100 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-28
U 1 1 5EAB0A71
P 5800 3100
F 0 "SW-28" H 5800 3243 50  0001 C CNN
F 1 "SW_SPST" H 5800 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 5800 3100 50  0001 C CNN
F 3 "~" H 5800 3100 50  0001 C CNN
	1    5800 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-28
U 1 1 5EAB0A7B
P 5600 3250
F 0 "D-28" V 5646 3171 50  0001 R CNN
F 1 "D" V 5555 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 5600 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 5600 3250 50  0001 C CNN
	1    5600 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-34
U 1 1 5EAB0A85
P 6300 3100
F 0 "SW-34" H 6300 3243 50  0001 C CNN
F 1 "SW_SPST" H 6300 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 6300 3100 50  0001 C CNN
F 3 "~" H 6300 3100 50  0001 C CNN
	1    6300 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-33
U 1 1 5EAB0A8F
P 6100 3250
F 0 "D-33" V 6146 3171 50  0001 R CNN
F 1 "D" V 6055 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 6100 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 6100 3250 50  0001 C CNN
	1    6100 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-39
U 1 1 5EAB0A99
P 6800 3100
F 0 "SW-39" H 6800 3250 50  0001 C CNN
F 1 "SW_SPST" H 6800 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 6800 3100 50  0001 C CNN
F 3 "~" H 6800 3100 50  0001 C CNN
	1    6800 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-38
U 1 1 5EAB0AA3
P 6600 3250
F 0 "D-38" V 6646 3171 50  0001 R CNN
F 1 "D" V 6555 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 6600 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 6600 3250 50  0001 C CNN
	1    6600 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-44
U 1 1 5EAB0AAD
P 7300 3100
F 0 "SW-44" H 7300 3243 50  0001 C CNN
F 1 "SW_SPST" H 7300 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 7300 3100 50  0001 C CNN
F 3 "~" H 7300 3100 50  0001 C CNN
	1    7300 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-43
U 1 1 5EAB0AB7
P 7100 3250
F 0 "D-43" V 7146 3171 50  0001 R CNN
F 1 "D" V 7055 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 7100 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 7100 3250 50  0001 C CNN
	1    7100 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-49
U 1 1 5EAB0AC1
P 7800 3100
F 0 "SW-49" H 7800 3243 50  0001 C CNN
F 1 "SW_SPST" H 7800 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 7800 3100 50  0001 C CNN
F 3 "~" H 7800 3100 50  0001 C CNN
	1    7800 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-48
U 1 1 5EAB0ACB
P 7600 3250
F 0 "D-48" V 7646 3171 50  0001 R CNN
F 1 "D" V 7555 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 7600 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 7600 3250 50  0001 C CNN
	1    7600 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-54
U 1 1 5EAB0AD5
P 8300 3100
F 0 "SW-54" H 8300 3243 50  0001 C CNN
F 1 "SW_SPST" H 8300 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 8300 3100 50  0001 C CNN
F 3 "~" H 8300 3100 50  0001 C CNN
	1    8300 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-53
U 1 1 5EAB0ADF
P 8100 3250
F 0 "D-53" V 8146 3171 50  0001 R CNN
F 1 "D" V 8055 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 8100 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 8100 3250 50  0001 C CNN
	1    8100 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-59
U 1 1 5EAB0AE9
P 8800 3100
F 0 "SW-59" H 8800 3243 50  0001 C CNN
F 1 "SW_SPST" H 8800 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 8800 3100 50  0001 C CNN
F 3 "~" H 8800 3100 50  0001 C CNN
	1    8800 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-58
U 1 1 5EAB0AF3
P 8600 3250
F 0 "D-58" V 8646 3171 50  0001 R CNN
F 1 "D" V 8555 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 8600 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 8600 3250 50  0001 C CNN
	1    8600 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-65
U 1 1 5EAB0AFD
P 9300 3100
F 0 "SW-65" H 9300 3243 50  0001 C CNN
F 1 "SW_SPST" H 9300 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 9300 3100 50  0001 C CNN
F 3 "~" H 9300 3100 50  0001 C CNN
	1    9300 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-64
U 1 1 5EAB0B07
P 9100 3250
F 0 "D-64" V 9146 3171 50  0001 R CNN
F 1 "D" V 9055 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 9100 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9100 3250 50  0001 C CNN
	1    9100 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-71
U 1 1 5EAB0B11
P 9800 3100
F 0 "SW-71" H 9800 3243 50  0001 C CNN
F 1 "SW_SPST" H 9800 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_2.25u_Plate" H 9800 3100 50  0001 C CNN
F 3 "~" H 9800 3100 50  0001 C CNN
	1    9800 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-70
U 1 1 5EAB0B1B
P 9600 3250
F 0 "D-70" V 9646 3171 50  0001 R CNN
F 1 "D" V 9555 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 9600 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9600 3250 50  0001 C CNN
	1    9600 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-77
U 1 1 5EAB0B25
P 10300 3100
F 0 "SW-77" H 10300 3243 50  0001 C CNN
F 1 "SW_SPST" H 10300 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 10300 3100 50  0001 C CNN
F 3 "~" H 10300 3100 50  0001 C CNN
	1    10300 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-76
U 1 1 5EAB0B2F
P 10100 3250
F 0 "D-76" V 10146 3171 50  0001 R CNN
F 1 "D" V 10055 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 10100 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 10100 3250 50  0001 C CNN
	1    10100 3250
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-83
U 1 1 5EAB0B39
P 10800 3100
F 0 "SW-83" H 10800 3243 50  0001 C CNN
F 1 "SW_SPST" H 10800 3244 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 10800 3100 50  0001 C CNN
F 3 "~" H 10800 3100 50  0001 C CNN
	1    10800 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-82
U 1 1 5EAB0B43
P 10600 3250
F 0 "D-82" V 10646 3171 50  0001 R CNN
F 1 "D" V 10555 3171 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 10600 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 10600 3250 50  0001 C CNN
	1    10600 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4000 2500 4000 3100
Wire Wire Line
	4500 2500 4500 3100
Wire Wire Line
	5000 2500 5000 3100
Wire Wire Line
	5500 2500 5500 3100
Wire Wire Line
	6000 2500 6000 3100
Wire Wire Line
	6500 2500 6500 3100
Wire Wire Line
	7000 2500 7000 3100
Wire Wire Line
	7500 2500 7500 3100
Wire Wire Line
	8500 2500 8500 3100
Wire Wire Line
	8000 2500 8000 3100
Wire Wire Line
	9000 2500 9000 3100
Wire Wire Line
	9500 2500 9500 3100
Wire Wire Line
	10000 2500 10000 3100
Wire Wire Line
	10500 2500 10500 3100
Wire Wire Line
	11000 2500 11000 3100
Connection ~ 3600 3400
Wire Wire Line
	3600 3400 4100 3400
Connection ~ 4000 2500
Connection ~ 4100 3400
Wire Wire Line
	4100 3400 4600 3400
Connection ~ 4500 2500
Connection ~ 4600 3400
Wire Wire Line
	4600 3400 5100 3400
Connection ~ 5000 2500
Connection ~ 5100 3400
Wire Wire Line
	5100 3400 5600 3400
Connection ~ 5500 2500
Connection ~ 5600 3400
Wire Wire Line
	5600 3400 6100 3400
Connection ~ 6000 2500
Connection ~ 6100 3400
Wire Wire Line
	6100 3400 6600 3400
Connection ~ 6500 2500
Connection ~ 6600 3400
Wire Wire Line
	6600 3400 7100 3400
Connection ~ 7000 2500
Connection ~ 7100 3400
Wire Wire Line
	7100 3400 7600 3400
Connection ~ 7500 2500
Connection ~ 7600 3400
Wire Wire Line
	7600 3400 8100 3400
Connection ~ 8000 2500
Connection ~ 8100 3400
Wire Wire Line
	8100 3400 8600 3400
Connection ~ 8500 2500
Connection ~ 8600 3400
Wire Wire Line
	8600 3400 9100 3400
Connection ~ 9000 2500
Connection ~ 9100 3400
Wire Wire Line
	9100 3400 9600 3400
Connection ~ 9500 2500
Connection ~ 9600 3400
Wire Wire Line
	9600 3400 10100 3400
Connection ~ 10000 2500
Connection ~ 10100 3400
Wire Wire Line
	10100 3400 10600 3400
Connection ~ 10500 2500
Connection ~ 11000 2500
$Comp
L keyboard:SW_SPST SW-5
U 1 1 5EAD90FC
P 3800 3700
F 0 "SW-5" H 3800 3850 50  0001 C CNN
F 1 "SW_SPST" H 3800 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_2.25u_Plate" H 3800 3700 50  0001 C CNN
F 3 "~" H 3800 3700 50  0001 C CNN
	1    3800 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-5
U 1 1 5EAD9106
P 3600 3850
F 0 "D-5" V 3646 3771 50  0001 R CNN
F 1 "D" V 3555 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 3600 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 3600 3850 50  0001 C CNN
	1    3600 3850
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-11
U 1 1 5EAD9110
P 4300 3700
F 0 "SW-11" H 4300 3843 50  0001 C CNN
F 1 "SW_SPST" H 4300 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 4300 3700 50  0001 C CNN
F 3 "~" H 4300 3700 50  0001 C CNN
	1    4300 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-11
U 1 1 5EAD911A
P 4100 3850
F 0 "D-11" V 4146 3771 50  0001 R CNN
F 1 "D" V 4055 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 4100 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 4100 3850 50  0001 C CNN
	1    4100 3850
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-17
U 1 1 5EAD9124
P 4800 3700
F 0 "SW-17" H 4800 3843 50  0001 C CNN
F 1 "SW_SPST" H 4800 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 4800 3700 50  0001 C CNN
F 3 "~" H 4800 3700 50  0001 C CNN
	1    4800 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-17
U 1 1 5EAD912E
P 4600 3850
F 0 "D-17" V 4646 3771 50  0001 R CNN
F 1 "D" V 4555 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 4600 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 4600 3850 50  0001 C CNN
	1    4600 3850
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-23
U 1 1 5EAD9138
P 5300 3700
F 0 "SW-23" H 5300 3843 50  0001 C CNN
F 1 "SW_SPST" H 5300 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 5300 3700 50  0001 C CNN
F 3 "~" H 5300 3700 50  0001 C CNN
	1    5300 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-23
U 1 1 5EAD9142
P 5100 3850
F 0 "D-23" V 5146 3771 50  0001 R CNN
F 1 "D" V 5055 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 5100 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 5100 3850 50  0001 C CNN
	1    5100 3850
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-29
U 1 1 5EAD914C
P 5800 3700
F 0 "SW-29" H 5800 3843 50  0001 C CNN
F 1 "SW_SPST" H 5800 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 5800 3700 50  0001 C CNN
F 3 "~" H 5800 3700 50  0001 C CNN
	1    5800 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-29
U 1 1 5EAD9156
P 5600 3850
F 0 "D-29" V 5646 3771 50  0001 R CNN
F 1 "D" V 5555 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 5600 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 5600 3850 50  0001 C CNN
	1    5600 3850
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-35
U 1 1 5EAD9160
P 6300 3700
F 0 "SW-35" H 6300 3843 50  0001 C CNN
F 1 "SW_SPST" H 6300 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 6300 3700 50  0001 C CNN
F 3 "~" H 6300 3700 50  0001 C CNN
	1    6300 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-34
U 1 1 5EAD916A
P 6100 3850
F 0 "D-34" V 6146 3771 50  0001 R CNN
F 1 "D" V 6055 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 6100 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 6100 3850 50  0001 C CNN
	1    6100 3850
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-40
U 1 1 5EAD9174
P 6800 3700
F 0 "SW-40" H 6800 3850 50  0001 C CNN
F 1 "SW_SPST" H 6800 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 6800 3700 50  0001 C CNN
F 3 "~" H 6800 3700 50  0001 C CNN
	1    6800 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-39
U 1 1 5EAD917E
P 6600 3850
F 0 "D-39" V 6646 3771 50  0001 R CNN
F 1 "D" V 6555 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 6600 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 6600 3850 50  0001 C CNN
	1    6600 3850
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-45
U 1 1 5EAD9188
P 7300 3700
F 0 "SW-45" H 7300 3843 50  0001 C CNN
F 1 "SW_SPST" H 7300 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 7300 3700 50  0001 C CNN
F 3 "~" H 7300 3700 50  0001 C CNN
	1    7300 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-44
U 1 1 5EAD9192
P 7100 3850
F 0 "D-44" V 7146 3771 50  0001 R CNN
F 1 "D" V 7055 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 7100 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 7100 3850 50  0001 C CNN
	1    7100 3850
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-50
U 1 1 5EAD919C
P 7800 3700
F 0 "SW-50" H 7800 3843 50  0001 C CNN
F 1 "SW_SPST" H 7800 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 7800 3700 50  0001 C CNN
F 3 "~" H 7800 3700 50  0001 C CNN
	1    7800 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-49
U 1 1 5EAD91A6
P 7600 3850
F 0 "D-49" V 7646 3771 50  0001 R CNN
F 1 "D" V 7555 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 7600 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 7600 3850 50  0001 C CNN
	1    7600 3850
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-55
U 1 1 5EAD91B0
P 8300 3700
F 0 "SW-55" H 8300 3843 50  0001 C CNN
F 1 "SW_SPST" H 8300 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 8300 3700 50  0001 C CNN
F 3 "~" H 8300 3700 50  0001 C CNN
	1    8300 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-54
U 1 1 5EAD91BA
P 8100 3850
F 0 "D-54" V 8146 3771 50  0001 R CNN
F 1 "D" V 8055 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 8100 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 8100 3850 50  0001 C CNN
	1    8100 3850
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-60
U 1 1 5EAD91C4
P 8800 3700
F 0 "SW-60" H 8800 3843 50  0001 C CNN
F 1 "SW_SPST" H 8800 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 8800 3700 50  0001 C CNN
F 3 "~" H 8800 3700 50  0001 C CNN
	1    8800 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-59
U 1 1 5EAD91CE
P 8600 3850
F 0 "D-59" V 8646 3771 50  0001 R CNN
F 1 "D" V 8555 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 8600 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 8600 3850 50  0001 C CNN
	1    8600 3850
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-66
U 1 1 5EAD91D8
P 9300 3700
F 0 "SW-66" H 9300 3843 50  0001 C CNN
F 1 "SW_SPST" H 9300 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.75u_Plate" H 9300 3700 50  0001 C CNN
F 3 "~" H 9300 3700 50  0001 C CNN
	1    9300 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-65
U 1 1 5EAD91E2
P 9100 3850
F 0 "D-65" V 9146 3771 50  0001 R CNN
F 1 "D" V 9055 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 9100 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9100 3850 50  0001 C CNN
	1    9100 3850
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-72
U 1 1 5EAD91EC
P 9800 3700
F 0 "SW-72" H 9800 3843 50  0001 C CNN
F 1 "SW_SPST" H 9800 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 9800 3700 50  0001 C CNN
F 3 "~" H 9800 3700 50  0001 C CNN
	1    9800 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-71
U 1 1 5EAD91F6
P 9600 3850
F 0 "D-71" V 9646 3771 50  0001 R CNN
F 1 "D" V 9555 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 9600 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9600 3850 50  0001 C CNN
	1    9600 3850
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-78
U 1 1 5EAD9200
P 10300 3700
F 0 "SW-78" H 10300 3843 50  0001 C CNN
F 1 "SW_SPST" H 10300 3844 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 10300 3700 50  0001 C CNN
F 3 "~" H 10300 3700 50  0001 C CNN
	1    10300 3700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-77
U 1 1 5EAD920A
P 10100 3850
F 0 "D-77" V 10146 3771 50  0001 R CNN
F 1 "D" V 10055 3771 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 10100 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 10100 3850 50  0001 C CNN
	1    10100 3850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4000 3100 4000 3700
Wire Wire Line
	4500 3100 4500 3700
Wire Wire Line
	5000 3100 5000 3700
Wire Wire Line
	5500 3100 5500 3700
Wire Wire Line
	6000 3100 6000 3700
Wire Wire Line
	6500 3100 6500 3700
Wire Wire Line
	7000 3100 7000 3700
Wire Wire Line
	7500 3100 7500 3700
Wire Wire Line
	8500 3100 8500 3700
Wire Wire Line
	8000 3100 8000 3700
Wire Wire Line
	9000 3100 9000 3700
Wire Wire Line
	9500 3100 9500 3700
Wire Wire Line
	10000 3100 10000 3700
Wire Wire Line
	10500 3100 10500 3700
Connection ~ 3600 4000
Wire Wire Line
	3600 4000 4100 4000
Connection ~ 4000 3100
Connection ~ 4100 4000
Wire Wire Line
	4100 4000 4600 4000
Connection ~ 4500 3100
Connection ~ 4600 4000
Wire Wire Line
	4600 4000 5100 4000
Connection ~ 5000 3100
Connection ~ 5100 4000
Wire Wire Line
	5100 4000 5600 4000
Connection ~ 5500 3100
Connection ~ 5600 4000
Wire Wire Line
	5600 4000 6100 4000
Connection ~ 6000 3100
Connection ~ 6100 4000
Wire Wire Line
	6100 4000 6600 4000
Connection ~ 6500 3100
Connection ~ 6600 4000
Wire Wire Line
	6600 4000 7100 4000
Connection ~ 7000 3100
Connection ~ 7100 4000
Wire Wire Line
	7100 4000 7600 4000
Connection ~ 7500 3100
Connection ~ 7600 4000
Wire Wire Line
	7600 4000 8100 4000
Connection ~ 8000 3100
Connection ~ 8100 4000
Wire Wire Line
	8100 4000 8600 4000
Connection ~ 8500 3100
Connection ~ 8600 4000
Wire Wire Line
	8600 4000 9100 4000
Connection ~ 9000 3100
Connection ~ 9100 4000
Wire Wire Line
	9100 4000 9600 4000
Connection ~ 9500 3100
Connection ~ 9600 4000
Wire Wire Line
	9600 4000 10100 4000
Connection ~ 10000 3100
Connection ~ 10500 3100
Connection ~ 11000 3100
$Comp
L keyboard:SW_SPST SW-6
U 1 1 5EB05A38
P 3800 4300
F 0 "SW-6" H 3800 4450 50  0001 C CNN
F 1 "SW_SPST" H 3800 4444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 3800 4300 50  0001 C CNN
F 3 "~" H 3800 4300 50  0001 C CNN
	1    3800 4300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-6
U 1 1 5EB05A42
P 3600 4450
F 0 "D-6" V 3646 4371 50  0001 R CNN
F 1 "D" V 3555 4371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 3600 4275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 3600 4450 50  0001 C CNN
	1    3600 4450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-12
U 1 1 5EB05A4C
P 4300 4300
F 0 "SW-12" H 4300 4443 50  0001 C CNN
F 1 "SW_SPST" H 4300 4444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 4300 4300 50  0001 C CNN
F 3 "~" H 4300 4300 50  0001 C CNN
	1    4300 4300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-12
U 1 1 5EB05A56
P 4100 4450
F 0 "D-12" V 4146 4371 50  0001 R CNN
F 1 "D" V 4055 4371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 4100 4275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 4100 4450 50  0001 C CNN
	1    4100 4450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-18
U 1 1 5EB05A60
P 4800 4300
F 0 "SW-18" H 4800 4443 50  0001 C CNN
F 1 "SW_SPST" H 4800 4444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 4800 4300 50  0001 C CNN
F 3 "~" H 4800 4300 50  0001 C CNN
	1    4800 4300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-18
U 1 1 5EB05A6A
P 4600 4450
F 0 "D-18" V 4646 4371 50  0001 R CNN
F 1 "D" V 4555 4371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 4600 4275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 4600 4450 50  0001 C CNN
	1    4600 4450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-24
U 1 1 5EB05A74
P 5300 4300
F 0 "SW-24" H 5300 4443 50  0001 C CNN
F 1 "SW_SPST" H 5300 4444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.25u_Plate" H 5300 4300 50  0001 C CNN
F 3 "~" H 5300 4300 50  0001 C CNN
	1    5300 4300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-24
U 1 1 5EB05A7E
P 5100 4450
F 0 "D-24" V 5146 4371 50  0001 R CNN
F 1 "D" V 5055 4371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 5100 4275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 5100 4450 50  0001 C CNN
	1    5100 4450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-30
U 1 1 5EB05A88
P 5800 4300
F 0 "SW-30" H 5800 4443 50  0001 C CNN
F 1 "SW_SPST" H 5800 4444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_6.25u_Plate" H 5800 4300 50  0001 C CNN
F 3 "~" H 5800 4300 50  0001 C CNN
	1    5800 4300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-SPACE1
U 1 1 5EB05A92
P 5600 4450
F 0 "D-SPACE1" V 5646 4371 50  0001 R CNN
F 1 "D" V 5555 4371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 5600 4275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 5600 4450 50  0001 C CNN
	1    5600 4450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-61
U 1 1 5EB05B00
P 8800 4300
F 0 "SW-61" H 8800 4443 50  0001 C CNN
F 1 "SW_SPST" H 8800 4444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 8800 4300 50  0001 C CNN
F 3 "~" H 8800 4300 50  0001 C CNN
	1    8800 4300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-60
U 1 1 5EB05B0A
P 8600 4450
F 0 "D-60" V 8646 4371 50  0001 R CNN
F 1 "D" V 8555 4371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 8600 4275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 8600 4450 50  0001 C CNN
	1    8600 4450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-67
U 1 1 5EB05B14
P 9300 4300
F 0 "SW-67" H 9300 4443 50  0001 C CNN
F 1 "SW_SPST" H 9300 4444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 9300 4300 50  0001 C CNN
F 3 "~" H 9300 4300 50  0001 C CNN
	1    9300 4300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-66
U 1 1 5EB05B1E
P 9100 4450
F 0 "D-66" V 9146 4371 50  0001 R CNN
F 1 "D" V 9055 4371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 9100 4275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9100 4450 50  0001 C CNN
	1    9100 4450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-73
U 1 1 5EB05B28
P 9800 4300
F 0 "SW-73" H 9800 4443 50  0001 C CNN
F 1 "SW_SPST" H 9800 4444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 9800 4300 50  0001 C CNN
F 3 "~" H 9800 4300 50  0001 C CNN
	1    9800 4300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-72
U 1 1 5EB05B32
P 9600 4450
F 0 "D-72" V 9646 4371 50  0001 R CNN
F 1 "D" V 9555 4371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 9600 4275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9600 4450 50  0001 C CNN
	1    9600 4450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-79
U 1 1 5EB05B3C
P 10300 4300
F 0 "SW-79" H 10300 4443 50  0001 C CNN
F 1 "SW_SPST" H 10300 4444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 10300 4300 50  0001 C CNN
F 3 "~" H 10300 4300 50  0001 C CNN
	1    10300 4300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-78
U 1 1 5EB05B46
P 10100 4450
F 0 "D-78" V 10146 4371 50  0001 R CNN
F 1 "D" V 10055 4371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 10100 4275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 10100 4450 50  0001 C CNN
	1    10100 4450
	0    -1   -1   0   
$EndComp
$Comp
L keyboard:SW_SPST SW-84
U 1 1 5EB05B50
P 10800 4300
F 0 "SW-84" H 10800 4443 50  0001 C CNN
F 1 "SW_SPST" H 10800 4444 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 10800 4300 50  0001 C CNN
F 3 "~" H 10800 4300 50  0001 C CNN
	1    10800 4300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D-83
U 1 1 5EB05B5A
P 10600 4450
F 0 "D-83" V 10646 4371 50  0001 R CNN
F 1 "D" V 10555 4371 50  0000 R CNN
F 2 "keyboard:D_DO-35_SOD27_P7.62mm_Horizontal" H 10600 4275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 10600 4450 50  0001 C CNN
	1    10600 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4000 3700 4000 4300
Wire Wire Line
	4500 3700 4500 4300
Wire Wire Line
	5000 3700 5000 4300
Wire Wire Line
	5500 3700 5500 4300
Wire Wire Line
	6000 3700 6000 4300
Wire Wire Line
	9000 3700 9000 4300
Wire Wire Line
	9500 3700 9500 4300
Wire Wire Line
	10000 3700 10000 4300
Wire Wire Line
	10500 3700 10500 4300
Connection ~ 3600 4600
Wire Wire Line
	3600 4600 4100 4600
Connection ~ 4000 3700
Connection ~ 4100 4600
Wire Wire Line
	4100 4600 4600 4600
Connection ~ 4500 3700
Connection ~ 4600 4600
Wire Wire Line
	4600 4600 5100 4600
Connection ~ 5000 3700
Connection ~ 5100 4600
Wire Wire Line
	5100 4600 5600 4600
Connection ~ 5500 3700
Connection ~ 5600 4600
Connection ~ 6000 3700
Connection ~ 8600 4600
Wire Wire Line
	8600 4600 9100 4600
Connection ~ 9000 3700
Connection ~ 9100 4600
Wire Wire Line
	9100 4600 9600 4600
Connection ~ 9500 3700
Connection ~ 9600 4600
Wire Wire Line
	9600 4600 10100 4600
Connection ~ 10000 3700
Connection ~ 10100 4600
Wire Wire Line
	10100 4600 10600 4600
Connection ~ 10500 3700
Wire Wire Line
	5600 4600 8600 4600
Wire Wire Line
	11000 3100 11000 4300
Text GLabel 1700 7150 2    50   Input ~ 0
CAPS
Text GLabel 1700 7050 2    50   Input ~ 0
SCLK
$Comp
L Device:LED_Small D1
U 1 1 5EA70247
P 1150 4450
F 0 "D1" V 1196 4382 50  0000 R CNN
F 1 "D" V 1105 4382 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" V 1150 4450 50  0001 C CNN
F 3 "~" V 1150 4450 50  0001 C CNN
	1    1150 4450
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED_Small D2
U 1 1 5EA8E351
P 1600 4450
F 0 "D2" V 1646 4382 50  0000 R CNN
F 1 "D" V 1555 4382 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" V 1600 4450 50  0001 C CNN
F 3 "~" V 1600 4450 50  0001 C CNN
	1    1600 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1150 4550 1350 4550
Wire Wire Line
	1350 4550 1350 4650
Connection ~ 1350 4550
Wire Wire Line
	1350 4550 1600 4550
Text GLabel 1150 4250 2    50   Input ~ 0
CAPS
Text GLabel 1600 4250 2    50   Input ~ 0
SCLK
Wire Wire Line
	1600 4250 1600 4350
Wire Wire Line
	1150 4250 1150 4350
$Comp
L power:GND #PWR05
U 1 1 5F06DE09
P 2100 6950
F 0 "#PWR05" H 2100 6700 50  0001 C CNN
F 1 "GND" H 2100 7000 50  0000 C CNN
F 2 "" H 2100 6950 50  0001 C CNN
F 3 "" H 2100 6950 50  0001 C CNN
	1    2100 6950
	1    0    0    -1  
$EndComp
$Comp
L power:VBUS #PWR07
U 1 1 5F08F9B9
P 1900 6650
F 0 "#PWR07" H 1900 6500 50  0001 C CNN
F 1 "VBUS" H 1800 6800 50  0000 L CNN
F 2 "" H 1900 6650 50  0001 C CNN
F 3 "" H 1900 6650 50  0001 C CNN
	1    1900 6650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5F104AB7
P 1350 4650
F 0 "#PWR04" H 1350 4400 50  0001 C CNN
F 1 "GND" H 1355 4477 50  0000 C CNN
F 2 "" H 1350 4650 50  0001 C CNN
F 3 "" H 1350 4650 50  0001 C CNN
	1    1350 4650
	1    0    0    -1  
$EndComp
Text GLabel 2900 4600 0    50   Input ~ 0
ROW6
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5EB4F08E
P 950 2350
F 0 "#FLG01" H 950 2425 50  0001 C CNN
F 1 "PWR_FLAG" H 950 2523 50  0000 C CNN
F 2 "" H 950 2350 50  0001 C CNN
F 3 "~" H 950 2350 50  0001 C CNN
	1    950  2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  2350 1350 2350
$Comp
L power:VBUS #PWR01
U 1 1 5EB5A947
P 1350 2350
F 0 "#PWR01" H 1350 2200 50  0001 C CNN
F 1 "VBUS" H 1365 2523 50  0000 C CNN
F 2 "" H 1350 2350 50  0001 C CNN
F 3 "" H 1350 2350 50  0001 C CNN
	1    1350 2350
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5EB5C181
P 950 2500
F 0 "#FLG02" H 950 2575 50  0001 C CNN
F 1 "PWR_FLAG" H 950 2673 50  0000 C CNN
F 2 "" H 950 2500 50  0001 C CNN
F 3 "~" H 950 2500 50  0001 C CNN
	1    950  2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  2500 1350 2500
$Comp
L power:PWR_FLAG #FLG03
U 1 1 5EB6BF7A
P 950 2650
F 0 "#FLG03" H 950 2725 50  0001 C CNN
F 1 "PWR_FLAG" H 950 2823 50  0000 C CNN
F 2 "" H 950 2650 50  0001 C CNN
F 3 "~" H 950 2650 50  0001 C CNN
	1    950  2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  2650 1350 2650
$Comp
L power:GND #PWR03
U 1 1 5EB777B2
P 1350 2650
F 0 "#PWR03" H 1350 2400 50  0001 C CNN
F 1 "GND" H 1355 2477 50  0000 C CNN
F 2 "" H 1350 2650 50  0001 C CNN
F 3 "" H 1350 2650 50  0001 C CNN
	1    1350 2650
	1    0    0    -1  
$EndComp
$Comp
L keyboard:EXT_5V #PWR02
U 1 1 5EB6A72A
P 1350 2500
F 0 "#PWR02" H 1350 2450 50  0001 C CNN
F 1 "EXT_5V" H 1367 2673 50  0000 C CNN
F 2 "" H 1350 2525 50  0001 C CNN
F 3 "" H 1350 2525 50  0001 C CNN
	1    1350 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 5800 6500 5800
Text Label 6700 5500 0    50   ~ 0
USBD_N
Text Label 6700 5700 0    50   ~ 0
USBD_P
Wire Wire Line
	6400 5600 6500 5600
$Comp
L power:GND #PWR08
U 1 1 5F3E8E25
P 5650 7600
F 0 "#PWR08" H 5650 7350 50  0001 C CNN
F 1 "GND" H 5655 7427 50  0000 C CNN
F 2 "" H 5650 7600 50  0001 C CNN
F 3 "" H 5650 7600 50  0001 C CNN
	1    5650 7600
	1    0    0    -1  
$EndComp
$Comp
L power:VBUS #PWR09
U 1 1 5F3FAE2E
P 6700 5000
F 0 "#PWR09" H 6700 4850 50  0001 C CNN
F 1 "VBUS" H 6715 5173 50  0000 C CNN
F 2 "" H 6700 5000 50  0001 C CNN
F 3 "" H 6700 5000 50  0001 C CNN
	1    6700 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 5000 6400 5000
Text Label 1700 6750 0    50   ~ 0
USBD_P
Text Label 1700 6850 0    50   ~ 0
USBD_N
$Comp
L power:GND #PWR06
U 1 1 5F2D2119
P 1900 6050
F 0 "#PWR06" H 1900 5800 50  0001 C CNN
F 1 "GND" H 1900 6100 50  0000 C CNN
F 2 "" H 1900 6050 50  0001 C CNN
F 3 "" H 1900 6050 50  0001 C CNN
	1    1900 6050
	1    0    0    -1  
$EndComp
$Comp
L keyboard:SW_SPST SW-1
U 1 1 5E90312E
P 3800 1300
F 0 "SW-1" H 3800 1450 50  0001 C CNN
F 1 "SW_SPST" H 3800 1200 50  0000 C CNN
F 2 "keyboard:SW_Cherry_MX_1.00u_Plate" H 3800 1300 50  0001 C CNN
F 3 "~" H 3800 1300 50  0001 C CNN
F 4 "Cxxx" H 3800 1300 50  0000 C CNN "LCSC"
	1    3800 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_Small D3
U 1 1 5F56C09F
P 1050 3400
F 0 "D3" V 1096 3332 50  0000 R CNN
F 1 "D" V 1005 3332 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" V 1050 3400 50  0001 C CNN
F 3 "~" V 1050 3400 50  0001 C CNN
	1    1050 3400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1450 3200 1450 3300
Wire Wire Line
	1050 3200 1050 3300
$Comp
L power:GND #PWR0101
U 1 1 5F56C0B3
P 1450 3600
F 0 "#PWR0101" H 1450 3350 50  0001 C CNN
F 1 "GND" H 1455 3427 50  0000 C CNN
F 2 "" H 1450 3600 50  0001 C CNN
F 3 "" H 1450 3600 50  0001 C CNN
	1    1450 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_Small D5
U 1 1 5F578C1D
P 1800 3400
F 0 "D5" V 1846 3332 50  0000 R CNN
F 1 "D" V 1755 3332 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" V 1800 3400 50  0001 C CNN
F 3 "~" V 1800 3400 50  0001 C CNN
	1    1800 3400
	0    -1   -1   0   
$EndComp
Text Label 1800 3200 0    50   ~ 0
L3
Wire Wire Line
	1800 3200 1800 3300
Text Label 1450 3200 0    50   ~ 0
L2
Text Label 1050 3200 0    50   ~ 0
L1
$Comp
L Device:LED_Small D4
U 1 1 5F56C0A5
P 1450 3400
F 0 "D4" V 1496 3332 50  0000 R CNN
F 1 "D" V 1405 3332 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" V 1450 3400 50  0001 C CNN
F 3 "~" V 1450 3400 50  0001 C CNN
	1    1450 3400
	0    -1   -1   0   
$EndComp
Connection ~ 1450 3500
Wire Wire Line
	1450 3500 1800 3500
Wire Wire Line
	1450 3500 1450 3600
Wire Wire Line
	1050 3500 1450 3500
Wire Wire Line
	1700 6650 1900 6650
Wire Wire Line
	1700 6950 2100 6950
Wire Wire Line
	1700 6050 1700 6150
Wire Wire Line
	1700 6050 1900 6050
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J1
U 1 1 5F8CE1E4
P 1400 6250
F 0 "J1" H 1450 7367 50  0000 C CNN
F 1 "Conn_02x20_Odd_Even" H 1450 7276 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical_SMD" H 1400 6250 50  0001 C CNN
F 3 "~" H 1400 6250 50  0001 C CNN
	1    1400 6250
	1    0    0    -1  
$EndComp
Connection ~ 1700 6050
Wire Wire Line
	1700 5750 1700 5850
Connection ~ 1700 5850
Wire Wire Line
	1700 5850 1700 5950
Connection ~ 1700 5950
Wire Wire Line
	1700 5950 1700 6050
Connection ~ 1700 6150
Wire Wire Line
	1700 6150 1700 6250
Connection ~ 1700 6250
Wire Wire Line
	1700 6250 1700 6350
Connection ~ 1700 6350
Wire Wire Line
	1700 6350 1700 6450
Connection ~ 1700 6450
Wire Wire Line
	1700 6450 1700 6550
Text Label 1700 5550 0    50   ~ 0
L1
Text Label 1700 5350 0    50   ~ 0
L3
Text Label 1700 5450 0    50   ~ 0
L2
$Comp
L keyboard:VDD33 #PWR0102
U 1 1 5F92B702
P 1900 5650
F 0 "#PWR0102" H 1900 5600 50  0001 C CNN
F 1 "VDD33" H 1917 5823 50  0000 C CNN
F 2 "" H 1900 5600 50  0001 C CNN
F 3 "" H 1900 5600 50  0001 C CNN
	1    1900 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 5650 1900 5650
$Comp
L keyboard:USB_C_Receptacle_16P J2
U 1 1 5F4A4F71
P 5800 6000
F 0 "J2" H 5907 7267 50  0000 C CNN
F 1 "USB_C_Receptacle_16P" H 5907 7176 50  0000 C CNN
F 2 "keyboard:USB_C_Receptacle_16P" H 5950 6000 50  0001 C CNN
F 3 "https://www.usb.org/sites/default/files/documents/usb_type-c.zip" H 5950 6000 50  0001 C CNN
	1    5800 6000
	1    0    0    -1  
$EndComp
NoConn ~ 6400 7200
NoConn ~ 6400 7300
Connection ~ 5650 7600
Wire Wire Line
	5650 7600 5800 7600
Wire Wire Line
	5500 7600 5650 7600
NoConn ~ 6400 5200
NoConn ~ 6400 5300
Wire Wire Line
	6400 5500 6500 5500
Wire Wire Line
	6400 5700 6500 5700
Wire Wire Line
	6500 5800 6500 5700
Connection ~ 6500 5700
Wire Wire Line
	6500 5700 6700 5700
Wire Wire Line
	6500 5600 6500 5500
Connection ~ 6500 5500
Wire Wire Line
	6500 5500 6700 5500
$EndSCHEMATC
