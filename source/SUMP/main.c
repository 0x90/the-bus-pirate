#include "SUMP.h"
#include "base.h"
#include "UART.h"

//set custom configuration for PIC 24F
_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE & I2C1SEL_PRI)		// Internal FRC OSC = 8MHz
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx1) //turn off junk we don't need

unsigned int userReset  __attribute__ ((space(prog),section(".init"))) = 0xC04 ;
unsigned char timeout  __attribute__ ((space(prog),section(".init"))) = 0x00 ;
void Initialize(void);

int main (void){
	Initialize();
	
	while(1){
		if(UART1RXRdy()) SUMPlogicCommand(UART1RX());
		SUMPlogicService();
	}

}

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

