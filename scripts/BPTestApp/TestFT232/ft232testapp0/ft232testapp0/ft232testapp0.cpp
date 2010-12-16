// ft232testapp0.cpp : Defines the entry point for the console application.
//
//See  D@XXX programmers reference
// Objective:   Find devices connected to ports and enumerate them


#include "stdafx.h"
#include <windows.h>
#pragma comment(lib, "FTD2XX.lib")
#include "FTD2XX.h"
#include <stdlib.h>
#include <conio.h>	

FT_STATUS ftStatus;			//Status defined in D2XX to indicate operation result
FT_HANDLE ftHandle;			//Handle of FT2232H device port 

int _tmain(int argc, _TCHAR* argv[])
{
char *devices[]={"FT_DEVICE_232BM",
				"FT_DEVICE_232AM",
				"FT_DEVICE_100AX",
				"FT_DEVICE_UNKNOWN",
				"FT_DEVICE_2232C",
				"FT_DEVICE_232R",
				"FT_DEVICE_2232H",
				"FT_DEVICE_4232H",
				NULL,
};

	DWORD i;
	UCHAR Mask = 0xff;
	UCHAR Mode = 1;     // Set asynchronous bit-bang mode
	LONG lComPortNumber;
	DWORD devIndex = 0;
	DWORD numDevs;
	UCHAR BitMode;
	FT_DEVICE_LIST_INFO_NODE *devInfo;
	
	ftStatus = FT_CreateDeviceInfoList(&numDevs);
	if (ftStatus == FT_OK)
	{ 
		printf("Number of devices is %d\n",numDevs);
	}
	if (numDevs > 0)
	{
		// allocate storage for list based on numDevs
		devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);  // get the device information list
		ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs); 
		if (ftStatus == FT_OK)
		{
			for (i = 0; i < numDevs; i++)
			{ 
				printf("Dev %d:\n",i);
				printf(" Flags=0x%x\n",devInfo[i].Flags);
				printf(" Type=%s\n",devices[devInfo[i].Type]); 
				printf(" ID=0x%x\n",devInfo[i].ID);
				printf(" LocId=0x%x\n",devInfo[i].LocId);
				printf(" SerialNumber=%s\n",devInfo[i].SerialNumber);
				printf(" Description=%s\n",devInfo[i].Description);
				printf(" ftHandle=0x%x\n",devInfo[i].ftHandle);			
				
			}
		}
	  
	  
		i=0;  //open first device
	
		ftStatus = FT_Open(i,&ftHandle);

		if (ftStatus != FT_OK)
		{
			printf("Can't open %s device! \n",devInfo[i].Description);
		}
		else
		{     
			printf("Successfully open  %s device! \n",devInfo[i].Description);	
			ftStatus = FT_GetComPortNumber(ftHandle,&lComPortNumber);
			if (ftStatus == FT_OK)
			{ 
				if (lComPortNumber == -1)
				{ 
					printf(" NO com port Assigned!\n");
				}
				else
				{ 
					// COM port assigned with number held in lComPortNumber
					printf(" Current assigned COM Port: %d \n",lComPortNumber);
				} 
			}
			else
			{
				printf(" Failed to get the COM Port!\n");
			}
			FT_PROGRAM_DATA ftData;
			char ManufacturerBuf[32];
			char ManufacturerIdBuf[16];
			char DescriptionBuf[64];
			char SerialNumberBuf[16];
			ftData.Signature1 = 0x00000000; 
			ftData.Signature2 = 0xffffffff; 
			ftData.Version = 0x00000002; 
		
			ftData.Manufacturer = ManufacturerBuf;
			ftData.ManufacturerId = ManufacturerIdBuf;
			ftData.Description = DescriptionBuf;
			ftData.SerialNumber = SerialNumberBuf;
			ftStatus = FT_EE_Read(ftHandle, &ftData);
			if (ftStatus == FT_OK)
			{ 
				// FT_EE_Read OK, data is available in ftData
				printf(" EEPROM READ OK\n");
				printf(" Cbus0 Value: 0x%02X\n",ftData.Cbus0);
				printf(" Cbus1 Value: 0x%02X\n",ftData.Cbus1);
				printf(" Cbus2 Value: 0x%02X\n",ftData.Cbus2);
				printf(" Cbus3 Value: 0x%02X\n",ftData.Cbus3);

			} 
			else
			{ 
				// FT_EE_Read FAILED! 
					printf(" EEPROM READ FAILED\n");

			}

			ftStatus = FT_GetBitMode(ftHandle, &BitMode);
			if (ftStatus == FT_OK)
			{
				// BitMode contains current value
				printf(" Current Bit Mode: 0X%02X\n",BitMode);
			} 
			else
			{ 
				// FT_GetBitMode FAILED!
					printf(" GetBitMode Failed!\n");
			}
			
			printf(" Setting to Asynchroous Bit-Bang mode... \n");
			
			ftStatus = FT_SetBitMode(ftHandle, Mask, Mode);
			if (ftStatus == FT_OK) 
			{
				// 0xff written to device
				printf(" 0X%02X was written to device\n",Mask);
			}
			else
			{ 
				// FT_SetBitMode FAILED!
				printf(" Failed SetBitMode \n");
			}
		}
		printf("Resetting Device...");
		ftStatus = FT_ResetDevice(ftHandle);
		if( ftStatus!=FT_OK)
		{
			printf("...Bad\n..");
		}
		else
		{
			printf("...Ok\n");
		}

		FT_Close(ftHandle);
		printf ("Device closed \n");
	}
	printf("Press any key to exit.... \n");
	while(!_kbhit());
	return 0;
}


