#include "base.h"
/*  Bus Pirate init function */
//bus pirate initialization
//setup clock, terminal UART, pins, LEDs, and display version info
void Initialize(void){

	CLKDIVbits.RCDIV0=0; //clock divider to 0
	AD1PCFG = 0xFFFF;                 // Default all pins to digital
	OSCCONbits.SOSCEN=0;	

	BP_LEDMODE_DIR=0; //MODE LED output

	IODIR|=(AUX+MOSI+CLK+MISO+CS);//AUX, MOSI, CLK, MISO, CS pins to input
	//IOLAT&=(~AUX+MOSI+CLK+MISO+CS); //low pin
	#ifdef BUSPIRATEV2
	BP_PULLUP_OFF();	//disable pullups
	#endif
	BP_VREG_OFF();		//disable vreg

	//set pin configuration using peripheral pin select
	BP_TERM_RX=BP_TERM_RX_RP;   //Inputs UART1 RX RPINR18bits.U1RXR=4;
	BP_TERM_TX_RP=BP_TERM_TX; 		// Outputs UART1 TX RPOR1bits.RP3R=U1TX_IO;
	InitializeUART1(); //init the PC side serial port

}

