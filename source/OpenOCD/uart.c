//
//
// Base user terminal UART functions
//
//
#include "base.h"

uint8_t *buf_recv;
uint16_t bytes_recv;
uint16_t bytes_to_recv;

uint8_t *buf_send;
uint16_t bytes_send;
uint16_t bytes_send_available;

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

void UART1Speed(uint8_t brg) {
	U1BRG = brg;
} 

//Initialize the terminal UART
void InitializeUART1(void){
	//setup UART
	U1BRG = 34;//34@32mhz=115200
	U1MODE = 0;
	U1MODEbits.BRGH = 1;
	U1STA = 0;
	U1MODEbits.UARTEN = 1;
	U1STAbits.UTXEN = 1;
	IFS0bits.U1RXIF = 0;
}

void UART1TX_Int() {
	if (IEC0bits.U1TXIE == 1)
		return;

	if (bytes_send_available == bytes_send)
		return;

	while(U1STAbits.UTXBF == 1); //if buffer is full, wait

	IFS0bits.U1TXIF = 0;
	IEC0bits.U1TXIE = 1;
	U1TXREG = buf_send[bytes_send];
}


void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
	buf_recv[bytes_recv] = U1RXREG;
	bytes_recv++;
	if (bytes_recv == bytes_to_recv) {
		// disable UART1 RX interrupt 
		IEC0bits.U1RXIE = 0;
	}
	IFS0bits.U1RXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
	bytes_send++;
	if (bytes_send == bytes_send_available) {
		// if everything is sent  disale interrupts
		IEC0bits.U1TXIE = 0;
	} else {
		U1TXREG = buf_send[bytes_send];	
	}
	IFS0bits.U1TXIF = 0;
}
