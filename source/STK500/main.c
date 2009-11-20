/*
** Made by fabien le mentec <texane@gmail.com>
** 
** Started on  Sun Sep 20 14:08:30 2009 texane
** Last update Tue Nov 17 19:52:04 2009 texane
*/
#include "types.h"
#include "stk500.h"

void serial_setup(void);
void serial_write(unsigned char* s, unsigned int len);
static int read_uint8(unsigned char* c, unsigned char do_timeout);

/* serial helper routines */
static int read_uint8(unsigned char* c, unsigned char do_timeout){
	int res = 0;
	int timeout=0xffff;
	
	while (UARTRXRdy() == 0){//wait for a byte in buffer
		timeout--;		
		if (do_timeout && (timeout==0)){
			res = -1;
			break;
		}
	}

	if(res==0) c=UARTRX();	
	return res;
}

/* main */
int main(void){
	stk500_error_t error;
	unsigned int isize;
	unsigned int osize;
	unsigned char do_timeout;
	unsigned char buf[STK500_BUF_MAX_SIZE];

	osc_setup();
	int_setup();
	serial_setup();
	stk500_setup();
	
	while (1){
		/* process new command */
		
		error = STK500_ERROR_MORE_DATA;
		
		do_timeout = 0;
		
		isize = 0;
		osize = 0;
		
		while (error == STK500_ERROR_MORE_DATA){
			if (read_uint8(buf + isize, do_timeout) == -1){//try to get a byte
				/* has timeouted */
				stk500_timeout(buf, isize, &osize);//reset the variables
				error = STK500_ERROR_SUCCESS; //must be some message to send below
				break;
			}
			
			do_timeout = 1; //next byte with timeout
			
			++isize; //increment buffer insize
			
			error = stk500_process(buf, isize, &osize); //check to see if this is a complete command
		}

		
		if ((error == STK500_ERROR_SUCCESS) && (osize))
			serial_write(buf, osize);
	}
}

void serial_setup(void){}

void serial_write(unsigned char* s, unsigned int len){
  unsigned int i;

  for (i = 0; i < len; ++i)
    UARTTX(s[i]);
}