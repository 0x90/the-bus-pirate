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
//manage user terminal input
unsigned int bpUserNumberPrompt(unsigned int maxBytes, unsigned int maxValue, unsigned int defValue);

//manage user terminal input
unsigned int bpGetUserInput(unsigned int *currentByte, unsigned int maxBytes, unsigned char *terminalInput );

//reads forward to grab ASCII number string, returns byte value
unsigned int bpGetASCIInumber(unsigned int totalBytes, unsigned int *currentByte, unsigned char *commandArr);

//convert ASCII number string (HEX, BIN, DEC) to INT value
unsigned int ASCII2INT(unsigned char totalDigits, unsigned char *numberArr);

//echo ASCII 0 or 1, given unsigned char c
//#define bpEchoState(c) UART1TX(c+0x30) 
void bpEchoState(unsigned char c);

//
//
//functions for terminal output of various types and lengths
//
//

//Write a string to the user terminal
void bpWstring(char *s);

//write a string and line break to the user terminal
void bpWline(char *s); 

//output an 8bit/byte hex value to the user terminal
void bpWhex(unsigned int c);

//output an 16bit/2byte hex value to the user terminal
void bpWinthex(unsigned int c); 

//output an 8bit/byte binary value to the user terminal
void bpWbin(unsigned char c);

//output an 8bit/byte decimal value to the user terminal
void bpWdec(unsigned char c);

//output an 16bit/integer decimal value to the user terminal
void bpWintdec(unsigned int i);

//output an 32bit/long decimal value to the user terminal
void bpWlongdec(unsigned long l);

//print a float number to the user terminal 
// (special to show volts to a single digit for ADC measurements)
void bpWvolts(unsigned int a);

//pseudofuncion break sequences
#define bpBR UART1TX('\x0D');UART1TX('\x0A') //macro for line break
#define bpWBR bpBR
#define bpSP UART1TX(' ') //macro for space
#define bpWchar(x) UART1TX(x)

//
//
// Base user terminal UART functions
//
//

//is byte available in RX buffer?
unsigned char UART1RXRdy(void); 

//get a byte from UART
unsigned char UART1RX(void); 

//add byte to buffer, pause if full
//uses PIC 4 byte UART FIFO buffer
void UART1TX(char c); 

//
//
// Ring buffer for UART
//
//
void UARTbufService(void);
void UARTbufSetup(void);
void UARTbuf(char c);
void bpWhexBuf(unsigned int c); //write a hex value to ring buffer

//
// Hardware functions and definitions
//

#define PIC_REV_A3	0x3003
#define PIC_REV_B4	0x3042
#define PIC_REV_B5	0x3043

// Read the lower 16 bits from programming flash memory
unsigned int bpReadFlash(unsigned int page, unsigned int addr);
