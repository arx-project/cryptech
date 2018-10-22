EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr B 17000 11000
encoding utf-8
Sheet 23 27
Title "rev02_21"
Date "15 10 2016"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 8100 4600 0    60   ~ 12
*) Power - AUX
Text Notes 5000 4600 0    60   ~ 12
*) Power - CORE & BRAM
Text Notes 2000 4500 0    60   ~ 12
*) Ground Pins
Text Notes 8460 10210 0    66   ~ 12
FPGA power and ground
$Comp
L power:GND GND_132
U 1 1 58023EE6
P 2000 9700
F 0 "GND_132" H 2000 9700 20  0000 C CNN
F 1 "+GND" H 2000 9630 30  0000 C CNN
F 2 "" H 2000 9700 70  0000 C CNN
F 3 "" H 2000 9700 70  0000 C CNN
	1    2000 9700
	1    0    0    -1  
$EndComp
$Comp
L power:GND GND_133
U 1 1 58023EE5
P 3800 9600
F 0 "GND_133" H 3800 9600 20  0000 C CNN
F 1 "+GND" H 3800 9530 30  0000 C CNN
F 2 "" H 3800 9600 70  0000 C CNN
F 3 "" H 3800 9600 70  0000 C CNN
	1    3800 9600
	1    0    0    -1  
$EndComp
$Comp
L Cryptech_Alpha:FPGA_VCCINT_1V0 FPGA_VCCINT_1V0
U 1 1 58023EE4
P 6000 4900
F 0 "FPGA_VCCINT_1V0" H 6000 4900 20  0000 C CNN
F 1 "+FPGA_VCCINT_1V0" H 6000 4830 30  0000 C CNN
F 2 "" H 6000 4900 70  0000 C CNN
F 3 "" H 6000 4900 70  0000 C CNN
	1    6000 4900
	1    0    0    -1  
$EndComp
$Comp
L Cryptech_Alpha:FPGA_VCCAUX_1V8 FPGA_VCCAUX_1V8_2
U 1 1 58023EE3
P 9000 4900
F 0 "FPGA_VCCAUX_1V8_2" H 9000 4900 20  0000 C CNN
F 1 "+FPGA_VCCAUX_1V8" H 9000 4830 30  0000 C CNN
F 2 "" H 9000 4900 70  0000 C CNN
F 3 "" H 9000 4900 70  0000 C CNN
	1    9000 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 9500 1800 9500
Wire Wire Line
	2000 9500 2000 9700
Wire Wire Line
	2000 9400 1800 9400
Wire Wire Line
	2000 9400 2000 9500
Wire Wire Line
	2000 9000 1800 9000
Wire Wire Line
	2000 9000 2000 9100
Wire Wire Line
	2000 9100 2000 9200
Wire Wire Line
	2000 9200 2000 9300
Wire Wire Line
	2000 9300 2000 9400
Wire Wire Line
	2000 9100 1800 9100
Wire Wire Line
	2000 9200 1800 9200
Wire Wire Line
	2000 9300 1800 9300
Wire Wire Line
	2000 8900 1800 8900
Wire Wire Line
	2000 8900 2000 9000
Wire Wire Line
	2000 8800 1800 8800
Wire Wire Line
	2000 8800 2000 8900
Wire Wire Line
	2000 8700 1800 8700
Wire Wire Line
	2000 8700 2000 8800
Wire Wire Line
	2000 8600 1800 8600
Wire Wire Line
	2000 8600 2000 8700
Wire Wire Line
	2000 8500 1800 8500
Wire Wire Line
	2000 8500 2000 8600
Wire Wire Line
	2000 8400 1800 8400
Wire Wire Line
	2000 8400 2000 8500
Wire Wire Line
	2000 8300 1800 8300
Wire Wire Line
	2000 8300 2000 8400
Wire Wire Line
	2000 8200 1800 8200
Wire Wire Line
	2000 8200 2000 8300
Wire Wire Line
	2000 8100 1800 8100
Wire Wire Line
	2000 8100 2000 8200
Wire Wire Line
	2000 8000 1800 8000
Wire Wire Line
	2000 8000 2000 8100
Wire Wire Line
	2000 7900 1800 7900
Wire Wire Line
	2000 7900 2000 8000
Wire Wire Line
	2000 7800 1800 7800
Wire Wire Line
	2000 7800 2000 7900
Wire Wire Line
	2000 7700 1800 7700
Wire Wire Line
	2000 7700 2000 7800
Wire Wire Line
	2000 7600 1800 7600
Wire Wire Line
	2000 7600 2000 7700
Wire Wire Line
	2000 7500 1800 7500
Wire Wire Line
	2000 7500 2000 7600
Wire Wire Line
	2000 7400 1800 7400
Wire Wire Line
	2000 7400 2000 7500
Wire Wire Line
	2000 7300 1800 7300
Wire Wire Line
	2000 7300 2000 7400
Wire Wire Line
	2000 7200 1800 7200
Wire Wire Line
	2000 7200 2000 7300
Wire Wire Line
	2000 7100 1800 7100
Wire Wire Line
	2000 7100 2000 7200
Wire Wire Line
	2000 7000 1800 7000
Wire Wire Line
	2000 7000 2000 7100
Wire Wire Line
	2000 6900 1800 6900
Wire Wire Line
	2000 6900 2000 7000
Wire Wire Line
	2000 6800 1800 6800
Wire Wire Line
	2000 6800 2000 6900
Wire Wire Line
	2000 6700 1800 6700
Wire Wire Line
	2000 6700 2000 6800
Wire Wire Line
	2000 6600 1800 6600
Wire Wire Line
	2000 6600 2000 6700
Wire Wire Line
	2000 6500 1800 6500
Wire Wire Line
	2000 6500 2000 6600
Wire Wire Line
	2000 6400 1800 6400
Wire Wire Line
	2000 6400 2000 6500
Wire Wire Line
	2000 6300 1800 6300
Wire Wire Line
	2000 6300 2000 6400
Wire Wire Line
	2000 6200 1800 6200
Wire Wire Line
	2000 6200 2000 6300
Wire Wire Line
	2000 6100 1800 6100
Wire Wire Line
	2000 6100 2000 6200
Wire Wire Line
	2000 6000 1800 6000
Wire Wire Line
	2000 6000 2000 6100
Wire Wire Line
	2000 5900 1800 5900
Wire Wire Line
	2000 5900 2000 6000
Wire Wire Line
	2000 5800 1800 5800
Wire Wire Line
	2000 5800 2000 5900
Wire Wire Line
	2000 5700 1800 5700
Wire Wire Line
	2000 5700 2000 5800
Wire Wire Line
	2000 5600 1800 5600
Wire Wire Line
	2000 5600 2000 5700
Wire Wire Line
	2000 5500 1800 5500
Wire Wire Line
	2000 5500 2000 5600
Wire Wire Line
	2000 5400 1800 5400
Wire Wire Line
	2000 5400 2000 5500
Wire Wire Line
	2000 5300 1800 5300
Wire Wire Line
	2000 5300 2000 5400
Wire Wire Line
	2000 5200 1800 5200
Wire Wire Line
	2000 5200 2000 5300
Wire Wire Line
	3800 9400 3600 9400
Wire Wire Line
	3800 9400 3800 9600
Wire Wire Line
	3800 5200 3600 5200
Wire Wire Line
	3800 5200 3800 5300
Wire Wire Line
	3800 5300 3800 5400
Wire Wire Line
	3800 5400 3800 5500
Wire Wire Line
	3800 5500 3800 5600
Wire Wire Line
	3800 5600 3800 5700
Wire Wire Line
	3800 5700 3800 5800
Wire Wire Line
	3800 5800 3800 5900
Wire Wire Line
	3800 5900 3800 6000
Wire Wire Line
	3800 6000 3800 6100
Wire Wire Line
	3800 6100 3800 6200
Wire Wire Line
	3800 6200 3800 6300
Wire Wire Line
	3800 6300 3800 6400
Wire Wire Line
	3800 6400 3800 6500
Wire Wire Line
	3800 6500 3800 6600
Wire Wire Line
	3800 6600 3800 6700
Wire Wire Line
	3800 6700 3800 6800
Wire Wire Line
	3800 6800 3800 6900
Wire Wire Line
	3800 6900 3800 7000
Wire Wire Line
	3800 7000 3800 7100
Wire Wire Line
	3800 7100 3800 7200
Wire Wire Line
	3800 7200 3800 7300
Wire Wire Line
	3800 7300 3800 7400
Wire Wire Line
	3800 7400 3800 7500
Wire Wire Line
	3800 7500 3800 7600
Wire Wire Line
	3800 7600 3800 7700
Wire Wire Line
	3800 7700 3800 7800
Wire Wire Line
	3800 7800 3800 7900
Wire Wire Line
	3800 7900 3800 8000
Wire Wire Line
	3800 8000 3800 8100
Wire Wire Line
	3800 8100 3800 8200
Wire Wire Line
	3800 8200 3800 8300
Wire Wire Line
	3800 8300 3800 8400
Wire Wire Line
	3800 8400 3800 8500
Wire Wire Line
	3800 8500 3800 8600
Wire Wire Line
	3800 8600 3800 8700
Wire Wire Line
	3800 8700 3800 8800
Wire Wire Line
	3800 8800 3800 8900
Wire Wire Line
	3800 8900 3800 9000
Wire Wire Line
	3800 9000 3800 9100
Wire Wire Line
	3800 9100 3800 9200
Wire Wire Line
	3800 9200 3800 9300
Wire Wire Line
	3800 9300 3800 9400
Wire Wire Line
	3800 5300 3600 5300
Wire Wire Line
	3800 5400 3600 5400
Wire Wire Line
	3800 5500 3600 5500
Wire Wire Line
	3800 5600 3600 5600
Wire Wire Line
	3800 5700 3600 5700
Wire Wire Line
	3800 5800 3600 5800
Wire Wire Line
	3800 5900 3600 5900
Wire Wire Line
	3800 6000 3600 6000
Wire Wire Line
	3800 6100 3600 6100
Wire Wire Line
	3800 6200 3600 6200
Wire Wire Line
	3800 6300 3600 6300
Wire Wire Line
	3800 6400 3600 6400
Wire Wire Line
	3800 6500 3600 6500
Wire Wire Line
	3800 6600 3600 6600
Wire Wire Line
	3800 6700 3600 6700
Wire Wire Line
	3800 6800 3600 6800
Wire Wire Line
	3800 6900 3600 6900
Wire Wire Line
	3800 7000 3600 7000
Wire Wire Line
	3800 7100 3600 7100
Wire Wire Line
	3800 7200 3600 7200
Wire Wire Line
	3800 7300 3600 7300
Wire Wire Line
	3800 7400 3600 7400
Wire Wire Line
	3800 7500 3600 7500
Wire Wire Line
	3800 7600 3600 7600
Wire Wire Line
	3800 7700 3600 7700
Wire Wire Line
	3800 7800 3600 7800
Wire Wire Line
	3800 7900 3600 7900
Wire Wire Line
	3800 8000 3600 8000
Wire Wire Line
	3800 8100 3600 8100
Wire Wire Line
	3800 8200 3600 8200
Wire Wire Line
	3800 8300 3600 8300
Wire Wire Line
	3800 8400 3600 8400
Wire Wire Line
	3800 8500 3600 8500
Wire Wire Line
	3800 8600 3600 8600
Wire Wire Line
	3800 8700 3600 8700
Wire Wire Line
	3800 8800 3600 8800
Wire Wire Line
	3800 8900 3600 8900
Wire Wire Line
	3800 9000 3600 9000
Wire Wire Line
	3800 9100 3600 9100
Wire Wire Line
	3800 9200 3600 9200
Wire Wire Line
	3800 9300 3600 9300
Wire Wire Line
	6000 5100 5800 5100
Wire Wire Line
	6000 5100 6000 5200
Wire Wire Line
	6000 5200 5800 5200
Wire Wire Line
	6000 5300 5800 5300
Wire Wire Line
	6000 5200 6000 5300
Wire Wire Line
	6000 4900 6000 5100
Wire Wire Line
	6000 5900 5800 5900
Wire Wire Line
	6000 5300 6000 5900
Wire Wire Line
	6000 6000 5800 6000
Wire Wire Line
	6000 5900 6000 6000
Wire Wire Line
	6000 6100 5800 6100
Wire Wire Line
	6000 6000 6000 6100
Wire Wire Line
	6000 6200 5800 6200
Wire Wire Line
	6000 6100 6000 6200
Wire Wire Line
	6000 6300 5800 6300
Wire Wire Line
	6000 6200 6000 6300
Wire Wire Line
	6000 6400 5800 6400
Wire Wire Line
	6000 6300 6000 6400
Wire Wire Line
	6000 6500 5800 6500
Wire Wire Line
	6000 6400 6000 6500
Wire Wire Line
	6000 7200 5800 7200
Wire Wire Line
	6000 7100 6000 7200
Wire Wire Line
	6000 7000 6000 7100
Wire Wire Line
	6000 6900 6000 7000
Wire Wire Line
	6000 6800 6000 6900
Wire Wire Line
	6000 6700 6000 6800
Wire Wire Line
	6000 6600 6000 6700
Wire Wire Line
	6000 6500 6000 6600
Wire Wire Line
	6000 6600 5800 6600
Wire Wire Line
	6000 6700 5800 6700
Wire Wire Line
	6000 6800 5800 6800
Wire Wire Line
	6000 6900 5800 6900
Wire Wire Line
	6000 7000 5800 7000
Wire Wire Line
	6000 7100 5800 7100
Wire Wire Line
	9000 5100 8800 5100
Wire Wire Line
	9000 5100 9000 5200
Wire Wire Line
	9000 5200 9000 5300
Wire Wire Line
	9000 5300 9000 5400
Wire Wire Line
	9000 5400 9000 5500
Wire Wire Line
	9000 5500 8800 5500
Wire Wire Line
	9000 5400 8800 5400
Wire Wire Line
	9000 5300 8800 5300
Wire Wire Line
	9000 5200 8800 5200
Wire Wire Line
	9000 4900 9000 5100
$Comp
L Cryptech_Alpha:XC7A200TFBG484_9 U13_13
U 1 1 58023EE2
P 1600 7300
F 0 "U13_13" H 1190 4890 60  0000 L BNN
	1    1600 7300
	1    0    0    -1
F 2 "Cryptech_Alpha_Footprints:BGA484C100P22X22_2300X2300X254" H 1190 4890 60  0001 C CNN
$EndComp
$Comp
L Cryptech_Alpha:XC7A200TFBG484_10 U13_14
U 1 1 58023EE1
P 3400 7300
F 0 "U13_14" H 2990 4990 60  0000 L BNN
	1    3400 7300
	1    0    0    -1
F 2 "Cryptech_Alpha_Footprints:BGA484C100P22X22_2300X2300X254" H 2990 4990 60  0001 C CNN
$EndComp
$Comp
L Cryptech_Alpha:XC7A200TFBG484_14 U13_15
U 1 1 58023EE0
P 8600 5300
F 0 "U13_15" H 8190 4890 60  0000 L BNN
	1    8600 5300
	1    0    0    -1
F 2 "Cryptech_Alpha_Footprints:BGA484C100P22X22_2300X2300X254" H 8190 4890 60  0001 C CNN
$EndComp
$Comp
L Cryptech_Alpha:XC7A200TFBG484_15 U13_16
U 1 1 58023EDF
P 5600 5200
F 0 "U13_16" H 5190 4890 60  0000 L BNN
	1    5600 5200
	1    0    0    -1
F 2 "Cryptech_Alpha_Footprints:BGA484C100P22X22_2300X2300X254" H 5190 4890 60  0001 C CNN
$EndComp
$Comp
L Cryptech_Alpha:XC7A200TFBG484_16 U13_17
U 1 1 58023EDE
P 5600 6600
F 0 "U13_17" H 5190 7410 60  0000 L TNN
	1    5600 6600
	1   0    0    1
F 2 "Cryptech_Alpha_Footprints:BGA484C100P22X22_2300X2300X254" H 5190 7410 60  0001 C CNN
$EndComp
$EndSCHEMATC
