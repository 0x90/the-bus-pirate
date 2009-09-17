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
#include "busPirateCore.h"
#include "procMenu.h"
#include "procSyntax.h"
#include "selftest.h"

//HACKADAY: set custom configuration for PIC 24F
_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE & I2C1SEL_PRI)		// Internal FRC OSC = 8MHz
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx1) //turn off junk we don't need

//****************************************
//If defined, the reset vector pointer and boot mode entry delay
// value will be stored in the device's vector space at addresses 0x100 and 0x102
//#define USE_VECTOR_SPACE
//****************************************
//Bootloader Vectors *********************
#ifdef USE_VECTOR_SPACE
	/*
		Store delay timeout value & user reset vector at 0x100 
		(can't be used with bootloader's vector protect mode).
		
		Value of userReset should match reset vector as defined in linker script.
		BLreset space must be defined in linker script.
	*/
	unsigned int userReset  __attribute__ ((space(prog),section(".BLreset"))) = 0xC00 ;  
	unsigned char timeout  __attribute__ ((space(prog),section(".BLreset"))) = 0x00 ;
#else
	/*
		Store delay timeout value & user reset vector at start of user space
	
		Value of userReset should be the start of actual program code since 
		these variables will be stored in the same area.
	*/
	unsigned int userReset  __attribute__ ((space(prog),section(".init"))) = 0xC04 ;
	unsigned char timeout  __attribute__ ((space(prog),section(".init"))) = 0x00 ;
#endif

unsigned char irqFlag=0;
void _T1Interrupt(void);
void ISRTable(); //Pseudo function to hold ISR remap jump table

struct _bpConfig bpConfig; //holds persistant bus pirate settings (see buspiratecore.h)
struct _modeConfig modeConfig; //holds mode info, cleared between modes

void Initialize(void);

//this buffer holds the characters entered into the terminal 
//		untill enter is pressed
#define TERMINAL_BUFFER 4000
unsigned char terminalInput[TERMINAL_BUFFER];
unsigned int currentByte;

#pragma code
//this loop services user input and passes it to be processed on <enter>
int main(void){

	Initialize();//setup bus pirate

	while(1){ //this loop services user input and passes it to be processed on <enter>

		if(bpGetUserInput(&currentByte, TERMINAL_BUFFER, terminalInput)==1){
			switch(currentByte){
				case 0:
					bpWmessage(MSG_ERROR_SYNTAX);
					break;
				case 1:
					if(checkMenuCommand(terminalInput[0]))break;
				default:
					processSyntaxString(currentByte, terminalInput);//process a syntax string
			}
			currentByte=0;
			bpEchoCurrentBusMode(); //print the bus mode
			UART1TX('>');//echo prompt
		}

		//send the periodic service command to the current protocol
		//allows to check UART for async RX bytes, etc, independent of user input
		if(modeConfig.periodicService==1) bpProcess(CMD_PERIODIC_SERVICE,0,0);

/*		//function to catch an interrupt and display IRQ, for testing interrupts
		if(irqFlag==1){
			irqFlag=0;
			bpWline("IRQ DETECTED");
			bpEchoCurrentBusMode(); //print the bus mode
			UART1TX('>');//echo back//prompt
		}
*/

	}//while
}

//bus pirate initialization
//setup clock, terminal UART, pins, LEDs, and display version info
void Initialize(void){

	CLKDIVbits.RCDIV0=0; //clock divider to 0
	AD1PCFG = 0xFFFF;                 // Default all pins to digital
	OSCCONbits.SOSCEN=0;	

	//set pin configuration using peripheral pin select
	BP_TERM_RX=BP_TERM_RX_RP;   //Inputs UART1 RX RPINR18bits.U1RXR=4;
	BP_TERM_TX_RP=BP_TERM_TX; 		// Outputs UART1 TX RPOR1bits.RP3R=U1TX_IO;
 
	//put startup values in config (do first)
	bpConfig.termSpeed=8;//default PC side port speed, startup in 115200, or saved state (later)....
	bpConfig.displayMode=HEX;

	bpInit();//put startup values in config (do first)clean up, exit in HI-Z
		
	InitializeUART1(); //init the PC side serial port (needs bpInit() first for speed setting)

	#ifdef BUSPIRATE_POST
	bpPOST();//check for power-on self-test jumper, if true, do test mode 
	#endif

	// Get the chip type and revision
	bpConfig.dev_type = bpReadFlash(DEV_ADDR_UPPER, DEV_ADDR_TYPE);
	bpConfig.dev_rev = bpReadFlash(DEV_ADDR_UPPER, DEV_ADDR_REV);

	UART1TX(0x11); 	//send XON 0x11 flow control for terms that need it at startup

	bpWBR; 	//send a line feed

	versionInfo();//prints hardware and firmware version info (base.c)

	bpEchoCurrentBusMode(); //print the bus mode
	UART1TX('>');//prompt

}

//Interrupt Remap method 1:  Using direct interrupt address
/*void __attribute__ ((interrupt,address(0xF00), no_auto_psv)) _T1Interrupt(){
	IFS0bits.T1IF = 0;
	IEC0bits.T1IE = 0;
	PR1 = 0xFFFF;
	T1CON = 0;
	irqFlag=1;
	
}
*/

//Interrupt Remap method 2:  Using Goto and jump table
/*
void __attribute__ ((interrupt,no_auto_psv)) _T1Interrupt(){
	IFS0bits.T1IF = 0;
	IEC0bits.T1IE = 0;
	PR1 = 0xFFFF;
	T1CON = 0;
	irqFlag=1;
	
}
*/

/*
 *	ISR JUMP TABLE
 *
 *	It is necessary to define jump table as a function because C30 will
 *	not store 24-bit wide values in program memory as variables.
 *
 *	This function should be stored at an address where the goto instructions 
 *	line up with the remapped vectors from the bootloader's linker script.
*//*
void __attribute__ ((address(0x1000))) ISRTable(){

	asm("reset"); //reset instruction to prevent runaway code
	asm("goto %0"::"i"(&_T1Interrupt));  //T2Interrupt's address
} 
*/
