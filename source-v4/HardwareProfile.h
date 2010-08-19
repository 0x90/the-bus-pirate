#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H
#include <p24fxxxx.h>
//these are unneeded, but the stack complains if they're not defined
//#define USE_SELF_POWER_SENSE_IO
#define tris_self_power     TRISCbits.TRISC2    
#define self_power          1

//#define USE_USB_BUS_SENSE_IO
#define tris_usb_bus_sense  TRISCbits.TRISC2    
#define USB_BUS_SENSE       1 

#endif 
