//
// SUMP LA
//
//#ifdef SUMP_LA
#include "base.h"
#include "UART.h"

//commandset
//http://www.sump.org/projects/analyzer/protocol/
#define SUMP_RESET 	0x00
#define SUMP_RUN	0x01
#define SUMP_ID		0x02
#define SUMP_XON	0x11
#define SUMP_XOFF 	0x13
#define SUMP_DIV 	0x80
#define SUMP_CNT	0x81
#define SUMP_FLAGS	0x82
#define SUMP_TRIG	0xc0
#define SUMP_TRIG_VALS 0xc1

void SUMPlogicCommand(unsigned char inByte);
void SUMPlogicService(void);

static enum _LAstate {
	LA_IDLE = 0,
	LA_ARMED,
} LAstate = LA_IDLE;

#define LA_SAMPLE_SIZE 1024
unsigned char samples[LA_SAMPLE_SIZE];
unsigned char sumpPadBytes;
unsigned int sumpSamples;
unsigned int sumpSpeeds[]={ 
	0x0018, 0x6a00, //10hz
	0xc, 0x3500,//20
	0x4, 0xe200,//50
	0x2, 0x7100, //100
	0x1, 0x3880, //200
	0, 0x7d00, //500
	0, 0x3e80, //1K
	0, 0x640, //10 k
	0, 0x320, //20K
	0, 0x140, //50K
	0, 0xa0, //100K
	0, 0x50, //200k
	0, 0x20, //500K
	0, 0x1, //1mhz 0x10, but force to 1
};

//reuse terminal buffer for SUMP sampling
//extern unsigned char terminalInput[LA_SAMPLE_SIZE];

void SUMP(void){

	IODIR|=(AUX+MOSI+CLK+MISO+CS);//AUX, MOSI, CLK, MISO, CS pins to input
	SUMPlogicCommand(SUMP_RESET);
	SUMPlogicCommand(SUMP_ID);
	while(1){
		if(UART1RXRdy()) SUMPlogicCommand(UART1RX());
		SUMPlogicService();
	}
}


void SUMPlogicCommand(unsigned char inByte){
	static unsigned char i;
	static unsigned long l;

	static enum _SUMP {
		C_IDLE = 0,
		C_PARAMETERS,
		C_PROCESS,
	} sumpRXstate = C_IDLE;

	static struct _sumpRX {
		unsigned char command[5];
		unsigned char parameters;
		unsigned char parCnt;
	} sumpRX;

	switch(sumpRXstate){ //this is a state machine that grabs the incoming commands one byte at a time

		case C_IDLE:

			switch(inByte){//switch on the current byte
				case SUMP_RESET://reset
					BP_LEDMODE=0;//LED
					CNEN2=0;//change notice off
					T4CONbits.TON=0; //stop count
					//default speed and samples
					//setup PR register
					PR5=sumpSpeeds[14];//most significant word
					PR4=sumpSpeeds[15];//least significant word
					sumpSamples=LA_SAMPLE_SIZE;
					sumpPadBytes=0;
					LAstate=LA_IDLE;
					break;
				case SUMP_ID://SLA0 or 1 backwards: 1ALS
					bpWstring("1ALS");
					break;
				case SUMP_RUN://arm the triger
					BP_LEDMODE=1;//ARMED, turn on LED
					//setup timer
					T4CON=0;	//make sure the counters are off
					//timer 4 internal, measures interval
					TMR5HLD=0x00;
					TMR4=0x00;
					T4CON=0b1000; //.T32=1, bit 3

					//setup change notice interrupt
					CNPU1=0; //pullups off
					CNPU2=0;
					CNEN1=0; //all change notice off
					CNEN2=0;
					IFS1bits.CNIF=0; //clear interrupt flag
					IEC1bits.CNIE=0; //interrupts DISABLED
					IPC4bits.CNIP=1; //priority to 0, not actual interupt

					CNEN2=0b111100001; //change notice on all pins
					//CNEN2=0b100000; //change notice on CS pin

					LAstate=LA_ARMED;
					break;
				case SUMP_XON://resume send data
				//	xflow=1;
					break;
				case SUMP_XOFF://pause send data
				//	xflow=0;
					break;
				default://long command
					sumpRX.command[0]=inByte;//store first command byte
					sumpRX.parameters=4; //all long commands are 5 bytes, get 4 parameters
					sumpRX.parCnt=0;//reset the parameter counter
					sumpRXstate=C_PARAMETERS;
					break;
			}
			break;
		case C_PARAMETERS: 
			sumpRX.command[sumpRX.parCnt]=inByte;//store each parameter
			sumpRX.parCnt++;
			if(sumpRX.parCnt<sumpRX.parameters) break; //if not all parameters, quit
		case C_PROCESS: //ignore all long commands for now
			switch(sumpRX.command[0]){
/*
				case SUMP_TRIG: //set CN on these pins
					if(sumpRX.command[1] & 0b10000)     CNEN2|=0b1; //AUX
					if(sumpRX.command[1] & 0b1000)    CNEN2|=0b100000;
					if(sumpRX.command[1] & 0b100)   CNEN2|=0b1000000;
					if(sumpRX.command[1] & 0b10)  CNEN2|=0b10000000;
					if(sumpRX.command[1] & 0b1) CNEN2|=0b100000000;
*/
				case SUMP_FLAGS:
					sumpPadBytes=0;//if user forgot to uncheck chan groups 2,3,4, we can send padding bytes
					if(sumpRX.command[1] & 0b100000) sumpPadBytes++;
					if(sumpRX.command[1] & 0b10000) sumpPadBytes++;
					if(sumpRX.command[1] & 0b1000) sumpPadBytes++;
					break;
				case SUMP_CNT:
					sumpSamples=sumpRX.command[2];
					sumpSamples<<=8;
					sumpSamples|=sumpRX.command[1];
					sumpSamples*=4;
					//prevent buffer overruns
					if(sumpSamples>LA_SAMPLE_SIZE) sumpSamples=LA_SAMPLE_SIZE;
					break;
				case SUMP_DIV:
					l=sumpRX.command[3];
					l<<=8;
					l|=sumpRX.command[2];
					l<<=8;
					l|=sumpRX.command[1];
					if(l>= 0x000063){ //1MHZ +
						i=13;
					}else if(l>=0x0000c7){//500khz
						i=12;
					}else if(l>=0x0001f3){//200khz
						i=11;
					}else if(l>=0x0003e7){//100khz
						i=10;
					}else if(l>=0x0007cf){//50khz
						i=9;
					}else if(l>=0x001387){//20khz
						i=8;
					}else if(l>=0x00270f){//10khz
						i=7;
					}else if(l>=0x01869f){//1khz
						i=6;
					}else if(l>=0x030d3f){//500hz
						i=5;
					}else if(l>=0x07a11f){//200hz
						i=4;
					}else if(l>=0x0f423f){//100hz
						i=3;
					}else if(l>=0x1e847f){//50hz
						i=2;
					}else if(l>=0x4c4b3f){//20hz
						i=1;
					}else{//if(l>=0x98967f){//10hz
						i=0;
					}
					//setup PR register
					PR5=sumpSpeeds[(i*2)];//most significant word
					PR4=sumpSpeeds[((i*2)+1)];;//least significant word
					break;
			}

			sumpRXstate=C_IDLE;
			break;					
		}
}

//
//
//	To avoid rewriting interrupt vectors with the bootloader,
//  this firmware currently uses polling to read the trigger and timer
// 	A final version should use interrupts after lots of testing.
//
//
void SUMPlogicService(void){
	static unsigned int i;
	static unsigned char j;

	switch(LAstate){//dump data
		case LA_ARMED: //check interrupt flags
			if(IFS1bits.CNIF==0)break;//no flags
	
			//else sample
			T4CONbits.TON=1;//start timer4
			IFS1bits.T5IF=0;//clear interrupt flag//setup timer and wait

			for(i=0;i<sumpSamples;i++){ //take SAMPLE_SIZE samples
				samples[i]=(PORTB>>6); //change to pointer for faster use...
				while(IFS1bits.T5IF==0); //wait for timer4 (timer 5 interrupt)
				IFS1bits.T5IF=0;//clear interrupt flag//setup timer and wait
			}

			for(i=sumpSamples; i>0; i--){ //send back to SUMP, backwards
				UART1TX(samples[(i-1)]);
				//for(j=0; j<sumpPadBytes; j++) UART1TX(0); //add padding if needed
			}

			LAstate = LA_IDLE;
			break;
	}

}


