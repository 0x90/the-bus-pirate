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

#include "uart.h"

#include "usbprogjtag.h"



void tap_shift_interrupt(uint8_t *in_buf, uint8_t *tdo_buf, uint16_t end_cnt)
{
	uint8_t unsent_data = 0;
	uint16_t bit_cnt;
	uint16_t buf_off;

	for (bit_cnt = 0; bit_cnt < end_cnt; bit_cnt++) {
		buf_off = (bit_cnt/8);

		// wait for interrupt to receive atleast 2 bytes
		while (bytes_recv <= buf_off*2+1);

		// control tdi
		if ((in_buf[buf_off*2] >> ((bit_cnt % 8))) & 0x1) //tdi 1
			SETBIT(BIT3_WRITE,BIT3);
		else // tdi 0
			CLEARBIT(BIT3_WRITE,BIT3);

		// control tms line
		if((in_buf[(buf_off*2)+1] >> ((bit_cnt % 8))) & 0x1)
			SETBIT(BIT1_WRITE,BIT1);
		else
			CLEARBIT(BIT1_WRITE,BIT1);

		// clock
		CLEARBIT(BIT2_WRITE,BIT2);
		asm("nop");
		asm("nop");
		//asm("nop");
		SETBIT(BIT2_WRITE,BIT2);

		// read tdo
		if(IS_BIT0_SET())
			tdo_buf[(bit_cnt)/8] |= 1 << (bit_cnt % 8);
		else
			tdo_buf[(bit_cnt)/8] &= ~(1 << (bit_cnt % 8));


		unsent_data = 1;
		// if last bit of one byte was written
		if (bit_cnt%8 == 7) {
			unsent_data = 0;
			bytes_send_available++;
			// go send something
			if (bytes_send_available - bytes_send > 64) {
				UART1TX_Int();
			}
		}
	}
	if (unsent_data == 1) {
		bytes_send_available++;
	}

	// if there is something left - send it
	UART1TX_Int();
}

void tap_shift(uint8_t *tdo_buf, uint8_t *tms_buf, uint16_t size)
{
	uint16_t bit_cnt;
	for (bit_cnt = 0; bit_cnt < size; bit_cnt++) {
		// control tdi
		if ((tdo_buf[bit_cnt/8] >> ((bit_cnt) % 8)) & 0x1) //tdi 1
			SETBIT(BIT3_WRITE,BIT3);
		else // tdi 0
			CLEARBIT(BIT3_WRITE,BIT3);

		// control tms line
		if((tms_buf[bit_cnt/8] >> ((bit_cnt) % 8)) & 0x1)
			SETBIT(BIT1_WRITE,BIT1);
		else
			CLEARBIT(BIT1_WRITE,BIT1);

		// clock
		CLEARBIT(BIT2_WRITE,BIT2);
		asm("nop");
		SETBIT(BIT2_WRITE,BIT2);

		// read tdo
		if(IS_BIT0_SET())
			tdo_buf[(bit_cnt)/8] |= 1 << ((bit_cnt) % 8);
		else
			tdo_buf[(bit_cnt)/8] &= ~(1 << ((bit_cnt) % 8));
	}
}

void set_direction(uint8_t direction)
{
	// 0 = input, 1 = output
	if(direction & 0x01) SETBIT(BIT0_DDR,BIT0); else CLEARBIT(BIT0_DDR,BIT0);
	if(direction & 0x02) SETBIT(BIT1_DDR,BIT1); else CLEARBIT(BIT1_DDR,BIT1);
	if(direction & 0x04) SETBIT(BIT2_DDR,BIT2); else CLEARBIT(BIT2_DDR,BIT2);
	if(direction & 0x08) SETBIT(BIT3_DDR,BIT3); else CLEARBIT(BIT3_DDR,BIT3);
	if(direction & 0x10) SETBIT(BIT4_DDR,BIT4); else CLEARBIT(BIT4_DDR,BIT4);
	if(direction & 0x20) SETBIT(BIT5_DDR,BIT5); else CLEARBIT(BIT5_DDR,BIT5);
}


void set_port(uint8_t value)
{
	if(value & 0x01) SETBIT(BIT0_WRITE,BIT0); else CLEARBIT(BIT0_WRITE,BIT0);
	if(value & 0x02) SETBIT(BIT1_WRITE,BIT1); else CLEARBIT(BIT1_WRITE,BIT1);
	if(value & 0x04) SETBIT(BIT2_WRITE,BIT2); else CLEARBIT(BIT2_WRITE,BIT2);
	if(value & 0x08) SETBIT(BIT3_WRITE,BIT3); else CLEARBIT(BIT3_WRITE,BIT3);
}
