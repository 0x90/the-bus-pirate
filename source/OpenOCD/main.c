/*
 * usbprog - A Downloader/Uploader for AVR device programmers
 * Copyright (C) 2006 Benedikt Sauter
    //USBNDeviceManufacture("B.Sauter");
    //USBNDeviceProduct("OpenOCD Debugger");
    //USBNDeviceSerialNumber("GNU/GPL2");
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#define UNKOWN_COMMAND    0x00
#define CMD_PORT_MODE     0x01
#define CMD_FEATURE       0x02
#define CMD_READ_ADCS     0x03
#define CMD_TAP_SHIFT     0x04
#define CMD_TAP_SHIFT2    0x05
#define CMD_JTAG_SPEED    0x06
#define CMD_UART_SPEED    0x07

enum {
	FEATURE_LED=0x01,
	FEATURE_VREG=0x02,
	FEATURE_TRST=0x04,
	FEATURE_SRST=0x08,
	FEATURE_PULLUP=0x10
};

enum {
	SERIAL_NORMAL=0,
	SERIAL_FAST=1
};


//#define F_CPU 16000000
#include "base.h"
#include "UART.h"
#include "usbprogjtag.h"

//set custom configuration for PIC 24F
_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE & I2C1SEL_PRI)		// Internal FRC OSC = 8MHz
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx1) //turn off junk we don't need

void CommandAnswer(int length);
void HandleFeature(uint8_t feat, uint8_t action);
void Commands(void);

char buf[4096];

void HandleFeature(uint8_t feat, uint8_t action) {
	switch (feat) {
		case FEATURE_LED:
			BP_LEDMODE_DIR=0; //LED to output
			BP_LEDMODE=action;
			break;
		case FEATURE_VREG:
			if (action) {
				BP_VREG_ON();
			} else {
				BP_VREG_OFF();
			}
			break;
		case FEATURE_PULLUP:
			if (action) {
				BP_PULLUP_ON();
			} else {
				BP_PULLUP_OFF();
			}
			break;
		case FEATURE_TRST:
			if (action) {
				SETBIT(BIT5_WRITE, BIT5);
			} else {
				CLEARBIT(BIT5_WRITE, BIT5);
			}
			break;
		case FEATURE_SRST:
			if (action) {
				SETBIT(BIT4_WRITE, BIT4);
			} else {
				CLEARBIT(BIT4_WRITE, BIT4);
			}
			break;
		default:
			break;
	}
}

void CommandAnswer(int length) {
	int i;

	for(i = 0; i < length; i++)
		UART1TX(buf[i]);

}

/* central command parser */
void Commands(void) {
	static int i,j;

	switch(buf[0]){
		case CMD_PORT_MODE://1 extra byte
			j = 0;
			if (buf[1] == 0x01) {
				j = 0x01;
			}
			set_direction((uint8_t)j);
			set_port(0x00);
			break;
		case CMD_FEATURE: //2 extra bytes
			HandleFeature((uint8_t)buf[1],  (uint8_t)buf[2] & 0x01);
			break;
		case CMD_READ_ADCS: // send 4 bytes
			buf[0] = CMD_READ_ADCS;
			// TODO
			buf[1] = 0x12;
			buf[2] = 0x34;
			buf[3] = 0x56;
			CommandAnswer(4);
			break;
		case CMD_JTAG_SPEED: // 2 extra bytes
			// TODO
			break;
		case CMD_UART_SPEED:
			if (buf[1] == SERIAL_FAST) {
				UART1Speed(UART_FAST_SPEED);
			} else {
				UART1Speed(UART_NORMAL_SPEED);
			}

			buf[2]=UART1RX();
			buf[3]=UART1RX();
			if (((uint8_t)buf[2] != 0xAA) || ((uint8_t)buf[3] != 0x55)) {
				UART1Speed(UART_NORMAL_SPEED);
				buf[1] = SERIAL_NORMAL;
			}

			CommandAnswer(2);
			break;
		case CMD_TAP_SHIFT2:
			j = ((uint8_t)buf[1] << 8) | ((uint8_t)buf[2]); // number of bit sequences
			i = (j+7) / 8; // number of actual bytes

			// send back the header, actual data will be send in int mode
			CommandAnswer(3);

			// prepare the interrupt transfer
			buf_recv = (uint8_t*)buf;
			bytes_to_recv = i*2;
			bytes_recv = 0;
			buf_send = (uint8_t*)(buf + 2500);
			bytes_send_available = 0;
			bytes_send = 0;

			// enable RX interrupt
			IEC0bits.U1RXIE = 1;

			tap_shift_interrupt(buf_recv, buf_send, j);

			break;
		case CMD_TAP_SHIFT:
			j = ((uint8_t)buf[1] << 8) | ((uint8_t)buf[2]); // number of bit sequences
			i = (j+7) / 8;

			tap_shift((uint8_t*)&buf[3], (uint8_t*)&buf[3+i], j); // tap_shift doesn't know about packet header

			CommandAnswer(i+3);
			break;

		default:// 0 extra bytes
			// unkown command
			buf[0] = UNKOWN_COMMAND;
			buf[1] = 0x00;
			CommandAnswer(2);
	}
}


//this is adopted from USB bulk to UART serial on the Bus Pirate
//since we don't have packet transfer abilities,
//each case gathers the extra bytes it needs
//before handing off processing to the Commands function
int main(void) {
	int i,j;

	//do setup and configuration
	Initialize(); 
	InitializeUART1();

	BP_LEDMODE_DIR=0; //LED to output
	BP_LEDMODE=1;//mode LED on

	while(1){
		buf[0]=UART1RX();//get command byte
		switch(buf[0]){
		case CMD_READ_ADCS://0 extra bytes
				break;

		case CMD_PORT_MODE://1 extra byte
		case CMD_UART_SPEED:
				buf[1]=UART1RX();//get extra byte
				break;
		
		case CMD_FEATURE://2 extra bytes
		case CMD_JTAG_SPEED:
		case CMD_TAP_SHIFT2:
				buf[1]=UART1RX();//get extra byte
				buf[2]=UART1RX();//get extra byte
				IFS0bits.U1RXIF = 0;
				break;
		
		case CMD_TAP_SHIFT:
				buf[1]=UART1RX();
				buf[2]=UART1RX();
				j = ((uint8_t)buf[1] << 8) | ((uint8_t)buf[2]); //get data packet size
				j = (j >> 3) + ((j & 0x07)?1:0);
				// j - number of bytes for TMS and TDI
				for(i=0;i<j*2;i++) { // we need *2
					buf[3+i]=UART1RX();
				}
				break;
			default:// 0 extra bytes
				break;
		}
		Commands();//process first command byte, gather remaining bytes wihtin this function
	}
}



