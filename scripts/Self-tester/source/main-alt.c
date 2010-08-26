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
#include <string.h>
#include <windef.h>

#include "buspirate.h"
#include "serial.h"


#define SELFTEST 0xff
#define ERR  -1
#define BBIO 0x00
#define SPI 0x01
#define I2C 0x02
#define ART  0x03
#define _1W0  0x04
#define RAW  0X05


int modem =FALSE;   //set this to TRUE of testing a MODEM
int verbose = 0;
int disable_comport = 0;   //1 to say yes, disable comport, any value to enable port default is 0 meaning port is enable.
int dumphandle;     // use by dump file when using the -d dumfile.txt parameter
char *dumpfile;

const char *modes[]={
    "BBIO",
    "SPI",
    "I2C",
    "ART",
    "1W0",
    "RAW",
};

int print_usage(char * appname)
	{
		//print usage
		printf("\n\n");

	  printf("-------------------------------------------------------\n");
		printf("\n");
        printf(" Usage:              \n");
		printf("   %s  -d device t test -e 1 -p 0 \n ",appname);
		printf("\n");
		printf("   Example Usage:   %s -d COM1 -s Speed -t Test -e 1 -p 0  -M mode \n",appname);
		printf("\n");
		printf("           Where: -d device is port e.g.  COM1  \n");
		printf("                  -s Speed is port Speed  default is 115200 \n");
		printf("                  -e ClockEdge is 0 or 1  default is 1 \n");
		printf("                  -p Polarity  is 0 or 1  default is 0 \n");
		printf("                  -t Test is short (s) or long (l) test e.g. -t s  or -t l \n");
		printf("                  -M mode (note: Upper case 'M') is one of the following: \n");
        printf("                         SPI, IC2, ART, 1W0 and RAW \n");
		printf("                         default is SPI mode e.g -M SPI\n        ");

		printf("\n");

        printf("\n");

       printf("-------------------------------------------------------\n");


		return 0;
	}



int main(int argc, char** argv)
{
int opt;
  char buffer[256] = {0};
  int fd;
  int res,c,counter;
  int status;
  char i;
  char *param_port = NULL;
  char *param_speed = NULL;
  char *param_polarity=NULL;
  char *param_clockedge=NULL;
  char *param_test=NULL;
  char *param_bbmode=NULL;
  int BBmode;
//  int clock_edge;
// int polarity;
 //default speed
 // param_port=strdup("COM3");    //default for debugging


    printf("-------------------------------------------------------\n");
    printf("\n");
    printf(" Bus Pirate binary mode SPI SNIFFER utility v0.3 (CC-0)\n");
    printf(" http://dangerousprototypes.com\n");
    printf("\n");
    printf("-------------------------------------------------------\n");
   printf("\n\n\n");

//p == port
// p=polarity
// e=clock edge

if (argc <= 1)  {
	    printf("ERROR: Invalid argument(s).\n\n");
	    printf("Help Menu\n");
		print_usage(argv[0]);
		exit(-1);
	}

while ((opt = getopt(argc, argv, "ms:p:e:d:t:M:")) != -1) {
       // printf("%c  \n",opt);
		switch (opt) {

			case 'd':  // device   eg. com1 com12 etc
				if ( param_port != NULL){
					printf("Device/PORT error!\n");
					exit(-1);
				}
				param_port = strdup(optarg);
				break;
			case 'e':      // clock edge
 				if (param_clockedge != NULL) {
					printf("Clock Edge should be 0 or 1\n");
					exit(-1);
				}
				param_clockedge = strdup(optarg);

				break;
			case 'p':
				if (param_polarity != NULL) {
					printf("Polarity must be 0 or 1\n");
					exit(-1);
				}
				param_polarity = strdup(optarg);

				break;
				case 's':
                        if (param_speed != NULL) {
                            printf("Speed should be set: eg  115200 \n");
					    exit(-1);
				        }
				        param_speed = strdup(optarg);
                        break;
	            case 't':
                        if (param_test != NULL) {
                            printf("Test Parameter should either be long or short \n");
					        exit(-1);
                        }
                        param_test = strupr(strdup(optarg));
                        if (strcmp(param_test,"S")==0)
                            {
                                 buffer[0]=0x10;
                            } else
                            if (strcmp(param_test,"L")==0){

                                  buffer[0]=0x11;
                            }

                            else{

                            printf("Test Parameter should either be long or short \n");
					        exit(-1);

                               }
                               printf("Self-Test Activated with '%s' parameter \n",param_test);

                               buffer[1]='\0';

                         break;
			case 'm':    //modem debugging for testing
                   modem =TRUE;   // enable modem mode
				break;
            case 'M':
                        if (param_bbmode != NULL) {
                            printf("-M mode where mode is any of the following:  \n");
                            printf("      SPI, IC2, ART, 1W0 and RAW \n");
	                    	printf("      default is SPI mode e.g -M SPI\n      ");
                            exit(-1);
                        }
                        param_bbmode = strupr(strdup(optarg));
                        char str[] ="SPI IC2 ART 1W0 RAW";
                        char *p;
                        char cmode[3];
                        p = strstr (str, param_bbmode);
                        if (p!=NULL)
                        {
                            strncpy (cmode, p, 3);
                            cmode[3]='\0';
                            //locate in array to fine get mode
                             int mode_size = sizeof(modes)/sizeof(char *);
                             for (counter=1;counter< mode_size;counter++)
                             {
                                 if (strcmp(cmode,modes[counter])==0)
                                 {

                                     BBmode=counter;
                                     break;
                                 }
                             }

                        }
                        else
                        {
                            printf("Error in Setting Mode Parameter\n");
                            exit(-1);
                        }
                        break;

			default:
				printf("Invalid argument %c", opt);
				print_usage(argv[0]);
				//exit(-1);
				break;
		}
	}
    printf(" Press escape to exit \n");
    printf("\n");



    //param_port=strdup("COM3");
    //Set default if NULL
    if (param_port==NULL){
        printf("No serial port set\n");
		print_usage(argv[0]);
		exit(-1);
    }

    if (param_clockedge==NULL)
          param_clockedge=strdup("1");

    if (param_polarity==NULL)
          param_polarity=strdup("0");
    if (param_bbmode==NULL) {
          param_bbmode=strdup("SPI");
          BBmode=0x01;
    }
    if (param_speed==NULL)
          param_speed=strdup("115200");


    printf("\n  Parameters used: Device = %s,  Speed = %s, Clock Edge= %s, Polarity= %s BBmode = %s \n\n",param_port,param_speed,param_clockedge,param_polarity,param_bbmode);

	printf(" Opening Bus Pirate on %s at %sbps...\n", param_port, param_speed);
	fd = serial_open(param_port);
	if (fd < 0) {
		fprintf(stderr, "Error opening serial port\n");
		return -1;
	}

    //
	// Enter binary mode, then enter a protocol mode
	//
	serial_setup(fd,(speed_t) param_speed);

	printf(" Starting SPI sniffer...\n");




    status= BP_EnableBinary(fd);  //enter BBIO, should response BBIO

    if (status==ERR )
    {
        fprintf(stderr, "Buspirate cannot switch to binary mode :( \n");
        return -1;
    }

	if (modem==TRUE){    // connected to modem for testing response	{

              serial_write( fd, "ATI3\x0D\0",5 );
	          Sleep(1);
	          res= serial_read(fd, buffer, sizeof(buffer));
	          printf("\n %s\n",buffer);

              serial_write( fd, "ATI4\x0D\0",5 );
	          Sleep(1);
	          res= serial_read(fd, buffer, sizeof(buffer));
	          printf("\n %s\n",buffer);
              serial_write( fd, "ATI7\x0D\0",5 );
	          Sleep(1);
	          res= serial_read(fd, buffer, sizeof(buffer));
	          printf("\n %s\n",buffer);


	}
	else
	{


        fprintf(stderr, " Configuring Bus Pirate...\n");


	}

       if (param_test!=NULL)
       {


       // Send 0x10 to run the short test, 0x11 to run the long test
       // Get the reply, decode according to these instructions:
       // http://dangerousprototypes.com/docs/Self-test
       // Close the serial port and pause for space (repeat) or esc (exit)
          fprintf(stderr, " Entering Self-test mode...\n");

                 serial_write( fd,buffer, 1);
                 res=SELFTEST;

           }


             else
       {  // Enter  SPI MODE

          res =  BP_EnableMode(fd, BBmode);
          if (res==ERR)
          {
              printf("The Device responde wrong! It should respond: 0X%0X\n",BBmode);
              printf("Exit and reset device\n");
              exit(-1);
          }
          printf("Current mode setting is %s\n",modes[res]);

       }


       if (res==BBmode){
          //
	      //Start sniffer
	      //
          //configure according to user settings
          //1000wxyz - SPI config, w=HiZ/3.3v, x=CKP idle, y=CKE edge, z=SMP sample
             i=0x80;
             if(param_clockedge)
                  i|=0x02;
             if(param_polarity)
                  i|=0x04;

            BP_WriteToPirate(fd, &i);

            //start the sniffer
             serial_write( fd, "\x0E", 1);
            // Done with setup

        }


	printf(" (OK) Happy sniffing! Press ESC to stop.\n");


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
        // if in testmode, if buffer[c]=0x00 means ok, other value means error?
        if(kbhit()){
           c = getch();

           if(c == 27){
                printf("\n Esc key hit, stopping...\n");

                if (param_test !=NULL)
                {
                   printf(" Stopping Self-test...\n");
                     buffer[0]=0xFF;//exit sniffer
                     res = serial_write( fd, buffer, 1);
                     Sleep(1);
                     res= serial_read(fd, buffer, 1);
                     if (buffer[0]==0x01)
                     {
                         printf("Returning to Binary Bitbang mode: \n");
                     }

                   printf(" Exiting Test Mode!)\n");
                }


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
    FREE (param_bbmode);
    FREE (param_test);
	FREE(param_port);
	FREE(param_speed);
    return 0;
}
