/*
 * This file is part of the Bus Pirate project (http://code.google.com/p/the-bus-pirate/).
 *
 * Written and maintained by the Bus Pirate project.
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
//setup the library first
void bbSetup(unsigned char pins, unsigned char speed);

//byte functions
unsigned char bbReadWriteByte(unsigned char c);
void bbWriteByte(unsigned char c);
unsigned char bbReadByte(void);

//bit read and write functions
unsigned char bbReadBit(void);
void bbWriteBit(unsigned char c);
void bbClockTicks(unsigned char c);

//generic pin direction functions including delays for bitwise pin functions
void bbMOSI(unsigned char dir);
void bbCLK(unsigned char dir);
void bbCS(unsigned char dir);
unsigned char bbMISO (void);

//pin twiddling functions with delays
void bbH(unsigned int pins, unsigned char delay);
void bbL(unsigned int pins, unsigned char delay);
void bbPins(unsigned char dir, unsigned int pins, unsigned char delay);
unsigned char bbR(unsigned int pin);

//protocol helper functions
void bbI2Cstart(void);
void bbI2Cstop(void);

//protocol specific pseudo functions 
#define bbI2Cack()  bbWriteBit(0) //low bit is ACK
#define bbI2Cnack()  bbWriteBit(1) //high bit is NACK
