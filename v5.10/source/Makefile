# Makefile for Linux/Unix by Stephan Walter <stephan@walter.name>

# change this line for your MPLAB installation
C30_PATH = /opt/microchip/mplabc30/v3.24

INCLUDES = -I$(C30_PATH)/support/PIC24F/h
PATH := $(C30_PATH)/bin:$(PATH)

DEFS = 
OPTIMIZE = -Os

CPU = 24FJ64GA002

SOURCES = 1wire.c AUXpin.c base.c baseIO.c baseUI.c basic.c binIO.c binIOhelpers.c binwire.c bitbang.c busPirateCore.c dio.c ee.c eetext.S HD44780.c I2C.c m_1wire_213.c main.c OpenOCD.c OpenOCD_asm.S pc_at_keyboard.c pic.c procMenu.c raw2wire.c raw3wire.c selftest.c SPI.c SUMP.c translations/en_US.s uart2io.c UART.c

# you shouldn't have to change anything below this line.

ARCH = pic30-
CC = $(ARCH)gcc
AS = $(ARCH)as
OBJDUMP = $(ARCH)objdump
BIN2HEX = $(ARCH)bin2hex

ASFLAGS = -p=$(CPU)
CFLAGS = -Wall $(OPTIMIZE) $(DEFS) $(INCLUDES) -mcpu=$(CPU) -mlarge-code -mlarge-data
LDFLAGS = -Tp$(CPU).gld

OBJ = $(patsubst %.S,%.S.o,$(patsubst %.c,%.o,${SOURCES}))

.PHONY: all clean
.PRECIOUS: %.o %.S.o %.coff

all: main.hex

clean:
	rm -rf *.o *.coff *.hex

%.S.o: %.S
	@echo "  CC      $@"
	@$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.c
	@echo "  CC      $@"
	@$(CC) -c $(CFLAGS) -o $@ $<

%.coff: $(OBJ)
	@echo "  LINK    $@"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

%.hex: %.coff
	@echo "  BIN2HEX $@"
	@$(BIN2HEX) $< -v

