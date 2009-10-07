/*
//0 resets
//send 1 for RAW SPI mode

Half-duplex SPI mode like 4bit LCD interface:
rawSPI mode:
00000000//reset
00000001//SPI mode/rawSPI version string (SPI1)
0001xxxx//low 4 bits of byte + send/read byte
0010xxxx//high 4 bits of byte
0011000x//set CS pin high (1) or low(0)
0100wxyz//configure peripherals w=power, x=pullups, y=AUX, z=CS
0101xxxx//bulk SPI, send 1-16 bytes (0==1byte!, 15==16bytes), BP replies OK, then sends read byte for each byte
0110wxyz //w=HiZ(0)/3.3v(1), x=CKP idle (low=0), y=CKE clock edge (active to idle=1), z=SMP sample (middle=0)
0111xxxx // SPI speed, 0000=30khz, 0001=125khz, 0010=250khz, 0011=1000khz

Tips:
A byte is sent/read on SPI each time the low bits are sent (0001xxxx). 
If the upper 4 bits are the same as the last byte, just send the lower 
bits again for a two-fold increase in speed.
*/

#include "base.h"

//direction registers
#define SPIMOSI_TRIS 	BP_MOSI_DIR	
#define SPICLK_TRIS 	BP_CLK_DIR	
#define SPIMISO_TRIS 	BP_MISO_DIR	
#define SPICS_TRIS 		BP_CS_DIR	

//pin control registers
#define SPIMOSI 		BP_MOSI
#define SPICLK 			BP_CLK	
#define SPIMISO 		BP_MISO	
#define SPICS 			BP_CS	

//open drain control registers for OUTPUT pins
#define SPIMOSI_ODC 		BP_MISO_ODC	
#define SPICLK_ODC 			BP_CLK_ODC	
#define SPICS_ODC 			BP_CS_ODC	

void rawBBpindirectionset(unsigned char inByte);
unsigned char rawBBpinset(unsigned char inByte);
void rawBBversion(void);
void rawspiSetup(void);
void rawspiDisable(void);
unsigned char spiW(unsigned char c);

static unsigned char bufOutByte;
static unsigned char rawSPIspeed[]={0b00000,0b11000,0b11100,0b11101};//30,125,250,1000khz; datasheet pg 142

void rawSPI(void){
	static unsigned char inByte, rawCommand, i, speed;
	
	//spi setup
    SPI1STATbits.SPIEN = 0;//disable, just in case...

	//startup in normal pin mode?	
	SPIMOSI_ODC=0;
	SPICLK_ODC=0; 
	SPICS_ODC=0;

	// Inputs 
	RPINR20bits.SDI1R=7; 		//B7 MISO
	// Outputs
	RPOR4bits.RP9R=SDO1_IO; 	//B9 MOSI
	RPOR4bits.RP8R=SCK1OUT_IO; 	//B8 CLK

	SPICS=1;				//B6 cs high
	SPICS_TRIS=0;			//B6 cs output

	//pps configures pins and this doesn't really matter....
	SPICLK_TRIS=0; 			//B8 sck output
	SPIMISO_TRIS=1; 		//B7 SDI input
	SPIMOSI_TRIS=0; 		//B9 SDO output

	//useful default values
	/* CKE=1, CKP=0, SMP=0 */
	SPI1CON1 = rawSPIspeed[2];//start with 250khz (30,125,250,1000khz)
	SPI1CON1bits.MSTEN=1;
	SPI1CON1bits.CKP=0;//idle low 0
	SPI1CON1bits.CKE=1;//active to idle	1	
	SPI1CON1bits.SMP=0;//sample middle 0
    SPI1CON2 = 0;
    SPI1STAT = 0;    // clear SPI
    SPI1STATbits.SPIEN = 1;
	bpWstring("SPI1");//1 - SPI setup and reply string

	while(1){

		while(U1STAbits.URXDA == 0);//wait for a byte
		inByte=U1RXREG; //grab it
		rawCommand=(inByte>>4);//get command bits in seperate variable
		
		switch(rawCommand){
			case 0://reset/setup/config commands
				if(inByte&0b1){
					bpWstring("SPI1");//1 - SPI setup and reply string
				}else{//0, reset exit
					SPI1STATbits.SPIEN = 0;
					RPINR20bits.SDI1R=0b11111;  //B7 MISO
					RPOR4bits.RP9R=0; 			//B9 MOSI
					RPOR4bits.RP8R=0; 			//B8 CLK
					return; //exit
				}		
				break;
			case 0b0001://add lower four bits to buffered byte, TX/RX
				inByte&=(~0b11110000); //clear command portion
				bufOutByte|=inByte; //set lower four bits
				//UART1TX(spiW(bufOutByte));//send buffered byte //return SPI read
				SPI1BUF = bufOutByte;
				while(!IFS0bits.SPI1IF);
				UART1TX(SPI1BUF);
				IFS0bits.SPI1IF = 0;
				break;
			case 0b0010://add upper four bits to buffered byte
				bufOutByte&=(~0b11110000);//clear current upper bits
				bufOutByte|=(inByte<<4); //set upper four bits;
				UART1TX(1);//send 1/OK
				break;
			case 0b0011: //set CS according to last bit of inByte
				if(inByte&0b1) //bit set, CS high
					SPICS=0; //cs enable/low
				else
					SPICS=1; //cs disable/high
		
				UART1TX(1);//send 1/OK
				break;
			case 0b0100:
				//configure peripherals w=power, x=pullups, y=AUX, z=CS
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
					SPICS=0;//CS high
				else
					SPICS=1;
		
				UART1TX(1);//send 1/OK		
				break;
			case 0b0110:
				//wxyz //w=HiZ(0)/3.3v(1), x=CKP idle (low=0), y=CKE clock edge (active to idle=1), z=SMP sample (middle=0)
				SPI1STATbits.SPIEN = 0;//disable SPI
				//use open drain control register to 
				//enable Hi-Z mode on hardware module outputs
				//inputs are already HiZ
				if((inByte&0b1000)==0){//hiz bit clear, hiz pins
					SPIMOSI_ODC=1;
					SPICLK_ODC=1; 
					SPICS_ODC=1;
				}else{//regular outputs
					SPIMOSI_ODC=0;
					SPICLK_ODC=0; 
					SPICS_ODC=0;
				}

				SPI1CON1 = rawSPIspeed[speed];//set speed
				SPI1CON1bits.MSTEN=1;
				if(inByte&0b100) SPI1CON1bits.CKP=1;//set idle
				if(inByte&0b10) SPI1CON1bits.CKE=1;//set edge	
				if(inByte&0b1) SPI1CON1bits.SMP=1;//set sample time
			    SPI1CON2 = 0;
			    SPI1STAT = 0;    // clear SPI
			    SPI1STATbits.SPIEN = 1;
				UART1TX(1);//send 1/OK	
				break;
			case 0b0111:
				//xxxx // SPI speed, 0000=30khz, 0001=125khz, 0010=250khz, 0011=1000khz
				inByte&=(~0b11111100);//clear command portion
				speed=inByte;

				SPI1STATbits.SPIEN = 0;//disable SPI
				SPI1CON1&=(~0b11111);//clear speed bits
				SPI1CON1|=rawSPIspeed[speed];//set speed
			    SPI1CON2 = 0;
			    SPI1STAT = 0;    // clear SPI
				SPI1STATbits.SPIEN = 1;//SPI on
				UART1TX(1);//send 1/OK	
				break;
			case 0b0101://get x+1 bytes
				inByte&=(~0b11110000); //clear command portion
				inByte++; //increment by 1, 0=1byte
				UART1TX(1);//send 1/OK		

				for(i=0;i<inByte;i++){
					while(U1STAbits.URXDA == 0);//wait for a byte
					SPI1BUF = U1RXREG;//grab it
					while(!IFS0bits.SPI1IF);
					UART1TX(SPI1BUF);
					IFS0bits.SPI1IF = 0;
				}

				break;
			default:
				UART1TX(0xff);//send 0/Error
				break;
		}//command switch
	}//while loop
}//function


/*
Bitbang is like a player piano or bitmap. The 1 and 0 represent the pins. 
So for the four Bus Pirate pins we use the the bits as follows:
COMMAND|POWER|PULLUP|AUX|CS|MISO|CLK|MOSI.

The Bus pirate also responds to each write with a read byte showing the current state of the pins.

The bits control the state of each of those pins when COMMAND=1. 
When COMMAND=0 then up to 127 command codes can be entered on the lower bits.
0x00 resets the Bus Pirate to bitbang mode.

10000000 (127 in decimal) turns off all the bus pirate pins.
11000000 turns on the power supplies.
10001000 raises the CS pin.

To clock in a bit in and read the result, you would do something like this:

10001000 //CS pin high (off)
10000000 //lower CS pin (active)
10000001 //MOSI high, clock in high bit
10000011 //raise the clock pin
10000011//(optional, can use byte from last op, depending on speed) send the same byte and save the return byte, bit 3 shows the state of the MISO pin
10000001//lower the clock pin
etc, etc,

Data:
1xxxxxxx //COMMAND|POWER|PULLUP|AUX|MOSI|CLK|MISO|CS

Commands:
00000000 //Reset
00000001 //enter rawSPI mode
010xxxxx //set input(1)/output(0) pin state
*/


void rawBB(void){
	static unsigned char inByte;
	
	rawBBpindirectionset(0);//pins to input on start
	rawBBpinset(0);//startup everything off, pins at ground
	
	rawBBversion();//send mode name and version

	while(1){

		while(U1STAbits.URXDA == 0);//wait for a byte
		inByte=U1RXREG; //grab it

		if((inByte&0b10000000)==0){//if command bit cleared, process command
			if(inByte==0){//reset, send BB version
				rawBBversion();
			}else if(inByte==1){//goto SPI mode
				rawSPI();//go into rawSPI loop
				rawBBpindirectionset(0);//pins to input on start
				rawBBpinset(0);//startup everything off, pins at ground
				rawBBversion(); //say name on return
			}else if((inByte>>5)&0b010){//set pin direction
				rawBBpindirectionset(inByte);
				UART1TX(1);
			}else{//unknown command, error
				UART1TX(0);
			}
		}else{//data for pins
			UART1TX(rawBBpinset(inByte));
		}//if
	}//while
}//function

void rawBBversion(void){bpWstring("BBIO1");}

void rawBBpindirectionset(unsigned char inByte){
	unsigned char i;
	//setup pin TRIS
	//using this method is long and nasty, 
	//but it makes it work for all hardware versions 
	//without special adjustments
	i=0;
	if(inByte&0b10000)i=1;
	BP_AUX_DIR=i; 

	i=0;
	if(inByte&0b1000)i=1;
	BP_MOSI_DIR=i; 

	i=0;
	if(inByte&0b100)i=1;
	BP_CLK_DIR=i;

	i=0;
	if(inByte&0b10)i=1;
	BP_MISO_DIR=i; 

	i=0;
	if(inByte&0b1)i=1;
	BP_CS_DIR=i;
}

unsigned char rawBBpinset(unsigned char inByte){
	unsigned char i;

	#ifndef BUSPIRATEV0A
	if(inByte&0b1000000){
		BP_VREG_ON();//power on
	}else{
		BP_VREG_OFF();//power off
	}
	#endif
	
	#if defined(BUSPIRATEV0A) || defined( BUSPIRATEV2)
	if(inByte&0b100000){
		BP_PULLUP_ON();//pullups on
	}else{
		BP_PULLUP_OFF();
	}
	#endif

	//set pin LAT
	//using this method is long and nasty, 
	//but it makes it work for all hardware versions 
	//without special adjustments
	i=0;
	if(inByte&0b10000)i=1;
	BP_AUX=i; 

	i=0;
	if(inByte&0b1000)i=1;
	BP_MOSI=i; 

	i=0;
	if(inByte&0b100)i=1;
	BP_CLK=i;

	i=0;
	if(inByte&0b10)i=1;
	BP_MISO=i; 

	i=0;
	if(inByte&0b1)i=1;
	BP_CS=i;

	//delay for a brief period
	bpDelayUS(5);

	//return PORT read
	inByte&=(~0b00011111);
	if(BP_AUX!=0)inByte|=0b10000;  
	if(BP_MOSI!=0)inByte|=0b1000; 
	if(BP_CLK!=0)inByte|=0b100;  	
	if(BP_MISO!=0)inByte|=0b10;  
	if(BP_CS!=0)inByte|=0b1;  

	return inByte;//return the read
}
