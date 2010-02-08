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

/*
//define keys used for each command
//only define the CAPATAL version, 
//  lowercase will be converted automagically
#define MENU_BUSMODE		'M'
#define MENU_DISPLAYMODE	'O'
#define MENU_PULLUPS		'P'
#define MENU_VMONITOR		'V'
#define MENU_BITORDER		'L'
#define MENU_HELP			'?'
#define MENU_FREQMEASURE	'F'
#define MENU_FREQGENERATE	'G'
#define MENU_VERSIONINFO	'I'
#define MENU_AUXPIN			'C'
#define MENU_BAUDRATE		'B'
#define MENU_RESET			'#'

//check byte c for valid menu commands, 0=no menu commands
unsigned char checkMenuCommand(unsigned char c);

*/ 

#define CMDHISTORY	15
#define BELL	0x07

#define CMDBUFLEN	256
#define CMDLENMSK	(CMDBUFLEN-1)

extern char cmdbuf[CMDBUFLEN];
extern unsigned int cmdend;
extern unsigned int cmdstart;
extern int cmderror;
//extern int currentproto;
//extern proto protos[MAXPROTO];

//prints version, used internally and in main.c
void versionInfo(void); 

void serviceuser(void);


int getint(void);
int getrepeat(void);
void consumewhitechars(void);
void changemode(void);
int cmdhistory(void);
int getnumber(int def, int max, int x);	

