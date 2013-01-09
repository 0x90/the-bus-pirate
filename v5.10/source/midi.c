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
#include "uart2io.h"

extern struct _modeConfig modeConfig;
extern struct _command bpCommand;

struct _UART{
	unsigned char eu:1;//echo uart
} midiSettings;

void midiProcess(void){
	static unsigned char c;
	static unsigned int i;

	switch(bpCommand.cmd){
		case CMD_PERIODIC_SERVICE:
		 	if(UART2RXRdy()){//data ready
				if(midiSettings.eu==1){
					bpWBR;
					bpWmessage(MSG_READ);			
					c=UART2RX();
					bpWbyte(c);
					bpWBR;
				}else{
					UART2RX();//clear the buffer....
				}
			}
			break;
		case CMD_READ:
				bpWmessage(MSG_READ);			
			if(UART2RXRdy()){
				c=UART2RX();
				bpWbyte(c);
				bpWBR;
			}else{
				bpWline(OUMSG_MIDI_READ_FAIL);	
			}
			break;
		case CMD_WRITE:
			//bpWmessage(MSG_WRITE);
			//bpWbyte(bpCommand.num);
			//bpWBR;
			//UART2TX(bpCommand.num);//send byte
			bpWmessage(MSG_WRITE);
			bpWbyte(bpCommand.num);
			if(bpCommand.repeat==1){
				UART2TX(bpCommand.num);//send byte
			}else{
				bpWstring(" , ");
				bpWbyte(bpCommand.repeat);
				bpWmessage(MSG_WRITEBULK);
				for(i=0;i<bpCommand.repeat;i++) UART2TX(bpCommand.num);//send byte
			}
			bpWBR;
			break;
		case CMD_STARTR:
		case CMD_START:
			//open, start bridge
			//start
			midiSettings.eu=1;//open uart
			modeConfig.periodicService=1;//start periodic service calls
			bpWline(OUMSG_MIDI_LIVE_DISPLAY_ON);
			break;
		case CMD_STOP:
			//close bridge
			midiSettings.eu=0;// uart
			modeConfig.periodicService=0;//start periodic service calls
			bpWline(OUMSG_MIDI_LIVE_DISPLAY_OFF);
			break;
		case CMD_PRESETUP:
			bpWmessage(MSG_OPT_OUTPUT_TYPE);			
			modeConfig.HiZ=(~(bpUserNumberPrompt(1, 2, 1)-1));
			//modeConfig.allowlsb=0; //auto 0'd
			#ifdef BUSPIRATEV2
			modeConfig.allowpullup=1;
			#endif
			//31250, 8,n,1
			//@32MHz, BRGH=0:SPBRG=31, **BRGH=1:SPBRG=127
			UART2Setup(127,modeConfig.HiZ, 0, 0, 0);
			break;
		case CMD_SETUP:
			//modeConfig.periodicService=1;//start periodic service calls
			bpWmessage(MSG_ADAPTER);
			UART2Enable();
			bpWmessage(MSG_READY);
			break;
		case CMD_CLEANUP:
			//turn off UART
			UART2Disable();
			break;
		case CMD_MACRO:
			switch(bpCommand.num){
				default:
					bpWmessage(MSG_ERROR_MACRO);
			}
			break;
		case CMD_ENDOFSYNTAX: break;
		default:
			bpWmessage(MSG_ERROR_MODE);
	}

}
