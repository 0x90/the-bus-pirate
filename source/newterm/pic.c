/*
 * This file is part of the Bus Pirate project (http://code.google.com/p/the-bus-pirate/).
 *
 * Initial written by Chris van Dongen, 2010.
 *
 * To the extent possible under law, the project has
 * waived all copyright and related or neighboring rights to Bus Pirate.
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/*

these are lowlevel interface subs for programming pics

supported platform (should) are:

pic10, pic12, pic14, pic16 and pic18

{0xFF} sends 4 byte cmd (pic18)
[0xFF] sends 6 byte cmd (pic10, 12, 14, 16)

*/

#include "pic.h"
#include "bitbang.h"
#include "baseIO.h"
#include "base.h"
#include "buspiratecore.h"
#include "procmenu.h"		// for the userinteraction subs


extern struct _bpConfig bpConfig;
extern struct _modeConfig modeConfig;

#ifdef BP_USE_PIC

int picmode;
int piccmddelay;

void picinit(void)
{	int mode, delay;
	int interactive;

	consumewhitechars();
	mode=getint();
	consumewhitechars();
	delay=getint();
	interactive=0;

	if(!((mode>0)&&(mode<=2)))
	{	interactive=1;
	}

	if((delay>0)&&(delay<=2))
	{	piccmddelay=delay;
	}
	else
	{	interactive=1;
	}

	if(interactive)
	{	cmderror=0;

		bpWline("Commandmode");
		bpWline("1. 6b cmd/14b data");
		bpWline("2. 4b cmd/16b data");
	
		mode=getnumber(1,2,0); 

		bpWline("Delay in ms");
		delay=getnumber(1,2,0);
	}

	switch(mode)
	{	case 1:	picmode=PICMODE6;
				break;
		case 2: picmode=PICMODE4;
				break;
		default: break;
	}
	piccmddelay=delay;

	if(!interactive)
	{	bpWstring("PIC (mod dly)=(");
		bpWdec(picmode); bpSP;
		bpWdec(piccmddelay);
		bpWline(")");
	}

	modeConfig.HiZ=1;				// to allow different Vcc 
	modeConfig.allowpullup=1;		// pullup is allowed
	modeConfig.int16=1;
	bbL(MOSI|CLK, PICSPEED);		// pull both pins to 0 before applying Vcc and Vpp
}

void piccleanup(void)
{	modeConfig.int16=0;				// other things are cleared except this one :D (we introduced it :D)
}

void picstart(void)					// switch  to commandmode
{	picmode|=PICCMD;
	bpWstring("CMD");
	UART1TX(0x30+(picmode&PICMODEMSK));			// display #commandbits 
	modeConfig.int16=0;
	bpSP;
}

void picstop(void)					// switch to datamode
{	picmode&=PICMODEMSK;
	modeConfig.int16=1;				// data is 14-16 bit
	bpWline("DTA");
}

unsigned int picread(void)
{	int i;
	unsigned int c;

	if(picmode&PICCMDMSK)
	{	bpWline("no read in cmd mode!!");
		return 0;
	}

	c=0;

	switch(picmode&PICMODEMSK)		// make it future proof
	{	case PICMODE6:	bbR(MOSI);		// switch in to input
						bbH(CLK, PICSPEED/2);
						bbL(CLK, PICSPEED/2);
						for(i=0; i<14; i++)
						{	c>>=1;
							bbH(CLK, PICSPEED/2);
							if(bbR(MOSI)) c|=0x2000;		// bit14
							bbL(CLK, PICSPEED/2);
						}
						bbH(CLK, PICSPEED/2);
						bbL(CLK, PICSPEED/2);
						bbL(MOSI, PICSPEED/5);
						break;
		case PICMODE4:	bbR(MOSI);
						for(i=0; i<16; i++)
						{	c>>=1;
							bbH(CLK, PICSPEED/2);
							if(bbR(MOSI)) c|=0x8000;		// bit16
							bbL(CLK, PICSPEED/2);
						}
						bbH(CLK, PICSPEED/2);
						bbL(CLK, PICSPEED/2);
						bbL(MOSI, PICSPEED/5);
						break;
		default:		bpWline("unknown picmode!!");
						return 0;
	}

//	bpWbin(c>>8); bpSP;
//	bpWbin(c&0x0FF); bpSP;
	return c;
}

unsigned int picwrite(unsigned int c)
{	int i;
	int mask;

	mask=0x01;

	if(picmode&PICCMDMSK)				// we got a command
	{	switch(picmode&PICMODEMSK)		// make it future proof
		{	case PICMODE6:	for(i=0; i<6; i++)
							{	bbH(CLK, PICSPEED/4);
								if(c&mask)
								{	bbH(MOSI, PICSPEED/4);
								}
								else
								{	bbL(MOSI, PICSPEED/4);
								}
								bbL(CLK, PICSPEED/4);
								bbL(MOSI, PICSPEED/4);		// both dat and clk low 
								mask<<=1;
							}
							break;
			case PICMODE4:	for(i=0; i<4; i++)
							{	bbH(CLK, PICSPEED/4);
								if(c&mask)
								{	bbH(MOSI, PICSPEED/4);
								}
								else
								{	bbL(MOSI, PICSPEED/4);
								}
								bbL(CLK, PICSPEED/4);
								bbL(MOSI, PICSPEED/4);		// both dat and clk low 
								mask<<=1;
							}
							break;
			default:		bpWline("unknown picmode!!");
							return 0;
		}
		bpDelayMS(piccmddelay);
	}
	else									// send data
	{	switch(picmode&PICMODEMSK)		// make it future proof
		{	case PICMODE6:	bbH(CLK, PICSPEED/4);			// send leading 0
							bbL(MOSI, PICSPEED/4);
							bbL(CLK, PICSPEED/4);
							bbL(CLK, PICSPEED/4);
							for(i=0; i<14; i++)				// 14 bits
							{	bbH(CLK, PICSPEED/4);
								if(c&mask)
								{	bbH(MOSI, PICSPEED/4);
								}
								else
								{	bbL(MOSI, PICSPEED/4);
								}
								bbL(CLK, PICSPEED/4);
								bbL(MOSI, PICSPEED/4);		// both dat and clk low 
								mask<<=1;
							}
							bbH(CLK, PICSPEED/4);			// send trailing 0
							bbL(MOSI, PICSPEED/4);
							bbL(CLK, PICSPEED/4);
							bbL(CLK, PICSPEED/4);
							break;
			case PICMODE4:	for(i=0; i<16; i++)				// does 16 bits at a time
							{	bbH(CLK, PICSPEED/4);
								if(c&mask)
								{	bbH(MOSI, PICSPEED/4);
								}
								else
								{	bbL(MOSI, PICSPEED/4);
								}
								bbL(CLK, PICSPEED/4);
								bbL(MOSI, PICSPEED/4);		// both dat and clk low 
								mask<<=1;
							}
							break;
			default:		bpWline("unknown picmode!!");
							return 0;
		}
	}
	return 0x100; 	// no data to display 
}

//todo 

void binpic(void)
{	return;
}
		
#endif
