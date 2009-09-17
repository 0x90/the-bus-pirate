//Bus Pirate bitbang base library
//consolidates all bitbang code into one place

// The software i2c routines were written in c from public domain pseudo code:
/// **** I2C Driver V1.1 Written by V.Himpe. Released as Public Domain **** /
// http://www.esacademy.com/faq/i2c/general/i2cpseud.htm
#include "base.h"
#include "bitbang.h" //need own functions

#define	BB_LOWSPEED_SETTLE 20 //~5KHz
#define	BB_LOWSPEED_CLOCK 100
#define	BB_LOWSPEED_HALFCLOCK BB_LOWSPEED_CLOCK/2

#define	BB_HISPEED_SETTLE 2 //~50KHz
#define	BB_HISPEED_CLOCK 10
#define	BB_HISPEED_HALFCLOCK BB_LOWSPEED_CLOCK/2

extern struct _modeConfig modeConfig;

struct _bitbang{
	unsigned char pins;
	unsigned int MOpin;
	unsigned int MIpin;
	unsigned char delaySettle;
	unsigned char delayClock;
	unsigned char delayHalfClock;
} bitbang;

void bbSetup(unsigned char pins, unsigned char speed){

	bitbang.pins=pins;

	//define pins for 2 or 3 wire modes (do we use a seperate input pin)
	if(pins==3){ //SPI-like
		bitbang.MOpin=MOSI;
		bitbang.MIpin=MISO;
	}else{ //I2C-like
		bitbang.MOpin=MOSI;
		bitbang.MIpin=MOSI;
	}
	
	
	//define delays for differnt speeds
	// I2C Bus timing in uS
	if(speed == 0){ //~~5khz
		bitbang.delaySettle = BB_LOWSPEED_SETTLE;
		bitbang.delayClock = BB_LOWSPEED_CLOCK;
		bitbang.delayHalfClock = BB_LOWSPEED_HALFCLOCK;
	}else{ //~50khz
		bitbang.delaySettle = BB_HISPEED_SETTLE;
		bitbang.delayClock = BB_HISPEED_CLOCK;
		bitbang.delayHalfClock = BB_HISPEED_HALFCLOCK;
	}
}

//
// HELPER functions
//
void bbI2Cstart(void){
//http://www.esacademy.com/faq/i2c/busevents/i2cstast.htm
	//setup both lines high first
	bbH(MOSI+CLK, bitbang.delayClock);

	//now take data low while clock is high
	bbL(MOSI, bitbang.delayClock);

	//next take clock low too
	bbL(CLK, bitbang.delayClock);	
	
	//example suggests returning SDA to high
	bbH(MOSI, bitbang.delayClock);

}


void bbI2Cstop(void){
//http://www.esacademy.com/faq/i2c/busevents/i2cstast.htm

	//setup both lines low first
	//example suggests just SDA, but some chips are flakey.
	bbL(MOSI+CLK, bitbang.delayClock);

	//take clock high
	bbH(CLK, bitbang.delayClock);

	//with clock high, bring data high too
	bbH(MOSI, bitbang.delayClock);

	//return clock low, importatnt for raw2wire smartcard
	bbL(CLK, bitbang.delayClock);
}

//
//BYTE functions
//

// ** Read with write for 3-wire protocols ** //

unsigned char bbReadWriteByte(unsigned char c){
	unsigned char i,bt,tem,di,dat=0;

	//begin with clock low...	

	if(modeConfig.lsbEN==0){bt=0x80;}else{bt=0x01;}

	tem=c;//????
	for(i=0;i<8;i++){
		bbPins((tem&bt), MOSI, bitbang.delaySettle); //set data out
		bbH(CLK,bitbang.delayClock);//set clock high
		di=bbR(MISO); //read data pin	
		bbL(CLK,bitbang.delayClock);;//set clock low

		if(modeConfig.lsbEN==0){//get MSB first
			tem=tem<<1;  //shift data output bits
			dat=dat<<1;  //shift the data input byte bits
			if(di)dat++; //if datapin in is high, set LBS
		}else{//get LSB first
			tem=tem<<1;  //shift data output bits
			dat=dat>>1;  //shift the data input byte bits
			if(di)dat+=0b10000000; //if datapin is HIGH, set MSB
		}
	}
	return dat;
}

// ** Seperate read/write for 2-wire protocols ** //

void bbWriteByte(unsigned char c){
	unsigned char i,bt,tem;

	//bbo();//prepare for output

	if(modeConfig.lsbEN==0){bt=0x80;}else{bt=0x01;}

	tem=c;//????
	for(i=0;i<8;i++){
		//if( (b & d)== 0) bbL(bitbang.MOpin,bitbang.delaySettle); else bbH(bitbang.MOpin,bitbang.delaySettle);//setup the data pin
		bbPins((tem&bt), MOSI, bitbang.delaySettle );
		bbH(CLK,bitbang.delayClock);
		bbL(CLK,bitbang.delayClock);

		if(modeConfig.lsbEN==0)tem=tem<<1; else tem=tem>>1;//next output bit
	}
}

unsigned char bbReadByte(void){
	unsigned char i,di,dat=0;

	//bbi();//prepare for input
	bbR(MOSI); //setup for input

	for(i=0;i<8;i++){
		bbH(CLK,bitbang.delayClock);//set clock high
		di=bbR(MOSI); //same as MISO on 2-wire
		bbL(CLK,bitbang.delayClock);;//set clock low
		
		if(modeConfig.lsbEN==0){//get MSB first
			dat=dat<<1;//shift the data input byte bits
			if(di)dat++;//if datapin in is high, set LBS
		}else{//get LSB first
			dat=dat>>1;//shift the data input byte bits
			if(di)dat|=0b10000000; //if datapin is HIGH, set MSB
		}

	}
	return dat;
}

//
// BIT functions
//

unsigned char bbReadBit(void){
	unsigned char c;

	bbR(bitbang.MIpin); //setup for input
	bbH(CLK,bitbang.delayClock);//set clock high
	c=bbR(bitbang.MIpin);
	bbL(CLK,bitbang.delayClock);;//set clock low
	return c;
}

void bbWriteBit(unsigned char c){

	bbPins(c,bitbang.MOpin, bitbang.delaySettle);

	bbH(CLK,bitbang.delayClock);
	bbL(CLK,bitbang.delayClock);
}

void bbClockTicks(unsigned char c){
	unsigned char i;

	for(i=0;i<c;i++){
		bbH(CLK,bitbang.delayClock);
		bbL(CLK,bitbang.delayClock);
	}
}

//
// PIN functions
//
void bbMOSI(unsigned char dir){ bbPins(dir, bitbang.MOpin, bitbang.delaySettle);}
void bbCLK(unsigned char dir){ bbPins(dir, CLK, bitbang.delaySettle);}
void bbCS(unsigned char dir){ bbPins(dir, CS, bitbang.delaySettle);}
unsigned char bbMISO (void){ return bbR(bitbang.MIpin);}

//
// BASE IO functions
//
void bbH(unsigned int pins, unsigned char delay){
	if(modeConfig.HiZ==0){
		IOLAT |= pins;//normal output high
		IODIR &=(~pins);//direction to output
	}else{
		IODIR |= pins;//open collector output high
	}
	bpDelayUS(delay);//delay
}

void bbL(unsigned int pins, unsigned char delay){
	IOLAT &=(~pins); //pins to 0
	IODIR &=(~pins);//direction to output
	bpDelayUS(delay);//delay	
}

void bbPins(unsigned char dir, unsigned int pins, unsigned char delay){
	if(dir==0){
		IOLAT &=(~pins); //pins to 0
		IODIR &=(~pins);//direction to output
	}else{
		if(modeConfig.HiZ==0){
			LATB |= pins;//normal output high
			IODIR &=(~pins);//direction to output
		}else{
			IODIR |= pins;//open collector output high
		}
	}
	bpDelayUS(delay);//delay	
}

unsigned char bbR(unsigned int pin){
	IODIR |= pin; //pin as input
	Nop();
	Nop();
	Nop();
	if(IOPOR & pin) return 1; else return 0;//clear all but pin bit and return result
}



