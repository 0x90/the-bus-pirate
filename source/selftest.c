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
#include "selftest.h"
#include "busPirateCore.h"

#ifndef BUSPIRATEV1A
void bpTest(unsigned char p, unsigned char d);
void bpBusPinsTest(unsigned char d);
void bpADCPinTest(unsigned char a, unsigned int lval, unsigned int hval);
//void bpPOSTWline(char *s);
//void bpPOSTWstring(char *s);

static unsigned char errors;
extern struct _bpConfig bpConfig;


//self test, showProgress=1 displays the test results in the terminal, set to 0 for silent mode
//errors are counted in the global errors variable
//returns number of errors
unsigned char selfTest(unsigned char showProgress, unsigned char jumperTest){
//toggle display of test results with show Progress variable
	errors=0;
	if(!showProgress) bpConfig.quiet=1;
	
//instructions (skip pause if no display output)
	if(showProgress && jumperTest){
		//bpPOSTWline("Disconnect any devices");
		//bpPOSTWline("Connect (Vpu to +5V) and (ADC to +3.3V)");
		BPMSG1163;
		BPMSG1251; // //bpPOSTWline("Press a key to start");
		while(!UART1RXRdy()); //wait for key
		UART1RX();//discard byte
	}

	//bpPOSTWline("Ctrl");
	BPMSG1164;
	BP_AUX=1;
	BP_AUX_DIR=0; 
	//bpPOSTWstring("AUX");
	BPMSG1165;
	bpTest(BP_AUX,1);
	BP_AUX=0;
	BP_AUX_DIR=1; 
				
	BP_LEDMODE=1;
	BP_LEDMODE_DIR=0;	
	//bpPOSTWstring("MODE LED");
	BPMSG1166;
	bpTest(BP_LEDMODE,1);
	BP_LEDMODE=0;
	
	BP_PULLUP_ON();
	//bpPOSTWstring("PULLUP H");
	BPMSG1167;
	bpTest(BP_PULLUP,1);
	BP_PULLUP_OFF();
	//bpPOSTWstring("PULLUP L");
	BPMSG1168;
	bpTest(BP_PULLUP,0);
	
	BP_VREG_ON();
	bpDelayMS(2);//in silent mode there's not enought delay for the power supplied to come on
	//bpPOSTWstring("VREG");
	BPMSG1169;
	bpTest(BP_VREGEN,1);

	//ADC check
	//bpPOSTWline("ADC and supply");
	BPMSG1170;
	ADCON(); // turn ADC ON

	//0x030F is 5volts
	//bpPOSTWstring("5V");
	BPMSG1171;
	bpADCPinTest(BP_ADC_5V0,V5L, V5H);
	
	if(jumperTest){
		//Vpullup is connected to 5volts
		//bpPOSTWstring("VPU");
		BPMSG1172;
		bpADCPinTest(BP_ADC_VPU,V5L, V5H);
	}

	//0x0208 is 3.3volts
	//bpPOSTWstring("3.3V");
	BPMSG1173;
	bpADCPinTest(BP_ADC_3V3,V33L, V33H);

	if(jumperTest){
		//ADC is connected to 3.3volts
		//bpPOSTWstring("ADC");
		BPMSG1174;
		bpADCPinTest(BP_ADC_PROBE,V33L, V33H);
	}

	ADCOFF(); // turn ADC OFF 

//*************
//
//  Test bus pins three ways, also tests on-board pullup resistors:
//	1. normal/high, 2. open collector ground, 3. open collector high.
//
//***************

	//pullup off, pins=output & high, read input, high?
	//bpPOSTWline("Bus high");
	BPMSG1175;
	TRISB&= ~(0b1111000000);//output
	LATB|=0b1111000000; //high	
	bpDelayMS(100);
	bpBusPinsTest(1);

	//pullup on, pins=output & low, read input, low?
	//bpPOSTWline("Bus Hi-Z 0");
	BPMSG1176;
	LATB&= ~(0b1111000000); //low
	if(jumperTest){
		BP_PULLUP_ON();
	}
	bpDelayMS(100);
	bpBusPinsTest(0);

	if(jumperTest){
	//pullup on, pins=input & low, read input, high?
		//bpPOSTWline("Bus Hi-Z 1");
		BPMSG1177;
		TRISB|= 0b1111000000;//output
		bpDelayMS(100);
		bpBusPinsTest(1);
	}

//instructions (skip pause if no display output)
	if(showProgress && jumperTest){
		BP_VREG_ON();
		BP_LEDMODE=1;
		//bpPOSTWline("MODE and VREG LEDs should be on! Any key exits.");
		BPMSG1178;
		BPMSG1250;
		while(!UART1RXRdy());
		UART1RX();
		BP_LEDMODE=0;
		BP_LEDMODE_DIR=1;
		BP_VREG_OFF();
	}

	bpInit();//clean up

	BPMSG1179;
	bpWdec(errors);
	BPMSG1180;
	bpConfig.quiet=0;


	return errors;

}

void bpADCPinTest(unsigned char a, unsigned int lval, unsigned int hval){
	unsigned int b;
	UART1TX('(');
	b=bpADC(a);
	bpWvolts(b);
	UART1TX(')');
	bpTest(((b>lval)&&(b<hval)),1);
}

//test that all bus pins are direction d
void bpBusPinsTest(unsigned char d){
	//bpPOSTWstring("MOSI");
	BPMSG1181;
	bpTest(BP_MOSI,d);
	//bpPOSTWstring("CLK");
	BPMSG1182;
	bpTest(BP_CLK,d);
	//bpPOSTWstring("MISO");
	BPMSG1183;
	bpTest(BP_MISO,d);
	//bpPOSTWstring("CS");
	BPMSG1184;
	bpTest(BP_CS,d);
}

//tests pin p for direction d
void bpTest(unsigned char p, unsigned char d){
	if(p==d){
		//bpPOSTWline(" OK");
		BPMSG1185;
	}else{
		//bpPOSTWline(" FAIL");
		BPMSG1186;
		errors++;
	}
}

#endif
