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
#include "baseIO.h"

#include "busPirateCore.h"//need access to bpConfig
extern struct _bpConfig bpConfig; //holds persistant bus pirate settings (see base.h) need hardware version info

//get a response value from 1-i, repeats until valid
unsigned int bpUserNumberPrompt(unsigned int maxBytes, unsigned int maxValue, unsigned int defValue){
	#define USER_PROMPT_MAX_BYTES 12
	static unsigned char termIn[USER_PROMPT_MAX_BYTES];
	unsigned int userNum, cntByte=0, curByte=0;
	
	if(defValue>0){//use a default value on enter
		UART1TX('(');
		bpWintdec(defValue);
		bpWstring(") ");
	}
	UART1TX('>');

	while(1){
		cntByte=0;//counts the bytes RX'd as they come into bpGetUserInput
		while(bpGetUserInput(&cntByte, maxBytes, termIn)==0); //wait for user input
		if(cntByte==0 && defValue>0) return defValue; //return default if default valid and greater than 0
		curByte=0;//counter for bpGetASCIInumber, must be 0'd
		userNum=bpGetASCIInumber(cntByte, &curByte, termIn); //convert to number
		if(userNum>0 && userNum<=maxValue) return userNum; //if valid, return value
		//bpWstring("INVALID, TRY AGAIN>");
		bpWmessage(MSP_OPT_INVALID);
	}
}

//move any data from buffer to array, use supplied counter
//returns 1 when <enter> is detected
//takes care of returning valid characters, and manages backspace
unsigned int bpGetUserInput(unsigned int *currentByte, unsigned int maxBytes, unsigned char *terminalInput ){
	unsigned char inbuf;

	while(UART1RXRdy()){
		inbuf=UART1RX();

		switch(inbuf){
			case 0x00://binary mode trigger
				return 0xff;
			case 0x02://SUMP mode trigger
				return 0xfe;
			//case 0x1b://escape, get 2 or 3 more bytes
				//get 2 bytes, ABCD are arrow keys, A is up
				//break;
			case 0x0A://enter
			case 0x0D:	
				bpWBR;
				return 1;
				break;
			case 0x08://backspace...
				if(*currentByte>0){
					(*currentByte)--;
					UART1TX(inbuf);//echo back
				}
				break;
			default:
				//don't overrun the buffer
				//only get characters space (ASCII32) to ~ (ASCII126) 
				if((*currentByte<maxBytes) && (inbuf > 31) && (inbuf <127)){
					terminalInput[*currentByte]=inbuf;
					UART1TX(inbuf);//echo back
					(*currentByte)++;
				}
				break;
		}//switch
	}//if RX data available
	return 0;
}

//scans through the text array and puts a numeric string of any sort into a second array
//second array is sent to ASCII2BYTE for conversion to an actual value
unsigned int bpGetASCIInumber(unsigned int totalBytes, unsigned int *currentByte, unsigned char *commandArr){
	unsigned char cnt=0;
	unsigned char numberArr[12];

	numberArr[1]=0;//force decimal interpretation of DEC #s with only one digit...

	//loop forward and suck up the whole number string into numberArr
	while(1){
		if((*currentByte)==totalBytes){(*currentByte)--;break;}//break at the end of data

		//is it numeric character (0-9, a-f, A-F, x,h,b)
		if(((commandArr[*currentByte]>0x2F && commandArr[*currentByte]<0x3A) || 
			(commandArr[*currentByte]>0x40 && commandArr[*currentByte]<0x47) ||
			(commandArr[*currentByte]>0x60 && commandArr[*currentByte]<0x67) || 
			commandArr[*currentByte]=='x' || commandArr[*currentByte]=='h' || 
			commandArr[*currentByte]=='X' || commandArr[*currentByte]=='H') ){
				numberArr[cnt]=commandArr[*currentByte];
				cnt++;					
				(*currentByte)++;		
		}else{//non-number, end of number sequence
			(*currentByte)--;//clean up
			break;
		}

	}//while

	return (ASCII2INT(cnt, numberArr)); //convert ASCII number string to byte

}

//return byte number (DEC, HEX, BIN) from ASCII text
//proper format: 0b (BIN), 0x or 0h (HEX), 0 or other (DEC)
// @b - number of chars in text
// @numberArr - ASCII string in an array to decode
//is the first digit a valis ASCII number? (0b,0x,0h,01,10,20,30,etc...)
unsigned int ASCII2INT(unsigned char totalDigits, unsigned char *numberArr){
	unsigned int value=0;
	unsigned char cnt;

	//determine the type of number (DEC, HEX, BIN) and decode it from ASCII text
	switch(numberArr[1]){
		case 'x'://HEX
		case 'h':
			//30-39 a-f41-46, A-F61-66 
			for(cnt=2;cnt<totalDigits;cnt++){
				value*=0x10;
				if(numberArr[cnt]<0x40){
					value+=(numberArr[cnt]-0x30);
				}else if (numberArr[cnt]<0x47){
					value+=(numberArr[cnt]-0x37);
				}else{
					value+=(numberArr[cnt]-0x57);
				}
			}
			break;
		case 'b'://BIN
			for(cnt=2;cnt<totalDigits;cnt++){
				value<<=1;	
				if(numberArr[cnt]=='1')value|=1;
			}
			break;
		default://DEC
			for(cnt=0;cnt<totalDigits;cnt++){
				value*=10;
				value+=(numberArr[cnt]-0x30);
			}
			break;
	}//switch
	return value;
}

//echo ASCII 0 or 1, given unsigned char c
void bpEchoState(unsigned char c){
		UART1TX(c+0x30);
}

//
//
//functions for terminal output of various types and lengths
//
//

//Write a string to the user terminal
void bpWstring(char *s){
    char c;
    while((c = *s++)) UART1TX(c);
}

//write a string to the user terminal, finish with a line break
void bpWline(char *s){
    char c;
    while((c = *s++)) UART1TX(c);
	UART1TX(0x0d);
	UART1TX(0x0a);

}

//output an 8bit/byte binary value to the user terminal
void  bpWbin(unsigned char c){
	unsigned char i,j;
	j=0b10000000;

	bpWstring("0b");

	for(i=0;i<8;i++){
		if(c&j){
			UART1TX('1');
		}else{
			UART1TX('0');
		}
		j>>=1;
	}

}

//output an 32bit/long decimal value to the user terminal
void  bpWlongdec(unsigned long l){
    unsigned long c,m;
	unsigned char j,k=0;

	c=100000000;
	for(j=0; j<8; j++){
		m=l/c;
		if(k || m){
			UART1TX(m + '0');
		    l = l - (m*c);
			k=1;
		}
		c/=10;	
	}
    UART1TX(l + '0');

}

//output an 16bit/integer decimal value to the user terminal
void  bpWintdec(unsigned int i){
    unsigned int c,m;
	unsigned char j,k=0;

	c=10000;
	for(j=0; j<4; j++){
		m=i/c;
		if(k || m){
			UART1TX(m + '0');
		    i = i - (m*c);
			k=1;
		}
		c/=10;	
	}
    UART1TX(i + '0');
}

//output an 8bit/byte decimal value to the user terminal
void  bpWdec(unsigned char c){
    unsigned char d,j,m, k=0;

	d=100;
	for(j=0; j<2; j++){
		m=c/d;
		if(k || m){
			UART1TX(m + '0');
		    c = c - (m*d);
			k=1;
		}
		d/=10;	
	}
    UART1TX(c + '0');
}

//output an 8bit/byte hex value to the user terminal
const unsigned char HEXASCII[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
void bpWhex(unsigned int c){
    unsigned int b;

	bpWstring("0x");
    b = (c>>4) & 0x0F;
    UART1TX(HEXASCII[b]);
    b = c & 0x0F;
    UART1TX(HEXASCII[b]);
    return;
}

void bpWhexBuf(unsigned int c){
    unsigned int b;

	UARTbuf('0');
	UARTbuf('x');
    b = (c>>4) & 0x0F;
    UARTbuf(HEXASCII[b]);
    b = c & 0x0F;
    UARTbuf(HEXASCII[b]);
    return;
}

// output a 16bit hex value to the user terminal
void bpWinthex(unsigned int c) {
    unsigned int b;
    
    bpWstring("0x");
    b = (c>>12) & 0x0F;
    UART1TX(HEXASCII[b]);
    b = (c>>8) & 0x0F;
    UART1TX(HEXASCII[b]);
    b = (c>>4) & 0x0F;
    UART1TX(HEXASCII[b]);
    b = c & 0x0F;
    UART1TX(HEXASCII[b]);
    return;
}


#if defined( BUSPIRATEV1A) || defined (BUSPIRATEV2)
//convert a float number to a x.1 decimal (max 255.9 because of char type...)
//extra attention is needed for leading 0s with more than one trailing decimal place
//we just use one and ignore....
void bpWvolts(unsigned int a){
	float v;
	unsigned char c;

	v=(float)((int)a/155.1515);//precalculated value for equal value resistor (/2)
								// adc/1024 *3.3 *2 = adc/155.1515

	c = (char) v;			//convert double to long	- ltemp=123

	bpWdec(c);
											
	UART1TX('.');

	v = (v - (int) v);               //Remove integer part... fval=0.456789
				
	v *= 10;
									
	c = (char) v;		//convert to long integer - ltemp=45678
	bpWdec(c);
}
#endif

//
//
// Base user terminal UART functions
//
//

//is data available in RX buffer?
//#define UART1RXRdy() U1STAbits.URXDA
unsigned char UART1RXRdy(void){
    return U1STAbits.URXDA;
}

//get a byte from UART
unsigned char UART1RX(void){

    while(U1STAbits.URXDA == 0);
	return U1RXREG;
}

//add byte to buffer, pause if full
//uses PIC 4 byte UART FIFO buffer
void UART1TX(char c){
	while(U1STAbits.UTXBF == 1); //if buffer is full, wait
    U1TXREG = c;
}

//new UART ring buffer
//uses user terminal input buffer to buffer UART output
//any existing user input will be destroyed
//best used for binary mode and sniffers
static struct _UARTRINGBUF{
	unsigned int writepointer;
	unsigned int readpointer;
}ringBuf;

void UARTbufSetup(void){
	//setup ring buffer pointers
	ringBuf.readpointer=0;
	ringBuf.writepointer=1;
}

void UARTbuf(char c){
	if(ringBuf.writepointer==ringBuf.readpointer){
		BP_LEDMODE=0;//drop byte, buffer full LED off
	}else{
		bpConfig.terminalInput[ringBuf.writepointer]=c;
		ringBuf.writepointer++;
		if(ringBuf.writepointer==TERMINAL_BUFFER) ringBuf.writepointer=0; //check for wrap
	}
}

void UARTbufService(void){
	unsigned int i;

	i=ringBuf.readpointer+1;
	if(i==TERMINAL_BUFFER) i=0; //check for wrap
	if(i==ringBuf.writepointer) return; //buffer empty, 

	if(U1STAbits.UTXBF == 0){//free slot, move a byte to UART
		ringBuf.readpointer=i;
		U1TXREG=bpConfig.terminalInput[ringBuf.readpointer];
	}
}

// Read the lower 16 bits from programming flash memory
unsigned int bpReadFlash(unsigned int page, unsigned int addr)
{
	TBLPAG = page;
	return (__builtin_tblrdh(addr) << 8) | __builtin_tblrdl(addr);
}
