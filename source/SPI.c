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

#include "SPI.h"
#include "base.h"

//#define USE_SPICS //the CS hardware pin on silicone REV 3 doesn't work, optionally enable it here

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

#define SPICS_RPIN		BP_CS_RPIN

extern struct _modeConfig modeConfig;
extern struct _command bpCommand;

void spiSetup(void);
void spiDisable(void);
unsigned char spiWriteByte(unsigned char c);
void spiSlaveDisable(void);
void spiSlaveSetup(void);
void spiSniffer(unsigned char csState);

struct _SPI{
	unsigned char ckp:1;
	unsigned char cke:1;
	unsigned char smp:1;
	unsigned char wwr:1;
} spiSettings;

static unsigned char SPIspeed[]={0b00000,0b11000,0b11100,0b11101};//30,125,250,1000khz; datasheet pg 142

void spiProcess(void){
	static unsigned char c;
	static unsigned int i;

	switch(bpCommand.cmd){
		case CMD_STARTR:
		case CMD_START:
			if(bpCommand.cmd==CMD_STARTR){spiSettings.wwr=1;}else{spiSettings.wwr=0;}
			//cs enable
			SPICS=0; 
			bpWmessage(MSG_CS_ENABLED);
			break;
		case CMD_STOP:
			//cs disable
			SPICS=1;
			bpWmessage(MSG_CS_DISABLED);
			break;
		case CMD_READ:
			if(bpCommand.repeat==1){
				bpWmessage(MSG_READ);
				c=spiWriteByte(0xff);
				bpWbyte(c);
			}else{
				bpWmessage(MSG_READBULK);	
				bpWbyte(bpCommand.repeat);
				bpWmessage(MSG_READBULK_BYTES);
				for(i=0;i<bpCommand.repeat;i++){	
					bpWbyte(spiWriteByte(0xff));
					bpSP;//space
				}
			}
			bpWBR;
			break;
		case CMD_WRITE:
			bpWmessage(MSG_WRITE);
			bpWbyte(bpCommand.num);
			if(bpCommand.repeat==1){
				c=spiWriteByte(bpCommand.num);
				if(spiSettings.wwr==1){
					bpSP;
					bpWmessage(MSG_READ);
					bpWbyte(c);
				}
			}else{
				bpWstring(" , ");
				bpWbyte(bpCommand.repeat);
				bpWmessage(MSG_WRITEBULK);
				for(i=0;i<bpCommand.repeat;i++)c=spiWriteByte(bpCommand.num);
			}
			bpWBR;
			break;
		case CMD_PRESETUP:
			//bpWstring("Set speed:\x0D\x0A 1. 30KHz\x0D\x0A 2. 125KHz\x0D\x0A 3. 250KHz\x0D\x0A 4. 1MHz\x0D\x0A");
			bpWline(OUMSG_SPI_SPEED);
			modeConfig.speed=(bpUserNumberPrompt(1, 4, 1)-1);

			//bpWstring("Clock polarity:\x0D\x0A 1. Idle low *default\x0D\x0A 2. Idle high\x0D\x0A");
			bpWmessage(MSG_OPT_CKP);
			spiSettings.ckp=(bpUserNumberPrompt(1, 2, 1)-1);

			//bpWstring("Output clock edge:\x0D\x0A 1. Idle to active\x0D\x0A 2. Active to idle *default\x0D\x0A");
			bpWmessage(MSG_OPT_CKE);
			spiSettings.cke=(bpUserNumberPrompt(1, 2, 2)-1);

			//bpWstring("Input sample phase:\x0D\x0A 1. Middle *default\x0D\x0A 2. End\x0D\x0A");
			bpWmessage(MSG_OPT_SMP);
			spiSettings.smp=(bpUserNumberPrompt(1, 2, 1)-1);

			bpWmessage(MSG_OPT_OUTPUT_TYPE);
			modeConfig.HiZ=(~(bpUserNumberPrompt(1, 2, 1)-1));
			
			modeConfig.allowlsb=0;
			#ifdef BUSPIRATEV2
			modeConfig.allowpullup=1;
			#endif
			break;
		case CMD_SETUP:
			//cleanup variables
			spiSettings.wwr=0;
			//do SPI peripheral setup
			spiSetup();
			bpWmessage(MSG_READY);
			break;
		case CMD_CLEANUP:
			//turn off SPI
			spiDisable();
			break;
		case CMD_MACRO:
			switch(bpCommand.num){
				case 0:
					bpWline(OUMSG_SPI_MACRO_MENU);
					break;
				case 1:
					bpWline(OUMSG_SPI_SNIFF_MENU);
					c=(bpUserNumberPrompt(1, 3, 1)-1);
					spiSniffer(c);
					break;
				default:
					bpWmessage(MSG_ERROR_MACRO);
			}
			break;
		case CMD_ENDOFSYNTAX: break;
		default:
			bpWmessage(MSG_ERROR_MODE);
	}

}

void spiSetup(void){
    SPI1STATbits.SPIEN = 0;//disable, just in case...
	
	//use open drain control register to 
	//enable Hi-Z mode on hardware module outputs
	//inputs are already HiZ
	if(modeConfig.HiZ==1){
		SPIMOSI_ODC=1;
		SPICLK_ODC=1; 
		SPICS_ODC=1;
	}

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
	SPI1CON1 = (SPIspeed[modeConfig.speed]); // CKE (output edge) active to idle, CKP idle low, SMP data sampled middle of output time.
	SPI1CON1bits.MSTEN=1;
	SPI1CON1bits.CKP=spiSettings.ckp;
	SPI1CON1bits.CKE=spiSettings.cke;		
	SPI1CON1bits.SMP=spiSettings.smp;
    SPI1CON2 = 0;
    SPI1STAT = 0;    // clear SPI
    SPI1STATbits.SPIEN = 1;
}

void spiDisable(void){
	SPI1STATbits.SPIEN = 0;
	RPINR20bits.SDI1R=0b11111;  //B7 MISO
	RPOR4bits.RP9R=0; 			//B9 MOSI
	RPOR4bits.RP8R=0; 			//B8 CLK
	//disable all open drain control register bits
	SPIMOSI_ODC=0;
	SPICLK_ODC=0; 
	SPICS_ODC=0;
}

//void spiCSHigh(void){SPICS=1;}

//void spiCSLow(void){SPICS=0;}

unsigned char spiWriteByte(unsigned char c){
	SPI1BUF = c;
	while(!IFS0bits.SPI1IF);
	c=SPI1BUF;
	IFS0bits.SPI1IF = 0;
	return c;
}

//need to use SPI2 to sniff other bus pin....
void spiSniffer(unsigned char csState){
	unsigned char c;
	//use current settings, configure SPI for slave mode
	bpWline(OUMSG_SPI_SNIFF_BEGIN);
	spiDisable();
	spiSlaveSetup();
	while(1){
		if(csState>1 || SPICS==csState){
			if(SPI1STATbits.SPIEN==0){SPI1STATbits.SPIEN=1; SPI2STATbits.SPIEN=1;} 
		}else{
			if(SPI1STATbits.SPIEN==1){
				SPI1STATbits.SPIEN=0; //only enable when CS matches desired state
				SPI2STATbits.SPIEN=0;
				bpWBR; //mark the end of the current packet
			}
		}

		if(SPI1STATbits.SRXMPT==0){//rx buffer NOT empty, get and display byte
			c=SPI1BUF;
			bpWbyte(c);
		}
		if(SPI2STATbits.SRXMPT==0){//rx buffer NOT empty, get and display byte
			c=SPI2BUF;
			bpWstring("(");
			bpWbyte(c);
			bpWstring(") ");
		}

		if(SPI1STATbits.SPIROV==1 || SPI2STATbits.SPIROV==1 ){//we weren't fast enough, buffer overflow
			bpWline(OUMSG_SPI_SNIFF_BUFFER);	
			SPI1STATbits.SPIROV=0;
			SPI2STATbits.SPIROV=0;						
			break;
		}

		if(U1STAbits.URXDA == 1){//any key pressed, exit
			c=U1RXREG;
			bpBR;
			break;
		}
	}
	spiSlaveDisable();
	spiSetup();
}

void spiSlaveSetup(void){
//	unsigned char c;
	//SPI1STATbits.SPIEN=0; //SPI module off

//assign pins for SPI slave mode
	SPICS_TRIS=1;			//B6 cs input
	SPICLK_TRIS=1; 			//B8 sck input
	SPIMISO_TRIS=1; 		//B7 SDI input
	SPIMOSI_TRIS=1;			//b9 SDO input

#ifdef USE_SPICS
	RPINR21bits.SS1R=6;//SPICS_RPIN; //assign CS function to bus pirate CS pin
	RPINR23bits.SS2R=6;
#endif
	RPINR20bits.SDI1R=9; //B9 MOSI
	RPINR20bits.SCK1R=8;//SPICLK_RPIN; //assign SPI1 CLK input to bus pirate CLK pin
	RPINR22bits.SDI2R=7; //B7 MiSo
	RPINR22bits.SCK2R=8; //SPICLK_RPIN; //assign SPI2 CLK input to bus pirate CLK pin	

//clear old SPI settings first
	SPI1CON1 = (SPIspeed[modeConfig.speed]); // CKE (output edge) active to idle, CKP idle low, SMP data sampled middle of output time.
	SPI1CON1bits.CKP=spiSettings.ckp;
	SPI1CON1bits.CKE=spiSettings.cke;
	//SPI1CON1bits.SMP=spiSettings.smp;
    SPI1CON2 = 0;
    SPI1STAT = 0;    // clear SPI

	SPI2CON1 = (SPIspeed[modeConfig.speed]); // CKE (output edge) active to idle, CKP idle low, SMP data sampled middle of output time.
	SPI2CON1bits.CKP=spiSettings.ckp;
	SPI2CON1bits.CKE=spiSettings.cke;	
    SPI2CON2 = 0;
    SPI2STAT = 0;    // clear SPI

//To set up the SPI module for the Enhanced Buffer
//Slave mode of operation:
//1. Clear the SPIxBUF register.
	SPI1BUF=0;
	SPI2BUF=0;
//3. Write the desired settings to the SPIxCON1 and SPIxCON2 registers with MSTEN (SPIxCON1<5>) = 0.
//4. Clear the SMP bit.
	SPI1CON1bits.SMP=0;
	SPI2CON1bits.SMP=0;
#ifdef USE_SPICS
	SPI1CON1bits.SSEN=1; //CS pin active
	SPI2CON1bits.SSEN=1; //CS pin active
#endif
	SPI1CON1bits.DISSDO=1;//Disable SDO pin in slave mode
	SPI1CON1bits.MSTEN=0;
	SPI2CON1bits.DISSDO=1;//Disable SDO pin in slave mode
	SPI2CON1bits.MSTEN=0;
//5. If the CKE bit is set, then the SSEN bit must be set, thus enabling the SSx pin.
//6. Clear the SPIROV bit (SPIxSTAT<6>).
	SPI1STATbits.SPIROV=0;
	SPI2STATbits.SPIROV=0;
//7. Select Enhanced Buffer mode by setting the SPIBEN bit (SPIxCON2<0>).
	SPI1CON2bits.SPIBEN=1;
	SPI2CON2bits.SPIBEN=1;
//8. Enable SPI operation by setting the SPIEN bit(SPIxSTAT<15>).
	//SPI1STATbits.SPIEN=1;
}

void spiSlaveDisable(void){
	SPI1STATbits.SPIEN=0; //SPI module off
	SPI1CON1bits.DISSDO=0;//restore SDO pin 
	SPI2STATbits.SPIEN=0; //SPI module off
	SPI2CON1bits.DISSDO=0;//restore SDO pin 
#ifdef USE_SPICS
	RPINR21bits.SS1R=0b11111;	//assign CS input to none
	RPINR23bits.SS2R=0b11111;	//assign CS input to none
#endif
	RPINR20bits.SDI1R=0b11111;
	RPINR20bits.SCK1R=0b11111;	//assign CLK input to none
	RPINR22bits.SDI2R=0b11111;
	RPINR22bits.SCK2R=0b11111;	//assign CLK input to none
	//SPI1CON1bits.SMP=spiSettings.smp;	//restore SMP setting (done in spiSetup()
}

