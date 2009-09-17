/*
 * This file is part of the Bus Pirate project (buspirate.com).
 *
 * Originally written by hackaday.com <legal@hackaday.com>
 *
 * To the extent possible under law, hackaday.com <legal@hackaday.com> has
 * waived all copyright and related or neighboring rights to Bus Pirate. This
 * work is published from United States.
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include "base.h"

//this is an array of terminal text messages for various functions 
//The idea is to save space, time, and do translations
//   by consolidating all the terminal text to one place.
//For example, to print "READ:" to the user terminal from a protocol library, use:
//     bpWmessage(MSG_READ);
//  MSG_READ is defined in baseUI.h, and corresponds to position 0 in the UImessages[] array,
//  so bpWmessage() prints the text located at UImessages[0]. 
//  UImessages[0] is another define (MSG_READ_T) which holds the actual text (located in \translate\*-*.h).
//Access these messages with the corresponding commands enumerated in baseUI.h 
//The order of commands in baseUI.h and text in this list must match 
char* UImessages[]={ 
	MSG_READY_T,

	MSG_READ_T,
	MSG_READBULK_T,
	MSG_READBULK_BYTES_T,
	MSG_WRITE_T,	
	MSG_WRITEBULK_T,
	MSG_ACK_T,
	MSG_NACK_T,
	MSG_I2C_START_T,
	MSG_I2C_STOP_T,
	MSG_CS_ENABLED_T,
	MSG_CS_DISABLED_T,
	MSG_ADAPTER_T,

	MSG_BIT_READ_T,
	MSG_BIT_PEEK_T,
	MSG_BIT_NOWINPUT_T,
	MSG_BIT_CLK_T,
	MSG_BIT_CLKH_T,
	MSG_BIT_CLKL_T,
	MSG_BIT_DATH_T,
	MSG_BIT_DATL_T,

	MSG_VREG_ON_T,
	MSG_VREG_OFF_T,

	MSG_ERROR_MACRO_T,
	MSG_ERROR_MODE_T,
	MSG_ERROR_SYNTAX_T,
	MSG_ERROR_BUFFER_T,
	MSG_ERROR_NOMODE_T,
	MSG_ERROR_NOTHIZPIN_T,

	MSP_OPT_INVALID_T,
	MSG_OPT_OUTPUT_TYPE_T,
	MSG_OPT_MODESET_T,
	MSG_OPT_DISPLAYMODE_T,
	MSG_OPT_DISPLAYMODESET_T,
	MSG_OPT_PULLUP_T,
	MSG_OPT_PULLUP_OFF_T,
	MSG_OPT_PULLUP_ON_T,
	MSG_OPT_VMONITOR_T,
	MSG_OPT_BITORDER_T,
	MSG_OPT_BITORDER_MSB_T,
	MSG_OPT_BITORDER_LSB_T,
	MSG_OPT_AUXPIN_T,
	MSG_OPT_AUXPIN_AUX_T,
	MSG_OPT_AUXPIN_CS_T,
	MSG_OPT_TERMBAUD_ADJUST_T,
	MSG_OPT_UART_BAUD_T,
	MSG_OPT_CKP_T, 
	MSG_OPT_CKE_T,
	MSG_OPT_SMP_T,
	MSG_OPT_BB_SPEED_T,

	MSG_STATUS_OUTPUT_HIZ_T,
	MSG_STATUS_OUTPUT_NORMAL_T,
	MSG_STATUS_PULLUP_NOTALLOWED_T,
	MSG_STATUS_BITORDER_NOTALLOWED_T,
};

//print text in UImessages[s] array (member s) to the user terminal
//message text defined in \translations\*-*.h
void bpWmessage(unsigned char s){
    bpWstring(UImessages[s]);
}

//Array that holds help message text
//message text defined in \translations\*-*.h
char* help[]=
	{	
		HELP_TITLE_MENUS_T,
		HELP_MENUS_HELP_T,
		HELP_MENUS_VERSION_T,
		HELP_MENUS_BUSMODE_T,
		HELP_MENUS_TERMBAUD_T,
		HELP_MENUS_DISPLAYMODE_T,
		#if defined(BUSPIRATEV1A) || defined(BUSPIRATEV2)
			HELP_MENUS_VMONITOR_T,//power monitoring
		#endif
		HELP_MENUS_FREQCOUNT_T,
		HELP_MENUS_FREQGEN_T,
		HELP_MENUS_AUXPIN_T,
		HELP_MENUS_BITORDER_T,
		#ifdef BUSPIRATEV0A
			HELP_MENUS_PULLUPV0A_T,
		#elif defined(BUSPIRATEV2)
			HELP_MENUS_PULLUPV2_T,
		#elif defined(BUSPIRATEV1A) //no pullups, was power supply toggle
			HELP_MENUS_VREG_T,
		#endif
		HELP_MENUS_HDBCONVERT_T, //conversions
#if defined(BUSPIRATEV25) || defined (BUSPIRATEV3)
			HELP_MENUS_SELFTEST_T,
		#endif
		HELP_MENUS_RESET_T,
//---//Syntax
		HELP_TITLE_SYNTAX_T,
		HELP_SYNTAX_AUXPIN_T,
		#if defined(BUSPIRATEV1A) || defined(BUSPIRATEV2) //no pullups, new features
			HELP_SYNTAX_VREG_T,
			HELP_SYNTAX_VPROBE_T,
		#endif
		HELP_SYNTAX_START_T,
		HELP_SYNTAX_STOP_T,
		HELP_SYNTAX_READ_T,
		HELP_SYNTAX_WRITEBIN_T,
		HELP_SYNTAX_WRITEHEX_T,
		HELP_SYNTAX_WRTIEDEC_T,
		HELP_SYNTAX_DELIMIT_T,
		HELP_SYNTAX_DELAY_T,
		HELP_SYNTAX_REPEAT_T,
		HELP_SYNTAX_MACRO_T,
//--// bitwise
		HELP_SYNTAX_BITWISETITLE_T,
		HELP_SYNTAX_BITCLKHL_T,
		HELP_SYNTAX_BITDATHL_T,
		HELP_SYNTAX_BITPEEK_T,
		HELP_SYNTAX_BITCLK_T,
		HELP_SYNTAX_BITREAD_T,
	};

//print the help info in help[] to the user terminal
//message text defined in \translations\*-*.h
void printHelp(void){
	unsigned int i;
	for(i=0; i<(sizeof(help)/2); i++){	
		bpWstring(help[i]);
		bpWBR;	
	}		
}
