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
#include "baseIO.h"

#define AUXPIN_DIR 		BP_AUX_DIR
#define AUXPIN_RPIN 	BP_AUX_RPIN
#define AUXPIN_RPOUT 	BP_AUX_RPOUT

extern struct _modeConfig modeConfig;

static enum _auxmode
	{
	 AUX_IO=0,
	 AUX_FREQ,
	 AUX_PWM,
	} AUXmode=AUX_IO;


void bpPWM(void){
	unsigned int PWM_period, PWM_dutycycle, PWM_freq, PWM_div;
	//unsigned long PWM_div;

	float PWM_pd;
	
	if(AUXmode==AUX_PWM){
		T2CONbits.TON = 0;		// Start Timer2 with assumed settings
		AUXPIN_RPOUT = 0;	 //remove output from AUX pin
		bpWline(OUMSG_AUX_PWM_OFF);
		AUXmode=AUX_IO;
		return;
	}

	//calculate frequency:
	bpWline(OUMSG_AUX_PWM_NOTE);
	bpWstring(OUMSG_AUX_PWM_FREQ);
	//PWM_period=(16000000/bpUserNumberPrompt(5, 0xffff, 50000))-1;
	PWM_freq=bpUserNumberPrompt(4, 4000, 50);
	//choose proper multiplier for whole range
	bpWstring(OUMSG_AUX_PWM_PRESCALE);
	if(PWM_freq<4){//use 256 //actual max is 62500hz
		bpWline("256");
		PWM_div=62;//actually 62500
		T2CONbits.TCKPS1=1;
		T2CONbits.TCKPS0=1;
	}else if(PWM_freq<31){//use 64
		bpWline("64");
		PWM_div=250;
		T2CONbits.TCKPS1=1;
		T2CONbits.TCKPS0=0;
	}else if(PWM_freq<245){//use 8
		bpWline("8");
		PWM_div=2000;
		T2CONbits.TCKPS1=0;
		T2CONbits.TCKPS0=1;
	}else{//use 1
		bpWline("1");
		PWM_div=16000;
		T2CONbits.TCKPS1=0;
		T2CONbits.TCKPS0=0;
	}
	PWM_period=(PWM_div/PWM_freq)-1;
	bpWstring("PR2:");
	bpWintdec(PWM_period);	
	bpBR;

	bpWstring(OUMSG_AUX_PWM_DUTY);
	PWM_pd=bpUserNumberPrompt(2, 99, 50);
	PWM_pd/=100;
	PWM_dutycycle=PWM_period * PWM_pd;
	//bpWdec(PWM_dutycycle);

	//assign pin with PPS
	//__builtin_write_OSCCONL(OSCCON & 0xbf); //unlock PPS
	AUXPIN_RPOUT = OC5_IO;
	//__builtin_write_OSCCONL(OSCCON | 0x40); 	//lock PPS

	//cleanup timers from FREQ measure
	T2CONbits.T32=0;//16 bit mode
	T4CONbits.T32=0;
	T2CONbits.TCS=0; //internal clock source


	OC5CONbits.OCM		= 0; 		// Output compare channel is disabled
	OC5R				= PWM_dutycycle;	// Initialize Compare Register1 with 50% duty cycle
	OC5RS				= PWM_dutycycle;	// Initialize Secondary Compare Register1 with 50% duty cycle
	OC5CONbits.OCSIDL	= 0;		// Output capture will continue to operate in CPU Idle mode
	OC5CONbits.OCFLT	= 0;		// No PWM Fault condition has occurred (this bit is only used when OCM<2:0> = 111)
	OC5CONbits.OCTSEL	= 0;		// Timer2 is the clock source for output Compare
	OC5CONbits.OCM		= 0x6;		// PWM mode on OC, Fault pin disabled
	PR2					= PWM_period;	// Initialize PR2 with 0x0132 = 0d306 as PWM cycle
	T2CONbits.TON		= 1;		// Start Timer2 with assumed settings

	bpWline(OUMSG_AUX_PWM_ON);
	AUXmode=AUX_PWM;

}

//frequency measurement
void bpFreq(void){
	static unsigned int j,k;
	static unsigned long l;

	if(AUXmode==AUX_PWM){
		bpWline(OUMSG_AUX_FREQ_PWM);
		return;
	}

	bpWstring(OUMSG_AUX_FREQCOUNT);
//setup timer
	T4CONbits.TON=0;	//make sure the counters are off
	T2CONbits.TON=0;	
//timer 2 external
	AUXPIN_DIR=1;//aux input
	RPINR3bits.T2CKR=AUXPIN_RPIN; //assign T2 clock input to aux input

	//T2CON=(T32|TCKPS1|TCKPS0|TCS);
	T2CONbits.T32=1;//32 bit mode
	T2CONbits.TCKPS1=1; //0=1,01=8,10=64,11=256....
	T2CONbits.TCKPS0=1;
	T2CONbits.TCS=1; //external clock source
	PR3=0xffff;//most significant word
	PR2=0xffff;//least significant word
	//clear counter, first write hold, then tmr2....
	TMR3HLD=0x00;
	TMR2=0x00;
//timer 4 internal, measures interval
	TMR5HLD=0x00;
	TMR4=0x00;
	//T4CON=(T32);
	T4CONbits.T32=1;
	T4CONbits.TCKPS0=0; //perhaps adjust these dynamically?
	T4CONbits.TCKPS1=0;
	T4CONbits.TCS=0; //internal source
	T4CONbits.TGATE=0; //no gate accumulation
	//one second of counting time
	PR5=0xf4;//most significant word
	PR4=0x2400;//least significant word
	IFS1bits.T5IF=0;//clear interrupt flag
//start timer4
	T4CONbits.TON=1;
//start count (timer2)
	T2CONbits.TON=1;
//wait for timer4 (timer 5 interrupt)
	while(IFS1bits.T5IF==0);
//stop count (timer2)
	T2CONbits.TON=0;
	T4CONbits.TON=0;
//find measurement
//spit out
	j=TMR2;
	k=TMR3HLD;
	l=k;
	l<<=16;
	l+=j;
	l*=256;//adjust for prescaler...
	bpWlongdec(l);
	bpWstring("Hz");				
	if(l<1000){
		//do nothing
	}else if(l<1000000){
		bpWstring(" (");
		bpWlongdec(l/1000);
		bpWstring("kHz)");
	}else{
		bpWstring(" (");
		bpWlongdec(l/1000000);
		bpWstring("MHz)");
	}
	bpWBR;
	//return clock input to other pin
	RPINR3bits.T2CKR=0b11111; //assign T2 clock input to nothing
}

//\leaves AUX in high impedance
void bpAuxHiZ(void){
	if(modeConfig.altAUX==0){
		BP_AUX_DIR=1;//aux input
	}else{
		BP_CS_DIR=1;
	}
	bpWline(OUMSG_AUX_HIZ);
}

// \leaves AUX to High 
void bpAuxHigh(void){

	if(modeConfig.altAUX==0){
		BP_AUX_DIR=0;//aux output
		BP_AUX=1;//aux high
	}else{
		BP_CS_DIR=0;//aux input
		BP_CS=1;//aux high
	}
	bpWline(OUMSG_AUX_HIGH);
}

// \leaves AUX to ground
void bpAuxLow(void){
	
	if(modeConfig.altAUX==0){
		BP_AUX_DIR=0;//aux output
		BP_AUX=0;//aux low
	}else{
		BP_CS_DIR=0;//aux output
		BP_CS=0;//aux low	
	}
	bpWline(OUMSG_AUX_LOW);
}

// \leaves AUX in high impedence
void bpAuxRead(void){
	unsigned char c;
	if(modeConfig.altAUX==0){
		BP_AUX_DIR=1;//aux input
		asm( "nop" );//needs one TCY to get pin direction
		asm( "nop" );//needs one TCY to get pin direction
		c=BP_AUX;
	}else{
		BP_CS_DIR=1;
		asm( "nop" );//needs one TCY to get pin direction
		asm( "nop" );//needs one TCY to get pin direction
		c=BP_CS;
	}
	bpWstring(OUMSG_AUX_INPUT_READ);
	bpEchoState(c);
	bpWBR;

}

/*1. Set the PWM period by writing to the selected
Timer Period register (PRy).
2. Set the PWM duty cycle by writing to the OCxRS
register.
3. Write the OCxR register with the initial duty cycle.
4. Enable interrupts, if required, for the timer and
output compare modules. The output compare
interrupt is required for PWM Fault pin utilization.
5. Configure the output compare module for one of
two PWM Operation modes by writing to the
Output Compare Mode bits, OCM<2:0>
(OCxCON<2:0>).
6. Set the TMRy prescale value and enable the time
base by setting TON (TxCON<15>) = 1.*/

