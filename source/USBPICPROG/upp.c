/**************************************************************************
*   Copyright (C) 2008 by Frans Schreuder                                 *
*   usbpicprog.sourceforge.net    
*	Ported to Bus Pirate platform by Ian Lesnet (2009)                    *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
**************************************************************************/
#define SETPOINT 625 //5volts (613=11.5v)
#define PWM_P 7 //50khz
#define PWM_D 4
#define byte unsigned char
#include "io_cfg.h"             // I/O pin mapping
#include "upp.h"
//#include <string.h>
#include "prog.h"
#include "prog_lolvl.h"
#include "svn_revision.h"

void getBytes(unsigned char bytes, unsigned char start);

static unsigned char VPP_CTRL;
#define VPP_RUN VPP_CTRL
#define USBGEN_EP_SIZE 64
byte input_buffer[USBGEN_EP_SIZE];
byte output_buffer[USBGEN_EP_SIZE];

static char upp_version[]={SVN_REVISION};

void InitAdc(void)
{
	//***MOD***Bus Pirate ADC setup
	//ADC setup?
	AD1PCFGbits.PCFG12=0;//B12/AN12/ADC1/EXT //setup ADC probe pin

	//configure the ADC
	AD1CON1bits.SSRC  = 0b111;// SSRC<3:0> = 111 implies internal
								// counter ends sampling and starts
								// converting.
	AD1CSSL = 0;
	AD1CON3 = 0x1F02; // Sample time = 31Tad,
						// Tad = 2 Tcy
	AD1CON2 = 0;
	AD1CHS=12;//set channel
	AD1CON1bits.ADON = 1; // turn ADC ON
}


void ReadAdc(unsigned char* data)
{
	unsigned int i;
	//***MOD*** BUs Pirate ADC
	//take ADC measurement
	AD1CON1bits.SAMP=1;//start sample
	AD1CON1bits.DONE=0;//clear done (not really needed)
	while(AD1CON1bits.DONE==0);//wait for conversion to finish
	i=ADC1BUF0;
	data[0]=i;
	data[1]=(i>>8);
}

void UserInit(void)
{
	//mInitAllLEDs();
	//mInitAllSwitches();
	
	InitAdc();
	//old_sw2 = sw2;
	//Pump1tris = 0;
	//Pump2tris = 0;
	//CS and AUX to output, ground (MCLR and VPP)
	BP_AUX=0; //PWM
	BP_AUX_DIR=0;
	BP_CS=0; //MCLR
	BP_CS_DIR=0;
	BP_LEDMODE_DIR=0;

	BP_MISO_DIR=0; //VPPEN
	BP_MISO=1;

	//PWM setup (leave off for now)
	//cleanup timers 
	T2CON=0;		// clear settings
	T4CON=0;
	OC5CON =0;

	T2CONbits.TCKPS1=1;
	T2CONbits.TCKPS0=0;

	//assign pin with PPS
	BP_AUX_RPOUT = OC5_IO;

	OC5R = PWM_D;	
	OC5RS = PWM_D;	
	OC5CON = 0x6;	
	PR2	= PWM_P;
	
	TRISVPP = 0; //output
	TRISVPP_RST=0; //output
	TRISPGD=0;    
	TRISPGC=0;    
	//TRISVDD=0;
	//TRISVPP_RUN=0;
//	VPP_RUN=0;	//run = off
	PGD_LOW=1;
	TRISPGD_LOW=1; //LV devices disabled, high impedance / input
	PGC_LOW=1;
	TRISPGC_LOW=1; //LV devices disabled, high impedance / input
	VPP = 1; //VPP is low (inverted)
	VPP_RST=0; //No hard reset (inverted
	PGD=0;		
	PGC=0;
	//INTCON2bits.RBPU=1; //disable Portb pullup resistors
	//timer1Init();
	//timer0Init();
}//end UserInit

void setLeds(char n)
{
	BP_LEDMODE=~(n&1);
	//mLED_2=~((n&2)>>1);
	//mLED_3=~((n&4)>>2);
}

void getBytes(unsigned char bytes, unsigned char start){
	unsigned char i;
	for(i=0;i<bytes; i++){
		input_buffer[start]=UART1RX();
		start++;
	}
}
	
extern unsigned long tick, lasttick;
//unsigned int input_buffer_offset=0;
PICFAMILY picfamily=PIC18;
PICTYPE pictype=P18F2XXX;

void ProcessIO(void)
{
	char oldPGDtris;
	char PIN;
	static byte counter=0;
	int nBytes;
	unsigned long address;
	unsigned char i;
	
	input_buffer[0]=UART1RX(); //USBGenRead((byte*)input_buffer,64);
//	if(nBytes>0)
//	{
		switch(input_buffer[0])
		{
			case CMD_ERASE:
				setLeds(LEDS_ON | LEDS_WR);
				getBytes(1,1);//get more data, #bytes, where to insert in input buffer array
				output_buffer[0]=bulk_erase(picfamily,pictype,input_buffer[1]);
				counter=1;
				setLeds(LEDS_ON);
				break;
			case CMD_READ_ID:
				setLeds(LEDS_ON | LEDS_RD);
				switch(picfamily)
				{
					case DSPIC30:
						read_code(picfamily,pictype,0xFF0000,(unsigned char*)output_buffer,2,3);
						break;
					case PIC18:
						read_code(picfamily,pictype,0x3FFFFE,(unsigned char*)output_buffer,2,3);  //devid is at location 0x3ffffe   for PIC18 devices
						break;
					case PIC16:
						set_vdd_vpp(picfamily, pictype, 0);
						read_code(picfamily,pictype,0x2006,(unsigned char*)output_buffer,2,3);  //devid is at location 0x2006  for PIC16 devices
						break;
				}
				counter=2;
				setLeds(LEDS_ON);
				break;
			case CMD_WRITE_CODE:
				setLeds(LEDS_ON | LEDS_WR);
				address=((unsigned long)input_buffer[2])<<16|
						((unsigned long)input_buffer[3])<<8|
						((unsigned long)input_buffer[4]);
				output_buffer[0]=write_code(picfamily,pictype,address, (unsigned char*)(input_buffer+6),input_buffer[1],input_buffer[5]);
				counter=1;
				setLeds(LEDS_ON);
				break;
			case CMD_READ_CODE:
				setLeds(LEDS_ON | LEDS_RD);
				address=((unsigned long)input_buffer[2])<<16|
						((unsigned long)input_buffer[3])<<8|
						((unsigned long)input_buffer[4]);
				read_code(picfamily,pictype,address,(unsigned char*)output_buffer,input_buffer[1],input_buffer[5]);
				counter=input_buffer[1];
				setLeds(LEDS_ON);
				break;
			case CMD_WRITE_DATA:
				setLeds(LEDS_ON | LEDS_WR);
				address=((unsigned long)input_buffer[2])<<16|
						((unsigned long)input_buffer[3])<<8|
						((unsigned long)input_buffer[4]);
				output_buffer[0]=write_data(picfamily,pictype,address, (unsigned char*)(input_buffer+6),input_buffer[1],input_buffer[5]); 
				counter=1;
				setLeds(LEDS_ON);
				break;
			case CMD_READ_DATA:
				setLeds(LEDS_ON | LEDS_RD);
				address=((unsigned long)input_buffer[2])<<16|
						((unsigned long)input_buffer[3])<<8|
						((unsigned long)input_buffer[4]);
				read_data(picfamily,pictype,address,(unsigned char*)output_buffer,input_buffer[1],input_buffer[5]); 
				counter=input_buffer[1];
				setLeds(LEDS_ON);
				break;
			case CMD_WRITE_CONFIG:
				setLeds(LEDS_ON | LEDS_WR);
				address=((unsigned long)input_buffer[2])<<16|
						((unsigned long)input_buffer[3])<<8|
						((unsigned long)input_buffer[4]);
				output_buffer[0]=write_config_bits(picfamily, pictype, address, (unsigned char*)(input_buffer+6),input_buffer[1],input_buffer[5]);
				counter=1;
				setLeds(LEDS_ON);
				break;
			case CMD_SET_PICTYPE:
				output_buffer[0]=set_pictype(input_buffer+1);
				//output_buffer[0]=1; //Ok
				counter=1;
				setLeds(LEDS_ON);
				break;
			case CMD_FIRMWARE_VERSION:
				for(counter=0; counter<18; counter++)output_buffer[counter]=upp_version[counter];
				counter=18;
				setLeds(LEDS_ON);
				break;
			case CMD_DEBUG:
				setLeds(LEDS_ON | LEDS_WR | LEDS_RD);
				switch(input_buffer[1])
				{
					case 0:
						set_vdd_vpp(dsP30F, DSPIC30, 1);
						output_buffer[0]=1;
						counter=1;	
						break;
					case 1:
						set_vdd_vpp(dsP30F, DSPIC30, 0);
						output_buffer[0]=1;
						counter=1;	
						break;
					case 2:
						dspic_send_24_bits(((unsigned long)input_buffer[2])|
								((unsigned long)input_buffer[3])<<8|
								((unsigned long)input_buffer[4])<<16);
						output_buffer[0]=1;
						counter=1;
						break;
					case 3:
						nBytes =  dspic_read_16_bits();
						output_buffer[0]=(unsigned char)nBytes;
						output_buffer[1]=(unsigned char)(nBytes>>8);
						counter=2;
						break;
						
				}
				break;
			case CMD_GET_PIN_STATUS:
				switch(input_buffer[1])
				{
					case SUBCMD_PIN_PGC:
						if((!TRISPGC_LOW)&&(!PGC_LOW)) //3.3V levels
						{
							if(PGC) output_buffer[0] = PIN_STATE_3_3V;
							else output_buffer[0] = PIN_STATE_0V;
						}
						else	//5V levels
						{
							if(PGC) output_buffer[0] = PIN_STATE_5V;
							else output_buffer[0] = PIN_STATE_0V;
						}
						counter=1;
						break;
					case SUBCMD_PIN_PGD:
						if(TRISPGD)//PGD is input
						{
							if(PGD_READ) output_buffer[0] = PIN_STATE_5V;
							else output_buffer[0] = PIN_STATE_0V;
						}
						else
						{							
							if((!TRISPGD_LOW)&&(!PGD_LOW)) //3.3V levels
							{
								if(PGD) output_buffer[0] = PIN_STATE_3_3V;
								else output_buffer[0] = PIN_STATE_0V;
							}
							else	//5V levels
							{
								if(PGD) output_buffer[0] = PIN_STATE_5V;
								else output_buffer[0] = PIN_STATE_0V;
							}
						}
						counter=1;
						break;
					case SUBCMD_PIN_VDD:
						//if(VDD) output_buffer[0] = PIN_STATE_FLOAT;
						//else output_buffer[0] = PIN_STATE_5V;
						output_buffer[0] = PIN_STATE_5V;
						counter = 1;
						break;
					case SUBCMD_PIN_VPP:
						counter=1;
						if(!VPP){output_buffer[0] = PIN_STATE_12V;break;}
						if(VPP_RST){output_buffer[0] = PIN_STATE_0V;break;}
						if(VPP_RUN){output_buffer[0] = PIN_STATE_5V;break;}
						output_buffer[0] = PIN_STATE_FLOAT;
						break;
					case SUBCMD_PIN_VPP_VOLTAGE:
						ReadAdc(output_buffer);
						counter=2;
						break;
					default:
						output_buffer[0]=3;
						counter=1;
						break;
				}
				break;
			case CMD_SET_PIN_STATUS:
				switch(input_buffer[1])
				{
					case SUBCMD_PIN_PGC:
						switch(input_buffer[2])
						{
							case PIN_STATE_0V:
								TRISPGC = 0;
								PGC = 0;
								TRISPGC_LOW = 1;
								PGC_LOW = 0;
								output_buffer[0]=1;//ok
								break;
							case PIN_STATE_3_3V:
								TRISPGC = 0;
								PGC = 1;
								TRISPGC_LOW = 0;
								PGC_LOW = 0;
								output_buffer[0]=1;//ok
								break;
							case PIN_STATE_5V:
								TRISPGC = 0;
								PGC = 1;
								TRISPGC_LOW = 1;
								PGC_LOW = 0;
								output_buffer[0]=1;//ok
								break;
							default:
								output_buffer[0]=3;
								break;
						}
						break;
					case SUBCMD_PIN_PGD:
						switch(input_buffer[2])
						{
							case PIN_STATE_0V:
								TRISPGD = 0;
								PGD = 0;
								TRISPGD_LOW = 1;
								PGD_LOW = 0;
								output_buffer[0]=1;//ok
								break;
							case PIN_STATE_3_3V:
								TRISPGD = 0;
								PGD = 1;
								TRISPGD_LOW = 0;
								PGD_LOW = 0;
								output_buffer[0]=1;//ok
								break;
							case PIN_STATE_5V:
								TRISPGD = 0;
								PGD = 1;
								TRISPGD_LOW = 1;
								PGD_LOW = 0;
								output_buffer[0]=1;//ok
								break;
							case PIN_STATE_INPUT:
								TRISPGD_LOW = 1;
								TRISPGD = 1;
								output_buffer[0]=1;//ok
								break;
							default:
								output_buffer[0]=3;
								break;
						}
						break;
					case SUBCMD_PIN_VDD:
						switch(input_buffer[2])
						{
							case PIN_STATE_5V:
								//VDD = 0;
								output_buffer[0]=1;
								break;
							case PIN_STATE_FLOAT:
								//VDD = 1;
								output_buffer[0]=1;
								break;
							default:
								output_buffer[0]=3;
								break;
						}
						break;
					case SUBCMD_PIN_VPP:
						switch(input_buffer[2])
						{
							case PIN_STATE_0V:
								VPP = 1;
								VPP_RST = 1;
								VPP_RUN = 0;
								output_buffer[0]=1;//ok
								break;
							case PIN_STATE_5V:
								VPP = 1;
								VPP_RST = 0;
								VPP_RUN = 1;
								output_buffer[0]=1;//ok
								break;
							case PIN_STATE_12V:
								VPP = 0;
								VPP_RST = 0;
								VPP_RUN = 0;
								output_buffer[0]=1;//ok
								break;
							case PIN_STATE_FLOAT:
								VPP = 1;
								VPP_RST = 0;
								VPP_RUN = 0;
								output_buffer[0]=1;//ok
								break;
							default:
								output_buffer[0]=3;
								break;
						}
						break;
					default:
						output_buffer[0]=3;
				}
				counter=1;
				break;
		}
	//} //if nBytes>0
	if(counter != 0)
	{
		//if(!mUSBGenTxIsBusy())
		//USBGenWrite((byte*)&output_buffer,counter);
		for(i=0; i<counter; i++) UART1TX(output_buffer[i]);
		counter=0;
	}
}//end ProcessIO


unsigned char set_pictype(unsigned char* data)
{
	pictype=data[0];
	switch(pictype)
	{
        	case P10F200:
		case P10F202:
		case P16F54:
		case P16F57:
		case P16F59:picfamily=PIC10;break;
		case P16F87XA:
		case P16F62XA:
		case P16F62X:
		case P12F629:
		case P12F6XX:
		case P12F61X:
		case P16F84A:
		case P16F81X:
		case P16F7X:
		case P16F7X7:
		case P16F87X:
		case P16F72:
		case P16F87:
		case P16F785:
		case P16F91X:
		case P16F88X:
		case P16C6XX:
		case P16C55X:
		case P16C7XX:
		case P16C64x:
		case P14000:
		case P16C50X:
		case P16C432:
		case P17CXX:
		case P16F716:
		case P17C7XX:picfamily=PIC16;break;
		case P18F2XXX:
		case P18FXX2:picfamily=PIC18;break;
		case P18FXX39:
		case P18F6X2X:
		case P18FXX80:
		case P18F8410:
		case P18F6XJXX:
		case P18F45J10:
		case P18F97J60:
		case P18F1X30:
		case P18FXX23:
		case P18FXXK20:picfamily=PIC18;break;
		case P24FJXXXGA0XX:
		case P24H:
		case P24FJXXXGA1:picfamily=PIC24;break;
		case dsP30F:picfamily=DSPIC30;break;
		case dsP33F:picfamily=dsPIC33;break;
   		default: pictype=P18F2XXX;picfamily=PIC18;return 3;break;
	}
	return 1;	
}


