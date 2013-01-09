/*
** Made by fabien le mentec <texane@gmail.com>
** 
** Started on  Sun Sep 20 14:08:30 2009 texane
** Last update Tue Nov 17 19:52:04 2009 texane
*/
#include "types.h"
#include "stk500.h"
#include "base.h"
#include "UART.h"

//set custom configuration for PIC 24F
_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE & I2C1SEL_PRI)		// Internal FRC OSC = 8MHz
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx1) //turn off junk we don't need

//unsigned int userReset  __attribute__ ((space(prog),section(".init"))) = 0xC04 ;
//unsigned char timeout  __attribute__ ((space(prog),section(".init"))) = 0x00 ;
void Initialize(void);
void serial_write(unsigned char* s, unsigned int len);
static int read_uint8(unsigned char* c, unsigned char do_timeout);

/* main */
int main(void){
	stk500_error_t error;
	unsigned int isize;
	unsigned int osize;
	unsigned char do_timeout;
	unsigned char buf[STK500_BUF_MAX_SIZE];

	Initialize();
	stk500_setup();
	
	while (1){
		/* process new command */
		
		error = STK500_ERROR_MORE_DATA;
		
		do_timeout = 0;
		
		isize = 0;
		osize = 0;
		
		while (error == STK500_ERROR_MORE_DATA){
			if (read_uint8(buf + isize, do_timeout)==0){//try to get a byte
				/* has timeouted */
				stk500_timeout(buf, isize, &osize);//reset the variables
				error = STK500_ERROR_SUCCESS; //must be some message to send below
				break;
			}
			
			do_timeout = 1; //next byte with timeout
			
			++isize; //increment buffer insize
			
			error = stk500_process(buf, isize, &osize); //check to see if this is a complete command
		}

		
		if ((error == STK500_ERROR_SUCCESS) && (osize))//send any reply bytes
			serial_write(buf, osize);
	}
}

/* serial helper routines */
static int read_uint8(unsigned char* c, unsigned char do_timeout){
	int timeout;
	
	timeout=0xffff;
	
	while (UART1RXRdy() == 0){//wait for a byte in buffer
		timeout--;		
		if (do_timeout && (timeout==0)){
			return 0;
		}
	}

	*c=UART1RX();	
	//UART1TX(*c);//debug
	return 1;
}

void serial_write(unsigned char* s, unsigned int len){
  unsigned int i;

  for (i = 0; i < len; ++i)
    UART1TX(s[i]);
}


//bus pirate initialization
//setup clock, terminal UART, pins, LEDs, and display version info
void Initialize(void){

	CLKDIVbits.RCDIV0=0; //clock divider to 0
	AD1PCFG = 0xFFFF;                 // Default all pins to digital
	OSCCONbits.SOSCEN=0;	

	BP_LEDMODE_DIR=0; //MODE LED output

	IODIR|=(AUX+MOSI+CLK+MISO+CS);//AUX, MOSI, CLK, MISO, CS pins to input
	//IOLAT&=(~AUX+MOSI+CLK+MISO+CS); //low pin
	#ifdef BUSPIRATEV2
	BP_PULLUP_OFF();	//disable pullups
	#endif
	BP_VREG_OFF();		//disable vreg

	//set pin configuration using peripheral pin select
	BP_TERM_RX=BP_TERM_RX_RP;   //Inputs UART1 RX RPINR18bits.U1RXR=4;
	BP_TERM_TX_RP=BP_TERM_TX; 		// Outputs UART1 TX RPOR1bits.RP3R=U1TX_IO;
	InitializeUART1(); //init the PC side serial port

}

