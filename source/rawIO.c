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

void rawspiSetup(void);
void rawspiDisable(void);
unsigned char spiW(unsigned char c);

static unsigned char bufOutByte;

void rawSPI(void){
	unsigned char inByte, rawCommand;
	
	bpWstring("BBIO1");//this should be sent from a BB mode management loop in the future

	while(1){

		while(U1STAbits.URXDA == 0);//wait for a byte
		inByte=U1RXREG; //grab it
		rawCommand=(inByte>>4);//get command bits in seperate variable
		
		switch(rawCommand){
			case 0://reset/setup/config commands
				if(inByte&0b1){
					bpWstring("SPI1");//1 - SPI setup and reply string
					//rawspiSetup();//spi reset
				    SPI1STATbits.SPIEN = 0;//disable, just in case...
					
					//use open drain control register to 
					//enable Hi-Z mode on hardware module outputs
					//inputs are already HiZ
					//SPIMOSI_ODC=1;
					//SPICLK_ODC=1; 
					//SPICS_ODC=1;
				
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
				
					/* CKE=1, CKP=0, SMP=0 */
					SPI1CON1 = 0b11100;//start with 250khz //{0b00000,0b11000,0b11100,0b11101};//30,125,250,1000khz
					SPI1CON1bits.MSTEN=1;
					SPI1CON1bits.CKP=0;//idle low 0
					SPI1CON1bits.CKE=1;//active to idle	1	
					SPI1CON1bits.SMP=0;//sample middle 0
				    SPI1CON2 = 0;
				    SPI1STAT = 0;    // clear SPI
				    SPI1STATbits.SPIEN = 1;
				}else{//0, reset exit
					SPI1STATbits.SPIEN = 0;
					RPINR20bits.SDI1R=0b11111;  //B7 MISO
					RPOR4bits.RP9R=0; 			//B9 MOSI
					RPOR4bits.RP8R=0; 			//B8 CLK
					bpWstring("BBIO1");
					//asm("RESET");
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
				if(inByte&0b1000){
					BP_VREG_ON();//power on
				}else{
					BP_VREG_OFF();//power off
				}
				
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
			default:
				UART1TX(0xff);//send 0/Error
				break;
		}//command switch
	}//while loop
}//function

void rawspiSetup(void){
    SPI1STATbits.SPIEN = 0;//disable, just in case...
	
	//use open drain control register to 
	//enable Hi-Z mode on hardware module outputs
	//inputs are already HiZ
	//SPIMOSI_ODC=1;
	//SPICLK_ODC=1; 
	//SPICS_ODC=1;

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

	/* CKE=1, CKP=0, SMP=0 */
	SPI1CON1 = 0b11100;//start with 250khz //{0b00000,0b11000,0b11100,0b11101};//30,125,250,1000khz
	SPI1CON1bits.MSTEN=1;
	SPI1CON1bits.CKP=0;//idle low 0
	SPI1CON1bits.CKE=1;//active to idle	1	
	SPI1CON1bits.SMP=0;//sample middle 0
    SPI1CON2 = 0;
    SPI1STAT = 0;    // clear SPI
    SPI1STATbits.SPIEN = 1;
}

void rawspiDisable(void){
	SPI1STATbits.SPIEN = 0;
	RPINR20bits.SDI1R=0b11111;  //B7 MISO
	RPOR4bits.RP9R=0; 			//B9 MOSI
	RPOR4bits.RP8R=0; 			//B8 CLK
	//disable all open drain control register bits
	//SPIMOSI_ODC=0;
	//SPICLK_ODC=0; 
	//SPICS_ODC=0;
}

unsigned char spiW(unsigned char c){
	SPI1BUF = c;
	while(!IFS0bits.SPI1IF);
	c=SPI1BUF;
	IFS0bits.SPI1IF = 0;
	return c;
}

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

This is really slow, 
but you would have to send/receive 3+bytes for every byte when you're parsing the ASCII. 
We can build on the bitbang mode with extra functions like a raw SPI write:

00000001 //command for raw SPI write, send one byte after this and read one byte
0x30 //send whatever value, Bus Pirate responds with a byte read from SPI

We can add commands as needed:
00000000 //reset to bitbang mode
00000001 //SPI read/write mode
*/

/*
//state machine

if(inByte&COMMAND_BIT==0){//if command bit cleared, process command
	switch(inByte){
		case 0: //reset
			break;
		case 1: //raw SPI
			break;
		case 2: //rawIO version
			break;
		case 3: //hardware/firmware version string
			break;
		default://could do other functions like
			//self test
			//pin direction set
			//?
			break;
	}
}else{//else, put values on the pins
	//POWER
	//Pullups
	//CS
	//

}
*/

