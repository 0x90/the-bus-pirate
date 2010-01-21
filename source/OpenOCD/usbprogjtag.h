/*
 * Copyright (C) 2006 Benedikt Sauter 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include "base.h"
#define BIT(x) (x)
#define SETBIT(addr,x)    (addr |= x)
#define CLEARBIT(addr,x)  (addr &= ~(x))

#define BIT0	    MISO //tdo  from the chip
#define BIT1  	    CS //tms
#define BIT2	    CLK //clk
#define BIT3	    MOSI //tdi  to the chip

#define BIT4	    AUX//SRST
#define BIT5	    0b1//TRST on PGD

#define BIT6	    LEDMODE //red LED


#define BIT0_DDR    IODIR
#define BIT1_DDR    IODIR
#define BIT2_DDR    IODIR
#define BIT3_DDR    IODIR

#define BIT4_DDR    IODIR
#define BIT5_DDR    IODIR
#define BIT6_DDR    LEDMODEDIR


#define BIT0_READ   IOPOR
#define BIT1_READ   IOPOR
#define BIT2_READ   IOPOR
#define BIT3_READ   IOPOR

#define BIT4_READ   IOPOR
#define BIT5_READ   IOPOR
#define BIT6_READ   LEDMODEPOR

//output port for pin writes (see3 hardwarevX.h for actual pins)
#define BIT0_WRITE   IOLAT
#define BIT1_WRITE   IOLAT
#define BIT2_WRITE   IOLAT
#define BIT3_WRITE   IOLAT

#define BIT4_WRITE   IOLAT
#define BIT5_WRITE   IOLAT
#define BIT6_WRITE   LEDMODELAT

// check if tdo == 1
#define IS_BIT0_SET()			    (BIT0_READ & BIT(BIT0))
#define IS_BIT1_SET()			    (BIT1_READ & BIT(BIT1)) 
#define IS_BIT2_SET()			    (BIT2_READ & BIT(BIT2))
#define IS_BIT3_SET()			    (BIT3_READ & BIT(BIT3))

#define IS_BIT4_SET()			    (BIT4_READ & BIT(BIT4))
#define IS_BIT5_SET()			    (BIT5_READ & BIT(BIT5))
#define IS_BIT6_SET()			    (BIT6_READ & BIT(BIT6))


#define SET_BIT0()			     SETBIT( BIT0_WRITE, BIT0 )
#define SET_BIT1()			     SETBIT( BIT1_WRITE, BIT1 )
#define SET_BIT2()			     SETBIT( BIT2_WRITE, BIT2 )
#define SET_BIT3()			     SETBIT( BIT3_WRITE, BIT3 )

#define SET_BIT4()			     SETBIT( BIT4_WRITE, BIT4 )
#define SET_BIT5()			     SETBIT( BIT5_WRITE, BIT5 )
#define SET_BIT6()			     SETBIT( BIT6_WRITE, BIT6 )

#define CLEAR_BIT0()			     CLEARBIT( BIT0_WRITE, BIT0 )
#define CLEAR_BIT1()			     CLEARBIT( BIT1_WRITE, BIT1 )
#define CLEAR_BIT2()			     CLEARBIT( BIT2_WRITE, BIT2 )
#define CLEAR_BIT3()			     CLEARBIT( BIT3_WRITE, BIT3 )

#define CLEAR_BIT4()			     CLEARBIT( BIT4_WRITE, BIT4 )
#define CLEAR_BIT5()			     CLEARBIT( BIT5_WRITE, BIT5 )
#define CLEAR_BIT6()			     CLEARBIT( BIT6_WRITE, BIT6 )





void write_tdi(char *buf, uint16_t size);
void write_tms(uint8_t  buf);
void write_and_read(char * buf, uint16_t size);
void read_tdo(char * buf, uint16_t size);

void set_direction(uint8_t direction);
void set_port(uint8_t value);
uint8_t get_port();
void set_bit(uint8_t bit, uint8_t value);
uint8_t get_bit(uint8_t bit);

