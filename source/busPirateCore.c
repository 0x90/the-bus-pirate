/*
 * This file is part of the Bus Pirate project (buspirate.com).
 *
 * Originally written by hackaday.com <legal@hackaday.com>
 *
 * To the extent possible under law, hackaday.com <legal@hackaday.com> has
 * waived all copyright and related or neighboring rights to Bus Pirate. This
 * work is published from United States.
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

//These functions abstract the various buses into a generic interface.
//add new modules here and in busPirateCore.h.
//be sure menu entries line up with the _bpConfig.busMode list in busPirateCore.h

#include "base.h"
#include "busPirateCore.h"

//be sure mode entries line up with the _bpConfig.busMode list in busPirateCore.h
char* mode[]  = 
   {
       "HiZ",
#ifdef BP_USE_1WIRE
       "1-WIRE",
#endif
#ifdef BP_USE_HWUART
		"UART",
#endif
#ifdef BP_USE_I2C
       "I2C",
#endif
#ifdef BP_USE_HWSPI
       "SPI",
#endif
#ifdef BP_USE_JTAG
		"JTAG",
#endif
#ifdef BP_USE_RAW2WIRE
       "RAW2WIRE",
#endif
#ifdef BP_USE_RAW3WIRE
       "RAW3WIRE",
#endif
#ifdef BP_USE_PCATKB
		"PC KEYBOARD",
#endif
#ifdef BP_USE_MIDI
		"MIDI",
#endif
#ifdef BP_USE_LIN
		"LIN",
#endif
#ifdef BP_USE_CAN
		"CAN",
#endif
#ifdef BP_USE_LCD
		"LCD",
#endif
   };

//include functions needed for protocol libraries
//add new libraries here
#ifdef BP_USE_1WIRE
	#include "1wire.h"
#endif
#ifdef BP_USE_HWUART
	#include "UART.h"
#endif
#ifdef BP_USE_I2C
	#include "I2C.h"
#endif
#ifdef BP_USE_HWSPI
	#include "SPI.h"
#endif
#ifdef BP_USE_JTAG
	#include "jtag.h"
#endif
#ifdef BP_USE_RAW2WIRE
	#include "raw2wire.h"
#endif
#ifdef BP_USE_RAW3WIRE
	#include "raw3wire.h"
#endif
#ifdef BP_USE_PCATKB
	#include "pc_at_keyboard.h"
#endif
#ifdef BP_USE_MIDI
	#include "midi.h"
#endif
#ifdef BP_USE_LIN
	#include "lin.h"
#endif
#ifdef BP_USE_CAN
	#include "can.h"
#endif
#ifdef BP_USE_LCD
	#include "HD44780.h"
#endif

extern struct _bpConfig bpConfig;
extern struct _modeConfig modeConfig;

//send command to correct protocol library for processing
//switch based on bpConfig.busMode variable
void bpProcess(unsigned char cmd, unsigned int numVal, unsigned int repeatVal){
	switch(bpConfig.busMode){
	#ifdef BP_USE_1WIRE
		case DS1WIRE:
			DS1wireProcess(cmd, numVal, repeatVal);
			break;
	#endif
	#ifdef BP_USE_HWUART
		case HWUART:
			uartProcess(cmd, numVal, repeatVal);
			break;
	#endif
	#ifdef BP_USE_I2C
		case I2C:
			i2cProcess(cmd, numVal, repeatVal);
			break;
	#endif
	#ifdef BP_USE_HWSPI
		case HWSPI:
			spiProcess(cmd, numVal, repeatVal);
			break;
	#endif
	#ifdef BP_USE_JTAG
		case JTAG:
			jtagProcess(cmd, numVal, repeatVal);
			break;
	#endif
	#ifdef BP_USE_RAW2WIRE
		case RAW2WIRE:
			r2wProcess(cmd, numVal, repeatVal);
			break;
	#endif
	#ifdef BP_USE_RAW3WIRE
		case RAW3WIRE:
			r3wProcess(cmd, numVal, repeatVal);
			break;
	#endif
	#ifdef BP_USE_PCATKB
		case PCATKB:
			kbProcess(cmd, numVal, repeatVal);	
			break;
	#endif
	#ifdef BP_USE_MIDI
		case MIDI:
			midiProcess(cmd, numVal, repeatVal);	
			break;
	#endif
	#ifdef BP_USE_LIN
		case LIN:
			linProcess(cmd, numVal, repeatVal);		
			break;
	#endif
	#ifdef BP_USE_CAN
		case CAN:
			canProcess(cmd, numVal, repeatVal);	
			break;
	#endif
	#ifdef BP_USE_LCD
		case LCD:
			HD44780Process(cmd, numVal, repeatVal);	
			break;
	#endif
		default: //error
			BP_LEDMODE=0;//turn off MODE LED, error/no mode (Hi-Z)
			break;
	}
}

//the number of bus modes available
//used to navigate the protocol list array, 
//done here because mode array isn't availble to other functions
unsigned char bpNumBusModes(void){return (sizeof(mode)/2);}

//echo the name of the current bus mode to the user terminal
//used to show user prompt
void bpEchoCurrentBusMode(void){bpWstring(mode[bpConfig.busMode]);}

//echo the name of the bus mode in the name array at position m to the user terminal
//used for listing available bus modes
void bpEchoBusMode(unsigned char m){bpWstring(mode[m]);}


