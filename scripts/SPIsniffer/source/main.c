/*
 * This file is part of the Bus Pirate project (http://code.google.com/p/the-bus-pirate/).
 *
 * Written and maintained by the Bus Pirate project and http://dangerousprototypes.com
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
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>


#include "serial.h"

int modem =FALSE;   //set this to TRUE of testing a MODEM
int verbose = 0;
int disable_comport = 0;   //1 to say yes, disable comport, any value to enable port default is 0 meaning port is enable.
int dumphandle;     // use by dump file when using the -d dumfile.txt parameter
char *dumpfile;

static uint32_t BP_WriteToPirate(int fd, char * val) {
	int res = -1;
	char ret = 0;


    serial_write(fd, val, 1);

    if (disable_comport != 1) {  //if comport is enable, we need a response from the port

          res = serial_read(fd, &ret, 1);

	      if( ret != '\x01') {
	          if (modem==TRUE){
	             printf("Modem responded with %i byte and with a value of 0X%X\n",res,ret);

	          } else {
		          printf("ERROR");
		          return -1;
	          }
	        }
        }
	return 0;
}

static void BP_EnableMode(int fd, char bbmode)
{
	int ret;
	char tmp[100] = { [0 ... 20] = 0x00 };
	int done = 0;
	//int cmd_sent = 0;
	int tries=0;

	printf(" Entering binary mode...\n");

	if (fd==-1)   //added because the fd has already returned null
	{
	    printf("Port does not exist!");
	    return;

	}
	while (!done) {
		tmp[0]=0x00;
		//printf("Sending 0X%X to port\n",tmp[0]);
		serial_write(fd, tmp, 1);
		tries++;
	//	printf("tries: %i Ret %i\n",tries,ret);
		usleep(1);
		ret = serial_read(fd, tmp, 5);
		if (modem==TRUE)
		{
            printf("\nModem Responded = %i\n",ret);
            done=1;
		}
		else {
		     if (ret != 5 && tries>20) {
			         fprintf(stderr, "Buspirate did not respond correctly :( %i \n", ret );
			         exit(-1);
		      }    else if (strncmp(tmp, "BBIO1", 5) == 0) {
			       done=1;
		           }
		}

		if (tries>25){
		printf("Buspirate:Too many tries in serial read! -exiting \n - chip not detected, or not readable/writable\n");
		exit(-1);
		}
	}

	done=0;
	tmp[0] = bbmode;
	//printf("Sending 0X%X to port\n",tmp[0]);
	serial_write(fd, tmp, 1);
	tries++;
	 usleep(1);
	ret = serial_read(fd, tmp, 4);
	if (modem==TRUE)
		{
            printf("Modem Responded = %i with value %s\n",ret,tmp);
		}
        else {
	         if ( (ret==4) && (strncmp(tmp, "SPI1", 4) == 0)) {

	         } else{
	        	fprintf(stderr, "Buspirate did not respond correctly :( %i \n", ret );
	        	exit(-1);
	        }
        }
}


int main(int argc, char** argv)
{

  char buffer[256] = {0};
  int fd;
  int res,c;

  char *param_port = NULL;
  char *param_speed = NULL;

  param_speed=strdup("115200"); //dummy
  param_port=strdup("COM3");    //default for debugging


    printf("--------------------------------------------\n");
    printf("\n");
    printf(" Bus Pirate binary mode SPI SNIFFER utility v0.1 (CC-0)\n");
    printf(" http://dangerousprototypes.com\n");
    if( argc == 1 )
	{
		//print usage
		printf("\n");
        printf(" Usage:              \n");
		printf("   %s portname\n ",argv[0]);
		printf("\n");
		printf("   Example Usage:   %s COM1 \n",argv[0]);
        printf("\n");

        printf("--------------------------------------------\n");


		return 0;
	}

    printf(" Press escape to exit \n");
    printf("\n");

    //
    // Open serial port
    //
    param_port=strdup(argv[1]);
	printf(" Opening Bus Pirate on %s at %sbps...\n", param_port, param_speed);
	fd = serial_open(param_port);
	if (fd < 0) {
		fprintf(stderr, "Error opening serial port\n");
		return -1;
	}
	serial_setup(fd,(speed_t)param_speed);

	//
	// Enter binary mode, then enter a protocol mode
	//
    fprintf(stderr, " Configuring Bus Pirate...\n");
    #define SPI 0x01
	BP_EnableMode(fd, SPI); //enter BBIO then SPI

    //
	//Start sniffer
	//

	//we could add various SPI/sniffer configuration options eventually
	printf(" Starting SPI sniffer...\n");
    serial_write( fd, "\x0E", 1);

    //
    // Done with setup
    //
	printf(" (OK) Happy sniffing! \n");

    //
    // Loop and print input from the serial port
    //
	 while(1){

        Sleep(1);
        res= serial_read(fd, buffer, 100);

        if(res>0){
            for(c=0; c<res; c++){
                printf("%02X ", (uint8_t)buffer[c]);
            }
        }

        if(kbhit()){
           c = getch();

           if(c == 27){
                printf("\n Esc key hit, stopping...\n");
                printf(" Clean up Bus Pirate...\n");
                buffer[0]=0x00;//exit sniffer
                buffer[1]=0x00;//exit spi
                buffer[2]=0x0f;//exit BBIO
                res = serial_write( fd, buffer, 3);
                printf(" (Bye for now!)\n");
                break;
            }
        }

    }    //hit enter to stop

#define FREE(x) if(x) free(x);

	FREE(param_port);
	FREE(param_speed);
    return 0;
}
