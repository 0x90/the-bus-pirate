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
#include "binIOhelpers.h"

extern struct _modeConfig modeConfig;
extern struct _command bpCommand;

struct _UART{
	unsigned char dbp:2; //databits and parity
	unsigned char sb:1;//stop bits
	unsigned char rxp:1;//receive polarity
	unsigned char eu:1;//echo uart
} uartSettings;

static unsigned int UART2speed[]={13332,3332,1666,832,416,207,103,68,34,127};//BRG:300,1200,2400,4800,9600,19200,38400,57600,115200, 31250,

void uartProcess(void){
	static unsigned char c;
	static unsigned int i;

	switch(bpCommand.cmd){
		case CMD_PERIODIC_SERVICE:
		 	if(UART2RXRdy()){//data ready
				if(uartSettings.eu==1){
					bpWBR;
					bpWmessage(MSG_READ); //bpWstring(OUMSG_UART_READ);	
					if(U2STAbits.PERR) bpWstring("-p "); //show any errors
					if(U2STAbits.FERR) bpWstring("-f ");
					c=UART2RX();
					bpWbyte(c);
					if(U2STAbits.OERR){
						bpWstring("*Bytes dropped*");
    					U2STA &= (~0b10); //clear overrun error if exists
					}	
					bpWBR;
				}else{
					UART2RX();//clear the buffer....
				}
			}
			break;
		case CMD_READ:
			bpWmessage(MSG_READ);			
			if(UART2RXRdy()){
				if(U2STAbits.PERR) bpWstring("-p "); //show any errors
				if(U2STAbits.FERR) bpWstring("-f ");
				c=UART2RX();
				bpWbyte(c);
				if(U2STAbits.OERR){
					bpWstring("*Bytes dropped*");
   					U2STA &= (~0b10); //clear overrun error if exists
				}	
				bpWBR;
			}else{
				bpWline(OUMSG_UART_READ_FAIL);	
			}
			break;
		case CMD_WRITE:
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
			//UART2Enable();
    		U2STA &= (~0b10); //clear overrun error if exists
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
			bpWline(" 10. 31250 (MIDI)"); //add midi to the standard list
			modeConfig.speed=(bpUserNumberPrompt(2, 10, 1)-1); //get user reply
	
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
			UART2Setup(UART2speed[modeConfig.speed],modeConfig.HiZ, uartSettings.rxp, uartSettings.dbp, uartSettings.sb );
			bpWmessage(MSG_READY);
			UART2Enable();
			break;
		case CMD_CLEANUP:
			//turn off UART
			UART2Disable();
			break;
		case CMD_MACRO:
			switch(bpCommand.num){
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
					U2STA &= (~0b10); //clear overrun error if exists
					while(1){//never ending loop, reset Bus Pirate to get out
						if((U2STAbits.URXDA==1)&& (U1STAbits.UTXBF == 0)){
								U1TXREG = U2RXREG; //URXDA doesn't get cleared untill this happens
						}
						if((U1STAbits.URXDA==1)&& (U2STAbits.UTXBF == 0)){
								U2TXREG = U1RXREG; //URXDA doesn't get cleared untill this happens
						}
					}
					break;
				case 2: //Watch raw UART
					bpWline("Raw UART input. Space to exit.");
					// could use a lot of improvement
					//buffers for baud rate differences
					//it's best to adjust the terminal to the same speed you want to use to avoid buffer overuns
					//it will fail silently
					U2STA &= (~0b10); //clear overrun error if exists
					while(1){//never ending loop, reset Bus Pirate to get out
						if((U2STAbits.URXDA==1)&& (U1STAbits.UTXBF == 0)){
								U1TXREG = U2RXREG; //URXDA doesn't get cleared untill this happens
						}
						if(UART1RX()==' ')break; //escape
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

/*
databits and parity (2bits)
1. 8, NONE *default \x0D\x0A 2. 8, EVEN \x0D\x0A 3. 8, ODD \x0D\x0A 4. 9, NONE
Stop bits:\x0D\x0A 1. 1 *default\x0D\x0A 2. 2 \x0D\x0A
Receive polarity:\x0D\x0A 1. Idle 1 *default\x0D\x0A 2. Idle 0\x0D\x0A
output type (hiz or regular
peripheral settings

# 00000000//reset to BBIO
# 00000001 – mode version string (ART1)
# 00000010 – UART start echo uart RX
# 00000011 – UART stop echo uart RX
# 00000111 - UART speed manual config, 2 bytes (BRGH, BRGL)
# 00001111 - bridge mode (reset to exit)
# 0001xxxx – Bulk transfer, send 1-16 bytes (0=1byte!)
# 0100wxyz – Set peripheral w=power, x=pullups, y=AUX, z=CS
# 0101wxyz – read peripherals 
# 0110xxxx - Set speed,0000=300,0001=1200,10=2400,4800,9600,19200,31250, 38400,57600,1010=115200,
# 0111xxxx - Read speed, 
# 100wxxyz – config, w=output type, xx=databits and parity, y=stop bits, z=rx polarity (default :00000)
# 101wxxyz – read config
*/
static unsigned int binUARTspeed[]={13332,3332,1666,832,416,207,127,103,68,34,};//BRG:300,1200,2400,4800,9600,19200,31250,38400,57600,115200

void binUARTversionString(void){bpWstring("ART1");}

void binUART(void){
	static unsigned char inByte, rawCommand,i;
	static unsigned int BRGval;

	uartSettings.dbp=0; //startup defaults
	uartSettings.sb=0;
	uartSettings.rxp=0;
	modeConfig.HiZ=1;
	BRGval=binUARTspeed[0]; //start at 300bps
	uartSettings.eu=0;
	UART2Setup(BRGval,modeConfig.HiZ, uartSettings.rxp, uartSettings.dbp, uartSettings.sb );
	UART2Enable();
	binUARTversionString();

	while(1){

		//check for incomming bytes on UART2
		//if echo enabled, send to USB
		//else, just clear the buffer
		if( UART2RXRdy()){
			if(uartSettings.eu==1){ 
				UART1TX(UART2RX());
			}else{
				UART2RX();//clear the buffer....
			}
		}
		if(U2STAbits.OERR) U2STA &= (~0b10); //clear overrun error if exists

		//process commands
		if(U1STAbits.URXDA == 1){//wait for a byte
			inByte=U1RXREG; //grab it
			rawCommand=(inByte>>4);//get command bits in seperate variable
			
			switch(rawCommand){
				case 0://reset/setup/config commands
					switch(inByte){
						case 0://0, reset exit
							UART2Disable();
							return; //exit
							break;
						case 1://reply string
							binUARTversionString();
							break;
						case 2://00000010 – Show UART input
							UART1TX(1);
							if(U2STAbits.OERR) U2STA &= (~0b10); //clear overrun error if exists
							uartSettings.eu=1;
							break;
						case 3://00000011 – Don't output UART input
							uartSettings.eu=0;
							UART1TX(1);
							break;
						case 7://00000111 - UART speed manual config, 2 bytes (BRGH, BRGL)
							UART1TX(1);
							UART2Disable();
							while(U1STAbits.URXDA == 0);//wait for a byte
							BRGval=(unsigned int)(U1RXREG<<8);
							UART1TX(1);
							while(U1STAbits.URXDA == 0);//wait for a byte
							BRGval|=U1RXREG;
							UART2Setup(BRGval,modeConfig.HiZ, uartSettings.rxp, uartSettings.dbp, uartSettings.sb );
							UART2Enable();
							UART1TX(1);
							break;
						case 15://00001111 - bridge mode (reset to exit)
							UART1TX(1);
							U2STA &= (~0b10); //clear overrun error if exists
							while(1){//never ending loop, reset Bus Pirate to get out
								if((U2STAbits.URXDA==1)&& (U1STAbits.UTXBF == 0)){
										U1TXREG = U2RXREG; //URXDA doesn't get cleared untill this happens
								}
								if((U1STAbits.URXDA==1)&& (U2STAbits.UTXBF == 0)){
										U2TXREG = U1RXREG; //URXDA doesn't get cleared untill this happens
								}
							}
						default:
							UART1TX(0);
							break;
					}	
					break;
				case 0b0001://get x+1 bytes
					inByte&=(~0b11110000); //clear command portion
					inByte++; //increment by 1, 0=1byte
					UART1TX(1);//send 1/OK		
	
					for(i=0;i<inByte;i++){
						while(U1STAbits.URXDA == 0);//wait for a byte
						UART2TX(U1RXREG);
						UART1TX(1);
					}
	
					break;
				case 0b0100: //configure peripherals w=power, x=pullups, y=AUX, z=CS
					binIOperipheralset(inByte);	
					UART1TX(1);//send 1/OK		
					break;
				case 0b0110://set speed 
					//0110xxxx - Set speed,0000=300,0001=1200,10=2400,4800,9600,19200,31250, 38400,57600,1010=115200,
					inByte&=(~0b11110000);//clear command portion
					if(inByte>0b1010) inByte=0b1010; //safe default if out of range
					BRGval=binUARTspeed[inByte];
					UART2Disable();
					UART2Setup(BRGval,modeConfig.HiZ, uartSettings.rxp, uartSettings.dbp, uartSettings.sb );
					UART2Enable();
					UART1TX(1);//send 1/OK	
					break;
				case 0b1000: //set config
				case 0b1001: //set config
					//100wxxyz – config, w=output type, xx=databits and parity, y=stop bits, z=rx polarity (default :00000)
					uartSettings.dbp=0;
					uartSettings.sb=0;
					uartSettings.rxp=0;
					modeConfig.HiZ=0;
					if(inByte&0b1000) uartSettings.dbp|=0b10;//set 
					if(inByte&0b100) uartSettings.dbp|=0b1;//set 
					if(inByte&0b10) uartSettings.sb=1;//set 	
					if(inByte&0b1) uartSettings.rxp=1;//set 
					if((inByte&0b10000)==0) modeConfig.HiZ=1;//hiz output if this bit is 1
					UART2Disable();
					UART2Setup(BRGval,modeConfig.HiZ, uartSettings.rxp, uartSettings.dbp, uartSettings.sb );
					UART2Enable();
					UART1TX(1);//send 1/OK	
					break;
				default:
					UART1TX(0x00);//send 0/Error
					break;
			}//command switch
		}//if inbyte
	}//while loop
}//function
