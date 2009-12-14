#include "base.h"
//#include "UART.h"
#include "upp.h"                              // Modifiable

#define SETPOINT 625 //5volts (613=11.5v)
#define PWM_P 7 //50khz
#define PWM_D 4

//set custom configuration for PIC 24F
_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE & I2C1SEL_PRI)		// Internal FRC OSC = 8MHz
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx1) //turn off junk we don't need
//unsigned int userReset  __attribute__ ((space(prog),section(".init"))) = 0xC04 ;
//unsigned char timeout  __attribute__ ((space(prog),section(".init"))) = 0x00 ;

//the main function waits for all the bytes in the STK500v2 packet, 
//then sends for processing in the above functions
int main(void){
	Initialize();
/*	//individual pin settings
	//ADC setup?
	AD1PCFGbits.PCFG12=0;//B12/AN12/ADC1/EXT //setup ADC probe pin

	//configure the ADC
	AD1CON1bits.SSRC  = 0b111;// SSRC<3:0> = 111 implies internal
								// counter ends sampling and starts
								// converting.
	AD1CSSL = 0;
	AD1CON3 = 0x1F02; // Sample time = 31Tad,
						// Tad = 2 Tcy
	AD1CON2 = 0;
	AD1CHS=12;//set channel
	AD1CON1bits.ADON = 1; // turn ADC ON
	
	//CS and AUX to output, ground (MCLR and VPP)
	BP_AUX=0; //PWM
	BP_AUX_DIR=0;
	BP_CS=0; //MCLR
	BP_CS_DIR=0;
	BP_LEDMODE_DIR=0;

	BP_MISO_DIR=0; //VPPEN
	BP_MISO=1;

	//PWM setup (leave off for now)
	//cleanup timers 
	T2CON=0;		// clear settings
	T4CON=0;
	OC5CON =0;

	T2CONbits.TCKPS1=1;
	T2CONbits.TCKPS0=0;

	//assign pin with PPS
	BP_AUX_RPOUT = OC5_IO;

	OC5R = PWM_D;	
	OC5RS = PWM_D;	
	OC5CON = 0x6;	
	PR2	= PWM_P;	

	//loop
	while(1){
		//take ADC measurement
		AD1CON1bits.SAMP=1;//start sample
		AD1CON1bits.DONE=0;//clear done (not really needed)
		while(AD1CON1bits.DONE==0);//wait for conversion to finish
		if(ADC1BUF0<SETPOINT){ //if<, PWM on, else off
			T2CONbits.TON = 1;		// Start Timer2 with assumed settings
			BP_LEDMODE=1;			
		}else{
			T2CONbits.TON = 0;
			BP_LEDMODE=0;
		}
	}
*/
	while(1) ProcessIO();

 
}

