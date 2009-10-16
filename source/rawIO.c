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

/* Binary access modes for Bus Pirate scripting 
	This code is very ugly
	We plan to develop the protocols, 
	and then look at the needs after working with it.

*/

#include "base.h"
#include "bitbang.h"
#include "selftest.h"
extern struct _modeConfig modeConfig;

/*
rawSPI mode:
    * 00000000 – Enter raw bitbang mode, reset to raw bitbang mode
    * 00000001 – SPI mode/rawSPI version string (SPI1)
    * 00000010 – CS low (0)
    * 00000011 – CS high (1)
    * 0001xxxx – Bulk SPI transfer, send 1-16 bytes (0=1byte!)
    * 0010xxxx – Low 4 bits of byte + single byte write/read
    * 0011xxxx – High 4 bits of byte
    * 0100wxyz – Configure peripherals, w=power, x=pullups, y=AUX, z=CS
    * 01010000 – Read peripherals
    * 01100xxx – Set SPI speed, 30, 125, 250khz; 1, 2, 2.6, 4, 8MHz
    * 01110000 – Read SPI speed
    * 1000wxyz – SPI config, w=output type, x=idle, y=clock edge, z=sample
    * 10010000 – Read SPI config
Tips:
A byte is sent/read on SPI each time the low bits are sent (0001xxxx). 
If the upper 4 bits are the same as the last byte, just send the lower 
bits again for a two-fold increase in speed.
*/
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

unsigned char rawBBpindirectionset(unsigned char inByte);
void rawBBperipheralset(unsigned char inByte);
unsigned char rawBBpinset(unsigned char inByte);
void rawBBversion(void);
void rawSPI(void);
void rawI2C(void);
void rawUART(void);


static unsigned char bufOutByte;
static unsigned char rawSPIspeed[]={0b00000,0b11000,0b11100,0b11101,0b00011,0b01000,0b10000,0b11000};//00=30,01=125,10=250,11=1000khz, 100=2mhz,101=2.667mhz,  110=4mhz, 111=8mhz; datasheet pg 142

void rawSPI(void){
	static unsigned char inByte, rawCommand, i, speed, rdper, rdspeed, rdSPIconf;
	
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
	SPI1CON1 = rawSPIspeed[0];//start with 250khz (30,125,250,1000khz)
	SPI1CON1bits.MSTEN=1;
	SPI1CON1bits.CKP=0;//idle low 0
	SPI1CON1bits.CKE=1;//active to idle	1	
	SPI1CON1bits.SMP=0;//sample middle 0
    SPI1CON2 = 0;
    SPI1STAT = 0;    // clear SPI
    SPI1STATbits.SPIEN = 1;
	bpWstring("SPI1");//1 - SPI setup and reply string

	rdper=0;//peripheral startup
	speed=0; //?
	rdSPIconf=0b0010; //hiz, 010

	while(1){

		while(U1STAbits.URXDA == 0);//wait for a byte
		inByte=U1RXREG; //grab it
		rawCommand=(inByte>>4);//get command bits in seperate variable
		
		switch(rawCommand){
			case 0://reset/setup/config commands
				switch(inByte){
					case 0://0, reset exit
						SPI1STATbits.SPIEN = 0;
						RPINR20bits.SDI1R=0b11111;  //B7 MISO
						RPOR4bits.RP9R=0; 			//B9 MOSI
						RPOR4bits.RP8R=0; 			//B8 CLK
						return; //exit
						break;
					case 1://1 - SPI setup and reply string
						bpWstring("SPI1");
						break;
					case 2:
						SPICS=0; //cs enable/low
						rdper&=(~0b1);
						UART1TX(1);
						break;
					case 3:
						SPICS=1; //cs disable/high
						rdper|=1;
						UART1TX(1);
						break;
					default:
						UART1TX(0);
						break;
				}	
				break;
			case 0b0001://get x+1 bytes
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
			case 0b0010://add lower four bits to buffered byte, TX/RX
				inByte&=(~0b11110000); //clear command portion
				bufOutByte|=inByte; //set lower four bits
				SPI1BUF = bufOutByte;
				while(!IFS0bits.SPI1IF);
				UART1TX(SPI1BUF);
				IFS0bits.SPI1IF = 0;
				break;
			case 0b0011://add upper four bits to buffered byte
				bufOutByte&=(~0b11110000);//clear current upper bits
				bufOutByte|=(inByte<<4); //set upper four bits;
				UART1TX(1);//send 1/OK
				break;
			case 0b0100: //configure peripherals w=power, x=pullups, y=AUX, z=CS
				//rawBBperipheralset(inByte);
				rdper=inByte;
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
					SPICS=1;//CS high
				else
					SPICS=0;
		
				UART1TX(1);//send 1/OK		
				break;
			case 0b0101: //read peripherals
				rdper|=0b01010000;
				UART1TX(rdper);
				break;
			case 0b0110://set speed 
				inByte&=(~0b11111000);//clear command portion
				speed=inByte;

				SPI1STATbits.SPIEN = 0;//disable SPI
				SPI1CON1&=(~0b11111);//clear speed bits
				SPI1CON1|=rawSPIspeed[speed];//set speed
			    SPI1CON2 = 0;
			    SPI1STAT = 0;    // clear SPI
				SPI1STATbits.SPIEN = 1;//SPI on
				UART1TX(1);//send 1/OK	
				break;
			case 0b0111: //read speed
				rdspeed=speed;
				rdspeed|=0b01110000;
				UART1TX(rdspeed);
				break;
			case 0b1000: //set SPI config
				rdSPIconf=inByte;
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
			case 0b1001://read SPI config
				rdSPIconf|=0b10010000;
				UART1TX(rdSPIconf);
				break;
			default:
				UART1TX(0x00);//send 0/Error
				break;
		}//command switch
	}//while loop
}//function

/*
rawI2C mode:
# 00000000//reset to BBIO
# 00000001 – mode version string (SPI1)
# 00000010 – I2C start bit
# 00000011 – I2C stop bit
# 00000100 - I2C read byte
# 00000110 - ACK bit
# 00000111 - NACK bit
# 0001xxxx – Bulk transfer, send 1-16 bytes (0=1byte!)
# 0100000x - Set I2C speed, 1=high (50kHz) 0=low (5kHz)
# 0101000x - Read speed, (planned)
# 0110wxyz – Configure peripherals w=power, x=pullups, y=AUX, z=CS
# 0111wxyz – read peripherals (planned, not implemented)
*/
#define SCL 		BP_CLK
#define SCL_TRIS 	BP_CLK_DIR     //-- The SCL Direction Register Bit
#define SDA 		BP_MOSI        //-- The SDA output pin
#define SDA_TRIS 	BP_MOSI_DIR    //-- The SDA Direction Register Bit

void rawI2C(void){
	static unsigned char inByte, rawCommand, i;
	
	//I2C setup
	SDA_TRIS=1;
	SCL_TRIS=1;
	SCL=0;			//B8 scl 
	SDA=0;			//B9 sda
	modeConfig.HiZ=1;//yes, always hiz (bbio uses this setting, should be changed to a setup variable because stringing the modeconfig struct everyhwere is getting ugly!)
	modeConfig.lsbEN=0;//just in case!
	bbSetup(2, 1);//configure the bitbang library for 2-wire, set the speed to high speed (50khz)
	bpWstring("I2C1");//1 - SPI setup and reply string

	while(1){

		while(U1STAbits.URXDA == 0);//wait for a byte
		inByte=U1RXREG; //grab it
		rawCommand=(inByte>>4);//get command bits in seperate variable
		
		switch(rawCommand){
			case 0://reset/setup/config commands
				switch(inByte){
					case 0://0, reset exit
						//cleanup!!!!!!!!!!
						return; //exit
						break;
					case 1://1 - id reply string
						bpWstring("I2C1");
						break;
					case 2://I2C start bit
						bbI2Cstart();
						UART1TX(1);
						break;
					case 3://I2C stop bit
						bbI2Cstop();
						UART1TX(1);
						break;
					case 4://I2C read byte
						UART1TX(bbReadByte());
						break;
					case 6://I2C send ACK
						bbI2Cack();
						UART1TX(1);
						break;
					case 7://I2C send NACK
						bbI2Cnack();
						UART1TX(1);
						break;
					default:
						UART1TX(0);
						break;
				}	
				break;

			case 0b0001://get x+1 bytes
				inByte&=(~0b11110000); //clear command portion
				inByte++; //increment by 1, 0=1byte
				UART1TX(1);//send 1/OK		

				for(i=0;i<inByte;i++){
					while(U1STAbits.URXDA == 0);//wait for a byte
					bbWriteByte(U1RXREG); //send byte
					UART1TX(bbReadBit());//return ACK0 or NACK1
				}

				break;

			case 0b0100://set speed 
				inByte&=(~0b11111110);//clear command portion
				bbSetup(2, inByte);//set I2C speed
				UART1TX(1);
				break;

			case 0b0110: //configure peripherals w=power, x=pullups, y=AUX, z=CS
				//rawBBperipheralset(inByte);
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
					SPICS=1;//CS high
				else
					SPICS=0;
		
				UART1TX(1);//send 1/OK		
				break;

			default:
				UART1TX(0x00);//send 0/Error
				break;
		}//command switch
	}//while loop

}

/*
Very simple mode
Settings, and then enter a never ending UART bridge.
options:
Baud
A) standard settings
B) send 2 bytes for custom BRG

databits and parity (2bits)
1. 8, NONE *default \x0D\x0A 2. 8, EVEN \x0D\x0A 3. 8, ODD \x0D\x0A 4. 9, NONE
Stop bits:\x0D\x0A 1. 1 *default\x0D\x0A 2. 2 \x0D\x0A
Receive polarity:\x0D\x0A 1. Idle 1 *default\x0D\x0A 2. Idle 0\x0D\x0A
output type (hiz or regular
peripheral settings

# 00000000//reset to BBIO
# 00000001 – mode version string (ART1)
# 00000010 - mode/version string (ART1)
# 00000011 - UART speed manual config, 2 bytes (BRGH, BRGL)
# 00000100 - live UART input begin
# 00000110 - live UART input end
# 00001111 - bridge mode (reset to exit)
# 0001xxxx – Bulk transfer, send 1-16 bytes (0=1byte!)
# 0100xxxx - Set speed,0000=300,0001=1200,10=2400,4800,9600,19200,33250, 38400,57600,1010=115200,
# 0101xxxx - Read speed, 
# 0110wxyz – Set peripheral w=power, x=pullups, y=AUX, z=CS
# 0111wxyz – read peripherals 
# 110wxxyz – config, w=output type, xx=databits and parity, y=stop bits, z=rx polarity (default :00000)
# 110wxxyz – read config
*/
void rawUART(void){}


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
00000000 //Reset to raw BB mode, get raw BB version string
00000001 //enter rawSPI mode
00000010 //enter raw I2C mode
00000011 //enter raw UART mode
00001101
00001110
00001111 //reset, return to user terminal
00010000 //short self test
00010001 //full self test with jumpers
010xxxxx //set input(1)/output(0) pin state (returns pin read)
*/


void rawBB(void){
	static unsigned char inByte;
	
	BP_LEDMODE=1;//light MODE LED
	rawBBpindirectionset(0xff);//pins to input on start
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
				rawBBpindirectionset(0xff);//pins to input on start
				rawBBpinset(0);//startup everything off, pins at ground
				rawBBversion(); //say name on return
			}else if(inByte==2){//goto I2C mode
				rawI2C();
				rawBBpindirectionset(0xff);//pins to input on start
				rawBBpinset(0);//startup everything off, pins at ground
				rawBBversion(); //say name on return
			}else if(inByte==0b1111){//return to terminal
				BP_LEDMODE=0;//light MODE LED
				asm("RESET");
			//self test is only for v2go and v3
			#if defined(BUSPIRATEV25) || defined (BUSPIRATEV3)
				}else if(inByte == 0b10000){//short self test
					rawSelfTest(0);
				}else if(inByte == 0b10001){//full self test with jumpers
					rawSelfTest(1);
			#endif
			}else if((inByte>>5)&0b010){//set pin direction, return read
				UART1TX(rawBBpindirectionset(inByte));
			}else{//unknown command, error
				UART1TX(0);
			}
		}else{//data for pins
			UART1TX(rawBBpinset(inByte));
		}//if
	}//while
}//function

void rawBBversion(void){bpWstring("BBIO1");}

unsigned char rawBBpindirectionset(unsigned char inByte){
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

void rawBBperipheralset(unsigned char inByte){
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
		SPICS=1;//CS high
	else
		SPICS=0;

	UART1TX(1);//send 1/OK		
}



