#include "base.h"
#include "selftest.h"
//#include "busPirateCore.h"

#if defined(BUSPIRATEV25) || defined (BUSPIRATEV3)
void bpTest(unsigned char p, unsigned char d);
void bpBusPinsTest(unsigned char d);
void bpADCPinTest(unsigned char a, unsigned int val);
void bpPOSTWline(char *s);
void bpPOSTWstring(char *s);

static unsigned char display,errors;

//silent POST for manufacturing
//when complete, 
//lights mode led on success
//echos all characters + number of errors
void bpPOST(void){
	unsigned char i;

	//setup POST trigger pin (PGC)
	BP_POST_DIR=1;Nop(); Nop(); //input
	BP_POST=0;					//ground, but not until it's an input!
	CNPU1|=0b10000; 			//enable internal pullup
	for(i=0; i<20; i++){ 		//verifty not high 20 times to avoid false entry
		if(BP_POST==1){CNPU1&=(~0b10000); return;}
	}
	selfTest(0);				//silent self-test
	BP_VREG_ON(); //VREG on for testing, LED
	if(errors==0) BP_LEDMODE=1;	//light MODE LED if success
	while(1){
		//echo incoming bytes + errors
		//tests FTDI chip, UART, retrieves results of test
		if(UART1RXRdy()) UART1TX(UART1RX()+errors);
	}
}

//self test, showProgress=1 displays the test results in the terminal, set to 0 for silent mode
//errors are counted in the global errors variable
void selfTest(unsigned char showProgress){
//toggle display of test results with show Progress variable
	errors=0;
	display=showProgress;

//instructions (skip pause if no display output)
	if(display){
		bpPOSTWline("Disconnect any devices");
		bpPOSTWline("Connect (Vpu to +5V) and (ADC to +3.3V)");
		bpPOSTWline("Press a key to start");
		while(!UART1RXRdy());
		UART1RX();
	}

	bpPOSTWline("Control");
	BP_AUX=1;
	BP_AUX_DIR=0; 
	bpPOSTWstring("AUX");
	bpTest(BP_AUX,1);
	BP_AUX=0;
	BP_AUX_DIR=1; 
				
	BP_LEDMODE=1;
	BP_LEDMODE_DIR=0;	
	bpPOSTWstring("MODE LED");
	bpTest(BP_LEDMODE,1);
	BP_LEDMODE=0;
	BP_LEDMODE_DIR=1;
	
	BP_PULLUP_ON();
	bpPOSTWstring("PULLUP H");
	bpTest(BP_PULLUP,1);
	BP_PULLUP_OFF();
	bpPOSTWstring("PULLUP L");
	bpTest(BP_PULLUP,0);
	
	BP_VREG_ON();
	bpDelayMS(2);//in silent mode there's not enought delay for the power supplied to come on
	bpPOSTWstring("VREG");
	bpTest(BP_VREGEN,1);

	//ADC check
	bpPOSTWline("Analog pin and pwr supply");
	AD1CON1bits.ADON = 1; // turn ADC ON

	//0x030F is 5volts
	bpPOSTWstring("5V");
	bpADCPinTest(9,0x250);

	//Vpullup is connected to 5volts
	bpPOSTWstring("VPU");
	bpADCPinTest(11,0x250);

	//0x0208 is 3.3volts
	bpPOSTWstring("3.3V");
	bpADCPinTest(10,0x150);

	//ADC is connected to 3.3volts
	bpPOSTWstring("ADC");
	bpADCPinTest(12,0x150);

	AD1CON1bits.ADON = 0; // turn ADC OFF 

//*************
//
//  Test bus pins three ways, also tests on-board pullup resistors:
//	1. normal/high, 2. open collector ground, 3. open collector high.
//
//***************

//pullup off, pins=output & high, read input, high?
	bpPOSTWline("Bus normal, high");
	TRISB&= ~(0b1111000000);//output
	LATB|=0b1111000000; //high	
	bpDelayMS(100);
	bpBusPinsTest(1);

//pullup on, pins=output & low, read input, low?
	bpPOSTWline("Bus Hi-Z, low");
	LATB&= ~(0b1111000000); //low
	BP_PULLUP_ON();
	bpDelayMS(100);
	bpBusPinsTest(0);

//pullup on, pins=input & low, read input, high?
	bpPOSTWline("Bus Hi-Z, high");
	TRISB|= 0b1111000000;//output
	bpDelayMS(100);
	bpBusPinsTest(1);

	bpInit();//clean up

}

void bpADCPinTest(unsigned char a, unsigned int val){
	unsigned int b;
	bpPOSTWstring("(");
	b=bpADC(a);
	if(display) bpWvolts(b); //only if display active
	bpPOSTWstring(")");
	bpTest(b>val,1);
}

//test that all bus pins are direction d
void bpBusPinsTest(unsigned char d){
	bpPOSTWstring("MOSI");
	bpTest(BP_MOSI,d);
	bpPOSTWstring("CLK");
	bpTest(BP_CLK,d);
	bpPOSTWstring("MISO");
	bpTest(BP_MISO,d);
	bpPOSTWstring("CS");
	bpTest(BP_CS,d);
}

//tests pin p for direction d
void bpTest(unsigned char p, unsigned char d){
	if(p==d){
		bpPOSTWline(" OK"); 
	}else{
		bpPOSTWline(" FAIL");
		errors++;
	}
}

void bpPOSTWline(char *s){
	if(display) bpWline(s);
}

void bpPOSTWstring(char *s){
	if(display) bpWstring(s);
}

#endif
