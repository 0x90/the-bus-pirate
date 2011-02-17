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
int cnt=0;
uint8_t *bin_buf;
uint32_t bin_buf_size;
#define FREE(x) if(x) free(x);
#ifndef WIN32
#define usleep(x) Sleep(x);
#endif
#define MAX_BUFFER 4096  //255 bytes

//http://www.whereisian.com/files/j-xsvf_002.swf

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
	uint8_t temp[2]={0};  // command buffer
	struct stat stbuf;
	int fd,timeout_counter;
	int res,c, nparam_bytechunks, bytePointer,filebytes, readSize;
	long fileSize;
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

/*	if (param_bytechunks==NULL) {
		param_bytechunks=strdup("200");  // default is 255 bytes
	}*/
	//nparam_bytechunks=atoi(param_bytechunks);
    nparam_bytechunks=MAX_BUFFER;

	if (param_speed==NULL) {
		param_speed=strdup("115200");  //default is 115200kbps
	}

	if (param_XSVF !=NULL) {
		//open the XSVF file
            XSVF = fopen(param_XSVF, "rb");
            if (XSVF == NULL) {
                printf("Error opening file\n");
            }

            fseek(XSVF, 0, SEEK_END);
            fileSize = ftell(XSVF);
            fseek(XSVF, 0, SEEK_SET);
            printf("File is %i bytes, ",fileSize);

            bin_buf = (uint8_t*)malloc(fileSize);
            if (bin_buf == NULL) {
               printf("Error allocating %ld bytes of memory\n", (long)fileSize);
               return -1;
            }
            memset(bin_buf, 0, fileSize);

            res = fread(bin_buf, sizeof(uint8_t), fileSize, XSVF);
            if (res <= 0) {
                printf("error reading file %s \n", param_XSVF);
            }
            printf("read %i bytes",res);

            fclose(XSVF);


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
	fprintf(stderr, " Entering XSVF Player Mode\n");
	temp[0]=0x03;
	serial_write( fd, temp, 1 );

	// Wait for 0xFF, if <0xFF then it is finished or error codes (see below)
    bytePointer=0; //where we are in the byte buffer array
    readSize=MAX_BUFFER; //hack this to be a full chunk
    cnt=0;
    printf(" Waiting for first data request...");
	while(1) {

            //wait for reply before sending the next chunks
			timeout_counter=0;
			while(1) {
				res= serial_read(fd, buffer, sizeof(buffer));
				if(res>0){
                    printf("ok\n");
				  // wait for 0xFF and send data, or error
					if ((buffer[0]!=XSVF_READY_FOR_DATA) || (fileSize==0)) {

					    //add text descriptions here
                        printf("End of operation reply %02X \n",buffer[0]);
                        switch (buffer[0]) {
                            case  XSVF_ERROR_NONE :
                                printf("  Success!\n");
                                break;
                            case XSVF_ERROR_UNKNOWN:
                             printf("  Unknown error: XSVF_ERROR_UNKNOWN \n");
                                break;
                            case XSVF_ERROR_TDOMISMATCH:
                             printf("  Device did not respond as expected: XSVF_ERROR_TDOMISMATCH \n");
                                break;
                            case XSVF_ERROR_MAXRETRIES:
                             printf("  Device did not respond: XSVF_ERROR_MAXRETRIES \n");
                                break;
                            case XSVF_ERROR_ILLEGALCMD :
                             printf("  Unknown XSVF command: XSVF_ERROR_ILLEGALCMD \n");
                                break;
                            case XSVF_ERROR_ILLEGALSTATE:
                             printf("  Unknown JTAG state: XSVF_ERROR_ILLEGALSTATE \n");
                                break;
                            case XSVF_ERROR_DATAOVERFLOW :
                             printf("  Error, data overflow: XSVF_ERROR_DATAOVERFLOW \n");
                                break;
                            case XSVF_ERROR_LAST:
                             printf("  Some other error I don't remember, probably isn't active: XSVF_ERROR_LAST \n");
                                break;
                            case XSVF_READY_FOR_DATA:
                             printf("  Error, end of file but the programmer says more data: XSVF_READY_FOR_DATA \n");
                                break;
                            default:
                             printf("Unkown error\n ");


                    }
						goto end;
                     }
                     break; //break loop and send data
				}else{
					printf(" waiting for reply...\n");
					Sleep(1);
					timeout_counter++;
					if(timeout_counter > 20){
						printf(" No reply.... Quitting.\n ");
						timeout_counter=0;
						goto end;
					}
				}
			}

            //send data
            if(fileSize<MAX_BUFFER){
                readSize=fileSize;
            }
			//send to bp
			temp[0]=(readSize>>8);
			temp[1]=readSize;
			cnt=cnt+readSize;

			printf("Sending %i Bytes (%04X)...",readSize, cnt);
			serial_write( fd, temp,2 );
			//for (c=0; c<readSize; c++)
			   //printf("%02X ", bin_buf[c+bytePointer]);
			//printf("\n");
			serial_write( fd, &bin_buf[bytePointer],readSize );

			bytePointer=bytePointer+readSize;//start 1 chunk in next itme
			fileSize=fileSize-readSize; //deincrement the remaining byte count

	}


	end:
    printf(" Thank you for Playing! :-)\n\n");
    fclose(XSVF);
	FREE(param_port);
 	FREE(param_speed);
    FREE(param_bytechunks);
    FREE(param_XSVF);
    return 0;
 }  //end main()
