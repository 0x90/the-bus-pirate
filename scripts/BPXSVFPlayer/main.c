#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifdef WIN32
#include <conio.h>
 #include <windef.h>

#else
//#include <curses.h>
#endif

#include "serial.h"
#include "buspirate.h"


#define  JTAG_RESET        0x01
#define  JTAG_CHAIN_SCAN   0x02
#define  XSVF_PLAYER       0x03


#define XSVF_ERROR_NONE            0x00
#define XSVF_ERROR_UNKNOWN         0x01
#define XSVF_ERROR_TDOMISMATCH     0x02
#define XSVF_ERROR_MAXRETRIES      0x03
#define XSVF_ERROR_ILLEGALCMD      0x04
#define XSVF_ERROR_ILLEGALSTATE    0x05
#define XSVF_ERROR_DATAOVERFLOW    0x06
#define XSVF_ERROR_LAST            0x07
#define XSVF_READY_FOR_DATA        0xFF

char *dumpfile;
HANDLE dumphandle;
int modem =FALSE;
#define FREE(x) if(x) free(x);
#ifndef WIN32
#define usleep(x) Sleep(x);
#endif
#define MAX_BUFFER 32  //255 bytes

int print_usage(char * appname)
{
		//print usage
		printf("\n");
		printf("\n");
	    printf(" Help Menu\n");
        printf(" Usage:              \n");
		printf("   %s  -p device -f filename.xsvf -s speed  \n ",appname);
		printf("\n");
		printf("   Example Usage:   %s -p COM1 -s 115200 -f example.xsvf  \n",appname);
		printf("\n");
		printf("           Where: -p device is port e.g.  COM1  \n");
		printf("                  -s Speed is port Speed  default is 115200 \n");
		printf("                  -f Filename of XSVF file \n");
//		printf("                  -x bytes to send per chunk default is 16 bytes \n");
		printf("\n");

        printf("-----------------------------------------------------------------------------\n");


		return 0;
}

int main(int argc, char** argv)
{
	int opt;
	uint8_t buffer[MAX_BUFFER]={0};
	uint8_t temp[1]={0};  // command buffer
	struct stat stbuf;
	int fd,timeout_counter;
	int res,c, nparam_bytechunks;
	FILE *XSVF;
	int  xsvf;
	char *param_port = NULL;
	char *param_speed = NULL;
	char *param_XSVF=NULL;
	char *param_bytechunks=NULL;

	printf("-----------------------------------------------------------------------------\n");
	printf("\n");
	printf(" BusPirate XSVF Player V.01\n");
	printf(" http://www.dangerousprototypes.com\n");
	printf("\n");
	printf("-----------------------------------------------------------------------------\n");



	if (argc <= 1)  {
		print_usage(argv[0]);
		exit(-1);
	}


	while ((opt = getopt(argc, argv, "s:p:f:")) != -1) {

		switch (opt) {
			case 'p':  // device   eg. com1 com12 etc
				if ( param_port != NULL){
					printf("Device/PORT error!\n");
					exit(-1);
				}
				param_port = strdup(optarg);
				break;

			case 'f':      // clock edge
				if (param_XSVF != NULL) {
					printf("XSVF file\n");
					exit(-1);
				}
				param_XSVF = strdup(optarg);

				break;

			case 's':
				if (param_speed != NULL) {
					printf("Speed should be set: eg  115200 \n");
					exit(-1);
				}
				param_speed = strdup(optarg);

				break;

			default:
				printf(" Invalid argument %c", opt);
				print_usage(argv[0]);
				exit(-1);
				break;
		}
	}

	if (param_port==NULL){
		printf(" No serial port specified\n");
		print_usage(argv[0]);
		exit(-1);
	}

	if (param_bytechunks==NULL) {
		param_bytechunks=strdup("26");  // default is 255 bytes
	}
	nparam_bytechunks=atoi(param_bytechunks);
    nparam_bytechunks=MAX_BUFFER;

	if (param_speed==NULL) {
		param_speed=strdup("115200");  //default is 115200kbps
	}

	if (param_XSVF !=NULL) {
		//open the XSVF file
		if(( xsvf=open(param_XSVF,O_RDONLY))==-1){
			printf("Cannot open XSVF file.\n");
			exit(-1);
		}
		else {
			XSVF = fdopen(xsvf, "rb");
			// get filesize, chunk should be smaller than or equal to
			if (fstat(xsvf, &stbuf) == -1) {
				printf("Error getting filesize\n");
				exit(-1);
			}
			if (nparam_bytechunks > stbuf.st_size) {
				nparam_bytechunks=stbuf.st_size;
				printf("chunk size exceeds filesize, using %i bytes",nparam_bytechunks);

			}
		}

	} else {
		printf("No file specified. Need an input xsvf file \n");
		exit(-1);
	}
	printf(" Opening Bus Pirate on %s at %sbps, using XSVF file %s \n", param_port, param_speed,param_XSVF);
	fd = serial_open(param_port);
	if (fd < 0) {
		fprintf(stderr, " Error opening serial port\n");
		return -1;
	}

	//setup port and speed
	serial_setup(fd,(speed_t) param_speed);

	// Enter XSVF Player Mode
	//Open the port and send 0x03 to enter XSVF player mode
    //try resetting

	fprintf(stderr, " Configuring Bus Pirate to use XSVF Player Mode\n");
	temp[0]=0x03;
	serial_write( fd, temp, 1 );
	// Wait for 0xFF, if <0xFF then it is finished or error codes (see below)
	timeout_counter=0;
	while(1) {
		res= serial_read(fd, buffer, sizeof(buffer));
		if(res>0){
			//wait for 0xFF
			if (buffer[0]==XSVF_READY_FOR_DATA) {
			// Mode ok
				break;
			}
			else{
				//display the response
				printf(" Error: BP reply with %i bytes ...\n",res);
				for(c=0; c<res; c++){
					printf("%02X ", buffer[c]);
				}
				printf("\nQuitting...\n");
				exit(1);
			}
		}
		else {
			printf(" waiting for reply...\n");
			Sleep(1);
			timeout_counter++;
			if(timeout_counter > 5){
				printf(" No reply.... Quitting.\n ");
				timeout_counter=0;
				exit(1);
			}
		}
	}

	printf(" Sending File Content.. \n");

	while(!feof(XSVF)) {
		if ((res=fread(&buffer,sizeof(unsigned char),nparam_bytechunks,XSVF)) > 0) {
			//send to bp

			temp[0]=res;
		//	printf("Sending %02X Bytes....\n",temp[0]);
			serial_write( fd, temp,1 );
			for (c=0; c<res; c++)
			   printf("%02X ", buffer[c]);
			printf("\n");
			serial_write( fd, buffer,res );
			//wait for reply before sending the next chunks
			timeout_counter=0;
			while(1) {
				res= serial_read(fd, buffer, sizeof(buffer));
				if(res>0){


                    switch (buffer[0]) {

                            case  XSVF_ERROR_NONE :
                                printf("  XSVF_ERROR_NONE \n");
                                break;
                            case XSVF_ERROR_UNKNOWN:
                             printf("  XSVF_ERROR_UNKNOWN \n");
                                break;
                            case XSVF_ERROR_TDOMISMATCH:
                             printf("  XSVF_ERROR_TDOMISMATCH \n");
                                break;
                            case XSVF_ERROR_MAXRETRIES:
                             printf("  XSVF_ERROR_MAXRETRIES \n");
                                break;
                            case XSVF_ERROR_ILLEGALCMD :
                             printf("  XSVF_ERROR_ILLEGALCMD \n");
                                break;
                            case XSVF_ERROR_ILLEGALSTATE:
                             printf("  XSVF_ERROR_ILLEGALSTATE \n");
                                break;
                            case XSVF_ERROR_DATAOVERFLOW :
                             printf("  XSVF_ERROR_DATAOVERFLOW \n");
                                break;
                            case XSVF_ERROR_LAST:
                             printf("  XSVF_ERROR_LAST \n");
                                break;
                            case XSVF_READY_FOR_DATA:
                             printf("  XSVF_READY_FOR_DATA \n");
                                break;
                            default:
                             printf("Unkown error\n ");


                    }
                    if (buffer[0]==XSVF_READY_FOR_DATA){
                       break;
                    }

				   printf(" Exiting with Error:  ...");
				   for(c=0; c<res; c++){
					  printf("%02X ", buffer[c]);
				   }
				   printf("\n\n");
				   exit(1);
				   //break;
				}
				else {
					printf(" waiting for reply...\n");
					Sleep(1);
					timeout_counter++;
					if(timeout_counter > 5){
						printf(" No reply.... Quitting.\n ");
						timeout_counter=0;
						exit(1);
						break;
					}
				}
			}
		}
	}
    printf(" Thank you for Playing! :-)\n\n");

    close(xsvf);
    fclose(XSVF);
	FREE(param_port);
 	FREE(param_speed);
    FREE(param_bytechunks);
    FREE(param_XSVF);
    return 0;
 }  //end main()
