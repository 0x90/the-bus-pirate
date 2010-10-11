/*
 * This file is part of the Bus Pirate project (http://code.google.com/p/the-bus-pirate/).
 *
 * Written and maintained by the Bus Pirate project.
 *
 * To the extent possible under law, the project has
 * waived all copyright and related or neighboring rights to Bus Pirate. This
 * work is published from United States.
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
//this profile is for the Bus Pirate v3 hardware from dangerousprototypes.com
#define BP_VERSION_STRING "Bus Pirate v4"// (Seeed Studio)"
#define BP_VERSION "v4"

//this is a different type of pin identifier used by the bitbang library
#define AUX		0b1000000 //RB10 on v1, 2, 2go, 3 (not v0)
#define MOSI 	0b1000  //RB9
#define CLK 	0b100    //RB8
#define MISO 	0b10 //RB7
#define CS 		0b10000 //RB6
#define IOPOR 	PORTD
#define IOLAT	LATD
#define IODIR	TRISD

//these macros set the pin IO used in each module
#define BP_MOSI 		PORTDbits.RD1
#define BP_CLK 			PORTDbits.RD2
#define BP_MISO 		PORTDbits.RD3
#define BP_CS 			PORTDbits.RD4
#define BP_AUX 			PORTDbits.RD5 //moved pin5 (AUX) to RB10
#define BP_LEDMODE		PORTBbits.RB8 //single MODE led on v2a
#define BP_VREGEN		PORTBbits.RB9 //single vreg enable pin on v2a
#define BP_PULLUP		PORTEbits.RE4 //Pull-up pin on V2a
#define BP_PGD			PORTBbits.RB7 //PGD pin on programming header

//these macros set the direction registers for each IO pin
#define BP_MOSI_DIR 	TRISDbits.TRISD1
#define BP_CLK_DIR 		TRISDbits.TRISD2
#define BP_MISO_DIR 	TRISDbits.TRISD3
#define BP_CS_DIR 		TRISDbits.TRISD4
#define BP_AUX_DIR 		TRISDbits.TRISD5
#define BP_LEDMODE_DIR	TRISBbits.TRISB8
#define BP_VREGEN_DIR	TRISBbits.TRISB9
#define BP_PULLUP_DIR	TRISEbits.TRISE4
#define BP_PGD_DIR		TRISBbits.TRISB7

//Open drain/high impedance pin setup
#define BP_MOSI_ODC 	ODCDbits.ODD1
#define BP_CLK_ODC 		ODCDbits.ODD2
#define BP_MISO_ODC 	ODCDbits.ODD3
#define BP_CS_ODC 		ODCDbits.ODD4
#define BP_AUX_ODC 		ODCDbits.ODD5

//Change notice assignment
#define BP_MOSI_CN		CNEN4bits.CN50IE
#define BP_CLK_CN		CNEN4bits.CN51IE

//ADC assignment
#define BP_ADC_PROBE 1
#define BP_ADC_3V3 0
#define BP_ADC_5V0 2
#define BP_ADC_VPU 5
#define BP_ADC_USB 15

//calculate the acceptable range of voltages for the power supplies
//these values will be compared to the ADC reading from the supply monitor
#define V5BASE 0x307 //(((5/2)/3.3)*1024))
#define V5H	V5BASE+0x50
#define V5L V5BASE-0x50

#define V33BASE 0x200 //(((3.3/2)/3.3)*1024))
#define V33H	V33BASE+0x50
#define V33L	V33BASE-0x50

#define ADCON() AD1CON1bits.ADON = 1 // turn ADC ON 
#define ADCOFF() AD1CON1bits.ADON = 0 // turn ADC OFF 

//ADC pin configuration
#define BP_ADC_PROBE_CFG AD1PCFGbits.PCFG1 //AN1/ADC1/EXT 
#define BP_ADC_3V3_CFG AD1PCFGbits.PCFG0 //AN0/ADC3/33V 
#define BP_ADC_5V0_CFG AD1PCFGbits.PCFG2 //AN2/ADC4/50V
#define BP_ADC_VPU_CFG AD1PCFGbits.PCFG5 //AN5/ADC2/Vextpullup
#define BP_ADC_USB_CFG AD1PCFGbits.PCFG15 //AN15/ADC5/Vusb

#define BP_ADC_PINSETUP() BP_ADC_PROBE_CFG=0;BP_ADC_3V3_CFG=0;BP_ADC_5V0_CFG=0;BP_ADC_VPU_CFG=0;BP_ADC_USB_CFG=0

//error fixing defines (find with keyword #BPV4
#define OC5CON OC5CON1

//define the PPS input/output for the AUX pin
#define BP_AUX_RPIN 20	
#define BP_AUX_RPOUT RPOR10bits.RP20R
#define BP_CS_RPIN 25
#define BP_CS_RPOUT RPOR12bits.RP25R

//pseudofunctions for pullup resistors
//for V2/3 we need B5/pullup to be output and gnd to turn OFF the pullups...
#define BP_PULLUP_ON() BP_PULLUP_DIR=1;BP_PULLUP=0
#define BP_PULLUP_OFF() BP_PULLUP=0;BP_PULLUP_DIR=0

//pseudofunctions for voltage regulator switch
#define BP_VREG_ON() BP_VREGEN_DIR=0; BP_VREGEN=1
#define BP_VREG_OFF() BP_VREGEN_DIR=0; BP_VREGEN=0

//define device ID and revision memory location
#define DEV_ADDR_UPPER	0x00FF
#define DEV_ADDR_TYPE	0x0000
#define DEV_ADDR_REV	0x0002
#define CFG_ADDR_UPPER 0x0000
#define BL_ADDR_VER		0xABFA //location of the bootloader version info
#define CFG_ADDR_1     0xABFC
#define CFG_ADDR_2     0xABFE

//these are unneeded, but the stack complains if they're not defined
//#define USE_SELF_POWER_SENSE_IO
#define tris_self_power     TRISCbits.TRISC2    
#define self_power          1

//#define USE_USB_BUS_SENSE_IO
#define tris_usb_bus_sense  TRISCbits.TRISC2    
#define USB_BUS_SENSE       U1OTGSTATbits.SESVD 

// Peripheral Pin Select Outputs
#define NULL_IO		0
#define C1OUT_IO	1
#define C2OUT_IO	2
#define U1TX_IO		3
#define U1RTS_IO	4
#define U2TX_IO		5
#define U2RTS_IO	6
#define SDO1_IO		7
#define SCK1OUT_IO	8
#define SS1OUT_IO	9
#define SDO2_IO		10
#define SCK2OUT_IO	11
#define SS2OUT_IO	12
#define OC1_IO		18
#define OC2_IO		19
#define OC3_IO		20
#define OC4_IO		21
#define OC5_IO		22

//Depending on the install location you may need to tweak the include paths under Project->build options.
#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "HardwareProfile.h"

#include "usb_config.h"
#include "./USB/usb.h"
#include "./USB/usb_function_cdc.h"
#include "./USB/usb_device.h"

#define putUnsignedCharArrayUsbUsart(u8Array,Num) 	putUSBUSART((char*)(u8Array),(Num))
#define getUnsignedCharArrayUsbUart(u8Array,Num)	getsUSBUSART((char*)(u8Array),(Num))
