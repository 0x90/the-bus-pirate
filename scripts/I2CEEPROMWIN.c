/* Author: James Stephenson
 * This program runs under windows and uses the bus pirate to write a file in 
 * ascii hex to an I2C eeprom such as the 24FC64, note the address used is 2 bytes.
 * Released under the WTF license.
 *
 * Hex file should contain space seperated hex values and no line breaks, ie: 
 * 0xFF 0xAA 0x BB
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(int argc, char **argv){
	FILE *inpfile;
    DCB my_dcb;
	HANDLE hComm;
    int bytes_written, bytes_received, retval, memaddr, loop;
    unsigned char receive_buf[8], write_buf[7], curcode[5], curbincode, chipaddr;
    
    if(argc != 4){
	    printf("pc_serial [com?] [addr 0-8] [file]\n");
		return 1;		
    }

	if(argv[2][0] > '8' || argv[2][0] < '0'){
		printf("Chip address out of range\n");
		return 2;
	}

	if(!(inpfile = fopen(argv[3], "rb"))){
		printf("Error opening input file\n");
		return 2;
	}
    
    hComm = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if(hComm == INVALID_HANDLE_VALUE){
        printf("Error Opening Serial Port\n");
        return 3;
    }
    
	my_dcb.DCBlength = sizeof(my_dcb);
	GetCommState(hComm, &my_dcb);
	my_dcb.BaudRate = CBR_115200;
	my_dcb.ByteSize = 8;
	my_dcb.StopBits = ONESTOPBIT;
	my_dcb.Parity = NOPARITY;

	if(!SetCommState(hComm, &my_dcb)){
		printf("Error setting up serial port\n");
		return 4;
	}	

	//Enter I2C binary mode and activate power, pullups and low speed.
	WriteFile(hComm, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xE0\x02", 22, &bytes_written, 0);
	ReadFile(hComm, receive_buf, 8, &bytes_received, 0);
	receive_buf[8] = 0;
	if(memcmp(receive_buf, "BBIO1\xE0I2C", 8)){
		printf("Error setting up RAW I2C mode: %s\n", receive_buf);
		printf("%x", receive_buf[5]);
		return 5;
	}

//0x02 start bit
//0x03 stop bit
//0x13 write 4 bytes
//0xAA chip address
//0xBB address high byte
//0xCC address low byte
//0xDD data byte

	memaddr = 0;
	chipaddr = 0xA0 | (argv[2][0] - '0');
	memcpy(write_buf, "\x02\x13\xAA\xBB\xCC\xDD\x03", 7);
	write_buf[2] = chipaddr;
	while(fread(curcode, 5, 1, inpfile)){
		if(!sscanf(curcode, "%X", &curbincode)){
			printf("Error processing code: %s", curcode);
			return 6;
		}
		write_buf[3] = memaddr >> 8; //address high byte
		write_buf[4] = memaddr & 0xFF; //address low byte
		write_buf[5] = curbincode; //data byte
		WriteFile(hComm, write_buf, 7, &bytes_written, 0);

		for(loop = 0; loop < 7; loop++)
			printf("%02x ", write_buf[loop]);
		ReadFile(hComm, receive_buf, 7, &bytes_received, 0);
		printf("- ");
		for(loop = 0; loop < 7; loop++)
			printf("%02x ", receive_buf[loop]);
		printf("\n");
		memaddr++;
	}

	WriteFile(hComm, "0x0F", 1, &bytes_written, 0);

    return 0;
}
