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
#include "AUXpin.h"
#include "busPirateCore.h"
#include "procMenu.h" //need our public versionInfo() function
#if defined(BUSPIRATEV25) || defined (BUSPIRATEV3)
	#include "selftest.h"
#endif
#include "binIO.h"
#include "SUMP.h"
#include "basic.h"

extern struct _bpConfig bpConfig;
extern struct _modeConfig modeConfig;
extern struct _command bpCommand;
extern proto protos[MAXPROTO];

void walkdungeon(void);
//void walkdungeon(void) {}

void setMode(void); //change protocol/bus mode
void setDisplayMode(void); //user terminal number display mode dialog (eg HEX, DEC, BIN, RAW)
void setPullups(void); //pullup resistor dialog
void measureSupplyVoltages(void); //display supply voltage measurements for 3.3, 5, and vpullup
void setBitOrder(void); //LSB/MSB menu for modes that allow it
void setAltAuxPin(void); //configure AUX syntax to control AUX or CS pin
void setBaudRate(void); //configure user terminal side UART baud rate
void statusInfo(void); //display properties of the current bus mode (pullups, vreg, lsb, output type, etc)
void convert(void); //convert input to HEX/DEC/BIN
void pinDirection(unsigned int pin);
void pinState(unsigned int pin);
void pinStates(void);


//global vars    move to bpconfig structure?
char cmdbuf[CMDBUFLEN];
unsigned int cmdend;
unsigned int cmdstart;
int cmderror;


//int currentproto;	// port to the other way :)

#define USRMACROS	5
#define USRMACROLEN	32

char usrmacros[USRMACROS][USRMACROLEN];
int usrmacro;


void serviceuser(void)
{	int cmd, stop;
	int newstart;
	int oldstart;
	int sendw;
	int repeat;
	unsigned char c;
	int temp;
	int binmodecnt;

	// init
	cmd=0;
	cmdstart=0;
	cmdend=0;
	bpConfig.busMode=0;
	cmderror=0;							// we don;t want to start with error do we?
	binmodecnt=0;

	for(repeat=0; repeat<USRMACROS;repeat++)
	{	for(temp=0; temp<32; temp++)
		{	usrmacros[repeat][temp]=0;
		}
	}
	usrmacro=0;

	while(1)
	{	bpWstring(protos[bpConfig.busMode].protocol_name);
		if(bpConfig.basic)
		{	//bpWstring("(BASIC)");
			BPMSG1084;
		}
		bpWstring("> ");
		while(!cmd)
		{	if(usrmacro)
			{	usrmacro--;
				temp=0;
				while(usrmacros[usrmacro][temp])
				{	cmdbuf[cmdend]=usrmacros[usrmacro][temp];
					UART1TX(usrmacros[usrmacro][temp]);
					cmdend++;
					temp++;
					cmdend&=CMDLENMSK;
				} 
				usrmacro=0;
			}

			while(!UART1RXRdy())		// as long as there is no user input poll periodicservice
			{	if(modeConfig.periodicService==1)
				{	if(protos[bpConfig.busMode].protocol_periodic())		// did we print something?
					{	bpWstring(protos[bpConfig.busMode].protocol_name);
						bpWstring("> ");
						if(cmdstart!=cmdend)
						{	for(temp=cmdstart; temp!=cmdend; temp++)
							{	UART1TX(cmdbuf[temp]);
								temp&=CMDLENMSK;
							}
						}
					}
				}
			}

			c=UART1RX();
			switch(c)
			{	case 0x08:	if(cmdend!=cmdstart)				// backspace pressed, do we have already input??
							{	cmdend--;
								cmdend&=CMDLENMSK;
								bpWstring("\x08 \x08");		// destructive backspace ian !! :P
							}								// editing could be done with the cursor :P
							break;
				case 0x0A:
				case 0x0D:	cmd=1;						// enter pressed, we got a command!!
							if(((cmdend+1)&CMDLENMSK)!=cmdstart)			// no bufferoverflow?
							{	cmdbuf[cmdend]=0x00;					// we can use this to find the typed history
								cmdend++;
								cmdend&=CMDLENMSK;
							}
							else
							{	UART1TX(BELL);			// echo beep (overflow)
								cmdbuf[cmdend]=0x00;
							}
							bpWline("");
							break;
				case 0x00:	binmodecnt++;
							if(binmodecnt==20)
							{	binBB();
								binmodecnt=0;			// do we get here or not?
							}
							break;
				case 0x02:	if(binmodecnt>=5)
							{	SUMP();
								binmodecnt=0;
							}
							break;
				default:	if(((cmdend+1)&CMDLENMSK)!=cmdstart)			// do we have room to store it?
							{	if((c>=0x20)&&(c<=127))		// printable??
								{	UART1TX(c);				// echo back and store it
									cmdbuf[cmdend]=c;
									cmdend++;
									cmdend&=CMDLENMSK;
								}
							}
							else
							{	UART1TX(BELL);			// echo beep (buffer overflow)
								cmdbuf[cmdend]=0x00;
							}
			}
		}

		newstart=cmdend;
		oldstart=cmdstart;
		cmd=0;

//		bpWline("\x0a\x0dreceived enter, processing input");
//		bpWline("cmdbuf[]=");

//		for(i=0; i<CMDBUFLEN; i++)						// print ringbuffer
//		{	if(cmdbuf[i]) UART1TX(cmdbuf[i]);
//				else UART1TX('.');
//		}

//		bpWline("");
//		bpWstring("cmdstart = ");
//		bpWinthex(cmdstart);
//		bpWstring(" cmdend = ");
//		bpWinthex(cmdend);
//		bpWline("");

		stop=0;
		cmderror=0;

		if(bpConfig.basic)
		{	basiccmdline();
			//bpWline("Ready.");
			BPMSG1085;
			stop=1;
		}

//		for(i=0; i<CMDBUFLEN; i++)						// print ringbuffer
//		{	if(cmdbuf[i]) UART1TX(cmdbuf[i]);
//				else UART1TX('.');
//		}

//		bpWline("");
//		bpWstring("cmdstart = ");
//		bpWinthex(cmdstart);
//		bpWstring(" cmdend = ");
//		bpWinthex(cmdend);
//		bpWline("");


		while(!stop)
		{	c=cmdbuf[cmdstart];
			switch(c)
			{		// generic commands (not bus specific)
				case 'h':	//bpWline("-command history");
							if(!cmdhistory())
							{	oldstart=cmdstart;
								newstart=cmdend;
							}
//							for(i=0; i<CMDBUFLEN; i++)						// print ringbuffer
//							{	if(cmdbuf[i]) UART1TX(cmdbuf[i]);
//									else UART1TX('.');
//							}
					
//							bpWline("");
//							bpWstring("cmdstart = ");
//							bpWinthex(cmdstart);
//							bpWstring(" cmdend = ");
//							bpWinthex(cmdend);
//							bpWline("");

							break;
				case '?':	//bpWline("-HELP");
							printHelp();
							break;
				case 'i':	//bpWline("-Status info");
							versionInfo();//display hardware and firmware version string
							if(bpConfig.busMode!=HIZ){			
								statusInfo();
							}
							break;
				case 'm':	//bpWline("-mode change");
							changemode();
							break;
				case 'b':	//bpWline("-terminal speed set");
							setBaudRate();
							break;
				case 'o':	//bpWline("-data output set");
							setDisplayMode();
							break;
				case 'v':	//bpWline("-check supply voltage");
							pinStates();
							//measureSupplyVoltages();
							break;
				case 'f':	//bpWline("-frequency count on AUX");
							bpFreq();
							break;
				case 'g':	//bpWline("-frequency generate on AUX");
							if((cmdbuf[(cmdstart+1)&CMDLENMSK])=='o')
							{	cmdstart+=2;
								cmdstart&=CMDLENMSK;
								walkdungeon();
								break;
							}

							if(bpConfig.busMode==HIZ)
							{	//bpWmessage(MSG_ERROR_MODE);
								BPMSG1088;
							}else{
								bpPWM();
							}
							break;
				case 'c':	//bpWline("-aux pin assigment");
							modeConfig.altAUX=0;
							//bpWmessage(MSG_OPT_AUXPIN_AUX);
							BPMSG1086;
							break;
				case 'C':	//bpWline("-aux pin assigment");
							modeConfig.altAUX=1;
							//bpWmessage(MSG_OPT_AUXPIN_CS);
							BPMSG1087;
							break;
				case 'L':	//bpWline("-bit order set (MSB)");
							//if(bpConfig.busMode==HIZ)
							//{	//bpWmessage(MSG_ERROR_MODE);
							//	BPMSG1088;
							//}
							//else
							//{	
								modeConfig.lsbEN=1;
								BPMSG1124;
							//}
							break;
				case 'l':	//bpWline("-bit order set (LSB)");
							//if(bpConfig.busMode==HIZ)
							//{	//bpWmessage(MSG_ERROR_MODE);`
							//	BPMSG1088;
							//}
							//else
							//{	
								modeConfig.lsbEN=0;
								BPMSG1123;
							//}
							break;
#if defined( BUSPIRATEV2)
				case 'p':	//bpWline("-pullup resistors off");


							//don't allow pullups on some modules. also: V0a limitation of 2 resistors
							if(bpConfig.busMode==HIZ)
							{	//bpWmessage(MSG_ERROR_MODE);
								BPMSG1088;
							}
							else
							{	BP_PULLUP_OFF(); //pseudofunction in hardwarevx.h
//								modeConfig.pullupEN=0;
								//bpWmessage(MSG_OPT_PULLUP_OFF);
								BPMSG1089;
							}
							break;
				case 'P':	//bpWline("-pullup resistors on");
							//don't allow pullups on some modules. also: V0a limitation of 2 resistors
							if(bpConfig.busMode==HIZ)
							{	//bpWmessage(MSG_ERROR_MODE);
								BPMSG1088;
							}
							else
							{	if(modeConfig.HiZ==0)
								{	//bpWmessage(MSG_ERROR_NOTHIZPIN);
									BPMSG1209;
								}
								BP_PULLUP_ON(); //pseudofunction in hardwarevx.h
//								modeConfig.pullupEN=1;
								//bpWmessage(MSG_OPT_PULLUP_ON);
								BPMSG1091;
								
								ADCON();
								if(bpADC(VPUADC)<0x50){ //no pullup voltage detected
									bpWline("Warning: no voltage on Vpullup pin");
								}
								ADCOFF();
							}
#endif
							break;
				case '=':	//bpWline("-HEX/BIN/DEC convertor");
							cmdstart++;
							cmdstart&=CMDLENMSK;
							consumewhitechars();
							temp=getint();
							bpWhex(temp);
							bpWstring(" = ");
							bpWdec(temp);
							bpWstring(" = ");
							bpWbin(temp);	
							bpBR;
							break;
				case '|':	//bpWline("-HEX/BIN/DEC convertor");
							cmdstart++;
							cmdstart&=CMDLENMSK;
							consumewhitechars();
							temp=getint();
							temp=bpRevByte((unsigned char)temp);
							bpWhex(temp);
							bpWstring(" = ");
							bpWdec(temp);
							bpWstring(" = ");
							bpWbin(temp);	
							bpBR;
							break;
#if defined(BUSPIRATEV2)
				case '~':	//bpWline("-selftest");
							if(bpConfig.busMode==HIZ){			
								selfTest(1,1);//self test, showprogress in terminal
							}else{
								//bpWline(OUMSG_PM_SELFTEST_HIZ);
								BPMSG1092;
							}
							break;
#endif
				case '#':	//bpWline("-reset BP");
							if(agree())
							{	//bpWline(OUMSG_PM_RESET);
								BPMSG1093;
								while(U1STAbits.TRMT==0); //wait untill TX finishes
								asm("RESET");
							}
							break;
				case '$':	//bpWline("-bootloader jump");
							if(agree())
							{	//bpWline("BOOTLOADER");
								BPMSG1094;
							bpDelayMS(100);
								bpInit();		// turn off nasty things, cleanup first needed?
								while(U1STAbits.TRMT==0); //wait untill TX finishes
								asm volatile ("mov #BLJUMPADDRESS, w1 \n" //bootloader location
											  "goto w1 \n");
							}
							break;
				case 'a':	//bpWline("-AUX low");
							repeat=getrepeat()+1;
							while(--repeat)	bpAuxLow();
							break;
				case 'A':	//bpWline("-AUX hi");
							repeat=getrepeat()+1;
							while(--repeat) bpAuxHigh();
							break;
				case '@':	//bpWline("-Aux read");
							repeat=getrepeat()+1;
							while(--repeat)	
							{		//bpWstring(OUMSG_AUX_INPUT_READ);
									BPMSG1095;
									bpEchoState(bpAuxRead());
									bpWBR;
							}
							break;
				case 'W':	//bpWline("-PSU on");	//enable any active power supplies
							if(bpConfig.busMode==HIZ)
							{	//bpWmessage(MSG_ERROR_MODE);
								BPMSG1088;
							}else{
								BP_VREG_ON();
								ADCON(); // turn ADC ON
								bpDelayMS(2);//wait for VREG to come up
							
								if((bpADC(V33ADC)>V33L)&&(bpADC(V5ADC)>V5L)){ //voltages are correct
									//bpWmessage(MSG_VREG_ON);
									BPMSG1096;
									//modeConfig.vregEN=1;
								}else{
									BP_VREG_OFF();
									bpWline("VREG too low, is there a short?");
									BPMSG1097;
								}
								ADCOFF(); // turn ADC OFF
							}
							break;
				case 'w':	//bpWline("-PSU off");	//disable the power supplies
							if(bpConfig.busMode==HIZ)
							{	//bpWmessage(MSG_ERROR_MODE);
								BPMSG1088;
							}else{
								BP_VREG_OFF();
								//bpWmessage(MSG_VREG_OFF);
								BPMSG1097;
								//modeConfig.vregEN=0;
							}
							break;
				case 'd':	//bpWline("-read ADC");	//do an adc reading
							//bpWstring(OUMSG_PS_ADC_VOLT_PROBE);	
							BPMSG1044;
							bpADCprobe();
							//bpWline(OUMSG_PS_ADC_VOLTS);`
							BPMSG1045;
							bpBR;
							break;
				case 'D':	//bpWline("-DVM mode");	//dumb voltmeter mode
							bpADCCprobe();
							break;
				case '&':	//bpWline("-delay 1ms");
							repeat=getrepeat();
							//bpWstring(OUMSG_PS_DELAY);
							BPMSG1099;
							bpWintdec(repeat);
							//bpWline(OUMSG_PS_DELAY_US);
							BPMSG1100;
							bpDelayUS(repeat);
							break;
				case '%':	repeat=getrepeat();
							BPMSG1099;
							bpWintdec(repeat);
							BPMSG1212;
							bpDelayMS(repeat);
							break;
				case '+':	//bpWline("-easter egg");
							//easterEgg();
							break;
#ifdef BP_USE_BASIC
				case 's':	//bpWline("Listing:");
							bpConfig.basic=1;
							break;
#endif
				case '<':	cmderror=1;
							temp=1;

							while(cmdbuf[((cmdstart+temp)&CMDLENMSK)]!=0x00)
							{	if(cmdbuf[((cmdstart+temp)&CMDLENMSK)]=='>') cmderror=0;	// clear error if we found a > before the command ends
								temp++;
							}
							if(temp>=(USRMACROLEN+3)) cmderror=1; // too long (avoid overflows)
							if(!cmderror)
							{	cmdstart++;
								cmdstart&=CMDLENMSK;
								temp=getint();
								if(cmdbuf[((cmdstart)&CMDLENMSK)]=='=')	// assignment
								{	if((temp>0)&&(temp<=USRMACROS))
									{	cmdstart++;
										cmdstart&=CMDLENMSK;
										temp--;
										for(repeat=0; repeat<USRMACROLEN; repeat++)
										{	usrmacros[temp][repeat]=0;
										}
										repeat=0;
										while(cmdbuf[cmdstart]!='>')
										{	usrmacros[temp][repeat]=cmdbuf[cmdstart];
											repeat++;
											cmdstart++;
											cmdstart&=CMDLENMSK;
										}
									}
									else
									{	cmderror=1;
									}
								}
								else
								{	if(temp==0)
									{	for(repeat=0; repeat<USRMACROS; repeat++)
										{	bpWdec(repeat+1);
											bpWstring(". <");
											bpWstring(usrmacros[repeat]);
											bpWline(">");
										}
									}
									else if((temp>0)&&(temp<=USRMACROS))
									{	//bpWstring("execute : ");
										//BPMSG1236;
										//bpWdec(temp-1);
										bpBR;
										usrmacro=temp;
									}
									else
									{	cmderror=1;
									}
								}
							}
							break;
					// command for subsys (i2c, UART, etc)
				case '(':	//bpWline("-macro");
							cmdstart++;
							cmdstart&=CMDLENMSK;
							sendw=getint();
							consumewhitechars();
							if(cmdbuf[((cmdstart)&CMDLENMSK)]==')' )
							{	//cmdstart++;				// skip )
								//cmdstart&=CMDLENMSK;
								//bpWdec(sendw);
								protos[bpConfig.busMode].protocol_macro(sendw);
								bpBR;
							}
							else
							{	cmderror=1;
							}
							break;
				case 0x22:	//bpWline("-send string");
							cmderror=1;
							temp=1;

							while(cmdbuf[((cmdstart+temp)&CMDLENMSK)]!=0x00)
							{	if(cmdbuf[((cmdstart+temp)&CMDLENMSK)]==0x22) cmderror=0;	// clear error if we found a " before the command ends
								temp++;
							}

							if(!cmderror)
							{	BPMSG1101;
								UART1TX(0x22);
								while(cmdbuf[((++cmdstart)&CMDLENMSK)]!=0x22)
								{	cmdstart&=CMDLENMSK;
									UART1TX(cmdbuf[cmdstart]);
									protos[bpConfig.busMode].protocol_send(cmdbuf[cmdstart]);
								}
								cmdstart&=CMDLENMSK;
								UART1TX(0x22);
								bpBR;
							}
							break;
				case '[':	//bpWline("-Start");
							protos[bpConfig.busMode].protocol_start();
							break;
				case '{':	//bpWline("-StartR");
							protos[bpConfig.busMode].protocol_startR();
							break;
				case ']':	//bpWline("-Stop");
							protos[bpConfig.busMode].protocol_stop();
							break;
				case '}':	//bpWline("-StopR");
							protos[bpConfig.busMode].protocol_stopR();
							break;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':	//bpWline("-Send");
							//bpWmessage(MSG_WRITE);
							BPMSG1101;
							sendw=getint();
							cmdstart--;	
							cmdstart&=CMDLENMSK;
							repeat=getrepeat()+1;
							while(--repeat)
							{	bpWbyte(sendw);
								if(modeConfig.lsbEN==1){//adjust bitorder
									sendw=bpRevByte(sendw);
								}
								temp=protos[bpConfig.busMode].protocol_send(sendw);
								bpSP;
								if(temp<0x100)
								{	//bpWmessage(MSG_READ);
									BPMSG1102;
									if(modeConfig.lsbEN==1){//adjust bitorder
										temp=bpRevByte((unsigned char)temp);
									}
									bpWbyte(temp);
									bpSP;
								}
							}
							bpBR;
							break;
				case 'r':	//bpWline("-Read");
							//bpWmessage(MSG_READ);							
							BPMSG1102;
							repeat=getrepeat()+1;
							while(--repeat)
							{	
								c=protos[bpConfig.busMode].protocol_read();
								if(modeConfig.lsbEN==1){//adjust bitorder
									c=bpRevByte(c);
								}
								bpWbyte(c);
								bpSP;
							}
							bpBR;
							break;
				case '/':	//bpWline("-CLK hi");
							//repeat=getrepeat()+1;
							//while(--repeat)
							//{	//bpWmessage(MSG_BIT_CLKH);
								BPMSG1103;
								protos[bpConfig.busMode].protocol_clkh();
							//}
							break;
				case '\\':	//bpWline("-CLK lo");
							//repeat=getrepeat()+1;
							//while(--repeat)
							//{	//bpWmessage(MSG_BIT_CLKL);
								BPMSG1104;
								protos[bpConfig.busMode].protocol_clkl();
							//}
							break;
				case '-':	//bpWline("-DAT hi");
							//repeat=getrepeat()+1;
							//while(--repeat)	
							//{	//bpWmessage(MSG_BIT_DATH);
								BPMSG1105;
								protos[bpConfig.busMode].protocol_dath();
							//}
							break;
				case '_':	//bpWline("-DAT lo");
							//repeat=getrepeat()+1;
							//while(--repeat)
							//{	//bpWmessage(MSG_BIT_DATL);
								BPMSG1106;
								protos[bpConfig.busMode].protocol_datl();
							//}
							break;
				case '.':	//bpWline("-DAT state read");
							//repeat=getrepeat()+1;
							BPMSG1098;
							//while(--repeat)	
							{	bpEchoState(protos[bpConfig.busMode].protocol_dats());
								//bpWmessage(MSG_BIT_NOWINPUT);
								//BPMSG1107;
							}
							break;
				case '^':	//bpWline("-CLK pulse");
							repeat=getrepeat();
							BPMSG1108;
							bpWbyte(repeat);
							repeat++;
							while(--repeat)
							{	//bpWmessage(MSG_BIT_CLK);
								protos[bpConfig.busMode].protocol_clk();
							}
							bpBR;
							break;
				case '!':	//bpWline("-bit read");
							repeat=getrepeat()+1;
							BPMSG1109;
							while(--repeat)	
							{	//bpWmessage(MSG_BIT_READ);
								bpEchoState(protos[bpConfig.busMode].protocol_bitr());
								bpSP;
							}
							//bpWmessage(MSG_BIT_NOWINPUT);
							BPMSG1107;
							break;
					// white char/delimeters
				case 0x00:
				case 0x0D:								// not necessary but got random error msg at end, just to be sure
				case 0x0A:								// same here
				case ' ':
				case ',':	break;
					// no match so it is an error
				default:	cmderror=1;
			}
			cmdstart++;
			cmdstart&=CMDLENMSK;
			
//			bpWline("");
//			bpWstring("cmdstart = ");
//			bpWinthex(cmdstart);
//			bpWstring(" cmdend = ");
//			bpWinthex(cmdend);
//			bpWline("");

			if(cmderror)
			{	//bpWstring("Syntax error at char ");
				BPMSG1110;
				if(cmdstart>oldstart)						// find error position :S
				{	bpWdec(cmdstart-oldstart);			
				}
				else
				{	bpWdec((CMDBUFLEN+cmdstart)-oldstart);
				}
				cmderror=0;
				stop=1;
				bpBR;
			}
				
			if(cmdstart==cmdend) stop=1;						// reached end of user input??
		}
		

		cmdstart=newstart;
		cmdend=newstart;									// 'empty' cmdbuffer
		cmd=0;
	}
	// you shouldn't come here :D
}

int getint(void)							// get int from user (accept decimal, hex (0x) or binairy (0b)
{	int i;
	int number;

	i=0;
	number=0;

	if((cmdbuf[((cmdstart+i)&CMDLENMSK)]>=0x31)&&(cmdbuf[((cmdstart+i)&CMDLENMSK)]<=0x39)) // 1-9 is for sure decimal
	{	number=cmdbuf[(cmdstart+i)&CMDLENMSK]-0x30;
		i++;
		while((cmdbuf[((cmdstart+i)&CMDLENMSK)]>=0x30)&&(cmdbuf[((cmdstart+i)&CMDLENMSK)]<=0x39))		// consume all digits
		{	number*=10;
			number+=cmdbuf[((cmdstart+i)&CMDLENMSK)]-0x30;
			i++;
		}
	}
	else if(cmdbuf[((cmdstart+i)&CMDLENMSK)]==0x30)				// 0 could be anything
	{	i++;
		if((cmdbuf[((cmdstart+i)&CMDLENMSK)]=='b')||(cmdbuf[((cmdstart+i)&CMDLENMSK)]=='B'))
		{	i++;
			while((cmdbuf[((cmdstart+i)&CMDLENMSK)]=='1')||(cmdbuf[((cmdstart+i)&CMDLENMSK)]=='0'))
			{	number<<=1;
				number+=cmdbuf[((cmdstart+i)&CMDLENMSK)]-0x30;
				i++;
			}
		}
		else if((cmdbuf[((cmdstart+i)&CMDLENMSK)]=='x')||(cmdbuf[((cmdstart+i)&CMDLENMSK)]=='X'))
		{	i++;
			while(((cmdbuf[((cmdstart+i)&CMDLENMSK)]>=0x30)&&(cmdbuf[((cmdstart+i)&CMDLENMSK)]<=0x39))|| \
				((cmdbuf[((cmdstart+i)&CMDLENMSK)]>='A')&&(cmdbuf[((cmdstart+i)&CMDLENMSK)]<='F'))|| \
				((cmdbuf[((cmdstart+i)&CMDLENMSK)]>='a')&&(cmdbuf[((cmdstart+i)&CMDLENMSK)]<='f')))
			{	number<<=4;
				if((cmdbuf[(cmdstart+i)&CMDLENMSK]>=0x30)&&(cmdbuf[((cmdstart+i)&CMDLENMSK)]<=0x39))
				{	number+=cmdbuf[((cmdstart+i)&CMDLENMSK)]-0x30;
				}
				else
				{	cmdbuf[((cmdstart+i)&CMDLENMSK)]|=0x20;		// make it lowercase
					number+=cmdbuf[((cmdstart+i)&CMDLENMSK)]-0x57;	// 'a'-0x61+0x0a
				}
				i++;
			}
		}
		else if((cmdbuf[((cmdstart+i)&CMDLENMSK)]>=0x30)&&(cmdbuf[((cmdstart+i)&CMDLENMSK)]<=0x39))
		{	number=cmdbuf[((cmdstart+i)&CMDLENMSK)]-0x30;
			while((cmdbuf[((cmdstart+i)&CMDLENMSK)]>=0x30)&&(cmdbuf[((cmdstart+i)&CMDLENMSK)]<=0x39))		// consume all digits
			{	number*=10;
				number+=cmdbuf[((cmdstart+i)&CMDLENMSK)]-0x30;
				i++;
			}
		}
	} 
	else										// how did we come here??
	{	cmderror=1;
		return 0;
	}
	
	cmdstart+=i;									// we used i chars
	cmdstart&=CMDLENMSK;
	return number;
}



int getrepeat(void)
{	int temp;

	if(cmdbuf[(cmdstart+1)&CMDLENMSK]==':')
	{	cmdstart+=2;
		cmdstart&=CMDLENMSK;
		temp=getint();
		cmdstart--;							// to allow [6:10] (start send 6 10 times stop) 
		cmdstart&=CMDLENMSK;
		return temp;
	}
	return 1;								// no repeat count=1
}

void consumewhitechars(void)
{	while(cmdbuf[cmdstart]==0x20)
	{	cmdstart++;		// remove spaces
		cmdstart&=CMDLENMSK;
	}
}

void changemode(void)
{	int i, busmode;

	busmode=0;

//	bpWline("--changemode()");

	cmdstart++;
	cmdstart&=CMDLENMSK;

	consumewhitechars();

//	bpWline("whitechars stripped");

	busmode=getint();

//	bpWstring("numbers: busmode=");
//	bpWinthex(busmode);
//	bpWline("");

	if(!busmode)							// no argument entered
	{	for(i=0; i<MAXPROTO; i++)
		{	bpWdec(i+1);
			bpWstring(". ");
			bpWline(protos[i].protocol_name);
		}
		//bpWline("x. exit(without change)");
		BPMSG1111;
		cmderror=0;							// error is set because no number found, but it is no error here:S eeeh confusing right?
		busmode=getnumber(1, 1, MAXPROTO, 1)-1;
//		bpWstring("busmode= ");
//		bpWdec(busmode);
		if((busmode==-2)||(busmode==-1))
		{	//bpWline("no mode change");
			BPMSG1112;
		}
		else 
		{	protos[bpConfig.busMode].protocol_cleanup();
			bpInit();
			bpConfig.busMode=busmode;
			protos[bpConfig.busMode].protocol_setup();
			if(busmode) BP_LEDMODE=1;		// mode led is on when proto >0
			//bpWmessage(MSG_READY);
			BPMSG1085;;
		}
	}
	else									// number entered
	{	busmode--;							// save a couple of programwords to do it here :D
		if(busmode<MAXPROTO)
		{	protos[bpConfig.busMode].protocol_cleanup();
			bpInit();
			bpConfig.busMode=busmode;
			protos[bpConfig.busMode].protocol_setup();
			if(busmode) BP_LEDMODE=1;		// mode led is on when proto >0
			//bpWmessage(MSG_READY);
			BPMSG1085;
		}
		else
		{	//bpWline("Nonexistent protocol!!");
			BPMSG1114;
		}
	}
	cmdstart=(cmdend-1)&CMDLENMSK;
}

int cmdhistory(void)
{	int i,j,k;

	int historypos[CMDHISTORY];


//	bpWline("--cmdhistory()");

	i=1;
	j=cmdstart-1;
	j&=CMDLENMSK;

	while(j!=cmdstart)										// scroll through the whole buffer
	{	if((cmdbuf[j]==0x00)&&(cmdbuf[(j+1)&CMDLENMSK]!=0x00))		// did we find an end? is it not empty?
		{	bpWdec(i);
			bpWstring(". ");
			k=1;
			while(cmdbuf[((j+k)&CMDLENMSK)])
			{	UART1TX(cmdbuf[((j+k)&CMDLENMSK)]);	// print it
				k++;
			}
			historypos[i]=(j+1)&CMDLENMSK;
//			bpWstring(" @");
//			bpWinthex((j+1)&CMDLENMSK);
			i++;
			if(i==CMDHISTORY) break;
			bpWline("");
		}
//		bpWinthex(j);
//		bpWline("");
		j--;
		j&=CMDLENMSK;
	}
	//bpWline("x. exit");
	BPMSG1115;

	j=getnumber(0, 1, i, 1);
//	if((j==0)||(j>(i+1)))
//	{	bpWline("invalid response!");
//		return 1;
//	}


	if (j==-1)
	{	return 1;
	}
	else
	{	
		i=0;
		while(cmdbuf[(historypos[j]+i)&CMDLENMSK])					// copy it to the end of the ringbuffer
		{	cmdbuf[(cmdend+i)&CMDLENMSK]=cmdbuf[(historypos[j]+i)&CMDLENMSK];
			i++;
		}
		cmdstart=(cmdend-1)&CMDLENMSK;		// start will be increased before parsing in main loop
		cmdend=(cmdstart+i+2)&CMDLENMSK;
		cmdbuf[(cmdend-1)&CMDLENMSK]=0x00;
	}
	return 0;
}


// gets number from input
// -1 = abort (x)
// -2 = input to much
// 0-max return
// x=1 exit is enabled (we don't want that in the mode changes ;)

int getnumber(int def, int min, int max, int x)	//default, minimum, maximum, show exit option
{	char c;
	char buf[6];									// max 4 digits;
	int i, j, stop, temp, neg;

again:											// need to do it proper with whiles and ifs..

	i=0;
	stop=0;
	temp=0;
	neg=0;

	bpWstring("\r\n(");
	bpWdec(def);
	bpWstring(")> ");

	while(!stop)
	{	c=UART1RX();
		switch(c)
		{	case 0x08:	if(i)
						{	i--;
							bpWstring("\x08 \x08");
						}
						else
						{	if(neg)
							{	neg=0;
								bpWstring("\x08 \x08");
							}
							else
							{	UART1TX(BELL);
							}
						}
						break;
			case 0x0A:
			case 0x0D:	stop=1;
						break;
			case '-':	if(!i)							// enable negative numbers
						{	UART1TX('-');
							neg=1;
						}
						else
						{	UART1TX(BELL);
						}
						break;
			case 'x':	if(x) return -1;					// user wants to quit :( only if we enable it :D
			default:	if((c>=0x30)&&(c<=0x39))	// we got a digit 
						{	if(i>3)					// 0-9999 should be enough??
							{	UART1TX(BELL);
								i=4;
							}
							else
							{	UART1TX(c);
								buf[i]=c;			// store user input
								i++;
							}
						}
						else						// ignore input :)
						{	UART1TX(BELL);
						}

		}
	}
	bpBR;

	if(i==0)
	{	return def;							// no user input so return default option
	}
	else
	{	temp=0;
		i--;
		j=i;

		for( ; i>=0; i--)
		{	temp*=10;
			temp+=(buf[j-i]-0x30);
		}

		if((temp>=min)&&(temp<=max))
		{	if(neg)
			{	return -temp;
			}
			else
			{	return temp;
			}
		}
		else
		{	//bpWline("\r\nInvalid choice, try again\r\n");
			BPMSG1211;
			goto again;
		}
	}
	return temp;								// we dont get here, but keep compiler happy
}







//print version info (used in menu and at startup in main.c)
void versionInfo(void){
	unsigned int i;

	#if defined (BUSPIRATEV2) //we can tell if it's v3a or v3b, show it here
		bpWstring(BP_VERSION_STRING);
		UART1TX(bpConfig.HWversion);
		bpBR;	
	#else
		bpWline(BP_VERSION_STRING);
	#endif

	bpWstring(BP_FIRMWARE_STRING);
	//bpWstring(" Bootloader v");
	BPMSG1126;
	i=bpReadFlash(CFG_ADDR_UPPER, BL_ADDR_VER);
	bpWdec(i>>8);
	UART1TX('.');
	bpWdec(i);
	bpWline("");

	//bpWstring("DEVID:");
	BPMSG1117;
	bpWinthex(bpConfig.dev_type);

	//bpWstring(" REVID:");
	BPMSG1210;
	bpWinthex(bpConfig.dev_rev);
	bpWstring(" (");
	switch(bpConfig.dev_rev) {
	case PIC_REV_A3:
		bpWstring("A3"); //also A4, but that's not in the wild and makes it confusing to users
		break;
	case PIC_REV_B4:
		bpWstring("B4");
		break;
	case PIC_REV_B5:
		bpWstring("B5");
		break;
	case PIC_REV_B8:
		bpWstring("B8");
		break;
	default:
		bpWstring("UNK");
		break;	
	}	
	bpWline(")");
	//bpWline("http://dangerousprototypes.com");
	BPMSG1118;
}

//display properties of the current bus mode (pullups, vreg, lsb, output type, etc)
void statusInfo(void){

	//bpWstring("CFG1:");
	BPMSG1136;
	bpWinthex(bpReadFlash(CFG_ADDR_UPPER, CFG_ADDR_1));
	//bpWstring(" CFG2:");
	BPMSG1137;
	bpWinthex(bpReadFlash(CFG_ADDR_UPPER, CFG_ADDR_2));
	bpBR;

	//bpWline("*----------*");
	BPMSG1119;

	pinStates();

	//vreg status (was modeConfig.vregEN)
	if(BP_VREGEN==1) BPMSG1096; else BPMSG1097;	//bpWmessage(MSG_VREG_ON); else bpWmessage(MSG_VREG_OFF);
	//voltage report
//	measureSupplyVoltages();
	
	//AUX pin setting
	if(modeConfig.altAUX==1) BPMSG1087; else BPMSG1086;	//bpWmessage(MSG_OPT_AUXPIN_CS); else bpWmessage(MSG_OPT_AUXPIN_AUX);

	//open collector outputs?
	if(modeConfig.HiZ==1) BPMSG1120; else BPMSG1121;	// bpWmessage(MSG_STATUS_OUTPUT_HIZ); else bpWmessage(MSG_STATUS_OUTPUT_NORMAL);

#if defined(BUSPIRATEV2)	
	//pullups available, enabled?
	//was modeConfig.pullupEN
	if(BP_PULLUP==1) BPMSG1091; else BPMSG1089;	//bpWmessage(MSG_OPT_PULLUP_ON); else bpWmessage(MSG_OPT_PULLUP_OFF);
#endif
	
	//bitorder toggle available, enabled
	if(modeConfig.lsbEN==0) BPMSG1123; else BPMSG1124;	//bpWmessage(MSG_OPT_BITORDER_LSB); else bpWmessage(MSG_OPT_BITORDER_MSB);

	//bpWline("*----------*");
	BPMSG1119;

}

void pinStates(void) 
{	//bpWline("Pinstates:");
	BPMSG1226;
	BPMSG1233;
	//bpWstring("GND\t3.3V\t5.0V\tADC\tVPU\tAUX\t");
#if defined(BUSPIRATEV25)
	BPMSG1235;
#else
	BPMSG1227;
#endif
	protos[bpConfig.busMode].protocol_pins();
	//bpWstring("P\tP\tP\tI\tI\t");
	BPMSG1228;
	pinDirection(AUX);
	pinDirection(CLK);
	pinDirection(MOSI);
	pinDirection(CS);
	pinDirection(MISO);
	bpBR;	

	//bpWstring("GND\t");
	BPMSG1234;
	AD1CON1bits.ADON = 1;
#if defined(BUSPIRATEV25)
	bpWvolts(bpADC(PROBEADC)); BPMSG1045; UART1TX('\t');
#else
	bpWvolts(bpADC(V33ADC)); BPMSG1045; UART1TX('\t');
#endif
	bpWvolts(bpADC(V5ADC)); BPMSG1045; UART1TX('\t');
#if defined(BUSPIRATEV25)
	bpWvolts(bpADC(V33ADC)); BPMSG1045; UART1TX('\t');
#else
	bpWvolts(bpADC(PROBEADC)); BPMSG1045; UART1TX('\t');
#endif
	bpWvolts(bpADC(VPUADC)); BPMSG1045; UART1TX('\t');
	AD1CON1bits.ADON = 0;
	pinState(AUX);
	pinState(CLK);
	pinState(MOSI);
	pinState(CS);
	pinState(MISO);
	bpBR;
}

void pinDirection(unsigned int pin){

	if(IODIR & pin){
		bpWstring("I\t");
	}else{
		bpWstring("O\t");
	}

}

void pinState(unsigned int pin){

	if(IOPOR & pin){
		bpWstring("H\t");
	}else{
		bpWstring("L\t");
	}

}

//user terminal number display mode dialog (eg HEX, DEC, BIN, RAW)
void setDisplayMode(void)
{	int mode;

	cmdstart++;
	cmdstart&=CMDLENMSK;

	consumewhitechars();
	mode=getint();

	if((mode>0)&&(mode<=4))
	{	bpConfig.displayMode=mode-1;
	}
	else
	{	cmderror=0;
		//bpWmessage(MSG_OPT_DISPLAYMODE); //show the display mode options message			
		BPMSG1127;
		//	bpConfig.displayMode=(bpUserNumberPrompt(1, 4, 1)-1); //get, store user reply
		bpConfig.displayMode=getnumber(1, 1, 4,0)-1; //get, store user reply
	}
	//bpWmessage(MSG_OPT_DISPLAYMODESET);//show display mode update text
	BPMSG1128;
}

//configure user terminal side UART baud rate
void setBaudRate(void)
{	unsigned char speed;
	unsigned char brg;

	cmdstart++;
	cmdstart&=CMDLENMSK;
	
	consumewhitechars();
	speed=getint();

	if((speed>0)&&(speed<=10))
	{	bpConfig.termSpeed=speed-1;
	}
	else
	{	cmderror=0;
		//bpWmessage(MSG_OPT_UART_BAUD); //show stored dialog
		BPMSG1133;
	//	bpConfig.termSpeed=(bpUserNumberPrompt(1, 9, 9)-1);
		bpConfig.termSpeed=getnumber(9,1,10,0)-1;
	}

	if(bpConfig.termSpeed==9)
	{	consumewhitechars();
		brg=getint();

		if(brg==0)
		{	cmderror=0;
			bpWline("Enter raw value for BRG");
			brg=getnumber(34,0,32767,0);
		}
	}

	//bpWmessage(MSG_OPT_TERMBAUD_ADJUST); //show 'adjust and press space dialog'
	BPMSG1134;
	BPMSG1251;
	while(U1STAbits.TRMT==0);//wait for TX to finish or reinit flushes part of prompt string from buffer

	if(bpConfig.termSpeed==9)
	{		UART1Speed(brg);
	}	
	InitializeUART1();
	while(1){ //wait for space to prove valid baud rate switch
		while(!UART1RXRdy());
		if(UART1RX()==' ')break;
	}
}




