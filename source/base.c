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

extern struct _bpConfig bpConfig; //global config variables
extern struct _modeConfig modeConfig; //mode config variables

void clearModeConfig(void); //private function to clear modeConfig on reset

//private function to clear modeConfig on reset
void clearModeConfig(void){
	//reset the options structure here...
	modeConfig.HiZ=0;
	modeConfig.speed=0; 
	modeConfig.periodicService=0;
	modeConfig.altAUX=0;
	modeConfig.allowlsb=0;
	modeConfig.lsbEN=0;
	modeConfig.allowpullup=0; 
	modeConfig.pullupEN=0;
	modeConfig.vregEN=0; 
}

//get bus pirate ready after first start
//or clean up after any dirty modules
//modules MUST teardown any PPS functions on the CMD_CLEANUP command
void bpInit(void){
	//do this manually so there aren't problems with hardware
	//that has I/O on different ports
	BP_MOSI_DIR=1;
	BP_CLK_DIR=1; 
	BP_MISO_DIR=1;
	BP_CS_DIR=1; 
	BP_AUX_DIR=1; 
	BP_LEDMODE=0; //mode LED OFF
	BP_LEDMODE_DIR=0;
	#ifdef BUSPIRATEV1A
		BP_PIN6_DIR=1; //AUX2... unused
		BP_LEDPWR=1; //light power led
		BP_LEDPWR_DIR=0;
	#endif

	bpConfig.busMode=HIZ;

	clearModeConfig(); //reset the mode settings structure
	
	#if defined( BUSPIRATEV0A) || defined( BUSPIRATEV2)
		BP_PULLUP_OFF();
	#endif

	#if defined( BUSPIRATEV1A) || defined( BUSPIRATEV2)
		
		BP_VREG_OFF();//disable the VREG

		//setup voltage monitoring on ADC. Should be moved to hardwarevx.h!
		AD1PCFGbits.PCFG9=0; //B15/AN9/ADC4/50V
		AD1PCFGbits.PCFG10=0;//B14/AN10/ADC3/33V
		AD1PCFGbits.PCFG11=0;//B13/AN11/ADC2/Vextpullup
		AD1PCFGbits.PCFG12=0;//B12/AN12/ADC1/EXT
		//AD1PCFG&=(~0b11110);//analog pins
	
		//configure the ADC
		AD1CON1bits.SSRC  = 0b111;// SSRC<3:0> = 111 implies internal
									// counter ends sampling and starts
									// converting.
		AD1CSSL = 0;
		AD1CON3 = 0x1F02; // Sample time = 31Tad,
							// Tad = 2 Tcy
		AD1CON2 = 0;
	#endif
}

#if defined( BUSPIRATEV1A) || defined (BUSPIRATEV2)
//take an ADC measurement on the specified channel
unsigned int bpADC(unsigned char c){
	AD1CHS=c;//set channel
	AD1CON1bits.SAMP=1;//start sample
	AD1CON1bits.DONE=0;//clear done (not really needed)
	while(AD1CON1bits.DONE==0);//wait for conversion to finish
	return ADC1BUF0;
}	

//takes a measurement from the ADC probe and prints the result to the user terminal
void bpADCprobe(void){
	AD1CON1bits.ADON = 1; // turn ADC ON
	bpWvolts(bpADC(12)); //print measurement
	AD1CON1bits.ADON = 0; // turn ADC OFF
}

#endif

//Initialize the terminal UART for the speed currently set in bpConfig.termSpeed
static unsigned int UARTspeed[]={13332,3332,1666,832,416,207,103,68,34,};//BRG:300,1200,2400,4800,9600,19200,38400,57600,115200
void InitializeUART1(void){
    U1BRG = UARTspeed[bpConfig.termSpeed];//13332=300, 1666=2400, 416=9600, 34@32mhz=115200....
    U1MODE = 0;
    U1MODEbits.BRGH = 1;
    U1STA = 0;
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;
    IFS0bits.U1RXIF = 0;
}

//print byte c to the user terminal in the format 
//  specified by the bpConfig.displayMode setting
void bpWbyte(unsigned char c){
	switch(bpConfig.displayMode){
		case HEX:
			bpWhex(c);
			break;
		case DEC:
			bpWdec(c);
			break;
		case BIN:
			bpWbin(c);
			break;
		case RAW:
			UART1TX(c);
			break;
	}
}

//delay in MS
void bpDelayMS(const unsigned char delay){
	volatile unsigned int i;
	volatile unsigned char c;
	
	for(c=0;c<delay;c++){
		for(i=0;i<4;i++) bpDelayUS(250);
	}

}

//delay in US
void bpDelayUS(const unsigned char delay)
{
	volatile unsigned char i;
	
	for(i=0;i<delay;i++){//@32MHz = 16MIPS, 16I/uS
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
	}
}




