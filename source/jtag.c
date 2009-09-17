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
#include "jtag.h"
//#include "jtag/micro.h"
//#include "jtag/ports.h"

extern struct _modeConfig modeConfig;

#define JTAGDATASETTLE 20
#define JTAGCLOCK 100

#define RESET 0
#define IDLE 1
#define SHIFTIR 2
#define SHIFTDR 3

//private functions
void jtagSetup(void);

//these are JTAG state machine related
void jtagSetState(unsigned char c);
void jtagLeaveState(void);
void jtagReset(void);
void jtagCleanPendingBit(void);
//high level byte operations
unsigned char jtagWriteByte(unsigned char c);
unsigned char jtagReadByte(void);
//bit level functions
unsigned char jtagWriteBit(unsigned char c);
unsigned char jtagReadBit(void);
unsigned char jtagReadDataState(void);
//bus level control
void jtagDataLow(void);
void jtagDataHigh(void);
void jtagClockLow(void);
void jtagClockHigh(void);
void jtagClockTicks(unsigned char c);
void jtagTMSHigh(void);
void jtagTMSLow(void);

static unsigned char jtagState=0, jtagBitPending=0, jtagDelayedBit=0;//static configuration variables for highZ and LSB

struct _JTAG{
	unsigned char HiZ:1;
} jtagSettings;

//this struct is unused, but it should replace the variables above
struct _JTAGSM {
	unsigned char state;
	unsigned char pending:1;//is there a bit pending
	unsigned char pbit:1; //what is it?
};

//struct _jtag jtagSM;

void jtagProcess(unsigned char cmd, unsigned int numVal, unsigned int repeatVal){
	static unsigned char c;
	static unsigned int i;

	switch(cmd){
		case CMD_PRESETUP:
			bpWmessage(MSG_OPT_OUTPUT_TYPE);
			jtagSettings.HiZ=(bpUserNumberPrompt(1, 2, 1)-1);
			modeConfig.HiZ=~jtagSettings.HiZ;
			modeConfig.allowlsb=1;
			#ifdef BUSPIRATEV2
			modeConfig.allowpullup=1;
			#endif
			break;
		case CMD_SETUP:
			jtagSetup();
			bpWmessage(MSG_READY);
			break;
		case CMD_CLEANUP://no cleanup needed (hi-z will be reset on pin reset function in buspirate.
			break;
		case CMD_START: //write to IR (instruction register)
			jtagLeaveState(); //clean up from previous state
			jtagSetState(SHIFTIR); //shift IR to enter data
			bpWline("JTAGSM: RDY TO WRITE INSTRUCTION REGISTER");
			break;
		case CMD_STARTR: //{, with reads
			jtagLeaveState(); //clean up from previous state
			jtagSetState(SHIFTDR); //shift IR to enter data
			bpWline("JTAGSM: RDY TO READ/WRITE DATA REGISTER");
			break;
		case CMD_STOP:
			jtagLeaveState(); //clean up from previous state
			//jtagSetState(IDLE);//clean up and go to idle state
							//this will send the last bit 
							//if we have a suspended write 
							//that needs to be sent with TMS state change
			bpWline("JTAGSM: IDLE");
			break;
		case CMD_READ:
			if(repeatVal==1){
				c=jtagReadByte();
				bpWmessage(MSG_READ);
				bpWbyte(c);
			}else{
				bpWmessage(MSG_READBULK);
				bpWbyte(repeatVal);
				bpWmessage(MSG_READBULK_BYTES);
				for(i=0;i<repeatVal;i++){	
					bpWbyte(jtagReadByte());
					bpSP;
				}
			}
			bpWBR;
			break;
		case CMD_WRITE:
			//c=jtagWriteByte(numVal);
			//bpWmessage(MSG_WRITE);	
			//bpWbyte(numVal);
			//bpWBR;

			bpWmessage(MSG_WRITE);
			bpWbyte(numVal);
			if(repeatVal==1){
				c=jtagWriteByte(numVal);
			}else{
				bpWstring(" , ");
				bpWbyte(repeatVal);
				bpWmessage(MSG_WRITEBULK);
				for(i=0;i<repeatVal;i++)c=jtagWriteByte(numVal);
			}
			bpWBR;
			break;
		case CMD_BIT_READ:
			c=jtagReadBit();
			bpWmessage(MSG_BIT_READ);
			bpEchoState(c);
			bpWBR;
			break;
		case CMD_BIT_PEEK:
			bpWmessage(MSG_BIT_PEEK);
			c=jtagReadDataState();
			bpEchoState(c);
			bpWBR;
			break;
		case CMD_BIT_CLK:
			bpWbyte(repeatVal);
			bpWmessage(MSG_BIT_CLK);
			jtagClockTicks(repeatVal);
			break;
		case CMD_BIT_CLKH:
			bpWmessage(MSG_BIT_CLKH);
			jtagClockHigh();
			break;
		case CMD_BIT_CLKL:
			bpWmessage(MSG_BIT_CLKL);
			jtagClockLow();
			break;
		case CMD_BIT_DATH:
			bpWmessage(MSG_BIT_DATH);
			jtagDataHigh();
			break;
		case CMD_BIT_DATL:
			bpWmessage(MSG_BIT_DATL);
			jtagDataLow();
			break;
		case CMD_MACRO:
			switch(numVal){
				case 0://jtag reset
					bpWstring(" 0.Macro menu\x0D\x0A 1.Reset chain\x0D\x0A 2.Probe chain\x0D\x0A 3.XSFV player (deprecated)\x0D\x0A");
					break;
				case 1://jtag reset
					jtagReset();//reset
					bpWline("JTAGSM: RESET");
					jtagLeaveState();//move chain to idle (gives own message)
					break;
				case 2://read ID, chain length, # devices
					bpWline("JTAG INIT CHAIN");
					jtagReset();//reset
					bpWline("JTAGSM: RESET");
					//data high
					jtagDataHigh();
					//how many devices?
					//[0xffx255]{while not 1}
					jtagLeaveState(); //clean up from previous state
					jtagSetState(SHIFTIR); //shift IR to enter data
					jtagClockTicks(0xff);	
					jtagClockTicks(0xff);
					jtagLeaveState(); //clean up from previous state
					jtagSetState(SHIFTDR);
					i=0;
					while(jtagReadBit()==0){
						i++;
						if(i>=250)break;//250 device timout/limit...
					}		
					jtagLeaveState(); //clean up from previous state			
					//reset
					jtagReset();
					bpWline("JTAGSM: RESET");
					//read ID#s (32 bits * devices) {r: (4*devices)}
					jtagLeaveState(); //clean up from previous state
					jtagSetState(SHIFTDR);

					bpWbyte(i);
					bpWline(" DEVICE(S) IN JTAG CHAIN");	
					for(c=0;c<i;c++){
						bpWbyte(c+1);
						bpWstring(" : ");
						bpWbyte(jtagReadByte());
					    bpSP;
						bpWbyte(jtagReadByte());
					    bpSP;
						bpWbyte(jtagReadByte());
					    bpSP;
						bpWbyte(jtagReadByte());
						bpBR;
					}
					jtagLeaveState(); //clean up from previous state
					break;
				case 3://XSFV player
					bpWline("XSFV player was removed in v2.1, if you need it downgrade to v2.0.");
					bpWline("It's huge, ugly, and the XSFV format is specialized.");
					bpWline("We'll add a real SFV player in the future.");			
					break;		
					/*UART1TX(0x11);//send XON 0x11
					bpWline("JTAG XSVF PLAYER");
					bpWline("XON/XOFF FLOW CONTROL REQUIRED");
					bpWline("PRESS z TO CONTINUE");
					while(1){
						while(IFS0bits.U1RXIF == 0);
						//return the byte
						i=U1RXREG;
					    IFS0bits.U1RXIF = 0;
						if(i==0x7a)break;
					}

					bpWline("BEGIN XSVF UPLOAD");
					UART1TX(0x13); //send XOFF 0x13		
					//data MUST be low when we start or we get error 3!
					jtagDataLow();
					jtagClockLow();
 					jtagTMSLow();


					//i=xsvfExecute();
					// Must #define XSVF_SUPPORT_ERRORCODES in micro.c to get these codes 
					switch(i){
						case 0 :
							bpWline("XSVF OK");
							break;
						case 1 :
							bpWline("XSVF UNKNOWN ERROR");
							break;
						case 2 :
							bpWline("XSVF ERROR TDO MISMATCH");
							break;
						case 3 ://TDO mismatch after max retries 
							bpWline("XSVF ERROR MAX RETRIES");
							break;
						case 4 :
							bpWline("XSVF ERROR ILLEGAL COMMAND");
							break;
						case 5 :
							bpWline("XSVF ERROR ILLEGAL STATE");
							break;
						case 6 : //Data > lenVal MAX_LEN buffer size
							bpWline("XSVF ERROR DATA OVERFLOW");
							break;
						default:
							bpWstring("XSVF ERROR: ");
							bpWbyte(i);
							bpWstring("\x0D\x0A");
					}

					bpWstring(" YOUR PC DRIBBLED MAX ");
					//bpWbyte(bm());
					bpWline(" BYTES AFTER XOFF (THAT'S OK)");
					bpWline("PRESS z 5 TIMES TO CONTINUE");
					UART1TX(0x11);//send XON 0x11, let buffer clear
					i=0;
					while(1){
						while(U1STAbits.URXDA == 0);
						c=U1RXREG;
						if(c==0x7a){ i++; }else{ i=0;}
						if(i==5)break;
					}		
					break;
				*/
				default:
					bpWmessage(MSG_ERROR_MACRO);
			}
			break;
		case CMD_ENDOFSYNTAX: break;
		default:
			bpWmessage(MSG_ERROR_MODE);
	}

}


//exits an existing JTAG state, moves to IDLE
void jtagLeaveState(void){
	//move to IDLE
	bpWstring("JTAGSM: ");
	switch(jtagState){
		case IDLE://already in idle
			bpWline("ALREADY IDLE");
			break;
		case RESET://move to idle 0
			jtagTMSLow();
			jtagClockTicks(1);
			jtagState=IDLE;	
			bpWline("RESET->IDLE");	
			break;
		case SHIFTIR://clean up pending writes...
			if(jtagBitPending==1){
				//set proper bit direction
				if(jtagDelayedBit==1){
					jtagDataHigh();
				}else{
					jtagDataLow();
				}
				jtagBitPending=0;//clear pending
				bpWstring("(WROTE DELAYED BIT) ");	
			}
			jtagTMSHigh();
			jtagClockTicks(2);
			jtagTMSLow();//always return to low for writes	
			jtagClockTicks(1);
			jtagState=IDLE;	
			bpWline("IR->IDLE");	
			break;
		case SHIFTDR://both same path 110
			jtagTMSHigh();
			jtagClockTicks(2);
			jtagTMSLow();//always return to low for writes	
			jtagClockTicks(1);
			jtagState=IDLE;	
			bpWline("DR->IDLE");	
			break;
		default:
			//couldn't change state, error, try resetting state machine...	
			bpWline("UNKNOWN STATE");	
			break;
	}
}

void jtagReset(void){
	jtagTMSHigh();
	jtagClockTicks(10);//one extra if clk starts high
	jtagTMSLow();//always return to low for writes	
	jtagState=RESET;	
}

//moves to specified state from IDLE (reset from anywhere)
void jtagSetState(unsigned char c){
	if(jtagState!=IDLE) bpWline("JTAGSM: WARNING OUT OF SYNC");
	bpWstring("JTAGSM: ");

	//move to desired state
	switch(c){
		case IDLE://alread idle
			bpWline("ALREADY IDLE");
			break;
		case RESET://always return to reset with 11111
			jtagReset();
			bpWline("RESET");
			break;
		case SHIFTDR://100 from IDLE
			jtagTMSHigh();
			jtagClockTicks(1);
			jtagTMSLow();//always return to low for writes	
			jtagClockTicks(2);
			jtagState=SHIFTDR;	
			bpWline("IDLE->Data Register");
			break;
		case SHIFTIR: //1100 from IDLE
			jtagTMSHigh();
			jtagClockTicks(2);
			jtagTMSLow();//always return to low for writes	
			jtagClockTicks(2);
			jtagState=SHIFTIR;	
			bpWline("IDLE->Instruction Register (DELAYED ONE BIT FOR TMS)");
			break;
		default:
		//unknown state, try resetting the JTAG state machine
			bpWline("UNKN STATE, TRY RESET (1)");
			break;
	}
}

void jtagSetup(void){
	JTAGTD0_TRIS=1;//input from chain
	JTAGTCK_TRIS=0;
	JTAGTDI_TRIS=0;
	JTAGTMS_TRIS=0;			//B6 cs output is state machine control
	//writes to the PORTs write to the LATCH
	JTAGTDO=0;
	JTAGTCK=0;
	JTAGTDI=0;
	JTAGTMS=0;			

}

//this is a new write routine, untested. See old below...
unsigned char jtagWriteByte(unsigned char c){
	unsigned char i,j,a,l;

	jtagClockLow();//begin with clock low...	
	
	//clean up any pending bits	
	if(jtagBitPending==1){
		jtagWriteBit(jtagDelayedBit);
		jtagBitPending=0;//clear pending
		bpWline("NOTE: WROTE DELAYED BIT");
	}

	if(modeConfig.lsbEN==1) l=0x01; else l=0b10000000;

	for(i=0;i<8;i++){
		if( (c & l)== 0) jtagDataLow(); else jtagDataHigh();//setup the data pin
			
		jtagClockHigh();//set clock high

		j=JTAGTDO;	
		if(modeConfig.lsbEN==1){
			c=c>>1;                 //-- Shift next bit into position	
			a=a>>1;
			if(j==1)a+=0b10000000;       
		}else{
			c=c<<1; 			//-- Shift next bit into position
			a=a<<1;    
			if(j==1)a++;     
		}

		jtagClockLow();//set clock low
		
		//catch bit seven and delay the write until we do the next byte or exit state with TMS=1....
		if(jtagState==SHIFTIR && i==6){
			jtagBitPending=1;
			if((c & l)==0) 	jtagDelayedBit=0; else jtagDelayedBit=1;
			return a;//meaningless....rather, 1 bit short
		}
	}
	return a;
}

unsigned char jtagReadByte(void){
	unsigned char i,j,a;

	jtagClockLow();//begin with clock low...	
	
	if(jtagBitPending==1){
		jtagWriteBit(jtagDelayedBit);
		jtagBitPending=0;//clear pending
		bpWline("NOTE: WROTE DELAYED BIT");
	}

	for(i=0;i<8;i++){
		jtagClockHigh();//set clock high
		j=JTAGTDO;	
		if(modeConfig.lsbEN==0){	
			a=a<<1;                 
			if(j)a++;			
		}else{
			a=a>>1;
			if(j)a+=0b10000000;
		}
		jtagClockLow();//set clock low
	}	

	return a;
}

unsigned char jtagWriteBit(unsigned char c){
	unsigned char i;

	if(c==0){
		jtagDataLow();
	}else{
		jtagDataHigh();
	}
	jtagClockHigh();//set clock high
	i=JTAGTDO;
	jtagClockLow();//set clock low
	return i;
}

unsigned char jtagReadBit(void){
	unsigned char i;

	jtagClockHigh();//set clock high
	i=JTAGTDO;
	jtagClockLow();//set clock low
	return i;
}

unsigned char jtagReadDataState(void){
	return JTAGTDO;
}

void jtagDataHigh(void){
	JTAGTDI_TRIS=(~jtagSettings.HiZ);//set output
	JTAGTDI=jtagSettings.HiZ;//data 
	bpDelayUS(JTAGDATASETTLE);//delay
}

void jtagDataLow(void){
	JTAGTDI=0; //data low
	JTAGTDI_TRIS=0;//set to output for HIGHZ low
	bpDelayUS(JTAGDATASETTLE);//delay
}

void jtagClockTicks(unsigned char c){
	unsigned char i;

	for(i=0;i<c;i++){
		jtagClockHigh();
		jtagClockLow();
	}
}

void jtagClockHigh(void){
	JTAGTCK_TRIS=(~jtagSettings.HiZ);//set output
	JTAGTCK=jtagSettings.HiZ;//data 
	bpDelayUS(JTAGCLOCK);//delay
}

void jtagClockLow(void){
	JTAGTCK=0;//set clock low	
	JTAGTCK_TRIS=0;//set clock output for HIGHZ
	bpDelayUS(JTAGCLOCK);//delay
}

void jtagTMSHigh(){
	JTAGTMS_TRIS=(~jtagSettings.HiZ);//set output
	JTAGTMS=jtagSettings.HiZ;//data 
	bpDelayUS(JTAGDATASETTLE);//delay
}

void jtagTMSLow(){
	JTAGTMS=0;//cs 
	JTAGTMS_TRIS=0;//cs output for HIGHZ
	bpDelayUS(JTAGDATASETTLE);//delay
}
