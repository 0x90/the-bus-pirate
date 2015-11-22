<h1>Bus Pirate: Reference</h1>

<p>This guide explains the <a href='http://www.buspirate.com/'>Bus Pirate</a> I/O pins, describes each menu available from the Bus Pirate terminal, and documents the syntax functions for each protocol library. This is the master updated copy of the Bus Pirate command reference. Most recently updated for firmware v3.0. See previous guides: <a href='http://www.buspirate.com'>v0h</a>, <a href='http://dangerousprototypes.com/2009/08/08/bus-pirate-menu-protocol-and-syntax-guide/'>v2.0</a>.<br />

<a> </a><br />
<strong>I/O header pin descriptions</strong><em><br />
</em></p>
<p><img src='http://wherelabs.files.wordpress.com/2009/08/mode-guide.png?w=450&#038;h=152' alt='mode-guide' height='152' width='450' title='mode-guide' /></p>
<p>The Bus Pirate I/O pins try to be consistent across all libraries, the same pins are used for similar functions. Unused pins are usually  in a safe high-impedance state. Modes not shown in the above diagram are similar to other libraries: MIDI=UART; raw2wire=HD44780=PC keyboard=I2C; raw3wire=SPI. All bus pins output at 3.3volts, but tolerate up to 5volts (5.5volts maximum).</p>
<p><em>Master-out slave-in</em> (MOSI) is the primary data pin, it's used for bi-directional data transfer in protocols like I2C and 1-Wire, and as data-out from the Bus Pirate in uni-directional protocols like SPI and asynchronous serial (UART).</p>
<p><em>Clock</em> is always a clock-out signal from the Bus Pirate, except in the PC keyboard library where the keyboard provides a clock signal <span>to</span> the Bus Pirate.</p>

<p><em>Master-in slave-out</em> (MISO) is used with protocols that have a dedicated data-input, such as SPI and UART.</p>
<p><em>Chip select</em> (CS) is an output used to activate the serial interface in SPI-like protocols. <em>Use the auxiliary pin config menu (c) to get manual control of the CS pin through the auxiliary pin commands (a, A, @).</em></p>
<p>The <em>auxiliary</em> pin (AUX) can be used as an output or input from the Bus Pirate terminal interface with the A, a, and @ commands. It's useful for protocols that require an additional signal, such as a reset.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/07/bpv3v2go-pinout.png?w=430&#038;h=265' alt='BPv3v2go-pinout' height='265' width='430' title='BPv3v2go-pinout' /></p>
<table border='0'>

<tbody>
<tr>
<td><strong>Pin name<br />
</strong></td>
<td><strong>Description (Bus Pirate is the master)</strong></td>
</tr>
<tr>
<td>MOSI</td>
<td>Master data out, slave in (SPI, JTAG), Serial data (1-Wire, I2C, KB), TX<b>(UART)</td>
</tr></b><tr>
<td>CLK</td>

<td>Clock signal (I2C, SPI, JTAG, KB)</td>
</tr>
<tr>
<td>MISO</td>
<td>Master data in, slave out (SPI, JTAG) RX (UART)</td>
</tr>
<tr>
<td>CS<b></td></b><td>Chip select (SPI), TMS (JTAG)</td>
</tr>
<tr>
<td>AUX</td>

<td>Auxiliary IO, frequency probe, pulse-width modulator</td>
</tr>
<tr>
<td>ADC</td>
<td>Voltage measurement probe (max 6volts)</td>
</tr>
<tr>
<td>Vpu</td>
<td>Voltage input for on-board pull-up resistors (0-5volts).</td>
</tr>
<tr>
<td>+3.3v</td>

<td>+3.3volt switchable power supply</td>
</tr>
<tr>
<td>+5.0v</td>
<td>+5volt switchable power supply</td>
</tr>
<tr>
<td>GND</td>
<td>Ground, connect to ground of test circuit</td>
</tr>
</tbody>
</table>

<p>Notes: **TX moved from CS to MOSI in firmware v0g.</p>**<p><strong>The user interface<br />
</strong></p>
<p>Talk to the Bus Pirate from a serial terminal set to 115200bps, 8/N/1.</p>
<p><b>Syntax error, type ? for help</b><br />
HiZ></p>
<p>Press enter to show the command prompt if your terminal is blank.</p>
<p>HiZ>m <strong><<<set mode command</strong><br />

1. HiZ<br />
...<br />
10. LCD<br />
(1) ><strong><<<press enter to select default option (1)</strong><br />
Mode selected<br />
HiZ></p>
<p>Most configuration and option prompts have a default value shown in (). Press enter to select the default option.</p>
<p>Read more in the <a href='http://dangerousprototypes.com/2009/07/23/bus-pirate-101/'>Bus Pirate 101 tutorial</a>.<br />

<a> </a><br />
<strong>Menus</strong></p>
<table border='0'>
<tbody>
<tr>
<td><strong>Menu</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>?</td>
<td>Help menu with latest menu and syntax options.</td>

</tr>
<tr>
<td>I</td>
<td>Hardware/firmware/<a href='http://dangerousprototypes.com/2009/08/07/find-your-bus-pirates-pic-revision/'>microcontroller</a> information<a href='http://dangerousprototypes.com/2009/08/07/find-your-bus-pirates-pic-revision/'></a> (firmware v2.1+).</td>
</tr>
<tr>
<td>M</td>
<td>Set bus mode (1-Wire, SPI, I2C, JTAG, UART, etc).</td>

</tr>
<tr>
<td>B</td>
<td>Set PC side serial port speed.</td>
</tr>
<tr>
<td>O</td>
<td>Data display format (DEC, HEX, BIN, or raw).</td>
</tr>
<tr>
<td>V</td>
<td>Power supply voltage report (v1+ hardware only).</td>

</tr>
<tr>
<td>F</td>
<td>Measure frequency on the AUX pin. (1Hz-40MHz)</td>
</tr>
<tr>
<td>G</td>
<td>Frequency generator/PWM on the AUX pin. (1kHz-4MHz)</td>
</tr>
<tr>
<td>C</td>
<td>Toggle AUX control between AUX and CS/TMS pins.</td>

</tr>
<tr>
<td>L</td>
<td>Set <a href='http://en.wikipedia.org/wiki/Least_significant_bit'>LSB/MSB</a> first in applicable modes.</td>
</tr>
<tr>
<td>P</td>
<td><a href='http://dangerousprototypes.com/2009/07/27/bus-pirate-practical-guide-to-pull-up-resistors/'>Pull-up resistors</a> (V0,V2+ hardware).</td>

</tr>
<tr>
<td>=</td>
<td>Convert HEX/DEC/BIN number format (firmware v2.1+).</td>
</tr>
<tr>
<td>~</td>
<td>Perform a <a href='http://dangerousprototypes.com/2009/07/28/bus-pirate-self-test-guide/'>self-test</a> (firmware v2.0+).</td>
</tr>
<tr>

<td>#</td>
<td>Reset (firmware v2.0+).</td>
</tr>
</tbody>
</table>
<p>Menu options are single character commands that configure the Bus Pirate. Type a letter, followed by <code>&lt;enter&gt;</code>, to access the menu. Some options are unavailable in some modes and on some hardware.</p>
<p><a href='http://dangerousprototypes.com/bus-pirate-manual/bus-pirate-menu-options-guide/'>Menu options guide</a>.</p>
<p><a> </a><br />
<strong>Syntax and macros</strong></p>

<table border='0'>
<tbody>
<tr>
<td><strong>Syntax</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>A/a/@</td>
<td>Toggle auxiliary pin. Capital “A” sets AUX high, small “a” sets to ground. @ sets aux to input (high impedance mode) and reads the pin value.</td>
</tr>
<tr>
<td>D/d</td>

<td>Measure voltage on the ADC pin (v1+ hardware only).</td>
</tr>
<tr>
<td>W/w</td>
<td>Capital ‘W’ enables the on-board power supplies. Small ‘w’ disables them. (v1+ hardware only).</td>
</tr>
<tr>
<td>{ or [</td>
<td>Bus start condition.</td>
</tr>
<tr>
<td>] or }</td>

<td>Bus stop condition.</td>
</tr>
<tr>
<td>R or r</td>
<td>Read one byte. (r:1…255 for bulk reads)</td>
</tr>
<tr>
<td>0b</td>
<td>Write this binary value. Format is 0b00000000 for a byte, but partial bytes are also fine: 0b1001.</td>
</tr>
<tr>
<td>0h/0x</td>

<td>Write this HEX value. Format is 0h01 or 0×01. Partial bytes are fine: 0xA. A-F can be lower-case or capital letters.</td>
</tr>
<tr>
<td>0-255</td>
<td>Write this decimal value. Any number not preceded by 0x, 0h, or 0b is interpreted as a decimal value.</td>
</tr>
<tr>
<td>,</td>
<td>Value delimiter. Use a coma or space to separate numbers. Any combination is fine, no delimiter is required between non-number values: {0xa6,0, 0 16 5 0b111 0haF}.</td>
</tr>
<tr>
<td>&</td>

<td>Delay 1uS. (&:1…255 for multiple delays)</td>
</tr>
<tr>
<td>(#)</td>
<td>Run macro, (0) for macro list</td>
</tr>
<tr>
<td><em>Bitwise</em></td>
<td></td>
</tr>
<tr>
<td>^</td>

<td>Send one clock tick. (^:1…255 for multiple clock ticks)</td>
</tr>
<tr>
<td>/ or \</td>
<td>Toggle clock level high (/) and low (\). Includes clock delay (100uS).</td>
</tr>
<tr>
<td>- or <i></td></i><td>Toggle data state high (-) and low (<i>). Includes data setup delay (20uS).</td>
</tr></i><tr>
<td>!</td>

<td>Read one bit with clock.</td>
</tr>
<tr>
<td>.</td>
<td>Read data pin state (no clock).</td>
</tr>
</tbody>
</table>
<p>A simple syntax is used to interact with chips. Syntax characters have the same general function in each bus mode, such as 'R' to read a byte of data.</p>
<p><a href='.md'>0x31 r:5</a></p>

<p>This example syntax sends a bus start , the value 0x31, and then reads 5 bytes, followed by bus stop. Up to 4000 characters of syntax may be entered into the Bus Pirate terminal at once, press enter to execute the syntax.</p>
<p>I2C>(0)<br />
0.Macro menu<br />
1.7bit address search<br />
2.I2C sniffer<br />
I2C>(1)</p>
<p>Macros perform complex actions, like scanning for I2C addresses, interrogating a smart card, or probing a JTAG chain. Macros are numbers entered inside (). Macro (0) always displays a list of macros available in the current bus mode.</p>

<p><a> </a><br />
<strong>Bus Modes</strong></p>
<p>The Bus Pirate always starts in <a href='http://en.wikipedia.org/wiki/High_impedance'>high impedance</a> mode (Hi-Z), a safe mode with all outputs disabled. It's intended to protect any connected devices from conditions beyond their specifications. Each bus mode is described on the pages below.</p>
<p>Go to: <a href='http://dangerousprototypes.com/bus-pirate-manual/bus-pirate-1-wire-guide/'>1-Wire</a>, <a href='http://dangerousprototypes.com/bus-pirate-manual/bus-pirate-uart-guide/'>UART</a>, <a href='http://dangerousprototypes.com/bus-pirate-manual/i2c-guide/'>I2C</a>, <a href='http://dangerousprototypes.com/bus-pirate-manual/bus-pirate-spi-guide/'>SPI</a>, <a href='http://dangerousprototypes.com/bus-pirate-manual/bus-pirate-jtag-guide/'>JTAG</a>, <a href='http://dangerousprototypes.com/bus-pirate-manual/bus-pirate-raw2wire-guide/'>raw 2-wire</a>, <a href='http://dangerousprototypes.com/bus-pirate-manual/bus-pirate-raw-3-wire-guide/'>raw 3-wire</a>, <a href='http://dangerousprototypes.com/bus-pirate-manual/bus-pirate-keyboard-guide/'>PC keyboard</a>, <a href='http://dangerousprototypes.com/bus-pirate-manual/bus-pirate-hd44780-lcd-library/'>HD44780 LCDs</a>, <a href='http://dangerousprototypes.com/bus-pirate-manual/bus-pirate-uart-guide/'>MIDI</a>.<a href='http://dangerousprototypes.com/bus-pirate-manual/bus-pirate-hd44780-lcd-library/'></a><em> </em></p>