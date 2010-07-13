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

#include "bitbang.h"
#include "base.h"
#include "procmenu.h"

#ifdef BP_USE_LCD

//PCF8574 I2C write address (0x40 with all ADDR pins to ground)
// moved to sturcture to make it userconfigurable ;)
//#define PCF8574_ADDRESS_WRITE 0x40

//Define how the PCF8574 pins connect to the LCD
#define PCF8574_LCD_RS 0b10000000
#define PCF8574_LCD_RW 0b01000000
#define PCF8574_LCD_EN 0b00100000
#define PCF8574_LCD_D4 0b00000001
#define PCF8574_LCD_D5 0b00000010
#define PCF8574_LCD_D6 0b00000100
#define PCF8574_LCD_D7 0b00001000
#define PCF8574_LCD_LED 0b00010000

//RS (register select) pin states
#define HD44780_COMMAND 0 
#define HD44780_DATA 1 

//
//HD44780 commands and related options
//
#define CMD_CLEARDISPLAY 	0b00000001 //82us-1.64ms

#define CMD_RETURNHOME 		0b00000010 //40us-1.64ms

#define CMD_ENTRYMODESET 	0b00000100 //40us
#define INCREMENT 0b10
#define DECREMENT 0b00
#define DISPLAYSHIFTON 0b1
#define DISPLAYSHIFTOFF 0

#define CMD_DISPLAYCONTROL 	0b00001000 //40us
#define DISPLAYON 0b100
#define DISPLAYOFF 0
#define CURSERON 0b10
#define CURSEROFF 0
#define BLINKON 0b1
#define BLINKOFF 0

#define CMD_CURSERDISPLAYSHIFT 0b00010000 //40us
#define DISPLAYSHIFT 0b1000
#define CURSERMOVE 0
#define SHIFTRIGHT 0b100
#define SHIFTLEFT 0

#define CMD_FUNCTIONSET 	0b00100000 //40us
#define DATAWIDTH8 0b10000
#define DATAWIDTH4 0
#define DISPLAYLINES2 0b1000
#define DISPLAYLINES1 0
#define FONT5X10 0b100
#define FONT5X7 0
#define MODULE24X4 0b1

#define CMD_SETCGRAMADDR 	0b01000000 //40us
//6bit character generator RAM address

#define CMD_SETDDRAMADDR 	0b10000000 //40us
//7bit display data RAM address

//configuration structure
extern struct _modeConfig modeConfig;
extern struct _command bpCommand;

/*
struct _HD44780_4bit_interface {
	unsigned char EN:1; //clock, active high
	unsigned char RS:1; //register select, 0=command, 1=text
	unsigned char RW:1; //read write, 0=, 1=
	unsigned char D4:1;
	unsigned char D5:1;
	unsigned char D6:1;
	unsigned char D7:1;
}
*/
struct _HD44780_interface {
	unsigned char EN:1; //clock, active high
	unsigned char RS:1; //register select, 0=command, 1=text
	unsigned char RW:1; //read write, 0=write, 1=read
	unsigned char LED:1; //LED on IO board, 0=on, 1=off
	unsigned char PCF8574; //address of expander
	//unsigned char dat; //8 data bits
} HD44780;

void HD44780_Term(void); //outputs typed text to the LCD
void HD44780_Reset(void); //reset the LCD to 4 bit mode
void HD44780_Init(unsigned char displaylines); //initialize LCD to 4bit mode with typical settings and X displaylines
void HD44780_WriteString(char *s); //write a string to the LCD
void HD44780_WriteByte(unsigned char reg, unsigned char dat); //write a byte to LCD to register REG
void HD44780_WriteNibble(unsigned char reg, unsigned char dat);//write 4 bits to LCD to register REG
void HD44780_I2Cwrite(unsigned char datout); //abstracts data output to PCF8574 IO expander over I2C bus
unsigned char HD44780_I2Cread(void);
unsigned char HD44780_ReadNibble(unsigned char reg);
unsigned char HD44780_ReadByte(unsigned char reg);
void HD44780_I2Cerror(void);

unsigned int LCDread(void)
{	return HD44780_ReadByte(HD44780.RS);
}

unsigned int LCDwrite(unsigned int c)
{	HD44780_WriteByte(HD44780.RS, c);

	return 0x100;
}

void LCDstart(void)
{	HD44780.RS=HD44780_COMMAND;
	//bpWline(OUMSG_LCD_COMMAND_MODE);
	BPMSG1213;
}

void LCDstop(void)
{	HD44780.RS=HD44780_DATA;
	//bpWline(OUMSG_LCD_DATA_MODE);
	BPMSG1214;
}

void LCDsetup(void)
{	int address, type;

	modeConfig.HiZ=1;//yes, always HiZ

	HD44780.RS=HD44780_DATA;

	consumewhitechars();
	type=getint();
	consumewhitechars();
	address=getint();

	if(!((type==1)&&(address>=0x00)&&(address<=0xFF)))
	{	cmderror=0;

		//bpWline(OUMSG_LCD_SETUP_ADAPTER);
		BPMSG1217;
		//c=bpUserNumberPrompt(1, 1, 1);
		getnumber(1,1,1,0);		// schiet mij maar in een kapotje :S
	
		// address of expander?
		BPMSG1215;
		HD44780.PCF8574=getnumber(0x40,0, 255, 0);
	}
	else
	{	BPMSG1218;
		bpWdec(type); bpSP;
		bpWdec(address); bpSP;
		BPMSG1162;
		HD44780.PCF8574=address;
	}

	//******** REQUIRED DEFINES ***********
	#define SCL 		BP_CLK
	#define SCL_TRIS 	BP_CLK_DIR     //-- The SCL Direction Register Bit
	#define SDA 		BP_MOSI        //-- The SDA output pin
	#define SDA_TRIS 	BP_MOSI_DIR    //-- The SDA Direction Register Bit
	
	#define I2CLOW  	0         //-- Puts pin into output/low mode
	#define I2CHIGH 	1         //-- Puts pin into Input/high mode
	
	#define I2C_SLOW	0
	#define I2C_FAST	1
	//-- Ensure pins are in high impedance mode --
	SDA_TRIS=1;
	SCL_TRIS=1;
	//writes to the PORTs write to the LATCH
	SCL=0;			//B8 scl 
	SDA=0;			//B9 sda
	bbSetup(2, 1); //2wire mode, high speed

	//bpWmessage(MSG_ADAPTER);
	BPMSG1216;
}

void LCDmacro(unsigned int c)
{	int input,i;

	consumewhitechars();
	input=getint();
	cmderror=0;

	switch(c)
	{	case 0://menu
			//bpWline(OUMSG_LCD_MACRO_MENU);
			BPMSG1219;
			break;
		case 1:
		case 2:
			//bpWline(OUMSG_LCD_MACRO_RESET);
			BPMSG1093;
			HD44780_Reset();
			if(c==1) break;
	
			if(!((input>=1)&&(input<=2)))
			{	//bpWline(OUMSG_LCD_MACRO_INIT_DISPLAYLINES);
				BPMSG1220;
				//c=bpUserNumberPrompt(1, 2, 2);
				input=getnumber(2,1,2, 0);
				if(input==1) HD44780_Init(DISPLAYLINES1); else HD44780_Init(DISPLAYLINES2);
				//bpWline(OUMSG_LCD_MACRO_INIT);
			}
			BPMSG1221;
			break;		
		case 3: //Clear LCD and return home
			HD44780_WriteByte(HD44780_COMMAND, CMD_CLEARDISPLAY);
			bpDelayMS(15);//delay 15ms
			//bpWline(OUMSG_LCD_MACRO_CLEAR);
			BPMSG1222;
			break;	
		case 4: 
			HD44780_WriteByte(HD44780_COMMAND, CMD_SETDDRAMADDR | (unsigned char)input);
			//bpWline(OUMSG_LCD_MACRO_CURSOR);
			BPMSG1223;
			break;
		case 6: //write numbers	
			HD44780_WriteByte(HD44780_COMMAND, CMD_CLEARDISPLAY);//Clear LCD and return home
			bpDelayMS(15);//delay 15ms
			c=0x30;
			for(i=0; i<input; i++){
				if(c>0x39) c=0x30;
				HD44780_WriteByte(HD44780_DATA, c);
				UART1TX(c);
				c++;
			}
			break;	
		case 7://write characters				
			HD44780_WriteByte(HD44780_COMMAND, CMD_CLEARDISPLAY); //Clear LCD and return home
			bpDelayMS(15);//delay 15ms
			c=0x21; //start character (!)
			if(input==0) input=80;
			for(i=0; i<input; i++){
				if(c>127)c=0x21;
				HD44780_WriteByte(HD44780_DATA, c);
				UART1TX(c);
				c++;
			}
			break;
/*		case 8://terminal mode/pass through   //superseeded by send string command
				bpWline(OUMSG_LCD_MACRO_TEXT);
				HD44780_Term();
			break; */
		default:
			//bpWmessage(MSG_ERROR_MACRO);
			BPMSG1016;
	}

}

void LCDpins(void)
{	BPMSG1231;	
}	


//initialize LCD to 4bits with standard features
//displaylines=0 for single line displays, displaylines=1 for multiline displays
void HD44780_Init(unsigned char displaylines){
	//Function set
	HD44780_WriteByte(HD44780_COMMAND, (CMD_FUNCTIONSET + DATAWIDTH4 + FONT5X7 + displaylines)); //0x28, 0b101000
	bpDelayMS(15);//delay 15ms
	
	//Turn display off
	HD44780_WriteByte(HD44780_COMMAND, CMD_DISPLAYCONTROL + DISPLAYOFF + CURSEROFF + BLINKOFF);//0x08, 0b1000
	bpDelayMS(15);//delay 15ms
	
	//Clear LCD and return home
	HD44780_WriteByte(HD44780_COMMAND, CMD_CLEARDISPLAY);
	bpDelayMS(15);//delay 15ms
	
	//Turn on display, turn off cursor and blink
	HD44780_WriteByte(HD44780_COMMAND, CMD_DISPLAYCONTROL + DISPLAYON + CURSERON + BLINKOFF);   // 0x0f, 0b1111
	bpDelayMS(15);//delay 15ms
}

//reset LCD to 4bit mode
void HD44780_Reset(void){

	HD44780_I2Cwrite(0); //clear IO pins to HD44780
	//# Wait more than 15 msecs after power is applied.
	bpDelayMS(15);
	//# Write 0x03 to LCD and wait 5 msecs for the instruction to complete
	HD44780_WriteNibble(HD44780_COMMAND, 0x03);
	bpDelayMS(5);
	//# Write 0x03 to LCD and wait 160 usecs for instruction to complete
	HD44780_WriteNibble(HD44780_COMMAND, 0x03);
	bpDelayUS(160);
	//# Write 0x03 AGAIN to LCD and wait 160 usecs (or poll the Busy Flag) 
	HD44780_WriteNibble(HD44780_COMMAND, 0x03);
	bpDelayUS(160);
	//Set the Operating Characteristics of the LCD
    //* Write 0x02 to the LCD to Enable Four Bit Mode 
	HD44780_WriteNibble(HD44780_COMMAND, 0x02);
	bpDelayUS(160);
}

/*
//write a string to the LCD
void HD44780_WriteString(char *s){
	char c;
	while((c = *s++)) HD44780_WriteByte(HD44780_DATA, c);
}
*/

//write byte dat to register reg
void HD44780_WriteByte(unsigned char reg, unsigned char dat){
	HD44780_WriteNibble(reg, (dat>>4) );
	HD44780_WriteNibble(reg, (dat & 0x0F));
}

//read byte from LCD register reg
unsigned char HD44780_ReadByte(unsigned char reg){
	unsigned char dat;
	
	dat=(HD44780_ReadNibble(reg)<<4);
	dat|=HD44780_ReadNibble(reg);
	return dat;
}

//write 4 bits dat to register reg
void HD44780_WriteNibble(unsigned char reg, unsigned char dat){
	//EN pin should already be low
	//RW bit should be 0 (already 0 in dat)
	//LED bit should be 0 (already 0 in dat)
	//databits are aligned with the lower four bits of PCF8574, we can just use dat
	//rearrange if you use a different pinout

	if(reg==HD44780_DATA){	//does RS need to be set?
		dat |= PCF8574_LCD_RS; //set register select flag for text
	}//leave as 0 for a command

	HD44780_I2Cwrite(dat); //load values

	dat |= PCF8574_LCD_EN; //raise the EN line to clock in the values
	HD44780_I2Cwrite(dat);

	//optional setup delay

	dat &= (~PCF8574_LCD_EN); //lower EN line
	HD44780_I2Cwrite(dat);

}

//read 4 bits from register reg
unsigned char HD44780_ReadNibble(unsigned char reg){
	unsigned char dat=0, nibble=0;

	//EN pin should already be low
	dat |= PCF8574_LCD_RW;//RW bit should be 1 (already 0 in dat)
	//LED bit should be 0 (already 0 in dat)
	if(reg==HD44780_DATA){	//does RS need to be set?
		dat |= PCF8574_LCD_RS; //set register select flag for text
	}//leave as 0 for a command
	dat|=0b1111;//PCF8574 IO pins must be high for reads

	HD44780_I2Cwrite(dat); //load values
	dat |= PCF8574_LCD_EN; //raise the EN line to clock in the values
	HD44780_I2Cwrite(dat);

	//optional setup delay

	nibble=HD44780_I2Cread();//read datastate
	nibble&=(~0b11110000); //clear upper four bits

	dat &= (~PCF8574_LCD_EN); //lower EN line
	HD44780_I2Cwrite(dat);
	return nibble;
}

unsigned char HD44780_I2Cread(void){
	unsigned char c;

	bbI2Cstart();
	//bbWriteByte((PCF8574_ADDRESS_WRITE+1)); //read address is WR+1
	bbWriteByte(HD44780.PCF8574+1); //read address is WR+1
	if(bbReadBit()==1){HD44780_I2Cerror(); return 0;}
	c=bbReadByte();
	bbWriteBit(1); //send NACK to end read
	bbI2Cstop();
	return c;
}

//write value to PCF8574 I2C IO expander, message and return on ACK error
void HD44780_I2Cwrite(unsigned char datout){
	bbI2Cstart();
	//bbWriteByte(PCF8574_ADDRESS_WRITE);
	bbWriteByte(HD44780.PCF8574);
	if(bbReadBit()==1){HD44780_I2Cerror(); return;}
	bbWriteByte(datout);
	if(bbReadBit()==1){HD44780_I2Cerror(); return;}
	bbI2Cstop();
}

void HD44780_I2Cerror(void)
{	//bpWline(OUMSG_LCD_ERROR_ADAPTER);
	BPMSG1224;
}

#endif
