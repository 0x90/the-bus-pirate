
#include "base.h"
#include "procMenu.h"
#include "busPirateCore.h" 

extern struct _bpConfig bpConfig;
extern struct _modeConfig modeConfig;

// directions
#define NORTH	0x01
#define WEST	0x02
#define EAST	0x04
#define SOUTH	0x08

int dungeon=0;

// n, w, e, s
const unsigned char paths[][4]={
{ 1, 0, 0, 0 },
{ 3, 2, 0, 0 },		// 1
{ 0, 0, 1, 0 },		// 2
{ 6, 0, 4, 1 },		// 3
{ 0, 3, 0, 0 },		// 4
{ 0, 0, 6, 0 },		// 5
{ 8, 5, 7, 3 },		// 6
{ 0, 6, 0, 0 },		// 7
{ 0, 0, 0, 0 }
};

void eeMsg(int offset, int length);
void eeMsgBR(int offset, int length);


// textes
#define	EETEXT1	eeMsgBR(0, 43)
#define	EETEXT2	eeMsgBR(43, 34)
#define	EETEXT3	eeMsgBR(77, 53)
#define	EETEXT4	eeMsgBR(130, 52)
#define	EETEXT5	eeMsg(182, 8)
#define	EETEXT6	eeMsgBR(190, 18)
#define	EETEXT7	eeMsg(208, 7)
#define	EETEXT8	eeMsg(215, 6)
#define	EETEXT9	eeMsg(221, 5)
#define	EETEXT10	eeMsg(226, 5)
#define	EETEXT11	eeMsg(231, 6)
#define	DUNGEON1	eeMsgBR(237, 25)
#define	DUNGEON2	eeMsgBR(262, 27)
#define	DUNGEON3	eeMsgBR(289, 51)
#define	DUNGEON4	eeMsgBR(340, 33)
#define	DUNGEON5	eeMsgBR(373, 4)
#define	DUNGEON6	eeMsgBR(377, 35)
#define	DUNGEON7	eeMsgBR(412, 16)
#define	DUNGEON8	eeMsgBR(428, 36)
#define	ASCII1	eeMsgBR(464, 53)
#define	ASCII2	eeMsgBR(517, 55)
#define	ASCII3	eeMsgBR(572, 55)
#define	ASCII4	eeMsgBR(627, 54)
#define	ASCII5	eeMsgBR(681, 53)
#define	ASCII6	eeMsgBR(734, 52)
#define	ASCII7	eeMsgBR(786, 53)
#define	ASCII8	eeMsgBR(839, 52)



//
extern void eemessages(void);

void eeMsg(int offset, int length) 
{	int i; 

	for(i=offset; i<(offset+length); i++) 
	{	if((i%3)==0)  UART1TX(__builtin_tblrdl((int)&eemessages+((i/3)<<1))&0x00FF); 
		if((i%3)==1) UART1TX((__builtin_tblrdl((int)&eemessages+((i/3)<<1))>>8)&0xFF); 
		if((i%3)==2)  UART1TX(__builtin_tblrdh((int)&eemessages+((i/3)<<1))&0x00FF); 
	}
}
 
void eeMsgBR(int offset, int length) 
{	eeMsg(offset, length); 
	bpBR; 
} 
 

void walkdungeon(void)
{	int dir;

	consumewhitechars(); 	
	
	switch(cmdbuf[cmdstart])
	{	case 'n':	dir=0;
					break;
		case 'w':	dir=1;
					break;
		case 'e':	dir=2;
					break;
		case 's':	dir=3;
					break;
		default:	dir=5;
					return;
	}
	while((cmdbuf[cmdstart]!=0x20)&&(cmdbuf[cmdstart]!=0x00))
	{	cmdstart++;
		cmdstart&=CMDLENMSK;
	}
	
	if((paths[dungeon][dir]==0)||(dir==5))
	{	EETEXT6;
		return;
	}

	dungeon=paths[dungeon][dir];

	EETEXT5;
	switch(dungeon)
	{	case 1:	DUNGEON1;
				break;
		case 2:	DUNGEON2;
				break;
		case 3:	DUNGEON3;
				BPMSG1136;
				bpWinthex(bpReadFlash(CFG_ADDR_UPPER, CFG_ADDR_1));
				BPMSG1137;
				bpWinthex(bpReadFlash(CFG_ADDR_UPPER, CFG_ADDR_2));
				bpSP;
				BPMSG1117; 
				bpWinthex(bpConfig.dev_type); 
				BPMSG1210;
				bpWinthex(bpConfig.dev_rev);
				bpBR;
				break;
		case 4:	DUNGEON4;
				break;
		case 5:	DUNGEON5;
				AD1CON1bits.ADON = 1;
				if(bpADC(10)>0x150) EETEXT1;
				AD1CON1bits.ADON = 0;
				break;
		case 6:	DUNGEON6;
				break;
		case 7:	DUNGEON7;
				if(BP_PULLUP==1) EETEXT2; //was modeConfig.pullupEN==1
				break;
		case 8:	DUNGEON8;
				AD1CON1bits.ADON = 1;
				if((bpConfig.busMode==3)&&(BP_PULLUP==1)&&(bpADC(10)>0x150)) //was modeConfig.pullupEN==1
				{	EETEXT3;
					ASCII1;
					ASCII2;
					ASCII3;
					ASCII4;
					ASCII5;
					ASCII6;
					ASCII7;
					ASCII8;
				}
				else
				{	EETEXT4;
					dungeon=1;
					EETEXT5; DUNGEON1;
				}
				AD1CON1bits.ADON = 0;
				break;
		default: break;
	}

	EETEXT7;

	if(paths[dungeon][0]) EETEXT8;
	if(paths[dungeon][1]) EETEXT9;
	if(paths[dungeon][2]) EETEXT10;
	if(paths[dungeon][3]) EETEXT11;
	bpBR;
}

