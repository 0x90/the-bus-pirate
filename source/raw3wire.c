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

#include "base.h"
//#include "raw3wire.h"
#include "bitbang.h"

#define R3WMOSI_TRIS 	BP_MOSI_DIR
#define R3WCLK_TRIS 	BP_CLK_DIR
#define R3WMISO_TRIS 	BP_MISO_DIR
#define R3WCS_TRIS 		BP_CS_DIR


#define R3WMOSI 		BP_MOSI
#define R3WCLK 			BP_CLK 
#define R3WMISO 		BP_MISO 
#define R3WCS 			BP_CS 

extern struct _modeConfig modeConfig;

struct _R3W{
	unsigned char wwr:1;
} r3wSettings;

void r3wProcess(unsigned char cmd, unsigned int numVal, unsigned int repeatVal){
	static unsigned char c;
	static unsigned int i;

	switch(cmd){
		case CMD_READ:
			if(repeatVal==1){
				bpWmessage(MSG_READ);
				bpWbyte(bbReadWriteByte(0xff));
			}else{
				bpWmessage(MSG_READBULK);
				bpWbyte(repeatVal);
				bpWmessage(MSG_READBULK_BYTES);
				for(i=0;i<repeatVal;i++){	
					bpWbyte(bbReadWriteByte(0xff));
					bpSP;
				}
			}
			bpWBR;
			break;
		case CMD_WRITE:
			bpWmessage(MSG_WRITE);
			bpWbyte(numVal);
			if(repeatVal==1){
				c=bbReadWriteByte(numVal);
				if(r3wSettings.wwr==1){
					bpSP;
					bpWmessage(MSG_READ);
					bpWbyte(c);
				}
			}else{
				bpWstring(" , ");
				bpWbyte(repeatVal);
				bpWmessage(MSG_WRITEBULK);
				for(i=0;i<repeatVal;i++)c=bbReadWriteByte(numVal);
			}
			bpWBR;
			break;
		case CMD_STARTR:
		case CMD_START:
			if(cmd==CMD_STARTR){r3wSettings.wwr=1;}else{r3wSettings.wwr=0;}
			bbCS(0);
			bpWmessage(MSG_CS_ENABLED);
			break;
		case CMD_STOP:
			r3wSettings.wwr=0;
			bbCS(1);
			bpWmessage(MSG_CS_DISABLED);
			break;
		case CMD_BIT_READ: //note: uses existing data state (good)
			bpWmessage(MSG_BIT_READ);
			bpEchoState(bbReadBit());
			bpWBR;
			break;
		case CMD_BIT_PEEK:
			bpWmessage(MSG_BIT_PEEK);
			bpEchoState(bbMISO());
			bpWBR;
			break;
		case CMD_BIT_CLK:
			bpWbyte(repeatVal);
			bpWmessage(MSG_BIT_CLK);
			bbClockTicks(repeatVal);
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
			bpWmessage(MSG_OPT_BB_SPEED);
			modeConfig.speed=(bpUserNumberPrompt(1, 2, 1)-1);
			bpWmessage(MSG_OPT_OUTPUT_TYPE);
			modeConfig.HiZ=(~(bpUserNumberPrompt(1, 2, 1)-1));
			modeConfig.allowlsb=1;
			#ifdef BUSPIRATEV2
			modeConfig.allowpullup=1;
			#endif
			break;
		case CMD_SETUP:
			//reset the write with read variable
			r3wSettings.wwr=0;
			
			bbSetup(3, modeConfig.speed); //setup the bitbang library, must be done before calling bbCS below
			//setup pins (pins are input/low when we start)
			//MOSI output, low
			//clock output, low
			//MISO input
			//CS output, high
			R3WMOSI_TRIS=0;
			R3WCLK_TRIS=0;
			R3WMISO_TRIS=1;
			bbCS(1);//takes care of custom HiZ settings too

			bpWmessage(MSG_READY);
			break;
		case CMD_CLEANUP://no cleanup needed
			break;
		case CMD_MACRO:
			//switch(numVal){
			//	default:
					bpWmessage(MSG_ERROR_MACRO);
			//}
			break;
		case CMD_ENDOFSYNTAX: break;
		default:
			bpWmessage(MSG_ERROR_MODE);
	}

}

