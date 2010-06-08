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
#ifdef BP_USE_PIC
	#include "pic.h"
#endif

extern struct _bpConfig bpConfig;
extern struct _modeConfig modeConfig;
extern int cmderror;	

void nullfunc1(void)
{	//bpWline("ERROR: command has no effect here");
	BPMSG1059;
	cmderror=1;
}

unsigned int nullfunc2(unsigned int c)
{	//bpWline("ERROR: command has no effect here");
	BPMSG1059;
	cmderror=1;
	return 0x100;
}

unsigned int nullfunc3(void)
{	//bpWline("ERROR: command has no effect here");
	BPMSG1059;
	cmderror=1;
	return 0;
}

void nullfunc4(unsigned int c)
{	//bpWline("ERROR: command has no effect here");
	BPMSG1059;
	cmderror=1;
}

void HiZsetup(void)
{
}

void HiZcleanup(void)
{
}

void HiZpins(void)
{	//bpWline("CLK\tMOSI\tCS\MISO");
	BPMSG1225;
}

proto protos[MAXPROTO+1] = {
{	nullfunc1,				// start
	nullfunc1,				// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	nullfunc2,				// send
	nullfunc3,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc3,				// dats
	nullfunc1,				// clk
	nullfunc3,				// bitr
	nullfunc3,				// periodic
	nullfunc4,				// macro
	HiZsetup,				// setup
	HiZcleanup,				// cleanup
	HiZpins,
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
	nullfunc3,				// dats
	OWbitclk,				// clk
	OWbitr, 				// bitr
	nullfunc3,				// periodic
	OWmacro,				// macro
	OWsetup,				// setup
	HiZcleanup,				// cleanup
	OWpins,
	"1-WIRE" 				// name
}
#endif
#ifdef BP_USE_HWUART
,
{	UARTstart,				// start
	UARTstart,				// startR
	UARTstop,				// stop
	UARTstop,				// stopR
	UARTwrite,				// send
	UARTread,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc3,				// dats
	nullfunc1,				// clk
	nullfunc3,				// bitr
	UARTperiodic,			// periodic
	UARTmacro,				// macro
	UARTsetup,				// setup
	UARTcleanup,			// cleanup
	UARTpins,
	"UART" 					// name
}
#endif
#ifdef BP_USE_I2C
,
{	I2Cstart,				// start
	I2Cstart,				// startR
	I2Cstop,				// stop
	nullfunc1,				// stopR
	I2Cwrite,				// send
	I2Cread,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc3,				// dats
	nullfunc1,				// clk
	nullfunc3,				// bitr
	nullfunc3,				// periodic
	I2Cmacro,				// macro
	I2Csetup,				// setup
	I2Ccleanup,				// cleanup
	I2Cpins,
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
	nullfunc3,				// dats
	nullfunc1,				// clk
	nullfunc3,				// bitr
	nullfunc3,				// periodic
	SPImacro,				// macro
	SPIsetup,				// setup
	SPIcleanup,				// cleanup
	SPIpins,
	"SPI" 					// name
}
#endif
#ifdef BP_USE_RAW2WIRE
,
{	R2Wstart,				// start
	R2Wstart,				// startR
	R2Wstop,				// stop
	R2Wstop,				// stopR
	R2Wwrite,				// send
	R2Wread,				// read
	R2Wclkh,				// clkh
	R2Wclkl,				// clkl
	R2Wdath,				// dath
	R2Wdatl,				// datl
	R2Wbitp,				// dats (=bitpeek)
	R2Wclk,					// clk
	R2Wbitr,				// bitr
	nullfunc3,				// periodic
	R2Wmacro,				// macro
	R2Wsetup,				// setup
	HiZcleanup,				// cleanup
	R2Wpins,
	"2WIRE"					// name
}
#endif
#ifdef BP_USE_RAW3WIRE
,
{	R3Wstart,				// start
	R3Wstartr,				// startR
	R3Wstop,				// stop
	R3Wstop,				// stopR
	R3Wwrite,				// send
	R3Wread,				// read
	R3Wclkh,				// clkh
	R3Wclkl,				// clkl
	R3Wdath,				// dath
	R3Wdatl,				// datl
	R3Wbitp,				// dats
	R3Wclk,					// clk
 	R3Wbitr,				// bitr
	nullfunc3,				// periodic
	nullfunc4,				// macro
	R3Wsetup,				// setup
	HiZcleanup,				// cleanup
	R3Wpins,
	"3WIRE" 					// name
}
#endif
#ifdef BP_USE_PCATKB
,
{	nullfunc1,				// start
	nullfunc1,				// startR
	nullfunc1,				// stop
	nullfunc1,				// stopR
	KEYBwrite,				// send
	KEYBread,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc3,				// dats
	nullfunc1,				// clk
	nullfunc3,				// bitr
	nullfunc3,				// periodic
	KEYBmacro,				// macro
	KEYBsetup,				// setup
	HiZcleanup,				// cleanup
	HiZpins,
	"KEYB" 					// name
}
#endif
#ifdef BP_USE_LCD
,
{	LCDstart,				// start
	LCDstart,				// startR
	LCDstop,				// stop
	LCDstop,				// stopR
	LCDwrite,				// send
	LCDread,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc3,				// dats
	nullfunc1,				// clk
	nullfunc3,				// bitr
	nullfunc3, 				// periodic
	LCDmacro,				// macro
	LCDsetup,				// setup
	HiZcleanup,				// cleanup
	LCDpins,
	"LCD" 					// name
}
#endif
#ifdef BP_USE_PIC
,
{	picstart,				// start
	picstart,				// startR
	picstop,				// stop
	picstop,				// stopR
	picwrite,				// send
	picread,				// read
	nullfunc1,				// clkh
	nullfunc1,				// clkl
	nullfunc1,				// dath
	nullfunc1,				// datl
	nullfunc3,				// dats
	nullfunc1,				// clk
	nullfunc3,				// bitr
	nullfunc3, 				// periodic
	picmacro,				// macro
	picinit,				// setup
	piccleanup,				// cleanup
	picpins,
	"PIC" 					// name
}
#endif

};

