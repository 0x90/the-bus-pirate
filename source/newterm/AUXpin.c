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
#include "procmenu.h"

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


// ripped :)

int PWMfreq;
int PWMduty;

void updatePWM(void)
{	unsigned int PWM_period, PWM_dutycycle, PWM_div;

	//cleanup timers 
	T2CON=0;		// clear settings
	T4CON=0;
	OC5CON =0;

	if(PWMfreq==0)
	{	AUXPIN_RPOUT = 0;	 //remove output from AUX pin
		AUXmode=AUX_IO;
		return;
	}

 	if(PWMfreq<4)
	{	//use 256 //actual max is 62500hz
		PWM_div=62;//actually 62500
		T2CONbits.TCKPS1=1;
		T2CONbits.TCKPS0=1;
	}
	else if(PWMfreq<31)
	{	//use 64
		PWM_div=250;
		T2CONbits.TCKPS1=1;
		T2CONbits.TCKPS0=0;
	}
	else if(PWMfreq<245)
	{	//use 8
		PWM_div=2000;
		T2CONbits.TCKPS1=0;
		T2CONbits.TCKPS0=1;
	}
	else
	{	//use 1
		PWM_div=16000;
		T2CONbits.TCKPS1=0;
		T2CONbits.TCKPS0=0;
	}
	PWM_period=(PWM_div/PWMfreq)-1;
	PR2	= PWM_period;	

	PWM_dutycycle=(PWM_period*PWMduty)/100;
	

	//assign pin with PPS
	AUXPIN_RPOUT = OC5_IO;

	OC5R = PWM_dutycycle;
	OC5RS = PWM_dutycycle;
	OC5CON = 0x6;			
	T2CONbits.TON = 1;	

	AUXmode=AUX_PWM;

}




void bpPWM(void){
	unsigned int PWM_period, PWM_dutycycle, PWM_freq, PWM_div;
	int done;
	//unsigned long PWM_div;

	float PWM_pd;
	//cleanup timers 
	T2CON=0;		// clear settings
	T4CON=0;
	OC5CON =0;
	
	if(AUXmode==AUX_PWM){ //PWM is on, stop it
		AUXPIN_RPOUT = 0;	 //remove output from AUX pin
		bpWline(OUMSG_AUX_PWM_OFF);
		AUXmode=AUX_IO;
		return;
	}

	done=0;

	cmdstart++;
	cmdstart&=CMDLENMSK;

	consumewhitechars();
	PWM_freq=getint();
	consumewhitechars();
	PWM_pd=getint();

	if((PWM_freq>0)&&(PWM_freq<4000)) done++;
	if((PWM_pd>0)&&(PWM_pd<100)) done++;


	//calculate frequency:
	if(done!=2)
	{	cmderror=0;

		bpWline(OUMSG_AUX_PWM_NOTE);
		bpWstring(OUMSG_AUX_PWM_FREQ);
		//PWM_period=(16000000/bpUserNumberPrompt(5, 0xffff, 50000))-1;
	//	PWM_freq=bpUserNumberPrompt(4, 4000, 50);
		PWM_freq=getnumber(50, 4000, 0);
	}

//	bpWstring("result=");
//	bpWinthex(PWM_freq);

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

	if(done!=2)
	{	bpWstring(OUMSG_AUX_PWM_DUTY);
	//	PWM_pd=bpUserNumberPrompt(2, 99, 50);
		PWM_pd=getnumber(50,99,0);
	}

//	bpWstring("result=");
//	bpWinthex(PWM_pd);


	PWM_pd/=100;
	PWM_dutycycle=PWM_period * PWM_pd;
	//bpWdec(PWM_dutycycle);

	//assign pin with PPS
	AUXPIN_RPOUT = OC5_IO;

	OC5R = PWM_dutycycle;
	OC5RS = PWM_dutycycle;
	OC5CON = 0x6;			
	PR2	= PWM_period;	
	T2CONbits.TON = 1;	

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
	T4CON=0;	//make sure the counters are off
	T2CON=0;	
//timer 2 external
	AUXPIN_DIR=1;//aux input
	RPINR3bits.T2CKR=AUXPIN_RPIN; //assign T2 clock input to aux input

	T2CON=0b111010; //(TCKPS1|TCKPS0|T32|TCS);
	//T2CONbits.T32=1;//32 bit mode
	//T2CONbits.TCKPS1=1; //0=1,01=8,10=64,11=256....
	//T2CONbits.TCKPS0=1;
	//T2CONbits.TCS=1; //external clock source
	PR3=0xffff;//most significant word
	PR2=0xffff;//least significant word
	//clear counter, first write hold, then tmr2....
	TMR3HLD=0x00;
	TMR2=0x00;
//timer 4 internal, measures interval
	TMR5HLD=0x00;
	TMR4=0x00;
	T4CON=0b1000; //.T32=1, bit 3
	//T4CONbits.T32=1;
	//T4CONbits.TCKPS0=0; //perhaps adjust these dynamically?
	//T4CONbits.TCKPS1=0;
	//T4CONbits.TCS=0; //internal source
	//T4CONbits.TGATE=0; //no gate accumulation
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
	T4CON=0;	//make sure the counters are off
	T2CON=0;
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
unsigned int bpAuxRead(void){
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
	return c;
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

