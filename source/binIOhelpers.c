#include "base.h"

void binIOperipheralset(unsigned char inByte){
	#ifndef BUSPIRATEV0A
	if(inByte&0b1000){
		BP_VREG_ON();//power on
	}else{
		BP_VREG_OFF();//power off
	}
	#endif
	
	#if defined(BUSPIRATEV0A) || defined( BUSPIRATEV2)
	if(inByte&0b100){
		BP_PULLUP_ON();//pullups on
	}else{
		BP_PULLUP_OFF();
	}
	#endif

	if(inByte&0b10){
		BP_AUX_DIR=0;//aux output
		BP_AUX=1;//aux high
	}else{
		BP_AUX_DIR=0;//aux output
		BP_AUX=0;//aux low
	}

	if(inByte&0b1)
		IOLAT|=CS; //BP_CS=1;//CS high
	else
		IOLAT&=(~CS); //BP_CS=0;

	//UART1TX(1);//send 1/OK		
}

