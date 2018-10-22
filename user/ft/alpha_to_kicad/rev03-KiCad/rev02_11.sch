EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr B 17000 11000
encoding utf-8
Sheet 13 27
Title "rev02_11"
Date "15 10 2016"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 4600 3100 0    126   ~ 12
AVR Tiny Tamper Detect MCU
Text Notes 13000 3930 0    84   ~ 12
Panic button
Text Notes 13200 6100 0    84   ~ 12
Expansion GPIO
Text Notes 12680 1730 0    60   ~ 12
Connector for external 3V3 battery.\nPlace a jumper between pins 1-2\nto "emulate" having a battery present.
Text Notes 4100 7000 0    60   ~ 12
AVR_GPIO* AVR_LED* and AVR_PANIC can be swapped.
Text Notes 13650 10210 0    84   ~ 12
AVR Tamper circuit
Text Notes 5900 3780 0    60   ~ 12
U10
Text Notes 5880 6680 0    60   ~ 12
ATTINY828R-AU
Text Notes 9700 4570 0    60   ~ 12
R30
Text Notes 14300 6300 2    60   ~ 12
M10LOCK
Text Notes 14300 7550 2    60   ~ 12
JP5
Text Notes 13200 4100 0    60   ~ 12
S2
Text Notes 14300 2200 2    60   ~ 12
M03LOCK
Text Notes 14300 2730 2    60   ~ 12
JP4
$Comp
L Cryptech_Alpha:3V3_BATT 3V3_BATT_3
U 1 1 58023FAE
P 3500 3600
F 0 "3V3_BATT_3" H 3500 3600 20  0000 C CNN
F 1 "+3V3_BATT" H 3500 3530 30  0000 C CNN
F 2 "" H 3500 3600 70  0000 C CNN
F 3 "" H 3500 3600 70  0000 C CNN
	1    3500 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND GND_79
U 1 1 58023FAD
P 3500 6700
F 0 "GND_79" H 3500 6700 20  0000 C CNN
F 1 "+GND" H 3500 6630 30  0000 C CNN
F 2 "" H 3500 6700 70  0000 C CNN
F 3 "" H 3500 6700 70  0000 C CNN
	1    3500 6700
	1    0    0    -1  
$EndComp
$Comp
L Cryptech_Alpha:3V3_BATT 3V3_BATT_4
U 1 1 58023FAC
P 10900 5700
F 0 "3V3_BATT_4" H 10900 5700 20  0000 C CNN
F 1 "+3V3_BATT" H 10900 5630 30  0000 C CNN
F 2 "" H 10900 5700 70  0000 C CNN
F 3 "" H 10900 5700 70  0000 C CNN
	1    10900 5700
	1    0    0    -1  
$EndComp
$Comp
L Cryptech_Alpha:3V3_BATT 3V3_BATT_5
U 1 1 58023FAB
P 9600 4100
F 0 "3V3_BATT_5" H 9600 4100 20  0000 C CNN
F 1 "+3V3_BATT" H 9600 4030 30  0000 C CNN
F 2 "" H 9600 4100 70  0000 C CNN
F 3 "" H 9600 4100 70  0000 C CNN
	1    9600 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND GND_80
U 1 1 58023FAA
P 10900 6700
F 0 "GND_80" H 10900 6700 20  0000 C CNN
F 1 "+GND" H 10900 6630 30  0000 C CNN
F 2 "" H 10900 6700 70  0000 C CNN
F 3 "" H 10900 6700 70  0000 C CNN
	1    10900 6700
	1    0    0    -1  
$EndComp
$Comp
L power:GND GND_81
U 1 1 58023FA9
P 2200 4800
F 0 "GND_81" H 2200 4800 20  0000 C CNN
F 1 "+GND" H 2200 4730 30  0000 C CNN
F 2 "" H 2200 4800 70  0000 C CNN
F 3 "" H 2200 4800 70  0000 C CNN
	1    2200 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND GND_82
U 1 1 58023FA8
P 14300 9200
F 0 "GND_82" H 14300 9200 20  0000 C CNN
F 1 "+GND" H 14300 9130 30  0000 C CNN
F 2 "" H 14300 9200 70  0000 C CNN
F 3 "" H 14300 9200 70  0000 C CNN
	1    14300 9200
	1    0    0    -1  
$EndComp
$Comp
L power:GND GND_83
U 1 1 58023FA7
P 13700 7500
F 0 "GND_83" H 13700 7500 20  0000 C CNN
F 1 "+GND" H 13700 7430 30  0000 C CNN
F 2 "" H 13700 7500 70  0000 C CNN
F 3 "" H 13700 7500 70  0000 C CNN
	1    13700 7500
	1    0    0    -1  
$EndComp
$Comp
L power:GND GND_84
U 1 1 58023FA6
P 14200 5300
F 0 "GND_84" H 14200 5300 20  0000 C CNN
F 1 "+GND" H 14200 5230 30  0000 C CNN
F 2 "" H 14200 5300 70  0000 C CNN
F 3 "" H 14200 5300 70  0000 C CNN
	1    14200 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND GND_85
U 1 1 58023FA5
P 13700 2800
F 0 "GND_85" H 13700 2800 20  0000 C CNN
F 1 "+GND" H 13700 2730 30  0000 C CNN
F 2 "" H 13700 2800 70  0000 C CNN
F 3 "" H 13700 2800 70  0000 C CNN
	1    13700 2800
	1    0    0    -1  
$EndComp
$Comp
L Cryptech_Alpha:3V3_BATT 3V3_BATT_6
U 1 1 58023FA4
P 13200 2200
F 0 "3V3_BATT_6" H 13200 2200 20  0000 C CNN
F 1 "+3V3_BATT" H 13200 2130 30  0000 C CNN
F 2 "" H 13200 2200 70  0000 C CNN
F 3 "" H 13200 2200 70  0000 C CNN
	1    13200 2200
	1    0    0    -1  
$EndComp
$Comp
L Cryptech_Alpha:VCCO_3V3 VCCO_3V3_19
U 1 1 58023FA3
P 13700 2200
F 0 "VCCO_3V3_19" H 13700 2200 20  0000 C CNN
F 1 "+VCCO_3V3" H 13700 2130 30  0000 C CNN
F 2 "" H 13700 2200 70  0000 C CNN
F 3 "" H 13700 2200 70  0000 C CNN
	1    13700 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND GND_86
U 1 1 58023FA2
P 12800 7500
F 0 "GND_86" H 12800 7500 20  0000 C CNN
F 1 "+GND" H 12800 7430 30  0000 C CNN
F 2 "" H 12800 7500 70  0000 C CNN
F 3 "" H 12800 7500 70  0000 C CNN
	1    12800 7500
	1    0    0    -1  
$EndComp
$Comp
L Cryptech_Alpha:3V3_BATT 3V3_BATT_7
U 1 1 58023FA1
P 12800 4400
F 0 "3V3_BATT_7" H 12800 4400 20  0000 C CNN
F 1 "+3V3_BATT" H 12800 4330 30  0000 C CNN
F 2 "" H 12800 4400 70  0000 C CNN
F 3 "" H 12800 4400 70  0000 C CNN
	1    12800 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 6200 3500 6200
Wire Wire Line
	3500 6200 3500 6300
Wire Wire Line
	3500 6300 3500 6700
Wire Wire Line
	3900 6300 3500 6300
Connection ~ 3500 6300
Wire Wire Line
	10900 6200 10800 6200
Wire Wire Line
	10900 6200 10900 6700
Wire Wire Line
	1900 4600 1900 4700
Wire Wire Line
	2200 4700 1900 4700
Wire Wire Line
	2200 4700 2200 4800
Wire Wire Line
	2500 4600 2500 4700
Wire Wire Line
	2500 4700 2200 4700
Wire Wire Line
	2200 4600 2200 4700
Connection ~ 2200 4700
Wire Wire Line
	14300 8700 14200 8700
Wire Wire Line
	14300 8900 14300 9000
Wire Wire Line
	14300 8800 14300 8900
Wire Wire Line
	14300 8700 14300 8800
Wire Wire Line
	14300 8800 14000 8800
Wire Wire Line
	14300 9000 14000 9000
Wire Wire Line
	14300 8900 14200 8900
Wire Wire Line
	14300 9000 14300 9200
Connection ~ 14300 8900
Connection ~ 14300 8800
Connection ~ 14300 9000
Wire Wire Line
	13900 7400 13700 7400
Wire Wire Line
	13700 7400 13700 7500
Wire Wire Line
	14200 4600 14100 4600
Wire Wire Line
	14200 4600 14200 4800
Wire Wire Line
	14200 4800 14200 5100
Wire Wire Line
	14200 5100 14200 5300
Wire Wire Line
	14200 4800 14100 4800
Wire Wire Line
	14200 5100 13800 5100
Wire Wire Line
	14200 4300 13800 4300
Wire Wire Line
	14200 4300 14200 4600
Connection ~ 14200 4800
Connection ~ 14200 5100
Connection ~ 14200 4600
Wire Wire Line
	13900 2600 13700 2600
Wire Wire Line
	13700 2600 13700 2800
Wire Wire Line
	12800 7100 12800 7500
Wire Wire Line
	10100 6200 9600 6200
Wire Wire Line
	9600 5200 9600 6200
Wire Wire Line
	9600 5200 8300 5200
Wire Wire Line
	9600 4800 9600 5200
Connection ~ 9600 5200
Text Label 9600 5700 0 48 ~
AVR_RESET
Wire Wire Line
	10900 6000 10800 6000
Wire Wire Line
	10900 5700 10900 6000
Wire Wire Line
	9600 4100 9600 4400
Wire Wire Line
	3900 4200 3500 4200
Wire Wire Line
	3500 4100 3500 4200
Wire Wire Line
	3500 3600 3500 4100
Wire Wire Line
	3900 4100 3500 4100
Wire Wire Line
	3500 4100 2500 4100
Wire Wire Line
	2500 4100 2200 4100
Wire Wire Line
	2200 4100 1900 4100
Wire Wire Line
	1900 4100 1900 4300
Wire Wire Line
	2200 4100 2200 4300
Wire Wire Line
	2500 4100 2500 4300
Connection ~ 3500 4100
Connection ~ 2200 4100
Connection ~ 2500 4100
Wire Wire Line
	13900 2500 13200 2500
Wire Wire Line
	13200 2200 13200 2500
Wire Wire Line
	12800 4400 12800 4500
Wire Wire Line
	3900 5000 3070 5000
Text GLabel 3070 5000 0 48 Output ~ 0
MKM_CONTROL_AVR_ENA
Wire Wire Line
	9700 5300 8500 5300
Wire Wire Line
	9700 5300 9700 6100
Wire Wire Line
	10100 6100 9700 6100
Wire Wire Line
	8500 5300 8300 5300
Text GLabel 8440 5300 2 48 Output ~ 0
MKM_AVR_SCK
Wire Wire Line
	3900 4900 3070 4900
Text GLabel 3070 4900 0 48 Output ~ 0
MKM_AVR_CS_N
Wire Wire Line
	8700 5000 8300 5000
Wire Wire Line
	11100 5000 8700 5000
Wire Wire Line
	11100 5000 11100 6100
Wire Wire Line
	11100 6100 10800 6100
Text GLabel 8440 5000 2 48 Output ~ 0
MKM_AVR_MOSI
Wire Wire Line
	10100 6000 9800 6000
Wire Wire Line
	9800 5100 9800 6000
Wire Wire Line
	9800 5100 8600 5100
Wire Wire Line
	8600 5100 8300 5100
Text GLabel 8440 5100 2 48 Input ~ 0
MKM_AVR_MISO
Wire Wire Line
	13900 8700 13600 8700
Wire Wire Line
	13200 8700 12610 8700
Text Label 12610 8700 0 48 ~
AVR_LED1
Wire Wire Line
	3900 4400 3170 4400
Text Label 3170 4400 0 48 ~
AVR_LED1
Wire Wire Line
	13700 8800 13290 8800
Wire Wire Line
	12890 8800 12610 8800
Text Label 12610 8800 0 48 ~
AVR_LED2
Wire Wire Line
	3900 4500 3170 4500
Text Label 3170 4500 0 48 ~
AVR_LED2
Wire Wire Line
	13900 8900 13600 8900
Wire Wire Line
	13200 8900 12610 8900
Text Label 12610 8900 0 48 ~
AVR_LED3
Wire Wire Line
	3900 4600 3180 4600
Text Label 3180 4600 0 48 ~
AVR_LED3
Wire Wire Line
	13700 9000 13290 9000
Wire Wire Line
	12890 9000 12610 9000
Text Label 12610 9000 0 48 ~
AVR_LED4
Wire Wire Line
	3900 4700 3170 4700
Text Label 3170 4700 0 48 ~
AVR_LED4
Wire Wire Line
	13900 6600 13500 6600
Text Label 13500 6600 2 48 ~ 0
AVR_GPIO_0
Wire Wire Line
	8500 4100 8300 4100
Text Label 8500 4100 0 48 ~
AVR_GPIO_0
Wire Wire Line
	13900 6700 13500 6700
Text Label 13500 6700 2 48 ~ 0
AVR_GPIO_1
Wire Wire Line
	8500 4200 8300 4200
Text Label 8500 4200 0 48 ~
AVR_GPIO_1
Wire Wire Line
	13900 6800 13500 6800
Text Label 13500 6800 2 48 ~ 0
AVR_GPIO_2
Wire Wire Line
	8500 4300 8300 4300
Text Label 8500 4300 0 48 ~
AVR_GPIO_2
Wire Wire Line
	13900 6900 13500 6900
Text Label 13500 6900 2 48 ~ 0
AVR_GPIO_3
Wire Wire Line
	8500 4400 8300 4400
Text Label 8500 4400 0 48 ~
AVR_GPIO_3
Wire Wire Line
	13900 7000 13500 7000
Text Label 13500 7000 2 48 ~ 0
AVR_GPIO_4
Wire Wire Line
	8500 4500 8300 4500
Text Label 8500 4500 0 48 ~
AVR_GPIO_4
Wire Wire Line
	13900 7100 13500 7100
Text Label 13500 7100 2 48 ~ 0
AVR_GPIO_5
Wire Wire Line
	8500 4600 8300 4600
Text Label 8500 4600 0 48 ~
AVR_GPIO_5
Wire Wire Line
	13900 7200 13500 7200
Text Label 13500 7200 2 48 ~ 0
AVR_GPIO_6
Wire Wire Line
	8500 4700 8300 4700
Text Label 8500 4700 0 48 ~
AVR_GPIO_6
Wire Wire Line
	13900 7300 13500 7300
Text Label 13500 7300 2 48 ~ 0
AVR_GPIO_7
Wire Wire Line
	8500 4800 8300 4800
Text Label 8500 4800 0 48 ~
AVR_GPIO_7
Wire Wire Line
	13200 5100 12800 5100
Wire Wire Line
	12800 5100 12500 5100
Wire Wire Line
	12800 4900 12800 5100
Text Label 12500 5100 0 48 ~
AVR_PANIC
Connection ~ 12800 5100
Wire Wire Line
	3900 4800 3170 4800
Text Label 3170 4800 0 48 ~
AVR_PANIC
Wire Wire Line
	13900 2400 13700 2400
Wire Wire Line
	13700 2200 13700 2400
Wire Wire Line
	3900 5300 3170 5300
Text GLabel 3170 5300 0 48 BiDi ~ 0
AVR_GPIO_ARM_0
Wire Wire Line
	3900 5400 3170 5400
Text GLabel 3170 5400 0 48 BiDi ~ 0
AVR_GPIO_ARM_1
Wire Wire Line
	3900 5700 3170 5700
Text GLabel 3170 5700 0 48 BiDi ~ 0
AVR_GPIO_FPGA_0
Wire Wire Line
	3900 5800 3170 5800
Text GLabel 3170 5800 0 48 BiDi ~ 0
AVR_GPIO_FPGA_1
Wire Wire Line
	12800 6400 12800 6500
Wire Wire Line
	13900 6500 12800 6500
Wire Wire Line
	12800 6500 12800 6800
Connection ~ 12800 6500
Wire Wire Line
	3900 5100 3070 5100
Text GLabel 3070 5100 0 48 Output ~ 0
MKM_CONTROL_FPGA_DIS
Wire Wire Line
	3900 5500 3170 5500
Text GLabel 3170 5500 0 48 BiDi ~ 0
AVR_GPIO_ARM_2
Wire Wire Line
	3900 5600 3170 5600
Text GLabel 3170 5600 0 48 BiDi ~ 0
AVR_GPIO_ARM_3
Wire Wire Line
	3900 5900 3170 5900
Text GLabel 3170 5900 0 48 BiDi ~ 0
AVR_GPIO_FPGA_2
Wire Wire Line
	3900 6000 3170 6000
Text GLabel 3170 6000 0 48 BiDi ~ 0
AVR_GPIO_FPGA_3
$Comp
L Cryptech_Alpha:VCCO_3V3 VCCO_3V3_20
U 1 1 58023FA0
P 12800 6400
F 0 "VCCO_3V3_20" H 12800 6400 20  0000 C CNN
F 1 "+VCCO_3V3" H 12800 6330 30  0000 C CNN
F 2 "" H 12800 6400 70  0000 C CNN
F 3 "" H 12800 6400 70  0000 C CNN
	1    12800 6400
	1    0    0    -1  
$EndComp
$Comp
L Cryptech_Alpha:ATTINY828R-AU U10
U 1 1 58023F9F
P 6100 5100
F 0 "U10" H 4070 3570 60  0000 L BNN
	1    6100 5100
	1    0    0    -1
F 2 "Cryptech_Alpha_Footprints:LQFP-32" H 4070 3570 60  0001 C CNN
$EndComp
$Comp
L Cryptech_Alpha:LEDCHIP-LED0603 LED10
U 1 1 58023F9E
P 13800 9000
F 0 "LED10" V 13770 8316 60  0000 R TNN
F 1 "LTST-C191KRKT" V 13760 7810 60  0000 R TNN
F 2 "Cryptech_Alpha_Footprints:VD_0603" H 13760 7810 60  0001 C CNN
F 3 "" H 13760 7810 60  0000 C CNN
	1    13800 9000
	0    -1   -1   0
$EndComp
$Comp
L Cryptech_Alpha:M10LOCK JP5
U 1 1 58023F9D
P 14300 7200
F 0 "JP5" H 14580 7630 60  0000 R TNN
	1    14300 7200
	-1   0    0    1
F 2 "Cryptech_Alpha_Footprints:HDR1X10" H 14580 7630 60  0001 C CNN
$EndComp
$Comp
L Cryptech_Alpha:TACTILE_SWITCH S2
U 1 1 58023F9C
P 13500 4700
F 0 "S2" H 14120 4810 60  0000 L BNN
F 1 "EVQPT9A15" H 13200 5170 60  0000 L BNN
F 2 "Cryptech_Alpha_Footprints:TACTILE_SWITCH" H 13200 5170 60  0001 C CNN
F 3 "" H 13200 5170 60  0000 C CNN
	1    13500 4700
	1    0    0    -1
$EndComp
$Comp
L Cryptech_Alpha:M03LOCK JP4
U 1 1 58023F9B
P 14200 2500
F 0 "JP4" H 14380 2830 60  0000 R TNN
	1    14200 2500
	-1   0    0    1
F 2 "Cryptech_Alpha_Footprints:PLS-3" H 14380 2830 60  0001 C CNN
$EndComp
$Comp
L Cryptech_Alpha:C-EUC0402 C105
U 1 1 58023F9A
P 12800 6900
F 0 "C105" H 12390 6850 60  0000 L BNN
F 1 "0.1uF" H 12380 6740 60  0000 L BNN
F 2 "Cryptech_Alpha_Footprints:C_0402" H 12380 6740 60  0001 C CNN
F 3 "" H 12380 6740 60  0000 C CNN
	1    12800 6900
	1    0    0    -1
$EndComp
$Comp
L Cryptech_Alpha:R-EU_R0402 R82
U 1 1 58023F99
P 12800 4700
F 0 "R82" V 12771 5047 60  0000 R TNN
F 1 "15k" V 12660 5050 60  0000 R TNN
F 2 "Cryptech_Alpha_Footprints:R_0402" H 12660 5050 60  0001 C CNN
F 3 "" H 12660 5050 60  0000 C CNN
	1    12800 4700
	0    -1   -1   0
$EndComp
$Comp
L Cryptech_Alpha:R-EU_R0402 R96
U 1 1 58023F98
P 13400 8700
F 0 "R96" H 13490 8520 60  0000 R TNN
F 1 "330" H 13500 8610 60  0000 R TNN
F 2 "Cryptech_Alpha_Footprints:R_0402" H 13500 8610 60  0001 C CNN
F 3 "" H 13500 8610 60  0000 C CNN
	1    13400 8700
	-1   0    0    1
$EndComp
$Comp
L Cryptech_Alpha:R-EU_R0402 R95
U 1 1 58023F97
P 13090 8800
F 0 "R95" H 13220 8520 60  0000 R TNN
F 1 "330" H 13230 8610 60  0000 R TNN
F 2 "Cryptech_Alpha_Footprints:R_0402" H 13230 8610 60  0001 C CNN
F 3 "" H 13230 8610 60  0000 C CNN
	1    13090 8800
	-1   0    0    1
$EndComp
$Comp
L Cryptech_Alpha:R-EU_R0402 R31
U 1 1 58023F96
P 13400 8900
F 0 "R31" H 13080 8510 60  0000 R TNN
F 1 "330" H 13090 8600 60  0000 R TNN
F 2 "Cryptech_Alpha_Footprints:R_0402" H 13090 8600 60  0001 C CNN
F 3 "" H 13090 8600 60  0000 C CNN
	1    13400 8900
	-1   0    0    1
$EndComp
$Comp
L Cryptech_Alpha:R-EU_R0402 R97
U 1 1 58023F95
P 13090 9000
F 0 "R97" H 13180 9170 60  0000 R TNN
F 1 "330" H 13190 9260 60  0000 R TNN
F 2 "Cryptech_Alpha_Footprints:R_0402" H 13190 9260 60  0001 C CNN
F 3 "" H 13190 9260 60  0000 C CNN
	1    13090 9000
	-1   0    0    1
$EndComp
$Comp
L Cryptech_Alpha:AVR_SPI_PRG_62X3_LOCK JP3
U 1 1 58023F94
P 10400 6100
F 0 "JP3" H 10230 6330 60  0000 L BNN
F 1 "AVR_SPI_PRG_62X3_LOCK" H 9440 5700 60  0000 L BNN
F 2 "Cryptech_Alpha_Footprints:PLD-6" H 9440 5700 60  0001 C CNN
F 3 "" H 9440 5700 60  0000 C CNN
	1    10400 6100
	1    0    0    -1
$EndComp
$Comp
L Cryptech_Alpha:R-EU_R0402 R30
U 1 1 58023F93
P 9600 4600
F 0 "R30" V 9510 4555 60  0000 R TNN
F 1 "15k" V 9540 4510 60  0000 R TNN
F 2 "Cryptech_Alpha_Footprints:R_0402" H 9540 4510 60  0001 C CNN
F 3 "" H 9540 4510 60  0000 C CNN
	1    9600 4600
	0    -1   -1   0
$EndComp
$Comp
L Cryptech_Alpha:C-EUC0805 C102
U 1 1 58023F92
P 1900 4400
F 0 "C102" H 1580 4400 60  0000 L BNN
F 1 "10uF" H 1570 4290 60  0000 L BNN
F 2 "Cryptech_Alpha_Footprints:C_0805" H 1570 4290 60  0001 C CNN
F 3 "" H 1570 4290 60  0000 C CNN
	1    1900 4400
	1    0    0    -1
$EndComp
$Comp
L Cryptech_Alpha:C-EUC0402 C104
U 1 1 58023F91
P 2500 4400
F 0 "C104" H 2630 4400 60  0000 L BNN
F 1 "0.1uF" H 2620 4300 60  0000 L BNN
F 2 "Cryptech_Alpha_Footprints:C_0402" H 2620 4300 60  0001 C CNN
F 3 "" H 2620 4300 60  0000 C CNN
	1    2500 4400
	1    0    0    -1
$EndComp
$Comp
L Cryptech_Alpha:C-EUC0402 C103
U 1 1 58023F90
P 2200 4400
F 0 "C103" H 2230 4490 60  0000 L BNN
F 1 "0.1uF" H 2220 4400 60  0000 L BNN
F 2 "Cryptech_Alpha_Footprints:C_0402" H 2220 4400 60  0001 C CNN
F 3 "" H 2220 4400 60  0000 C CNN
	1    2200 4400
	1    0    0    -1
$EndComp
$Comp
L Cryptech_Alpha:LEDCHIP-LED0603 LED11
U 1 1 58023F8F
P 14000 8700
F 0 "LED11" V 13970 8216 60  0000 R TNN
F 1 "LTST-C193TBKT-5A" V 13960 7710 60  0000 R TNN
F 2 "Cryptech_Alpha_Footprints:VD_0603" H 13960 7710 60  0001 C CNN
F 3 "" H 13960 7710 60  0000 C CNN
	1    14000 8700
	0    -1   -1   0
$EndComp
$Comp
L Cryptech_Alpha:LEDCHIP-LED0603 LED9
U 1 1 58023F8E
P 13800 8800
F 0 "LED9" V 13770 8110 60  0000 R TNN
F 1 "LTST-C191KGKT" V 13755 7616 60  0000 R TNN
F 2 "Cryptech_Alpha_Footprints:VD_0603" H 13755 7616 60  0001 C CNN
F 3 "" H 13755 7616 60  0000 C CNN
	1    13800 8800
	0    -1   -1   0
$EndComp
$Comp
L Cryptech_Alpha:LEDCHIP-LED0603 LED12
U 1 1 58023F8D
P 14000 8900
F 0 "LED12" V 13970 8416 60  0000 R TNN
F 1 "LTST-C191KSKT" V 13960 7920 60  0000 R TNN
F 2 "Cryptech_Alpha_Footprints:VD_0603" H 13960 7920 60  0001 C CNN
F 3 "" H 13960 7920 60  0000 C CNN
	1    14000 8900
	0    -1   -1   0
$EndComp
NoConn ~ 13200 4300
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5AF61081
P 13200 2500
F 0 "#FLG?" H 13200 2575 50  0001 C CNN
F 1 "PWR_FLAG" V 13200 2628 50  0000 L CNN
F 2 "" H 13200 2500 50  0001 C CNN
F 3 "~" H 13200 2500 50  0001 C CNN
        1    13200 2500
        0    -1   -1   0
$EndComp
Connection ~ 13200 2500
$EndSCHEMATC
