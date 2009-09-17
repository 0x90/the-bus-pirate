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

//this is an ordered list of defines to access the text display messages available 
//   through the bpWmessage() function. 
//The idea is to save space, time, and do translations
//   by consolidating all the terminal text to one place.
//For example, to print "READ:" to the user terminal from a protocol library, use:
//     bpWmessage(MSG_READ);
//The text of the messages is stored in the corresponding member of the UImessages array in baseUI.c 
//The order of these commands must align with the placement in the UImessages array in baseUI.c 
enum {
	MSG_READY=0,

	MSG_READ,
	MSG_READBULK,
	MSG_READBULK_BYTES,
	MSG_WRITE,	
	MSG_WRITEBULK,
	MSG_ACK,
	MSG_NACK,
	MSG_I2C_START,
	MSG_I2C_STOP,
	MSG_CS_ENABLED,
	MSG_CS_DISABLED,
	MSG_ADAPTER,

	MSG_BIT_READ,
	MSG_BIT_PEEK,
	MSG_BIT_NOWINPUT,
	MSG_BIT_CLK,
	MSG_BIT_CLKH,
	MSG_BIT_CLKL,
	MSG_BIT_DATH,
	MSG_BIT_DATL,

	MSG_VREG_ON,
	MSG_VREG_OFF,

	MSG_ERROR_MACRO,
	MSG_ERROR_MODE,
	MSG_ERROR_SYNTAX,
	MSG_ERROR_BUFFER,
	MSG_ERROR_NOMODE,
	MSG_ERROR_NOTHIZPIN,

	MSP_OPT_INVALID,
	MSG_OPT_OUTPUT_TYPE,
	MSG_OPT_MODESET,
	MSG_OPT_DISPLAYMODE,
	MSG_OPT_DISPLAYMODESET,
	MSG_OPT_PULLUP,
	MSG_OPT_PULLUP_OFF,
	MSG_OPT_PULLUP_ON,
	MSG_OPT_VMONITOR,
	MSG_OPT_BITORDER,
	MSG_OPT_BITORDER_MSB,
	MSG_OPT_BITORDER_LSB,
	MSG_OPT_AUXPIN,
	MSG_OPT_AUXPIN_AUX,
	MSG_OPT_AUXPIN_CS,
	MSG_OPT_TERMBAUD_ADJUST,
	MSG_OPT_UART_BAUD,
	MSG_OPT_CKP, 
	MSG_OPT_CKE,
	MSG_OPT_SMP,
	MSG_OPT_BB_SPEED,

	MSG_STATUS_OUTPUT_HIZ,
	MSG_STATUS_OUTPUT_NORMAL,
	MSG_STATUS_PULLUP_NOTALLOWED,
	MSG_STATUS_BITORDER_NOTALLOWED,

};

//print text in UImessages[s] array (member s) to the user terminal
//message text defined in \translations\*-*.h
void bpWmessage(unsigned char s);

//print the help info in help[] to the user terminal
//message text defined in \translations\*-*.h
void printHelp(void);



