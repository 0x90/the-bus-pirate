#include "base.h"
#include "bitbang.h"
#include "binIOhelpers.h"

extern struct _modeConfig modeConfig;
void binrawversionString(void);

#define R3WMOSI_TRIS 	BP_MOSI_DIR
#define R3WCLK_TRIS 	BP_CLK_DIR
#define R3WMISO_TRIS 	BP_MISO_DIR
#define R3WCS_TRIS 		BP_CS_DIR


#define R3WMOSI 		BP_MOSI
#define R3WCLK 			BP_CLK 
#define R3WMISO 		BP_MISO 
#define R3WCS 			BP_CS 

/*
    * 00000000 – Enter raw bitbang mode, reset to raw bitbang mode
	*define PINS_DIR	0x01	//1,
#define PINS_WRITE	0x02	//1,
#define PINS_READ	0x03//0,1
#define PINS_READ_BIT	0x05//1,1
#define PINS_WRITE_BIT	0x04//2,
#define TMS_WRITE_1	0x09 //1,
#define TMS_WRITE_MULTIPLE	0x0a //1=# of extra bytes, 
//read or write bytes, trip tms at the end
//j = ((uint8_t)buf[1] << 8) | ((uint8_t)buf[2]); //get data packet size
//j = (j >> 3) + ((j & 0x07)?1:0);
//get data packet size extra bytes
#define WRITE 0x06 //2+data
#define READ	0x07 //2+data (why do we get bytes, they aren't used!)
#define WRITE_READ 0x08
#define UNKNOWN 0x00 //0,1=0x00,

*/

//command, (bytes read, sent)
#define PINS_DIR	0x01	//1,
#define PINS_WRITE	0x02	//1,
#define PINS_READ	0x03//0,1
#define PINS_READ_BIT	0x05//1,1
#define PINS_WRITE_BIT	0x04//2,
#define TMS_WRITE_1	0x09 //1,
#define TMS_WRITE_MULTIPLE	0x0a //1=# of extra bytes, 
//read or write bytes, trip tms at the end
//j = ((uint8_t)buf[1] << 8) | ((uint8_t)buf[2]); //get data packet size
//j = (j >> 3) + ((j & 0x07)?1:0);
//get data packet size extra bytes
#define WRITE 0x06 //2+data
#define READ	0x07 //2+data (why do we get bytes, they aren't used!)
#define WRITE_READ 0x08
#define UNKNOWN 0x00 //0,1=0x00,

void binrawversionString(void){bpWstring("OCD1");}

void OpenOCDservice(void){
	unsigned char inByte;
	while(1){
		while(U1STAbits.URXDA == 0);//wait for a byte
		inByte=U1RXREG; //grab it

		switch(inByte){
			case PINS_DIR:
				break;
			case PINS_WRITE:
				break;
			case PINS_READ:
				break;
			case PINS_READ_BIT:
				break;
			case PINS_WRITE_BIT	0x04//2,
				break;
			case TMS_WRITE_1	0x09 //1,
				break;

//get byte 1 extra bytes
			case TMS_WRITE_MULTIPLE	0x0a //1=# of extra bytes, 
				break;

//read or write bytes, trip tms at the end
//j = ((uint8_t)buf[1] << 8) | ((uint8_t)buf[2]); //get data packet size
//j = (j >> 3) + ((j & 0x07)?1:0);
//get data packet size extra bytes
			case  WRITE 0x06 //2+data
				break;
			case  READ	0x07 //2+data (why do we get bytes, they aren't used!)
				break;
			case  WRITE_READ 0x08
				break;
			default: //UNKNOWN 0x00 //0,1=0x00,
				break;




		}
	}
}








}