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
#include "base.h"
//#include "raw2wire.h"
#include "bitbang.h"
#include "AUXpin.h"

#define R2WCLK_TRIS 	BP_CLK_DIR
#define R2WCLK 			BP_CLK 

#define R2WDIO_TRIS 	BP_MOSI_DIR
#define R2WDIO 			BP_MOSI

#define MENU 0
#define ISO78133ATR 1
#define ISO78133ATR_PARSE 2

extern struct _modeConfig modeConfig;
extern struct _command bpCommand;

void r2wMacro_78133Read(void);
void r2wMacro_78133Write(void);

void r2wProcess(void){
	static unsigned char c;
	static unsigned int i;

	switch(bpCommand.cmd){
		case CMD_READ:
			if(bpCommand.repeat==1){
				bpWmessage(MSG_READ);
				c=bbReadByte();
				bpWbyte(c);
			}else{
				bpWmessage(MSG_READBULK);
				bpWbyte(bpCommand.repeat);
				bpWmessage(MSG_READBULK_BYTES);
				for(i=0;i<bpCommand.repeat;i++){	
					bpWbyte(bbReadByte());
					bpSP;
				}
			}
			bpWBR;
			break;
		case CMD_WRITE:
			//bpWmessage(MSG_WRITE);	
			//bbWriteByte(bpCommand.num);
			//bpWbyte(bpCommand.num);
			//bpWBR;
			bpWmessage(MSG_WRITE);
			bpWbyte(bpCommand.num);
			if(bpCommand.repeat==1){
				bbWriteByte(bpCommand.num);//send byte
			}else{
				bpWstring(" , ");
				bpWbyte(bpCommand.repeat);
				bpWmessage(MSG_WRITEBULK);
				for(i=0;i<bpCommand.repeat;i++) bbWriteByte(bpCommand.num);//send byte
			}
			bpWBR;
			break;
		case CMD_STARTR:
		case CMD_START:
			bbI2Cstart();
			bpWstring("(\\-/_\\)");
			bpWmessage(MSG_I2C_START);
			break;
		case CMD_STOP:
			bbI2Cstop();
			bpWstring("(_/-\\)");
			bpWmessage(MSG_I2C_STOP);
			break;
		case CMD_BIT_READ:
			bpWmessage(MSG_BIT_READ);
			bpEchoState(bbReadBit());
			bpWmessage(MSG_BIT_NOWINPUT);	
			break;
		case CMD_BIT_PEEK:
			bpWmessage(MSG_BIT_PEEK);
			bpEchoState(bbMISO());
			bpWmessage(MSG_BIT_NOWINPUT);
			break;
		case CMD_BIT_CLK:
			bpWbyte(bpCommand.repeat);
			bpWmessage(MSG_BIT_CLK);
			bbClockTicks(bpCommand.repeat);
			break;
		case CMD_BIT_CLKH:
			bpWmessage(MSG_BIT_CLKH);
			bbCLK(1);
			break;
		case CMD_BIT_CLKL:
			bpWmessage(MSG_BIT_CLKL);
			bbCLK(0);
			break;
		case CMD_BIT_DATH:
			bpWmessage(MSG_BIT_DATH);
			bbMOSI(1);
			break;
		case CMD_BIT_DATL:
			bpWmessage(MSG_BIT_DATL);
			bbMOSI(0);
			break;
		case CMD_PRESETUP:
			//set the options avaiable here....
			modeConfig.allowlsb=1;
			modeConfig.allowpullup=1; 
			bpWmessage(MSG_OPT_BB_SPEED);
			modeConfig.speed=(bpUserNumberPrompt(1, 3, 1)-1);
			bpWmessage(MSG_OPT_OUTPUT_TYPE);
			modeConfig.HiZ=(~(bpUserNumberPrompt(1, 2, 1)-1));
			break;
		case CMD_SETUP:
			//writes to the PORTs write to the LATCH
			R2WCLK=0;			//B8 scl 
			R2WDIO=0;			//B9 sda
			R2WDIO_TRIS=1;//data input
			R2WCLK_TRIS=0;//clock output
			bbSetup(2, modeConfig.speed);
			bpWmessage(MSG_READY);
			break;
		case CMD_CLEANUP://no cleanup needed
			break;
		case CMD_MACRO:
			switch(bpCommand.num){
				case MENU:
					bpWstring(OUMSG_R2W_MACRO_MENU);
					break;
				case ISO78133ATR:
					r2wMacro_78133Write();
				case ISO78133ATR_PARSE:
					r2wMacro_78133Read();
					break;
				default:
					bpWmessage(MSG_ERROR_MACRO);
			}
			break;
		case CMD_ENDOFSYNTAX: break;
		default:
			bpWmessage(MSG_ERROR_MODE);
	}

}


//
// R2W macros

//ISO 7813-3 Answer to reset macro for smartcards
// syntax: a0%255@^a
// forces LSB format for easy use
// now uses CS pin instead of AUX pin because 1,2,3 have build in pullups on CS but not AUX
void r2wMacro_78133Write(void){

	bpWline("ISO 7816-3 ATR (RESET on CS)");
	bpWline("RESET HIGH, CLOCK TICK, RESET LOW");
	
	//Reset needs to start low
	bbCS(0); //bpAuxLow();
	bpDelayUS(0xff);
	
	//RESET HIGH
	bbCS(1);

	//clock tick
	bbClockTicks(1);

	//reset low again
	bbCS(0); //bpAuxLow();
}
	
void r2wMacro_78133Read(void){	
	unsigned char m[4];//macro buffer...
	unsigned char c;
	unsigned int i;

	bpWstring("ISO 7816-3 reply (uses current LSB setting): ");

	//force LSB fist setting for ISO compliance
	//c=modeConfig.lsbEN;//store origional setting
	//modeConfig.lsbEN=1;

	//read and display ISO 7813-3 bytes
	for(i=0; i<4; i++){
		m[i]=bbReadByte();
		bpWhex(m[i]);
		bpSP;
	}
	bpWBR;

	//modeConfig.lsbEN=c;//return to previous LSB setting

	//parse the first two bytes for 7813-3 atr header info
	//bits8:5 8=serial, 9=3wire, 10=2wire 0xf=RFU
	//c=(m[0]>>4);
	bpWstring("Protocol: ");
	switch((m[0]>>4)){
		case 0x08:
			bpWline("serial");
			break;
		case 0x09:
			bpWline("3 wire");
			break;
		case 0x0A:
			bpWline("2 wire");
			break;
		case 0x0F:
			bpWline("RFU");
			break;
		default:
			bpWline("unknown");
			break;
	}

	//bits4 RFU
	//bits 3:1 structure, x00 reserved, 010 general, 110 proprietary, x01 x11, special
	
	//bit 8 Supports random read lengths (0=false)
	bpWstring("Read type: ");
	//c=(m[1]>>7);
	if((m[1]>>7)==0){
		bpWline("to end");
	}else{
		bpWline("variable length");
	}
	
	//bit 7:4 data units (0001=128, 0010 = 256, 0011=512, etc, 1111=RFU)
	bpWstring("Data units: ");
	c=((m[1]&(~0b10000111))>>3);
	if(c==0){
		bpWstring("no indication");
	}else if(c==0b1111){
		bpWstring("RFU");
	}else{
		i=64;//no 0...
		for(m[0]=0;m[0]<c;m[0]++)i*=2;//multiply by two each time
		bpWintdec(i);
	}
	bpWBR;
	
	//bit 3:1 length of data units in bits (2^(3:1))
	bpWstring("Data unit length (bits): ");
	c=(m[1]&(~0b11111000));
	i=1;
	for(m[0]=0;m[0]<c;m[0]++)i*=2;//multiply by two each time
	bpWdec(i);
	bpBR;
}
