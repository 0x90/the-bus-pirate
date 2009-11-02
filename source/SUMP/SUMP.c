//
// SUMP LA
//
//#ifdef SUMP_LA
#include <p24fxxxx.h>
#include "hardwarev3.h"
#include "UART.h"

//commandset
//http://www.sump.org/projects/analyzer/protocol/
#define SUMP_RESET 	0x00
#define SUMP_RUN	0x01
#define SUMP_ID		0x02
#define SUMP_XON	0x11
#define SUMP_XOFF 	0x13

static enum _LAstate {
	LA_IDLE = 0,
	LA_ARMED,
} LAstate = LA_IDLE;

volatile static struct {
	unsigned int sample;
	unsigned int ptr;
	unsigned char btrack;
}loga;

#define LA_SAMPLE_SIZE 4096
unsigned char samples[LA_SAMPLE_SIZE];


void SUMPlogicCommand(unsigned char inByte){

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
					LAstate=LA_IDLE;
					break;
				case SUMP_ID://SLA0 or 1 backwards: 1ALS
					UART1TX('1');
					UART1TX('A');
					UART1TX('L');
					UART1TX('S');
					break;
				case SUMP_RUN://arm the triger
					BP_LEDMODE=1;//ARMED, turn on LED
					//setup timer
					T4CON=0;	//make sure the counters are off
					//timer 4 internal, measures interval
					TMR5HLD=0x00;
					TMR4=0x00;
					//T4CON=0b1000; //.T32=1, bit 3
					T4CONbits.T32=1;
					T4CONbits.TCKPS0=0; //perhaps adjust these dynamically?
					T4CONbits.TCKPS1=0;
					T4CONbits.TCS=0; //internal source
					T4CONbits.TGATE=0; //no gate accumulation
					//10kHz timer
					PR5=0x00;//most significant word
					PR4=0x0651;//least significant word

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

	switch(LAstate){//dump data
		case LA_ARMED: //check interrupt flags
			if(IFS1bits.CNIF==0)break;//no flags
	
			//else sample
			T4CONbits.TON=1;//start timer4

			for(i=0;i<LA_SAMPLE_SIZE;i++){ //take SAMPLE_SIZE samples
				IFS1bits.T5IF=0;//clear interrupt flag//setup timer and wait
				samples[i]=(PORTB>>6); //change to pointer for faster use...
				while(IFS1bits.T5IF==0); //wait for timer4 (timer 5 interrupt)
			}

			for(i=LA_SAMPLE_SIZE; i>0; i--){ //send back to SUMP, backwards
				UART1TX(samples[(i-1)]);
			}

			LAstate = LA_IDLE;
			break;
	}

}


