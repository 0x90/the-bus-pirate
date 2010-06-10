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

/*
// just to keep the linker happy (for now) jtag and lcd only uses them
unsigned int bpUserNumberPrompt(unsigned int maxBytes, unsigned int maxValue, unsigned int defValue)
{	return 0;
}
unsigned int bpGetUserInput(unsigned int *currentByte, unsigned int maxBytes, unsigned char *terminalInput )
{	return 0;
}

*/

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

// userfriendly printing of looooonng ints
void bpWlongdecf(unsigned long l)
{	unsigned long int temp;
	int mld, mil;

	mld=0; mil=0; temp=0;

	if(l>=1000000)
	{	temp=l/1000000;
		bpWintdec(temp);
		UART1TX(',');
		l%=1000000;
		if(l<1000) bpWstring("000,");
		mld=1;
		mil=1;
	}
	if(l>=1000)
	{	temp=l/1000;
		if(temp>100)
		{	bpWintdec(temp);
		}
		else if(mld)
		{	if(temp>10)
			{	UART1TX('0');		// 1 leading zero
			}
			else
			{	bpWstring("00");
			}
			bpWintdec(temp);
		}
		else bpWintdec(temp);
		UART1TX(',');
		l%=1000;
		mil=1;
	}	
	if(l>100)
	{	bpWintdec(l);
	}
	else if(mil)
	{	if(l>10)
		{	UART1TX('0');		// 1 leading zero
		}
		else
		{	bpWstring("00");
		}
		bpWintdec(l);
	}
	else bpWintdec(l);
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

			// the precision of 1 bit is 0.006V ( 6.6 V / 1024) so we could display two digits!! Whoot
			// too bad we depend on some cheapy 3.3v regulator ;)
			// first digit :)
	v = (v - (int) v);				//Remove integer part... fval=0.456789
 	v *= 10;
	c = (char) v;					//convert to long integer - ltemp=45678
 	bpWdec(c);

			// second digit :) whoot!!
	v=(v-(int)v);
	v*=10;
	c=(char) v;
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
void UART1TX(char c)
{	if(bpConfig.quiet) return;
	while(U1STAbits.UTXBF == 1); //if buffer is full, wait
    U1TXREG = c;
}

void UART1Speed(unsigned char brg) {
	U1BRG = brg;
}

/* interrupt transfer related stuff */
unsigned char *UART1RXBuf;
unsigned int UART1RXToRecv;
unsigned int UART1RXRecvd;
unsigned char *UART1TXBuf;
unsigned int UART1TXSent;
unsigned int UART1TXAvailable;

void UART1TXInt() {
	if (IEC0bits.U1TXIE == 1)
		return; 	if (UART1TXAvailable == UART1TXSent)
		return; 	while(U1STAbits.UTXBF == 1); //if buffer is full, wait 	IFS0bits.U1TXIF = 0;
	IEC0bits.U1TXIE = 1;
	U1TXREG = UART1TXBuf[UART1TXSent];
}

// UART1 ISRs
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
	UART1RXBuf[UART1RXRecvd] = U1RXREG;
	UART1RXRecvd++;
	if (UART1RXRecvd == UART1RXToRecv) {
		// disable UART1 RX interrupt 
		IEC0bits.U1RXIE = 0;
	}
	IFS0bits.U1RXIF = 0;
} void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
	UART1TXSent++;
	if (UART1TXSent == UART1TXAvailable) {
		// if everything is sent  disale interrupts
		IEC0bits.U1TXIE = 0;
	} else {
		// feed next byte
		U1TXREG = UART1TXBuf[UART1TXSent];	
	} 	IFS0bits.U1TXIF = 0;
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
