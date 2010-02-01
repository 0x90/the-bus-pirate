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

//These functions abstract the various buses into a generic interface.
//add new modules here and in busPirateCore.h.
//be sure menu entries line up with the _bpConfig.busMode list in busPirateCore.h

#include "base.h"
#include "busPirateCore.h"

/*
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
*/
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

/*
//send command to correct protocol library for processing
//switch based on bpConfig.busMode variable
void bpProcess(void){
	switch(bpConfig.busMode){
	#ifdef BP_USE_1WIRE
		case DS1WIRE:
			DS1wireProcess();
			break;
	#endif
	#ifdef BP_USE_HWUART
		case HWUART:
			uartProcess();
			break;
	#endif
	#ifdef BP_USE_I2C
		case I2C:
			i2cProcess();
			break;
	#endif
	#ifdef BP_USE_HWSPI
		case HWSPI:
			spiProcess();
			break;
	#endif
	#ifdef BP_USE_JTAG
		case JTAG:
			jtagProcess();
			break;
	#endif
	#ifdef BP_USE_RAW2WIRE
		case RAW2WIRE:
			r2wProcess();
			break;
	#endif
	#ifdef BP_USE_RAW3WIRE
		case RAW3WIRE:
			r3wProcess();
			break;
	#endif
	#ifdef BP_USE_PCATKB
		case PCATKB:
			kbProcess();	
			break;
	#endif
	#ifdef BP_USE_MIDI
		case MIDI:
			midiProcess();	
			break;
	#endif
	#ifdef BP_USE_LIN
		case LIN:
			linProcess();		
			break;
	#endif
	#ifdef BP_USE_CAN
		case CAN:
			canProcess();	
			break;
	#endif
	#ifdef BP_USE_LCD
		case LCD:
			HD44780Process();	
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
*/

void nullfunc1(void)
{
}
void nullfunc2(unsigned int c)
{
}

void HiZsetup(void)
{
}

void HiZcleanup(void)
{
}

proto protos[MAXPROTO+1] = {
{	nullfunc1,				// start
	nullfunc1,				// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	nullfunc2,				// send
	nullfunc1,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc1,				// dats
	nullfunc1,				// clk
	nullfunc1,				// bitr
	nullfunc2,				// macro
	HiZsetup,				// setup
	HiZcleanup,				// cleanup
	"HiZ" 					// name
}
#ifdef BP_USE_1WIRE
,
{	DS1wireReset,			// start
	DS1wireReset,			// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	OWwrite,				// send
	OWread,					// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	OWdath,					// dath
	OWdatl,					// datl
	nullfunc1,				// dats
	OWbitclk,				// clk
	OWbitr, 				// bitr
	OWmacro,				// macro
	OWsetup,				// setup
	HiZcleanup,				// cleanup
	"1-WIRE" 				// name
}
#endif
#ifdef BP_USE_HWUART
,
{	nullfunc1,				// start
	nullfunc1,				// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	UARTwrite,				// send
	UARTread,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc1,				// dats
	nullfunc1,				// clk
	nullfunc1,				// bitr
	UARTmacro,				// macro
	UARTsetup,				// setup
	UARTcleanup,			// cleanup
	"UART" 					// name
}
#endif
#ifdef BP_USE_I2C
,
{	nullfunc1,				// start
	nullfunc1,				// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	nullfunc2,				// send
	nullfunc1,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc1,				// dats
	nullfunc1,				// clk
	nullfunc1,				// bitr
	nullfunc2,				// macro
	HiZsetup,				// setup
	HiZcleanup,				// cleanup
	"I2C" 					// name
}
#endif
#ifdef BP_USE_HWSPI
,
{	SPIstart,				// start
	SPIstartr,				// startR
	SPIstop,				// stop
	nullfunc1,				// stopR
	SPIwrite,				// send
	SPIread,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc1,				// dats
	nullfunc1,				// clk
	nullfunc1,				// bitr
	SPImacro,				// macro
	SPIsetup,				// setup
	SPIcleanup,				// cleanup
	"SPI" 					// name
}
#endif
#ifdef BP_USE_JTAG
,
{	nullfunc1,				// start
	nullfunc1,				// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	nullfunc2,				// send
	nullfunc1,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc1,				// dats
	nullfunc1,				// clk
	nullfunc1,				// bitr
	nullfunc2,				// macro
	HiZsetup,				// setup
	HiZcleanup,				// cleanup
	"JTAG" 					// name
}
#endif
#ifdef BP_USE_RAW2WIRE
,
{	nullfunc1,				// start
	nullfunc1,				// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	nullfunc2,				// send
	nullfunc1,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc1,				// dats
	nullfunc1,				// clk
	nullfunc1,				// bitr
	nullfunc2,				// macro
	HiZsetup,				// setup
	HiZcleanup,				// cleanup
	"2WIRE"					// name
}
#endif
#ifdef BP_USE_RAW3WIRE
,
{	nullfunc1,				// start
	nullfunc1,				// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	nullfunc2,				// send
	nullfunc1,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc1,				// dats
	nullfunc1,				// clk
	nullfunc1,				// bitr
	nullfunc2,				// macro
	HiZsetup,				// setup
	HiZcleanup,				// cleanup
	"3WIRE" 					// name
}
#endif
#ifdef BP_USE_PCATKB
,
{	nullfunc1,				// start
	nullfunc1,				// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	nullfunc2,				// send
	nullfunc1,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc1,				// dats
	nullfunc1,				// clk
	nullfunc1,				// bitr
	nullfunc2,				// macro
	HiZsetup,				// setup
	HiZcleanup,				// cleanup
	"KEYB" 					// name
}
#endif
#ifdef BP_USE_MIDI
,
{	nullfunc1,				// start
	nullfunc1,				// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	nullfunc2,				// send
	nullfunc1,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc1,				// dats
	nullfunc1,				// clk
	nullfunc1,				// bitr
	nullfunc2,				// macro
	HiZsetup,				// setup
	HiZcleanup,				// cleanup
	"MIDI" 					// name
}
#endif
#ifdef BP_USE_LIN
,
{	nullfunc1,				// start
	nullfunc1,				// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	nullfunc2,				// send
	nullfunc1,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc1,				// dats
	nullfunc1,				// clk
	nullfunc1,				// bitr
	nullfunc2,				// macro
	HiZsetup,				// setup
	HiZcleanup,				// cleanup
	"LIN" 					// name
}
#endif
#ifdef BP_USE_CAN
,
{	nullfunc1,				// start
	nullfunc1,				// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	nullfunc2,				// send
	nullfunc1,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc1,				// dats
	nullfunc1,				// clk
	nullfunc1,				// bitr
	nullfunc2,				// macro
	HiZsetup,				// setup
	HiZcleanup,				// cleanup
	"CAN" 					// name
}
#endif
#ifdef BP_USE_LCD
,
{	nullfunc1,				// start
	nullfunc1,				// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	nullfunc2,				// send
	nullfunc1,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc1,				// dats
	nullfunc1,				// clk
	nullfunc1,				// bitr
	nullfunc2,				// macro
	HiZsetup,				// setup
	HiZcleanup,				// cleanup
	"LCD" 					// name
}
#endif

};

