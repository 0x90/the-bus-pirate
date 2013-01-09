/**************************************************************************
*   Copyright (C) 2008 by Frans Schreuder                                 *
*   usbpicprog.sourceforge.net                                            *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
**************************************************************************/
#include "base.h"

/** Programmer pins *************************************************/
#define VPP 		BP_MISO
#define TRISVPP 	BP_MISO_DIR
#define VPP_RST 	BP_CS
#define TRISVPP_RST BP_CS_DIR
#define PGD 		BP_MOSI
#define TRISPGD 	BP_MOSI_DIR
#define PGD_READ 	BP_MOSI
#define PGC 		BP_CLK
#define TRISPGC 	BP_CLK_DIR
//#define VDD LATBbits.LATB2
//#define TRISVDD TRISBbits.TRISB2
//#define VPP_RUN LATAbits.LATA3
//#define TRISVPP_RUN TRISAbits.TRISA3
#define PGD_LOW 	BP_MOSI
#define TRISPGD_LOW BP_MOSI_DIR
#define PGC_LOW 	BP_CLK
#define TRISPGC_LOW BP_CLK_DIR
/** Voltage pump ****************************************************/
/*#define Pump1 LATAbits.LATA0
#define Pump2 LATAbits.LATA1
#define Pump1tris TRISAbits.TRISA0
#define Pump2tris TRISAbits.TRISA1
#define TMR1_PERIOD 1000 
#define CLOCK_FREQ 48
#define TMR1_PRESET (65535-((CLOCK_FREQ/4)*TMR1_PERIOD))
#define TMR1H_PRESET ((TMR1_PRESET & 0xFF00)>>8)
#define TMR1L_PRESET (TMR1_PRESET & 0x00FF)

#define TMR0_PERIOD 250
//TMR0 has a 1:16 prescaler
#define TMR0L_PRESET (255-((CLOCK_FREQ*TMR0_PERIOD)/(4*16))*/
