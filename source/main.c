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
#include "busPirateCore.h"
#include "procMenu.h"
//#include "procSyntax.h"
#include "selftest.h"
//#include "binIO.h"
//#include "SUMP.h"
#include "basic.h"

#if defined (BUSPIRATEV2) || defined (BUSPIRATEV1A)
//set custom configuration for PIC 24F (now always set in bootloader page, not needed here)
//_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE & I2C1SEL_PRI)		// Internal FRC OSC = 8MHz
//_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx1) //turn off junk we don't need
#elif defined (BUSPIRATEV4)
	_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2) 
	_CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSDCMD & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV3 & IOL1WAY_ON & PLL_96MHZ_ON)
#endif

unsigned char irqFlag=0;
//void _T1Interrupt(void);
void ISRTable(); //Pseudo function to hold ISR remap jump table

static unsigned char  __attribute__ ((section (".bss.end"))) _buffer[TERMINAL_BUFFER];
struct _bpConfig bpConfig = { .terminalInput = _buffer }; //holds persistant bus pirate settings (see buspiratecore.h)
struct _modeConfig modeConfig; //holds mode info, cleared between modes
struct _command bpCommand; //holds the current active command so we don't ahve to put so many variables on the stack

void Initialize(void);

unsigned char binmodecnt=0;//, terminalInput[TERMINAL_BUFFER];

#pragma code
//this loop services user input and passes it to be processed on <enter>

int main(void){

	Initialize();//setup bus pirate

//wait for the USB connection to enumerate
#if defined (BUSPIRATEV4)

    #if defined(USB_INTERRUPT)
        USBDeviceAttach();
    #endif

    while(1){
    	#if defined(USB_POLLING)
        USBDeviceTasks();
		#endif

    	if(((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1))) continue;
		break;
	}	

     //enable timer 1 with interrupts, 
     //service with function in main.c.
     IEC0bits.T1IE = 1;
     IFS0bits.T1IF = 0;
     PR1 = 0xFFFF;
     T1CON = 0x8010;
#endif

	serviceuser();

	return 0;
}

//bus pirate initialization
//setup clock, terminal UART, pins, LEDs, and display version info
void Initialize(void){
    
#if defined (BUSPIRATEV2) || defined (BUSPIRATEV1A)
	CLKDIVbits.RCDIV0=0; //clock divider to 0
#elif defined (BUSPIRATEV4)
    CLKDIV = 0x0000;    // Set PLL prescaler (1:1)
#endif 
	AD1PCFG = 0xFFFF;                 // Default all pins to digital
	OSCCONbits.SOSCEN=0;	

	//set pin configuration using peripheral pin select
#if defined (BUSPIRATEV2) || defined (BUSPIRATEV1A)
	BP_TERM_RX=BP_TERM_RX_RP;   //Inputs UART1 RX RPINR18bits.U1RXR=4;
	BP_TERM_TX_RP=BP_TERM_TX; 		// Outputs UART1 TX RPOR1bits.RP3R=U1TX_IO;
#endif 

	//put startup values in config (do first)
	bpConfig.termSpeed=8;//default PC side port speed, startup in 115200, or saved state (later)....
	bpConfig.displayMode=HEX;

	bpInit();//put startup values in config (do first)clean up, exit in HI-Z
		
#if defined (BUSPIRATEV2) || defined (BUSPIRATEV1A)
	InitializeUART1(); //init the PC side serial port
#elif defined (BUSPIRATEV4)
    USBDeviceInit();//setup usb
	usbbufflush();	//setup the USB byte buffer
#endif 


	#if defined (BUSPIRATEV2)
		//find the Bus Pirate revision
		//pullup on, do it now so it can settle during the next operations
		CNPU1bits.CN6PUE=1;
	#endif
#ifndef BUSPIRATEV4
	// Get the chip type and revision
	bpConfig.dev_type = bpReadFlash(DEV_ADDR_UPPER, DEV_ADDR_TYPE);
	bpConfig.dev_rev = bpReadFlash(DEV_ADDR_UPPER, DEV_ADDR_REV);
#endif

	#if defined (BUSPIRATEV2)
		//now check the revision
		//if 0 3b, else v2go, or v3
		if(PORTBbits.RB2==1){
			bpConfig.HWversion='a';
		}else{
			bpConfig.HWversion='b';
		}
		//pullup off
		CNPU1bits.CN6PUE=0;
	#else
		bpConfig.HWversion=0;
	#endif

	bpConfig.quiet=0;		// turn output on (default)
	modeConfig.numbits=8;
#ifdef BP_USE_BASIC
	initpgmspace();
#endif

	TBLPAG=0; // we need to be in page 0 (somehow this isn't set)

#ifndef BUSPIRATEV4
	bpWBR; 	//send a line feed
	versionInfo();//prints hardware and firmware version info (base.c)
#endif

}




//Interrupt Remap method 2:  Using Goto and jump table
/*
void __attribute__ ((interrupt,no_auto_psv)) _T1Interrupt(){
	IFS0bits.T1IF = 0;
	IEC0bits.T1IE = 0;
	PR1 = 0xFFFF;
	T1CON = 0;
	irqFlag=1;
	
}
*/

#ifdef BUSPIRATEV4
//
//
//the stack calls these, if they aren't here we get errors. 
//
//
void USBCBSuspend(void){}
void USBCBWakeFromSuspend(void){}
void USBCB_SOF_Handler(void){}
void USBCBErrorHandler(void){}
void USBCBCheckOtherReq(void){USBCheckCDCRequest();}//end
void USBCBStdSetDscHandler(void){}//end
void USBCBInitEP(void){CDCInitEP();}
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size){
    switch(event){
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER:
            Nop();
            break;
        default:
            break;
    }      
    return TRUE; 
}
#endif


