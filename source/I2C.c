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
#include "bitbang.h"
#include "busPirateCore.h"//need access to bpConfig
#include "binIOhelpers.h"

#define SCL 		BP_CLK
#define SCL_TRIS 	BP_CLK_DIR     //-- The SCL Direction Register Bit
#define SDA 		BP_MOSI        //-- The SDA output pin
#define SDA_TRIS 	BP_MOSI_DIR    //-- The SDA Direction Register Bit

//software or hardware I2C mode defines
#define SOFT 0
#define HARD 1

extern struct _bpConfig bpConfig; //holds persistant bus pirate settings (see base.h) need hardware version info
extern struct _modeConfig modeConfig;
extern struct _command bpCommand;

//hardware functions
void hwi2cSetup(void);
void hwi2cstart(void);
void hwi2cstop(void);
void hwi2csendack(unsigned char ack);
unsigned char hwi2cgetack(void);
void hwi2cwrite(unsigned char c);
unsigned char hwi2cread(void);
void binI2CversionString(void);

static unsigned char I2Cspeed[]={157,37,13};//100,400,1000khz; datasheet pg 145

//software functions
void I2C_Setup(void);
void I2C_SnifferSetup(void);
void I2C_Sniffer(void);

//this function links the underlying i2c functions to generic commands that the bus pirate issues
//put most used functions first for best performance
void i2cProcess(void){
	static unsigned int i;
	static unsigned char c, i2cmode, ackPending=0;	

	if(ackPending==1){//we don't ACK or NACK reads until we know what the next byte is
		bpSP; //a space between the last character
		if(bpCommand.cmd==CMD_STARTR || bpCommand.cmd==CMD_START || bpCommand.cmd==CMD_STOP){
			bpWmessage(MSG_NACK); bpBR;//bpWline(OUMSG_I2C_READ_PEND_NACK);
			if(i2cmode==SOFT) bbI2Cnack(); else hwi2csendack(1); //the last read before a stop/start condition gets an NACK
		}else if(bpCommand.cmd==CMD_ENDOFSYNTAX){
			bpWline(OUMSG_I2C_READ_PEND);
			return;
		}else{
			bpWmessage(MSG_ACK);bpBR;//bpWline(OUMSG_I2C_READ_PEND_ACK);
			if(i2cmode==SOFT) bbI2Cack(); else hwi2csendack(0);//all other reads get an ACK
			
		}
		ackPending=0;
	}

	switch(bpCommand.cmd){
		case CMD_READ:
			if(bpCommand.repeat==1){
				bpWmessage(MSG_READ);
				if(i2cmode==SOFT)c=bbReadByte(); else c=hwi2cread();
				bpWbyte(c);
			}else{
				bpWmessage(MSG_READBULK);
				bpWbyte(bpCommand.repeat);
				bpWmessage(MSG_READBULK_BYTES);
				
				for(i=0;i<bpCommand.repeat;i++){	
					if(i>0){//ack at the top, skip beginning, don't ack last byte (may be NACKed above)
						bpSP; bpWmessage(MSG_ACK); bpSP;
						if(i2cmode==SOFT) bbI2Cack(); else hwi2csendack(0); 
					}
					if(i2cmode==SOFT)c=bbReadByte(); else c=hwi2cread();
					bpWbyte(c);
				}
			}
			ackPending=1;//we don't (n)ack now, we wait until we know what the next instruction is
			break;
		case CMD_WRITE:
			bpWmessage(MSG_WRITE);
			bpWbyte(bpCommand.num);
			if(bpCommand.repeat>1){
				bpWstring(" , ");
				bpWbyte(bpCommand.repeat);
				bpWmessage(MSG_WRITEBULK);
			}

			for(i=0;i<bpCommand.repeat;i++){
	 			if(i2cmode==SOFT){
					bbWriteByte(bpCommand.num); 
					c=bbReadBit();
				}else{
					hwi2cwrite(bpCommand.num);
					c=hwi2cgetack();
				}
			}
			
			//show ACK or NACK, for multiples, show last byte status
			bpSP;
			if(c==0)bpWmessage(MSG_ACK);else bpWmessage(MSG_NACK);	
			bpBR;
			break;
		case CMD_STARTR:
		case CMD_START:
			//start condition
			if(i2cmode==SOFT) bbI2Cstart(); else hwi2cstart();
			bpWmessage(MSG_I2C_START);
			break;
		case CMD_STOP:
			//stop condition
			if(i2cmode==SOFT) bbI2Cstop(); else hwi2cstop();
			bpWmessage(MSG_I2C_STOP);
			break;
		case CMD_PRESETUP:
			//set the options avaiable here....
			modeConfig.HiZ=1;//yes, always hiz
			modeConfig.allowpullup=1; 
			//modeConfig.allowlsb=0; //auto cleared on mode change

			bpWline(OUMSG_I2C_CON);
			i2cmode=(bpUserNumberPrompt(1, 2, 1)-1);

			if(i2cmode==SOFT){
				bpWmessage(MSG_OPT_BB_SPEED);
				modeConfig.speed=(bpUserNumberPrompt(1, 2, 1)-1);
			}else{
				// There is a hardware incompatibility with <B4
				// See http://forum.microchip.com/tm.aspx?m=271183&mpage=1
				if(bpConfig.dev_rev<=PIC_REV_A3) bpWline(OUMSG_I2C_REV3_WARN);
				bpWline(OUMSG_I2C_HWSPEED);
				modeConfig.speed=(bpUserNumberPrompt(1, 3, 1)-1);
			}
			break;
		case CMD_SETUP:
			if(i2cmode==SOFT){
				SDA_TRIS=1;
				SCL_TRIS=1;
				SCL=0;			//B8 scl 
				SDA=0;			//B9 sda
				bbSetup(2, modeConfig.speed);//configure the bitbang library for 2-wire, set the speed
			}else{
				hwi2cSetup();
			}
			bpWmessage(MSG_READY);
			break;
		case CMD_CLEANUP: //no cleanup needed...
			ackPending=0;//clear any pending ACK from previous use
			if(i2cmode==HARD) I2C1CONbits.I2CEN = 0;//disable I2C module
			break;
		case CMD_MACRO:
			switch(bpCommand.num){
				case 0://menu
					bpWline(OUMSG_I2C_MACRO_MENU);// 2. I2C bus sniffer\x0D\x0A");
					break;
				case 1:
					bpWline(OUMSG_I2C_MACRO_SEARCH);
					for(i=0;i<0x100;i++){

						if(i2cmode==SOFT){
							bbI2Cstart(); //send start
							bbWriteByte(i);//send address
							c=bbReadBit();//look for ack
						}else{
							hwi2cstart();
					 		hwi2cwrite(i);
							c=hwi2cgetack();
						}

						if(c==0){//0 is ACK
							bpWbyte(i);
							bpWchar('('); //bpWstring("(");
							bpWbyte((i>>1));
							if((i&0b1)==0){//if the first bit is set it's a read address, send a byte plus nack to clean up
								bpWstring(" W");
							}else{
								if(i2cmode==SOFT){
									bbReadByte();
									bbI2Cnack(); //bbWriteBit(1);//high bit is NACK
								}else{
									hwi2cread();
									hwi2csendack(1);//high bit is NACK
								}
								bpWstring(" R");
							}
							bpWstring(")");
							bpSP;	
						}
						if(i2cmode==SOFT) bbI2Cstop(); else hwi2cstop();
					}
					bpWBR;	
					break;
				case 2: 
					if(i2cmode==SOFT){ //if not soft, fall through and say error...
						bpWline(OUMSG_I2C_MACRO_SNIFFER);	
						I2C_SnifferSetup();
						while(1){
							I2C_Sniffer();
	
							if(U1STAbits.URXDA == 1){//any key pressed, exit
								i=U1RXREG;
								bpBR;
								break;
							}
						}
						break;
					}				
				default:
					bpWmessage(MSG_ERROR_MACRO);
			}
			break;
		case CMD_ENDOFSYNTAX: break;
		default:
			bpWmessage(MSG_ERROR_MODE);
	}

}

//*******************/
//
//
//	sofware I2C sniffer (very alpha)
//
//
//*******************/
static enum _i2cstate
	{
	IDLE=0,
	 START,
	 DATA,
	 ACK,
	 STOP
	} I2C_state=IDLE;
static struct _i2csniff
	{
	unsigned char pSDA:1;
	unsigned char cSDA:1;
	unsigned char pSCL:1;
	unsigned char cSCL:1;
	} I2Cpin;

unsigned char I2C_bits;//=0;

void I2C_SnifferSetup(void){
//we dont actually use interrupts, we poll the interrupt flag
/*
1. Ensure that the CN pin is configured as a digital input by setting the associated bit in the
TRISx register.
2. Enable interrupts for the selected CN pins by setting the appropriate bits in the CNENx
registers.
3. Turn on the weak pull-up devices (if desired) for the selected CN pins by setting the
appropriate bits in the CNPUx registers.
4. Clear the CNxIF interrupt flag.
*/
	//-- Ensure pins are in high impedance mode --
	SDA_TRIS=1;
	SCL_TRIS=1;
	//writes to the PORTs write to the LATCH
	SCL=0;			//B8 scl 
	SDA=0;			//B9 sda
	
	//enable change notice on SCL and SDA
	CNEN2bits.CN21IE=1;//MOSI
	CNEN2bits.CN22IE=1;

	//clear the CNIF interrupt flag
	IFS1bits.CNIF=0;

	I2C_state=IDLE;
	I2C_bits=0;
	I2Cpin.pSDA=SDA; //save current pin state in var
	I2Cpin.pSCL=SCL; //use to see which pin changes on interrupt

}

//S/[ - start
//0x - data
//A/+ - ACK +
//N/- - NACK -
//P/] - stop

void I2C_Sniffer(void){
	static unsigned char I2C_val;//=0;
	unsigned char I2C_ack;//=0;

	//check for change in pin state, if none, return
	if(IFS1bits.CNIF==0) return;

	I2Cpin.cSDA=SDA;
	I2Cpin.cSCL=SCL;
	IFS1bits.CNIF=0;

	//if data changed while clock is high, start condition (HL) or stop condition (LH)
	if(I2Cpin.pSCL==1 && I2Cpin.cSCL==1 ){//clock high, must be data transition

		if(I2Cpin.pSDA==1 && I2Cpin.cSDA==0){//start condition
			I2C_state=DATA;
			I2C_bits=0;
			//say start
			UART1TX('[');//might be better to use bus pirate syntax to display data
		}else if(I2Cpin.pSDA==0 && I2Cpin.cSDA==1){//stop condition
			I2C_state=IDLE;
			I2C_bits=0;
			//say stop
			UART1TX(']');		
		}


	} else if (I2Cpin.pSCL==0 && I2Cpin.cSCL==1){//sample when clock goes low to high 

		switch (I2C_state){
			//case IDLE: //do nothing
			//	break;
			//case START: //do nothing
			//	break;
			case DATA:
				//the next 8 bits are data
				I2C_val = I2C_val << 1; //move over one bit
				I2C_val += I2Cpin.cSDA; //get bit
				I2C_bits++;
				if(I2C_bits==8){
					I2C_bits=0;
					I2C_state=ACK;
				}
				break;
			case ACK:
				//delay, 
				I2C_ack=SDA; //check for ACK/NACK
				bpWbyte(I2C_val); //write byte value
				if(I2C_ack)UART1TX('-'); else UART1TX('+'); //write ACK status
				I2C_state=DATA; //next time start a new byte
				break;
			//case STOP:
			//	break;
			default:
				break;
	
		}

	}	
	I2Cpin.pSDA=I2Cpin.cSDA;//move current pin state to previous pin state
	I2Cpin.pSCL=I2Cpin.cSCL;
}


//
//
//	HARDWARE I2C BASE FUNCTIONS
//
//
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


/*
rawI2C mode:
# 00000000//reset to BBIO
# 00000001 � mode version string (I2C1)
# 00000010 � I2C start bit
# 00000011 � I2C stop bit
# 00000100 - I2C read byte
# 00000110 - ACK bit
# 00000111 - NACK bit
# 0001xxxx � Bulk transfer, send 1-16 bytes (0=1byte!)
# (0110)000x - Set I2C speed, 1=high (50kHz) 0=low (5kHz) (was 0100)
# (0111)000x - Read speed, (planned)
# (0100)wxyz � Configure peripherals w=power, x=pullups, y=AUX, z=CS (was 0110)
# (0101)wxyz � read peripherals (planned, not implemented)
*/
void binI2CversionString(void){bpWstring("I2C1");}

void binI2C(void){
	static unsigned char inByte, rawCommand, i;
	
	//I2C setup
	SDA_TRIS=1;
	SCL_TRIS=1;
	SCL=0;			//B8 scl 
	SDA=0;			//B9 sda

	//set CS pin direction to output on setup
	BP_CS_DIR=0;			//B6 cs output

	modeConfig.HiZ=1;//yes, always hiz (bbio uses this setting, should be changed to a setup variable because stringing the modeconfig struct everyhwere is getting ugly!)
	modeConfig.lsbEN=0;//just in case!
	bbSetup(2, 1);//configure the bitbang library for 2-wire, set the speed to high speed (50khz)
	binI2CversionString();//reply string

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
						binI2CversionString();//reply string
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

			case 0b0110://set speed 
				inByte&=(~0b11111110);//clear command portion
				bbSetup(2, inByte);//set I2C speed
				UART1TX(1);
				break;

			case 0b0100: //configure peripherals w=power, x=pullups, y=AUX, z=CS
				binIOperipheralset(inByte);
				UART1TX(1);//send 1/OK		
				break;

			default:
				UART1TX(0x00);//send 0/Error
				break;
		}//command switch
	}//while loop

}


