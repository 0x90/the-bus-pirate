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

#define BP_FIRMWARE_STRING "Firmware 3.5"

#define LANGUAGE_EN_US
//#define LANGUAGE_IT_IT
//#define LANGUAGE_ES_ES

//include/exclude modules here
#define BP_USE_1WIRE
#define BP_USE_HWUART //hardware uart (now also MIDI)
#define BP_USE_I2C
//#define BP_USE_I2C_HW
#define BP_USE_HWSPI //hardware spi
#define BP_USE_JTAG
#define BP_USE_RAW2WIRE
#define BP_USE_RAW3WIRE
#define BP_USE_PCATKB
//#define BP_USE_MIDI //merged with UART
//#define BP_USE_LIN
//#define BP_USE_CAN
#define BP_USE_LCD // include HD44780 LCD library

//
//
//
// END CONFIG AREA
//
//
//
#if defined(LANGUAGE_EN_US)
	#include "translations\en-US.h"
#elif defined(LANGUAGE_IT_IT)
	#include "translations\it-IT.h"
//	#include "translations\en-US.h"
#elif defined(LANGUAGE_ES_ES)
	#include "translations\es-ES.h"
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
};

struct _command {
	unsigned char cmd;
	unsigned int num; 
	unsigned int repeat;	
};

/********************************
*
*	BUS ABSTRACTION COMMANDS
*
**********************************/
//prepare for writes on the bus
//end writes on the bus
//write a byte to the bus, with optional read where applicable.
//read a byte from the bus
enum{
	CMD_READ,
	CMD_WRITE,

	CMD_START, //write only [
	CMD_STARTR,//with reads {
	CMD_STOP,
	CMD_MACRO,
/**************************************
*
*	RAW BUS OPERATION COMMANDS
*
*****************************************/
//reads a single bit, with a clock pulse, sets direction to input
//read data pin without a clock pulse, sets direction to input.
//set data output to desired state
//set clock output to desired state
//send clock ticks
	CMD_BIT_READ,
	CMD_BIT_PEEK,
	CMD_BIT_CLK,
	CMD_BIT_CLKH,
	CMD_BIT_CLKL,
	CMD_BIT_DATH,
	CMD_BIT_DATL,
	CMD_ERROR_MACRO,
	CMD_ERROR_MODE,

/**************************************
*
*	GLOBAL COMMANDS
*
*****************************************/
	CMD_AUXH,
	CMD_AUXL,
	CMD_AUXIN,
	CMD_DELAY,
	CMD_PWR_EN,
	CMD_PWR_DIS,
	CMD_ADC,
	
	//internal commands
	CMD_PERIODIC_SERVICE,
	CMD_NOP,
	CMD_PRESETUP,
	CMD_SETUP,
	CMD_CLEANUP,
	CMD_ERROR,
	CMD_ENDOFSYNTAX, //command to signal end of syntax to library
};

//reset all peripherals before configuring a new bus protocol
void bpInit(void); 

//Initialize the terminal UART for the speed currently set in bpConfig.termSpeed
void InitializeUART1(void); 

//take an ADC measurement on channel c
unsigned int bpADC(unsigned char c);
//takes a measurement from the ADC probe and prints the result to the user terminal
void bpADCprobe(void);

//print byte c to the user terminal in the format 
//  specified by the bpConfig.displayMode setting
void bpWbyte(unsigned char c);

//delays used by many libraries
void bpDelayMS(const unsigned char delay);
void bpDelayUS(const unsigned char delay);
#endif
