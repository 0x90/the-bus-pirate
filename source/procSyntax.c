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
//convert commands to actual character in a #DEFINE CMD_READ 'R' and get rid of the silly switch statement
//convert menu commands to defines, use caps only (lowercase adjusted automatically)
//create processing structure with proper variable names

#include "base.h"
#include "AUXpin.h"
#include "busPirateCore.h"

extern struct _bpConfig bpConfig;
extern struct _modeConfig modeConfig;
extern struct _command bpCommand; //holds the current active command so we don't ahve to put so many variables on the stack

//reads forward to grab repeat values following read, delay, and clock
unsigned int bpGetRepeatVal(unsigned int totalBytes, unsigned int *currentByte, unsigned char *commandArr); 
//convert ASCII text input in the syntax string to a command
unsigned char ASCII2CMD(unsigned char ASCIIcommand);

/*	static struct _syn{
		unsigned int currentByte;
		unsigned char command;
		unsigned char ASCIInumber[12];
		unsigned char writeVal;
		unsigned char repeatVal;
		unsigned char macroVal;
		unsigned char error:1;
	} syntax; 
*/

//master function that processes terminal input 
//scans for valid syntax, converts to values and general bus commands
void processSyntaxString(unsigned int totalBytes, unsigned char *commandArr){
	static unsigned int currentByte,numVal,repeatVal;
	static unsigned char command,error=0;

	if(bpConfig.busMode==0){bpWmessage(MSG_ERROR_NOMODE); return;}

	//process each byte of the command string and act on it
	for(currentByte=0;currentByte<totalBytes;currentByte++){

		command=ASCII2CMD(commandArr[currentByte]);//lookup command code

		if(command==CMD_WRITE || command==CMD_MACRO){ //get number for MACRO or value
			if(command==CMD_MACRO){	//position beyond '(' to get macro
				currentByte++;//increment the pointer
				if(currentByte==totalBytes){ //check for buffer overrun
					error++; 
					currentByte--;
				}//don't overrun the array
			}			

			numVal=bpGetASCIInumber(totalBytes, &currentByte, commandArr); //pass currentByte by reference because it has to be updated
		}

		repeatVal=bpGetRepeatVal(totalBytes, &currentByte, commandArr);  //check for repeat value

		if(command==CMD_MACRO){//check if number ends with ), check for unexpected end of sequence
			currentByte++;
			if(currentByte==totalBytes || commandArr[currentByte]!=')'){
				currentByte--;
				error++;
				//break;
			}
		}
		
		if(error){//stop processing if there are errors.
			bpWmessage(MSG_ERROR_SYNTAX);
			error=0;
			return;
			break; 
		}

		switch(command){
			case CMD_NOP://space (0x20 , 0x0a  0x0d)
				break;//do nothing...
			case CMD_AUXH: //aux output to high
				bpAuxHigh();
				break;
			case CMD_AUXL: //aux output to low
				bpAuxLow();
				break;
			case CMD_AUXIN://aux to input, read
				bpAuxRead();
				break;
			case CMD_DELAY://delay
				bpWstring(OUMSG_PS_DELAY);
				bpWbyte(repeatVal);
				bpWline(OUMSG_PS_DELAY_US);
				bpDelayUS(repeatVal);
				break;	
			#if defined( BUSPIRATEV1A) || defined( BUSPIRATEV2)
				case CMD_PWR_EN://enable any active power supplies
					BP_VREG_ON();
					bpWmessage(MSG_VREG_ON);
					modeConfig.vregEN=1;
					break;
				case CMD_PWR_DIS://disable the power supplies
					BP_VREG_OFF();
					bpWmessage(MSG_VREG_OFF);
					modeConfig.vregEN=0;
					break;
				case CMD_ADC://do an adc reading
					bpWstring(OUMSG_PS_ADC_VOLT_PROBE);	
					bpADCprobe();
					bpWline(OUMSG_PS_ADC_VOLTS);
					break;
				case CMD_ADCC://dumb voltmeter mode
					bpADCCprobe();
					break;

			#endif
			default: //send command to library
				bpCommand.cmd=command; //move to global command struct
				bpCommand.num=numVal;
				bpCommand.repeat=repeatVal;
				bpProcess();//process the command using the values in the global command struct
		}//switch
	}//for
	
	bpCommand.cmd=CMD_ENDOFSYNTAX;
	bpProcess(); //tell library it's the end of syntax, do any cleanup

}//function

//reads forward to grab repeat values following read, delay, and clock
//i must be passed by reference (&i) because we move it forward to avoid reprocessing the same bytes next time.
unsigned int bpGetRepeatVal(unsigned int totalBytes, unsigned int *currentByte, unsigned char *commandArr){
	unsigned int repeatVal=0;
	
	//check for repeat indicator, check for unexpected end of sequence
	if((*currentByte)+1<totalBytes && commandArr[*currentByte+1]==':'){//don't overrun the array
		(*currentByte)+=2;
		repeatVal=bpGetASCIInumber(totalBytes, &(*currentByte), commandArr);
		return repeatVal;
	}
	return 1;
}

//convert ASCII text input in the syntax string to a command
//CMD statements are generic and processed by each bus library
//CMD statements are defined and enumerated in base.h
unsigned char ASCII2CMD(unsigned char ASCIIcommand){
	//process as a number...
	if(ASCIIcommand>0x2F && ASCIIcommand<0x40) return CMD_WRITE;
	
	switch(ASCIIcommand){
		case 'A': return CMD_AUXH;
		case 'a': return CMD_AUXL;
		case '@': return CMD_AUXIN;
		case '&': return CMD_DELAY;
		case '(': return CMD_MACRO;
		//case ')': return CMD_ERROR; //should never get here CMD_NOP;
		case '{': return CMD_STARTR; //start bus with read=true
		case '[': return CMD_START;//start bus
		case '}'://stop bus
		case ']': return CMD_STOP;
		case 'r'://read one byte from the bus
		case 'R': return CMD_READ;
		case '!': return CMD_BIT_READ;//read bit with clock
		case '.': return CMD_BIT_PEEK;//read bit no clock
		case '/': return CMD_BIT_CLKH;//clock high
		case 0x5c:return CMD_BIT_CLKL; //(\)clock low
		case '^': return CMD_BIT_CLK; //clock pulse
		case '_': return CMD_BIT_DATL; //data low
		case '-': return CMD_BIT_DATH;//data high
		case 0x20: return CMD_NOP;//space
		case ',': return CMD_NOP;
		case 0x0a: return CMD_NOP;
		case 0x0d: return CMD_NOP;
#if defined( BUSPIRATEV1A) || defined( BUSPIRATEV2)
		case 'W':return CMD_PWR_EN;
		case 'w':return CMD_PWR_DIS;
		case 'D':return CMD_ADCC;
		case 'd':return CMD_ADC;
#endif
		default: return CMD_ERROR;
	}	
}
