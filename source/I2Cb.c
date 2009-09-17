//this DOES NOT work with the PIC 24Fj64GA002
//there is an error in revision 3 silicon
//with the I2C1 module
//no work around
// we'll use a dspic in a future revision, but stuck to the software routine for now.
//http://forum.microchip.com/tm.aspx?m=271183&mpage=1
#include "I2Cb.h"
#include "base.h"
#include "busPirateCore.h"//need access to bpConfig

extern struct _modeConfig modeConfig;
extern struct _bpConfig bpConfig; //holds persistant bus pirate settings (see base.h)

void hwi2cSetup(void);
void hwi2cstart(void);
void hwi2cstop(void);
void hwi2csendack(unsigned char ack);
unsigned char hwi2cgetack(void);
void hwi2cwrite(unsigned char c);
unsigned char hwi2cread(void);

static unsigned char I2Cspeed[]={157,37,13};//100,400,1000khz; datasheet pg 145

void hwi2cProcess(unsigned char cmd, unsigned char val, unsigned char repeatVal){
	static unsigned int i;
	static unsigned char ackPending=0;	

	if(ackPending==1){//we don't ACK or NACK reads until we know what the next byte is
		if(cmd==CMD_STARTR || cmd==CMD_START || cmd==CMD_STOP){
			bpWline(" NACK");
			hwi2csendack(1);//high is NACK //the last read before a stop/start condition gets an NACK
		}else if(cmd==CMD_ENDOFSYNTAX){
			bpWline(" *(N)ACK PENDING");
			return;
		}else{
			bpWline(" ACK");
			hwi2csendack(0);//low is ACK //all other reads get an ACK
		}
		ackPending=0;
	}

	switch(cmd){//most frequent operations first
		case CMD_READ:
			if(repeatVal==1) {
				bpWmessage(MSG_READ);
				bpWbyte(hwi2cread());
			}else{
				bpWmessage(MSG_READBULK);
				bpWbyte(repeatVal);
				bpWmessage(MSG_READBULK_BYTES);

				for(i=0; i<repeatVal;i++){
					if(i>0){//ack at the top, skip beginning, don't ack last byte (may be NACKed above)
						bpWstring(" ACK ");
						hwi2csendack(0);//low is ACK 
					}
					bpWbyte(hwi2cread());
				}
			}
			//bpWBR;
			ackPending=1;//we don't (n)ack now, we wait until we know what the next instruction is
			break;
		case CMD_WRITE:
			bpWmessage(MSG_WRITE);
			bpWbyte(val);
			hwi2cwrite(val);
			if(hwi2cgetack()==0){
				bpWline(" GOT ACK: YES");
			}else{
				bpWline(" GOT ACK: NO");			
			}
			break;
		case CMD_STARTR:
		case CMD_START:
			// Enable a start condition
			hwi2cstart();
			bpWmessage(MSG_I2C_START);
			break;
		case CMD_STOP:
			hwi2cstop();
			bpWmessage(MSG_I2C_STOP);
			break;
		case CMD_PRESETUP:
			// There is a hardware incompatibility with <B4
			// See http://forum.microchip.com/tm.aspx?m=271183&mpage=1
			if(bpConfig.dev_rev<=PIC_REV_A3) bpWstring(OUMSG_WARN_HWI2C_REV3_T);	
			//set the options avaiable here....
			modeConfig.HiZ=1;//yes, always hiz
			//modeConfig.allowlsb=0; //auto cleared on mode change
			modeConfig.allowpullup=1; 
			bpWstring("Set speed:\x0D\x0A 1. 100KHz\x0D\x0A 2. 400KHz\x0D\x0A 3. 1MHz\x0D\x0A SPEED>");
			modeConfig.speed=(bpUserNumberPrompt(1, 3, 1)-1);
			break;
		case CMD_SETUP:
			hwi2cSetup();
			bpWline("HWI2C READY");
			break;
		case CMD_CLEANUP:
			//disable I2C module
			I2C1CONbits.I2CEN = 0;
			//should do any pin direction cleanup too?
			ackPending=0;//clear any pending ACK from previous use
			break;
		case CMD_MACRO:
			switch(val){
				case 0://menu
					bpWstring(" 0.Macro menu\x0D\x0A 1.7bit address search\x0D\x0A");
					break;
				case 1:
					bpWline("Searching 7bit I2C address space. \x0D\x0A   Found devices at:");
					for(i=0;i<0x100;i++){
						hwi2cstart();
			 			hwi2cwrite(i);
						if(hwi2cgetack()==0){
							bpWbyte(i);
							bpWchar('('); //bpWstring("(");
							bpWbyte((i>>1));
							if((i&0b1)==0){//if the first bit is set it's a read address, send a byte plus nack to clean up
								bpWstring("W");
							}else{
								hwi2cread();
								hwi2csendack(1);//high bit is NACK
								bpWstring("R");
							}
							bpWstring(")");
							bpSP;		
						}
						hwi2cstop();
					}
					bpBR;	
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
void hwi2cstart(void){
	// Enable a start condition
	I2C1CONbits.SEN = 1;
	while(I2C1CONbits.SEN==1);//wait
}

void hwi2cstop(void){
	I2C1CONbits.PEN = 1;
	while(I2C1CONbits.PEN==1);//wait
}

unsigned char hwi2cgetack(void){
	return I2C1STATbits.ACKSTAT;
}

void hwi2csendack(unsigned char ack){
	I2C1CONbits.ACKDT=ack;//send ACK (0) or NACK(1)?
	I2C1CONbits.ACKEN=1;
	while(I2C1CONbits.ACKEN==1);
}

void hwi2cwrite(unsigned char c){
	I2C1TRN=c;
	while(I2C1STATbits.TRSTAT==1);
}

unsigned char hwi2cread(void){
	unsigned char c;
	I2C1CONbits.RCEN=1;
	while(I2C1CONbits.RCEN==1);
	c=I2C1RCV;
	return c;
}

void hwi2cSetup(void){

	I2C1CONbits.A10M=0;
	I2C1CONbits.SCLREL=0;

	I2C1ADD=0;
	I2C1MSK=0;

	// Enable SMBus 
	I2C1CONbits.SMEN = 0; 

	// Baud rate setting
	I2C1BRG = I2Cspeed[modeConfig.speed];
	
	// Enable I2C module
	I2C1CONbits.I2CEN = 1;
	
//
// This work around didn't work for me...
//
/*
	//NICE TRY, BUT NO CIGAR
	//for revision 3, the SDA has to be hit once manually before
	//it will work, we use the connected pullup resistor to jump start
	//the broken hardware module.
	bpDelayUS(200);
	LATBbits.LATB11=0;//hold to ground
	TRISBbits.TRISB11=0;//SDA Pullup
	bpDelayUS(250);
	TRISBbits.TRISB11=1;//SDA Pullup
	LATBbits.LATB11=1;//release
*/

}
