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
#include "uart2io.h"

extern struct _modeConfig modeConfig;

struct _UART{
	unsigned char dbp:2; //databits and parity
	unsigned char sb:1;//stop bits
	unsigned char rxp:1;//receive polarity
	unsigned char eu:1;//echo uart
} uartSettings;

static unsigned int UARTspeed[]={13332,3332,1666,832,416,207,103,68,34,};//BRG:300,1200,2400,4800,9600,19200,38400,57600,115200

void uartProcess(unsigned char cmd, unsigned int numVal, unsigned int repeatVal){
	static unsigned char c;
	static unsigned int i;

	switch(cmd){
		case CMD_PERIODIC_SERVICE:
		 	if(UART2RXRdy()){//data ready
				if(uartSettings.eu==1){
					bpWBR;
					bpWmessage(MSG_READ); //bpWstring(OUMSG_UART_READ);				
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
				bpWline(OUMSG_UART_READ_FAIL);	
			}
			break;
		case CMD_WRITE:
			bpWmessage(MSG_WRITE);
			bpWbyte(numVal);
			if(repeatVal==1){
				UART2TX(numVal);//send byte
			}else{
				bpWstring(" , ");
				bpWbyte(repeatVal);
				bpWmessage(MSG_WRITEBULK);
				for(i=0;i<repeatVal;i++) UART2TX(numVal);//send byte
			}
			bpWBR;
			break;
		case CMD_STARTR:
		case CMD_START:
			//open, start bridge
			//start
			//UART2Enable();
			uartSettings.eu=1;//open uart
			modeConfig.periodicService=1;//start periodic service calls
			bpWline(OUMSG_UART_LIVE_DISPLAY_ON);
			break;
		case CMD_STOP:
			//close bridge
			//UART2Disable();
			uartSettings.eu=0;// uart
			modeConfig.periodicService=0;//start periodic service calls
			bpWline(OUMSG_UART_LIVE_DISPLAY_OFF);
			break;
		case CMD_PRESETUP:
			bpWmessage(MSG_OPT_UART_BAUD); //write text (baud rate)
			modeConfig.speed=(bpUserNumberPrompt(1, 9, 1)-1); //get user reply
	
			//bpWstring("Data bits and parity:\x0D\x0A 1. 8, NONE *default \x0D\x0A 2. 8, EVEN \x0D\x0A 3. 8, ODD \x0D\x0A 4. 9, NONE \x0D\x0A");
			bpWline(OUMSG_UART_DATABITS_PARITY); //write text (data bit and parity)
			uartSettings.dbp=(bpUserNumberPrompt(1, 4, 1)-1);

			//bpWstring("Stop bits:\x0D\x0A 1. 1 *default\x0D\x0A 2. 2 \x0D\x0A");
			bpWline(OUMSG_UART_STOPBITS); //write text 
			uartSettings.sb=(bpUserNumberPrompt(1, 2, 1)-1);

			//string("Receive polarity:\x0D\x0A 1. Idle 1 *default\x0D\x0A 2. Idle 0\x0D\x0A");				
			bpWline(OUMSG_UART_RXPOLARITY); //write text 
			uartSettings.rxp=(bpUserNumberPrompt(1, 2, 1)-1);

			bpWmessage(MSG_OPT_OUTPUT_TYPE);			
			modeConfig.HiZ=(~(bpUserNumberPrompt(1, 2, 1)-1));
			//modeConfig.allowlsb=0; //already reset to 0
			#ifdef BUSPIRATEV2
			modeConfig.allowpullup=1;
			#endif
			break;
		case CMD_SETUP:
			UART2Setup(UARTspeed[modeConfig.speed],modeConfig.HiZ, uartSettings.rxp, uartSettings.dbp, uartSettings.sb );
			bpWmessage(MSG_READY);
			UART2Enable();
			break;
		case CMD_CLEANUP:
			//turn off UART
			UART2Disable();
			break;
		case CMD_MACRO:
			switch(numVal){
				case 0://menu
					bpWline(OUMSG_UART_MACRO_MENU);
					break;
				case 1://transparent UART
					bpWline("UART bridge. Space continues, anything else exits.");
					if(UART1RX()!=' ')break; //escape
					bpWline("Reset to exit.");
					// could use a lot of improvement
					//buffers for baud rate differences
					//it's best to adjust the terminal to the same speed you want to use to avoid buffer overuns
					//it will fail silently
					while(1){//never ending loop, reset Bus Pirate to get out
						if(U2STAbits.URXDA==1){
							if(U1STAbits.UTXBF == 0)
								U1TXREG = U2RXREG; //URXDA doesn't get cleared untill this happens
						}
						if(U1STAbits.URXDA==1){
							if(U2STAbits.UTXBF == 0)
								U2TXREG = U1RXREG; //URXDA doesn't get cleared untill this happens
						}

					}
					break;
				//case 2://auto UART baud rate
				//	break;			
				default:
					bpWmessage(MSG_ERROR_MACRO);
			}
			break;
		case CMD_ENDOFSYNTAX: break;
		default:
			bpWmessage(MSG_ERROR_MODE);
	}

}


