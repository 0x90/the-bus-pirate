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

#define UNKOWN_COMMAND	0x00
#define PORT_DIRECTION	0x01
#define PORT_SET	0x02
#define PORT_GET	0x03
#define PORT_SETBIT	0x04
#define PORT_GETBIT	0x05
#define WRITE_TDI	0x06
#define READ_TDO	0x07
#define WRITE_AND_READ	0x08
#define WRITE_TMS	0x09
#define WRITE_TMS_CHAIN	0x0A

//#define F_CPU 16000000
#include "base.h"
#include "UART.h"
#include "usbprogjtag.h"

//set custom configuration for PIC 24F
_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE & I2C1SEL_PRI)		// Internal FRC OSC = 8MHz
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx1) //turn off junk we don't need
unsigned int userReset  __attribute__ ((space(prog),section(".init"))) = 0xC04 ;//bootloader stuff
unsigned char timeout  __attribute__ ((space(prog),section(".init"))) = 0x00 ;

void CommandAnswer(int length);
void Commands(void);

char answer[64];
char buf[1024];//max packet should be 320 bytes, but why not 1024?

void CommandAnswer(int length){
  int i;

  for(i = 0; i < length; i++)
    UART1TX(answer[i]);
}

/* central command parser */
void Commands(void){
  int i;
  switch(buf[0]){
    case PORT_DIRECTION://1 extra byte
      set_direction((uint8_t)buf[1]);
    break;
    case PORT_SET://1 extra byte
      set_port((uint8_t)buf[1]);
    break;
    case PORT_GET://0 extra bytes
      answer[0] = PORT_GET; 
      answer[1] = get_port();
      CommandAnswer(2);
    break;
    case PORT_SETBIT://2 extra bytes
      set_bit((uint8_t)buf[1],(uint8_t)buf[2]);
    break;
    case PORT_GETBIT://1 extra bytes
      answer[0] = PORT_GETBIT; 
      answer[1] = (char)get_bit((uint8_t)buf[1]);
      CommandAnswer(2);
    break;
    
    case WRITE_TDI:// buf[1]+buf[2] extra bytes?????
      write_tdi(buf,((uint8_t)buf[1]*256)+(uint8_t)buf[2]);	// size = numbers of byte not bits!!! round up
      // tck 0 tms 0 tdi 0
      CLEARBIT(BIT2_WRITE,BIT2);  // clk
      CLEARBIT(BIT1_WRITE,BIT1);  // tdi
      CLEARBIT(BIT3_WRITE,BIT3);  // tms
      
      // tck 1 tms 0 tdi 0
      SETBIT(BIT2_WRITE,BIT2);  // clk
    break;
 
    case WRITE_TMS://1 extra bytes
      write_tms((uint8_t)buf[1]);
    break;
   
    case WRITE_TMS_CHAIN://buf[1] extra bytes
      for(i=0;i<(int)buf[1];i++){
		write_tms((uint8_t)buf[2+i]);
		asm("nop");
		asm("nop");
      }
    break;

    case READ_TDO:// buf[1]+buf[2] extra bytes?????
      read_tdo(buf,((uint8_t)buf[1]*256)+(uint8_t)buf[2]);	// size = numbers of byte not bits!!! round up
      #if 1
      // tck 0 tms 0 tdi 0
      CLEARBIT(BIT2_WRITE,BIT2);  // clk
      CLEARBIT(BIT1_WRITE,BIT1);  // tdi
      CLEARBIT(BIT3_WRITE,BIT3);  // tms
      
      // tck 1 tms 0 tdi 0
      SETBIT(BIT2_WRITE,BIT2);  // clk
      #endif
      for(i=0;i<64;i++)
		answer[i]=buf[i];
      CommandAnswer(64);
    break;

    case WRITE_AND_READ:// buf[1]+buf[2] extra bytes?????
      write_and_read(buf,((uint8_t)buf[1]*256)+(uint8_t)buf[2]);	// size = numbers of byte not bits!!! round up
      
      #if 1
      // tck 0 tms 0 tdi 0
      CLEARBIT(BIT2_WRITE,BIT2);  // clk
      CLEARBIT(BIT1_WRITE,BIT1);  // tdi
      CLEARBIT(BIT3_WRITE,BIT3);  // tms
      
      // tck 1 tms 0 tdi 0
      SETBIT(BIT2_WRITE,BIT2);  // clk
      #endif
      for(i=0;i<64;i++)
		answer[i]=buf[i];
      CommandAnswer(64);
    break;
    
    default:// 0 extra bytes
      // unkown command
      answer[0] = UNKOWN_COMMAND; 
      answer[1] = 0x00; 
      CommandAnswer(2);
  }


}


//this is adopted from USB bulk to UART serial on the Bus Pirate
//		since we don't have packet transfer abilities, 
//      each case gathers the extra bytes it needs
//		before handing off processing to the Commands function
int main(void){
	int i,j;

	//do setup and configuration
	Initialize(); 
	InitializeUART1();
	BP_LEDMODE_DIR=0; //LED to output
	BP_LEDMODE=1;//mode LED on

    while(1){
		buf[0]=UART1RX();//get command byte
  		switch(buf[0]){
    		case PORT_DIRECTION://1 extra byte
    		case PORT_SET://1 extra byte
    		case PORT_GETBIT://1 extra bytes
    		case WRITE_TMS://1 extra bytes
				buf[1]=UART1RX();//get extra byte
				break;
    		case PORT_SETBIT://2 extra bytes
				buf[1]=UART1RX();//get extra byte
				buf[2]=UART1RX();//get extra byte
				break;
    		case WRITE_TMS_CHAIN://buf[1] extra bytes    
				buf[1]=UART1RX();//get data length
			   	for(i=0;i<(int)buf[1];i++){
					buf[2+i]=UART1RX();
				}
				break;
    		case WRITE_TDI:// buf[1]+buf[2] extra bytes?????
			case READ_TDO:// buf[1]+buf[2] extra bytes?????
    		case WRITE_AND_READ:// buf[1]+buf[2] extra bytes?????
				buf[1]=UART1RX();//get extra byte
				buf[2]=UART1RX();//get extra byte
				j=((uint8_t)buf[1]*256)+(uint8_t)buf[2]; //get data packet size
			   	for(i=0;i<j;i++){
					buf[2+i]=UART1RX();
				}
				break;
    		case PORT_GET://0 extra bytes
			default:// 0 extra bytes
				break;
  		}
		Commands();//process first command byte, gather remaining bytes wihtin this function
	}

}


