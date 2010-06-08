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
#ifndef BASE 
#define BASE
#include <p24fxxxx.h>

//this sets the hardware version
//#define BUSPIRATEV0A //http://hackaday.com/2008/11/19/how-to-the-bus-pirate-universal-serial-interface/
//#define BUSPIRATEV2A
//#define BUSPIRATEV25 //AKA Bus Pirate v2go
//#define BUSPIRATEV1A //http://hackaday.com/2009/01/22/how-to-bus-pirate-v1-improved-universal-serial-interface/
#define BUSPIRATEV3 

//#define BUSPIRATE_POST //used to switch POST on and off

#define BP_FIRMWARE_STRING "Firmware v5.0-pre3 (r358)"

#define LANGUAGE_EN_US
//#define LANGUAGE_IT_IT
//#define LANGUAGE_ES_ES

//include/exclude modules here
#define BP_USE_1WIRE
#define BP_USE_HWUART //hardware uart (now also MIDI)
#define BP_USE_I2C
//#define BP_USE_I2C_HW
#define BP_USE_HWSPI //hardware spi
#define BP_USE_RAW2WIRE
#define BP_USE_RAW3WIRE
//#define BP_USE_PCATKB
#define BP_USE_LCD // include HD44780 LCD library
#define BP_USE_PIC

#define MAXPROTO 9	// need to set it manually for now (is there a smart way for this?)

#define BP_USE_BASIC   // basic subsystem


// only 1 should be uncommented
//#define BASICTEST
//#define BASICTEST_I2C
//#define BASICTEST_UART
//#define BASICTEST_R3W
//#define BASICTEST_PIC10			// program blink a led
//#define BASICTEST_PIC10_2			// read whole pic

//sets the address in the bootloader to jump to on the bootloader command
//must be defined in asm
asm (".equ BLJUMPADDRESS, 0xABF8");

//
//
//
// END CONFIG AREA
//
//
//


#if defined(LANGUAGE_EN_US)
	#include "translations\en_US.h"
/*	my italian and spanish aint that good ;)
#elif defined(LANGUAGE_IT_IT)
	#include "translations\it-IT.h"
//	#include "translations\en-US.h"
#elif defined(LANGUAGE_ES_ES)
	#include "translations\es-ES.h"
*/
#else
	#error "No language defined in base.h."
#endif


#if defined(BUSPIRATEV0A)
	#include "hardwarev0a.h"
#elif defined(BUSPIRATEV1A)
	#include "hardwarev1a.h"
#elif defined(BUSPIRATEV2A)
	#define BUSPIRATEV2
	#include "hardwarev2a.h"
#elif defined(BUSPIRATEV25)
	#define BUSPIRATEV2
	#include "hardwarev25.h"
#elif defined(BUSPIRATEV3)
	#define BUSPIRATEV2
	#include "hardwarev3.h"
#else
	#error "No hardware defined in base.h."
#endif

#include "baseIO.h"
#include "baseUI.h"

//these settings are destroyed between modes.
//this is used to pass stuff from protocol libraries to BP
//for example, allowpullup determines if the P menu is available
//TO DO: add global scratch buffer to setting array for use in 
//	1-Wire enumeration, JTAG input buffer, etc...
struct _modeConfig {
	unsigned char speed; 
	unsigned char altAUX:1;
	unsigned char periodicService:1;
	unsigned char allowlsb:1;
	unsigned char lsbEN:1;
	unsigned char allowpullup:1; 
	unsigned char pullupEN:1; 
	unsigned char HiZ:1;
	unsigned char vregEN:1;
	unsigned char int16:1;			// 16 bits output?
};

struct _command {
	unsigned char cmd;
	unsigned int num; 
	unsigned int repeat;	
};

//reset all peripherals before configuring a new bus protocol
void bpInit(void); 

//Initialize the terminal UART for the speed currently set in bpConfig.termSpeed
void InitializeUART1(void); 

//take an ADC measurement on channel c
unsigned int bpADC(unsigned char c);
//takes a measurement from the ADC probe and prints the result to the user terminal
void bpADCprobe(void);
void bpADCCprobe(void);

//print byte c to the user terminal in the format 
//  specified by the bpConfig.displayMode setting
void bpWbyte(unsigned int c);

//delays used by many libraries
//void bpDelayMS(const unsigned char delay);
//void bpDelayUS(const unsigned char delay);
void bpDelayMS(int delay);
void bpDelayUS(int delay);
#endif
