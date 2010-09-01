/*
This work is licensed under the Creative Commons Attribution 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/
or send a letter to
	Creative Commons,
	171 Second Street,
	Suite 300,
	San Francisco,
	California,
	94105,
	USA.
*/

    _CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2) 
    _CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV6 & IOL1WAY_ON)

#include <p24fxxxx.h>
#include "usb_stack.h"
#include "cdc.h"

#ifdef __DEBUG
#include <usart.h>
#include <stdio.h>
#endif

void main( void ) {
#ifdef __DEBUG
	OpenUSART(	USART_TX_INT_OFF &
				USART_RX_INT_OFF &
				USART_ASYNCH_MODE &
				USART_EIGHT_BIT &
				USART_CONT_RX &
				USART_BRGH_HIGH,
				25);								// 115200:8-n-1 @ 20MHz XTAL
	stderr = _H_USART;
	fprintf(stderr, (const far rom char *) "\n\nHonken USB Stack Debug\n");
#endif
	usb_init();

	// Infinity local echo
	while(1) {
		usb_handler();
		if (DataRdyCDC())
			putcCDC(getcCDC());
	}
}

