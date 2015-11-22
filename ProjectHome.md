![http://the-bus-pirate.googlecode.com/svn/wiki/side.450.jpg](http://the-bus-pirate.googlecode.com/svn/wiki/side.450.jpg)

Bus Pirate v3. **[Buy a BPv3 for $30, including worldwide shipping](http://www.seeedstudio.com/depot/bus-pirate-v3-assembled-p-609.html?cPath=61_68).**

**[Bus Pirate manual and chip demonstrations](http://dangerousprototypes.com/docs/Bus_Pirate)**

[Read about the v3 hardware](http://dangerousprototypes.com/docs/Bus_Pirate#Hardware_documentation)

### New Download and SVN location ###
**[Bus Pirate downloads and SVN have moved!](http://code.google.com/p/dangerous-prototypes-open-hardware/source/browse/#svn%2Ftrunk%2FBus_Pirate)**


### About ###
Interfacing a new microchip can be a hassle. Breadboarding a circuit, writing code, hauling out the programmer, or maybe even prototyping a PCB. We never seem to get it right on the first try.

The ‘Bus Pirate’ is a universal bus interface that talks to most chips from a PC serial terminal, eliminating a ton of early prototyping effort when working with new or unknown chips. Many serial protocols are supported at 0-5.5volts, more can be added.
  * 1-Wire
  * I2C
  * SPI
  * JTAG
  * Asynchronous serial
  * MIDI
  * PC keyboard
  * HD44780 LCD
  * 2- and 3-wire libraries with bitwise pin control
  * Scriptable binary bitbang, 1-Wire, I2C, SPI, and UART modes

We added other stuff we need, like,
  * 0-6volt measurement probe
  * 1Hz-40MHz frequency measurement
  * 1kHz - 4MHz pulse-width modulator, frequency generator
  * On-board multi-voltage pull-up resistors
  * On-board 3.3volt and 5volt power supplies with software reset
  * Macros for common operations
  * Bus traffic sniffers (SPI, I2C)
  * A bootloader for easy firmware updates
  * Transparent USB->serial mode
  * 10Hz-1MHz [SUMP compatible](http://www.sump.org/projects/analyzer/client/) low-speed [logic analyzer](http://dangerousprototypes.com/2009/11/03/bus-pirate-logic-analyzer-mode/)
  * AVR STK500 v2 programmer clone
  * Supported in AVRDude programmer
  * Scriptable from Perl, Python, etc.
  * Translations (currently Spanish and Italian)

Since this has been such a useful tool for us, we cleaned up the code, documented the design, and released it here with specs, schematic, and source code.

**[Bus Pirate manual and chip demonstrations](http://dangerousprototypes.com/docs/Bus_Pirate)**

### License ###

All our work is public domain, but we used some other open code that isn't.

NOTE: not all files are public domain. Code, code modifications, and hardware created by the project are released into the public domain under the [Creative Commons '0' license](http://creativecommons.org/publicdomain/zero/1.0/), as noted in each source file.

This source may also include files from other authors which have other licenses, for example GPL, or other open but restrictive licenses. These licenses may or may not be included in the source files.

  * 1wire, I2C library. GPL, (c) 2000 Michael Pearce. (I2C deprecated)
  * Python PIC24F programmer script. GPL, (c) 2009 Joseph Jezak.
  * 1wire search functions, CRC. Public domain, Maxim 1Wire Public Domain Kit.

The AVRSTKv2 programmer firmware is a port of Guido Socher’s GPL'd source for the [AvrUSB500v2 programmer](http://www.tuxgraphics.org/electronics/200705/article07052.shtml). [The original AvrUSB500v2 hardware is available here](http://shop.tuxgraphics.org/electronic/index-avr-programmer.html).

This program and hardware is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.