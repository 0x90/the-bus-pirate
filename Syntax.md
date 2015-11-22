Supported protocols: <em><a href='#1wire'>1-Wire</a>, <a href='#uart'>UART</a>, <a href='#i2c'>I2C</a>, <a href='#spi'>SPI</a>, <a href='#jtag'>JTAG</a>, <a href='#raw2wire'>raw 2 wire</a>, <a href='#raw3wire'>raw 3 wire</a>, <a href='#MIDI'>MIDI</a>, <a href='#PCKB'>PC keyboard</a>, <a href='#LCD'>HD44780 LCDs</a>.</em>

<strong>Protocol and device tutorials</strong>
<ul>
<blockquote><li><a href='http://hackaday.com/2009/07/02/how-to-bus-pirate-probe-cable/'>How-to: Bus Pirate probe cable</a></li>
<li><a href='http://hackaday.com/2009/07/01/mixed-voltage-interfacing-with-the-bus-pirate/'>Mixed voltage interfacing with the Bus Pirate</a></li>
<li><a href='http://hackaday.com/2008/11/19/how-to-the-bus-pirate-universal-serial-interface/#EEPROM'>24LC1024 EEPROM</a> (I2C)</li>
<li><a href='http://hackaday.com/2008/11/19/how-to-the-bus-pirate-universal-serial-interface/'>EM406 GPS </a>(UART)</li>
<li><a href='http://hackaday.com/2008/11/25/how-to-read-a-fedex-kinkos-smart-card-sle4442/'>SLE4442 (FedEx Kinko's) smart card</a> (raw2 wire)</li>
<li><a href='http://hackaday.com/2008/11/28/parts-133mhz-162khz-programmable-oscillator-ds1077/'>DS1077 133MHz programmable oscillator</a> (I2C)</li>
<li><a href='http://hackaday.com/2008/12/01/bus-pirate-firmware-update-v0c-jtag-and-more/'>XC9572XL CPLD</a> (JTAG)</li>
<li><a href='http://hackaday.com/2008/12/10/parts-1-wire-temperature-sensor-ds1822'>DS1822 temperature sensor</a> (1-Wire)</li>
<li><a href='http://hackaday.com/2008/12/27/parts-8bit-io-expander-pcf8574/'>PCF8574 IO Expander</a> (I2C)</li>
<li><a href='http://hackaday.com/2008/12/24/parts-1k-1-wire-eeprom-ds2431/'>DS2431 1K EEPROM</a> (1-Wire)</li>
<li><a href='http://hackaday.com/2008/12/29/parts-precision-humidity-and-temperature-sensor-sht1x7x/'>SHT1x/7x humidity and temperature sensor</a> (raw2wire)</li>
<li><a href='http://hackaday.com/2009/01/02/parts-i2c-digital-thermometer-tc74/'>TC74 temperature sensor</a> (I2C)</li>
<li><a href='http://hackaday.com/2009/01/22/how-to-bus-pirate-v1-improved-universal-serial-interface/'>LTC2640 digital to analog converter</a> (SPI, raw3wire)</li>
<li><a href='http://hackaday.com/2009/02/09/parts-ltc2631a-i2c-digital-to-analog-converter/'>LTC2631A digital to analog converter</a> (I2C)</li>
<li><a href='http://hackaday.com/2009/01/26/parts-at-keyboard/'>PC keyboard</a></li>
<li><a href='http://hackaday.com/2009/02/16/parts-i2c-audio-volume-potentiometer-ds1807/'>DS1807 audio volume potentiometer</a> (I2C)</li>
<li><a href='http://hackaday.com/2009/03/02/parts-32kb-spi-sram-memory-23k256/'>23K256 32K serial SRAM memory</a> (SPI)</li>
<li><a href='http://hackaday.com/2009/03/09/parts-4x4-rgb-button-pad-controller-spi/'>SparkFun 4×4 RGB button pad controller</a> (raw3wire)</li>
<li><a href='http://hackaday.com/2009/03/16/parts-ds1801-spi-audio-volume-potentiometer/'>DS1801 audio volume potentiometer</a> (SPI)</li>
<li><a href='http://hackaday.com/2009/03/30/parts-programmable-gain-amplifier-mcp6s26/'>MCP6S26 programmable gain amplifier</a> (raw3wire)</li>
<li><a href='http://hackaday.com/2009/06/25/bus-pirate-firmware-update-v0g/'>Firmware v0g new feature demonstration</a></li>
<li><a href='http://hackaday.com/2009/06/26/parts-i2c-real-time-clock-calendar-pcf8563/'>PCF8563 real time clock calendar</a> (I2C)</li>
<li><a href='http://hackaday.com/2009/06/29/parts-shiftbrite-rgb-led-module-a6281/'>ShiftBrite with A6281 3 channel LED driver</a> (SPI)</li>
<li><a href='http://hackaday.com/2009/06/30/parts-spi-eeprom-25aa25lc/'>25AA/25LC serial EEPROM</a> (SPI)</li>
<li><a href='http://hackaday.com/2009/07/13/parts-4x20-vfd-character-display-na204sd02/'>NA204SD02 Futaba VFD character display</a> (raw2wire)</li>
</ul>
<em>See syntax descriptions below: <a href='#1wire'>1-Wire</a>, <a href='#uart'>UART</a>, <a href='#i2c'>I2C</a>, <a href='#spi'>SPI</a>, <a href='#jtag'>JTAG</a>, <a href='#raw2wire'>raw 2 wire</a>, <a href='#raw3wire'>raw 3 wire</a>, <a href='#MIDI'>MIDI</a>, </em><em><a href='#PCKB'>PC keyboard</a>, <a href='#LCD'>HD44780 LCDs</a>.</em></blockquote>

<strong>Pinout descriptions</strong>

Pin location diagrams: <a href='http://hackadaycom.wordpress.com/files/2009/01/brd1.png'>v0a</a>, <a href='http://hackadaycom.wordpress.com/files/2009/01/v1abrd.png'>v1a</a>, <a href='http://hackadaycom.wordpress.com/files/2009/01/brd3.png'>v2a</a>, <a href='http://hackadaycom.wordpress.com/files/2009/01/brd251.png'>v2g0</a>.
<table border='0'>
<tbody>
<tr>
<td><strong>Pin name<br>
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
</tbody></table>
Notes: **TX moved from CS to MOSI in firmware v0g.**

<strong>Menus</strong>

Menu options are single character commands that don’t involve data  transfers. Enter the character, followed by &lt;enter&gt;, to access  the menu. Menus apply to most modes. Some menus are unavailable in some modes, bit order is not configurable for hardware modules.
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
<td>B</td>
<td>Set PC side serial port speed.</td>
</tr>
<tr>
<td>O</td>
<td>Data display format (DEC, HEX, BIN, or raw).</td>
</tr>
<tr>
<td>F</td>
<td>Measure frequency on the AUX pin.</td>
</tr>
<tr>
<td>G</td>
<td>Frequency generator/PWM on the AUX pin.</td>
</tr>
<tr>
<td>C</td>
<td>Toggle AUX control between AUX and CS/TMS pins.</td>
</tr>
<tr>
<td>M</td>
<td>Set bus mode (1-Wire, SPI, I2C, JTAG, UART, etc).</td>
</tr>
<tr>
<td>L</td>
<td>Set LSB/MSB first in applicable modes.</td>
</tr>
<tr>
<td>P</td>
<td>Pull-up resistors (V0,V2+ hardware). <span>Power supply configuration.</span> Deprecated. (v1 hardware).</td>
</tr>
<tr>
<td>V</td>
<td>Power supply voltage report (v1+ hardware only).</td>
</tr>
<tr>
<td>I</td>
<td>Hardware/firmware version information.</td>
</tr>
</tbody></table>
<strong>Syntax and macros</strong>

A simple syntax is used to communicate with chips over a bus.  Syntax characters represent generic functions,  such as 'R' to read a byte of data, that apply to all bus  types. Each protocol is addressed individually below.

Skip to: <a href='#1wire'>1-Wire</a>, <a href='#uart'>UART</a>, <a href='#i2c'>I2C</a>, <a href='#spi'>SPI</a>, <a href='#jtag'>JTAG</a>, <a href='#raw2wire'>raw 2 wire</a>, <a href='#raw3wire'>raw 3 wire</a>, <a href='#MIDI'>MIDI</a>, <em><a href='#PCKB'>PC keyboard</a>, <a href='#LCD'>HD44780 LCDs</a>.</em>

<em><a>Dallas/Maxim 1-Wire Protocol</a></em>

<a href='http://en.wikipedia.org/wiki/1-Wire'>1-Wire</a> requires a single data line (SDA) and a ground connection. The Bus Pirate pin is <a href='http://en.wikipedia.org/wiki/High_impedence'>high-impedance</a> and requires a 2K-10K <a href='http://en.wikipedia.org/wiki/Pull-up_resistor'>pull-up</a> resistor, maximum 5.5volts (5volt safe).
<table border='0'>
<tbody>
<tr>
<td width='46'><strong>Syntax</strong></td>
<td width='611'><strong>Description</strong></td>
</tr>
<tr>
<td>A/a/@</td>
<td>Toggle auxiliary pin. Capital “A” sets AUX  high, small “a” sets to ground. @ sets aux to input (high impedance  mode) and reads the pin value.</td>
</tr>
<tr>
<td>D/d</td>
<td>Measure voltage on the ADC pin (v1+ hardware only).</td>
</tr>
<tr>
<td>W/w</td>
<td>Capital 'W' enables the on-board power supplies. Small 'w' disables them. (v1+ hardware only).</td>
</tr>
<tr>
<td>{ or [</td>
<td>1-Wire bus reset.</td>
</tr>
<tr>
<td>] or }</td>
<td>--</td>
</tr>
<tr>
<td>R or r</td>
<td>Read one byte. (r:1...255 for bulk reads)</td>
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
<td>Value delimiter. Use a coma or space  to separate numbers. Any combination is fine, no delimiter is required  between non-number values: {0xa6,0, 0 16 5 0b111 0haF}.</td>
</tr>
<tr>
<td>&amp;</td>
<td>Delay 1uS. (&amp;:1…255 for multiple delays)</td>
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
<td>One clock tick, use data state from previous - or <i>operation. (^:1…255 for multiple clock ticks)</td>
</tr></i><tr>
<td>/ or \</td>
<td>--</td>
</tr>
<tr>
<td>- or <i></td></i><td>Send 1-Wire 1 (-) or 0 (<i>) bit.</td>
</tr></i><tr>
<td>!</td>
<td>Read one bit with clock.</td>
</tr>
<tr>
<td>.</td>
<td>--</td>
</tr>
</tbody></table>
<table border='0'>
<tbody>
<tr>
<td><strong>Macro</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>0</td>
<td>Macro menu</td>
</tr>
<tr>
<td>1-50</td>
<td>Reserved for device address shortcuts.</td>
</tr>
<tr>
<td>51</td>
<td>READ ROM (0x33) <b>for single device bus</td>
</tr></b><tr>
<td>85</td>
<td>MATCH ROM (0x55) <b>followed by 64bit address</td>
</tr></b><tr>
<td>204</td>
<td>SKIP ROM (0xCC) <b>followed by command</td>
</tr></b><tr>
<td>236</td>
<td>ALARM SEARCH (0xEC)</td>
</tr>
<tr>
<td>240</td>
<td>SEARCH ROM (0xF0)</td>
</tr>
</tbody></table>
<em><a>Serial protocol UART</a></em>

The <a href='http://en.wikipedia.org/wiki/Serial_uart'>serial UART</a> is hardware-based, and operates at 3.3volts (normal pins) or 0-5.5volts (<a href='http://en.wikipedia.org/wiki/High_impedence'>high-impedance</a> pins with 2K-10K <a href='http://en.wikipedia.org/wiki/Pull-up_resistor'>pull-up</a> resistors). Requires two data pins (RX/TX) and a ground connection.
<table border='0'>
<tbody>
<tr>
<td><strong>Syntax</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>A/a/@</td>
<td>Toggle auxiliary pin. Capital “A” sets AUX  high, small “a” sets to ground. @ sets aux to input (high impedance  mode) and reads the pin value.</td>
</tr>
<tr>
<td>D/d</td>
<td>Measure voltage on the ADC pin (v1+ hardware only).</td>
</tr>
<tr>
<td>W/w</td>
<td>Capital 'W' enables the on-board power supplies. Small 'w' disables them. (v1+ hardware only).</td>
</tr>
<tr>
<td>[</td>
<td>Open UART, discard  received bytes.</td>
</tr>
<tr>
<td>{</td>
<td>Open UART, display data as it arrives asynchronously.</td>
</tr>
<tr>
<td>] or }</td>
<td>Close UART.</td>
</tr>
<tr>
<td>R or r</td>
<td>Check UART for byte, or fail if empty. (r:1...255 for bulk reads)</td>
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
<td>Value delimiter. Use a coma or space  to separate numbers. Any combination is fine, no delimiter is required  between non-number values: {0xa6,0, 0 16 5 0b111 0haF}.</td>
</tr>
<tr>
<td>&amp;</td>
<td>Delay 1uS. (&amp;:1…255 for multiple delays)</td>
</tr>
<tr>
<td>(#)</td>
<td>Run macro, (0) for macro list</td>
</tr>
</tbody></table>
<em><a>MIDI</a></em>

<a href='http://en.wikipedia.org/wiki/Musical_Instrument_Digital_Interface'>MIDI</a> is a command set used by electronic (music) instruments. It travels over a standard serial UART configured for 31250bps/8/n/1.   The MIDI library functions like the <a href='#uart'>asynchronous serial</a> (UART) library.

MIDI is a ring network, each node has an input and output socket. Each node passes messages to the next in the ring. The input and outputs are opto-isolated. The signaling is at 5volts, 5ma (current-based signaling). An adapter is required: <a href='http://www.compuphase.com/electronics/midi_rs232.htm'>example 1</a>, <a href='http://www.midi.org/techspecs/electrispec.php'>example 2</a>.

<em><a>I2C</a></em>

<a href='http://en.wikipedia.org/wiki/I2c'>I2C</a> requires two pins (SDA/SCL) and a ground connection.<em> </em>The Bus Pirate pins are <a href='http://en.wikipedia.org/wiki/High_impedence'>high-impedance</a> and require 2K-10K <a href='http://en.wikipedia.org/wiki/Pull-up_resistor'>pull-up</a> resistors, maximum 5.5volts (5volt safe).
<table border='0'>
<tbody>
<tr>
<td><strong>Syntax</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>A/a/@</td>
<td>Toggle auxiliary pin. Capital “A” sets AUX  high, small “a” sets to ground. @ sets aux to input (high impedance  mode) and reads the pin value.</td>
</tr>
<tr>
<td>D/d</td>
<td>Measure voltage on the ADC pin (v1+ hardware only).</td>
</tr>
<tr>
<td>W/w</td>
<td>Capital 'W' enables the on-board power supplies. Small 'w' disables them. (v1+ hardware only).</td>
</tr>
<tr>
<td>{ or [</td>
<td>Issue I2C start condition.</td>
</tr>
<tr>
<td>] or }</td>
<td>Issue I2C stop condition.</td>
</tr>
<tr>
<td>R or r</td>
<td>Read one byte, send ACK. (r:1...255 for bulk reads)</td>
</tr>
<tr>
<td>0b</td>
<td>Write this binary value, check ACK. Format is 0b00000000 for a byte, but partial bytes are also fine: 0b1001.</td>
</tr>
<tr>
<td>0h/0x</td>
<td>Write this HEX value, check ACK. Format is 0h01 or 0×01. Partial bytes are fine: 0xA. A-F can be lower-case or capital letters.</td>
</tr>
<tr>
<td>0-255</td>
<td>Write this decimal value, check ACK. Any number not preceded by 0x, 0h, or 0b is interpreted as a decimal value.</td>
</tr>
<tr>
<td>,</td>
<td>Value delimiter. Use a coma or space  to separate numbers. Any combination is fine, no delimiter is required  between non-number values: {0xa6,0, 0 16 5 0b111 0haF}.</td>
</tr>
<tr>
<td>&amp;</td>
<td>Delay 1uS. (&amp;:1…255 for multiple delays)</td>
</tr>
<tr>
<td>(#)</td>
<td>Run macro, (0) for macro list</td>
</tr>
</tbody></table>
<table border='0'>
<tbody>
<tr>
<td><strong>Macro</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>0</td>
<td>Macro menu</td>
</tr>
<tr>
<td>1</td>
<td>7bit address search. Find all connected devices by brute force.</td>
</tr>
<tr>
<td>2</td>
<td>I2C snooper (new in v0h)</td>
</tr>
</tbody></table>
<em><a>SPI</a></em>

<a href='http://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus'>SPI</a> requires four pins (MOSI/MISO/CLOCK/CS) and a ground connection. SPI is hardware-based, and operates at 3.3volts (normal pins) or 0-5.5volts (<a href='http://en.wikipedia.org/wiki/High_impedence'>high-impedance</a> pins with a 2K-10K <a href='http://en.wikipedia.org/wiki/Pull-up_resistor'>pull-up</a> resistor, maximum 5.5volts).<em> </em>
<table border='0'>
<tbody>
<tr>
<td><strong>Syntax</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>A/a/@</td>
<td>Toggle auxiliary pin. Capital “A” sets AUX  high, small “a” sets to ground. @ sets aux to input (high impedance  mode) and reads the pin value.</td>
</tr>
<tr>
<td>D/d</td>
<td>Measure voltage on the ADC pin (v1+ hardware only).</td>
</tr>
<tr>
<td>W/w</td>
<td>Capital 'W' enables the on-board power supplies. Small 'w' disables them. (v1+ hardware only).</td>
</tr>
<tr>
<td>[</td>
<td>Chip select (CS) active (low).</td>
</tr>
<tr>
<td>{</td>
<td>CS active (low), show the SPI read byte after every write.</td>
</tr>
<tr>
<td>] or }</td>
<td>CS disable (high).</td>
</tr>
<tr>
<td>R or r</td>
<td>Read one byte by sending dummy byte (0xff). (r:1...255 for bulk reads)</td>
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
<td>Value delimiter. Use a coma or space  to separate numbers. Any combination is fine, no delimiter is required  between non-number values: {0xa6,0, 0 16 5 0b111 0haF}.</td>
</tr>
<tr>
<td>&amp;</td>
<td>Delay 1uS. (&amp;:1…255 for multiple delays)</td>
</tr>
<tr>
<td>(#)</td>
<td>Run macro, (0) for macro list</td>
</tr>
</tbody></table>
<table border='0'>
<tbody>
<tr>
<td><strong>Macro</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>0</td>
<td>Macro menu</td>
</tr>
<tr>
<td>1</td>
<td>SPI bus sniffer with configurable CS filter.</td>
</tr>
</tbody></table>
<em><a>JTAG</a></em>

<a href='http://en.wikipedia.org/wiki/JTAG'>JTAG</a> is actually a protocol over SPI. This library performs common JTAG functions, manages the JTAG state machine, and includes a XSVF-based JTAG programmer.<em> </em>3.3volt I/O, or <a href='http://en.wikipedia.org/wiki/High_impedence'>high-impedance</a> pins for 0-5volt interfacing (use 2K-10K <a href='http://en.wikipedia.org/wiki/Pull-up_resistor'>pull-up</a> resistors, maximum 5.5volts).
<table border='0'>
<tbody>
<tr>
<td><strong>Syntax</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>A/a/@</td>
<td>Toggle auxiliary pin. Capital “A” sets AUX  high, small “a” sets to ground. @ sets aux to input (high impedance  mode) and reads the pin value.</td>
</tr>
<tr>
<td>D/d</td>
<td>Measure voltage on the ADC pin (v1+ hardware only).</td>
</tr>
<tr>
<td>W/w</td>
<td>Capital 'W' enables the on-board power supplies. Small 'w' disables them. (v1+ hardware only).</td>
</tr>
<tr>
<td>[</td>
<td>Move JTAG state machine (SM) to INSTRUCTION register. Last bit of byte writes is delayed until leaving the INSTRUCTION register.</td>
</tr>
<tr>
<td>{</td>
<td>Move JTAG SM to DATA register.</td>
</tr>
<tr>
<td>] or }</td>
<td>Move JTAG SM to IDLE register.</td>
</tr>
<tr>
<td>R or r</td>
<td>Read one byte. (r:1...255 for bulk reads)</td>
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
<td>Value delimiter. Use a coma or space  to separate numbers. Any combination is fine, no delimiter is required  between non-number values: {0xa6,0, 0 16 5 0b111 0haF}.</td>
</tr>
<tr>
<td>&amp;</td>
<td>Delay 1uS. (&amp;:1…255 for multiple delays)</td>
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
</tbody></table>
<table border='0'>
<tbody>
<tr>
<td><strong>Macro</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>0</td>
<td>Macro menu</td>
</tr>
<tr>
<td>1</td>
<td>Reset chain</td>
</tr>
<tr>
<td>2</td>
<td>Probe chain</td>
</tr>
<tr>
<td>3</td>
<td>XSVF player. JTAG programmer.</td>
</tr>
</tbody></table>
<em><a>Raw 2 wire</a></em>

The raw 2 wire library is similar to I2C but includes bitwise pin control. Requires two pins (SDA/SCL) and a ground connection.<em> </em><a href='http://en.wikipedia.org/wiki/High_impedence'>High-impedance</a> pins for 0-5volt interfacing (use 2K-10K <a href='http://en.wikipedia.org/wiki/Pull-up_resistor'>pull-up</a> resistors, maximum 5.5volts), or optional 3.3volt I/O mode.
<table border='0'>
<tbody>
<tr>
<td><strong>Syntax</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>A/a/@</td>
<td>Toggle auxiliary pin. Capital “A” sets AUX  high, small “a” sets to ground. @ sets aux to input (high impedance  mode) and reads the pin value.</td>
</tr>
<tr>
<td>D/d</td>
<td>Measure voltage on the ADC pin (v1+ hardware only).</td>
</tr>
<tr>
<td>W/w</td>
<td>Capital 'W' enables the on-board power supplies. Small 'w' disables them. (v1+ hardware only).</td>
</tr>
<tr>
<td>{ or [</td>
<td>Issue I2C-style start condition.</td>
</tr>
<tr>
<td>] or }</td>
<td>Issue I2C-style stop condition.</td>
</tr>
<tr>
<td>R or r</td>
<td>Read one byte. (r:1...255 for bulk reads)</td>
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
<td>Value delimiter. Use a coma or space  to separate numbers. Any combination is fine, no delimiter is required  between non-number values: {0xa6,0, 0 16 5 0b111 0haF}.</td>
</tr>
<tr>
<td>&amp;</td>
<td>Delay 1uS. (&amp;:1…255 for multiple delays)</td>
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
</tbody></table>
<table border='0'>
<tbody>
<tr>
<td><strong>Macro</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>0</td>
<td>Macro menu</td>
</tr>
<tr>
<td>1</td>
<td>ISO7813-3 ATR for smart cards, parses reply bytes.</td>
</tr>
<tr>
<td>2</td>
<td>ISO7813-3 parse only (provide your own ATR command).</td>
</tr>
<tr>
<td></td>
<td></td>
</tr>
</tbody></table>
<em><a>Raw 3 wire</a></em>

The raw 3 wire library is like SPI, but includes bitwise pin control. Requires four pins (MOSI/MISO/CLOCK/CS) and a ground connection. 3.3volt I/O, or <a href='http://en.wikipedia.org/wiki/High_impedence'>high-impedance</a> pins for 0-5volt interfacing (use 2K-10K <a href='http://en.wikipedia.org/wiki/Pull-up_resistor'>pull-up</a> resistors, maximum 5.5volts).
<table border='0'>
<tbody>
<tr>
<td><strong>Syntax</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>A/a/@</td>
<td>Toggle auxiliary pin. Capital “A” sets AUX  high, small “a” sets to ground. @ sets aux to input (high impedance  mode) and reads the pin value.</td>
</tr>
<tr>
<td>D/d</td>
<td>Measure voltage on the ADC pin (v1+ hardware only).</td>
</tr>
<tr>
<td>W/w</td>
<td>Capital 'W' enables the on-board power supplies. Small 'w' disables them. (v1+ hardware only).</td>
</tr>
<tr>
<td>[</td>
<td>Chip select (CS) active (low).</td>
</tr>
<tr>
<td>{</td>
<td>CS active (low), show the SPI read byte after every write.</td>
</tr>
<tr>
<td>] or }</td>
<td>CS disable (high).</td>
</tr>
<tr>
<td>R or r</td>
<td>Read one byte by sending dummy byte (0xff). (r:1...255 for bulk reads)</td>
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
<td>Value delimiter. Use a coma or space  to separate numbers. Any combination is fine, no delimiter is required  between non-number values: {0xa6,0, 0 16 5 0b111 0haF}.</td>
</tr>
<tr>
<td>&amp;</td>
<td>Delay 1uS. (&amp;:1…255 for multiple delays)</td>
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
</tbody></table>
<em><a>HD44780 LCD (v0h+)<br>
</a></em>

<a href='http://ouwehand.net/~peter/lcd/lcd.shtml'></a>The LCD library interfaces common <a href='http://ouwehand.net/~peter/lcd/lcd.shtml'>HD44780 LCD character displays</a>. The Bus Pirate doesn't have enough pins to interface the LCD directly, so the library uses a <a href='http://hackaday.com/2008/12/27/parts-8bit-io-expander-pcf8574/'>PCF8574</a> I2C I/O expander (see our <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/hardware/adapters/HD44780_LCD'>adapter board</a>).
<table border='0'>
<tbody>
<tr>
<td><strong>Syntax</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>A/a/@</td>
<td>Toggle auxiliary pin. Capital “A” sets AUX  high, small “a” sets to ground. @ sets aux to input (high impedance  mode) and reads the pin value.</td>
</tr>
<tr>
<td>D/d</td>
<td>Measure voltage on the ADC pin (v1+ hardware only).</td>
</tr>
<tr>
<td>W/w</td>
<td>Capital 'W' enables the on-board power supplies. Small 'w' disables them. (v1+ hardware only).</td>
</tr>
<tr>
<td>{ or [</td>
<td>RS low. Next read/write is a COMMAND.</td>
</tr>
<tr>
<td>] or }</td>
<td>RS high. Next read/write is TEXT/DATA.</td>
</tr>
<tr>
<td>R or r</td>
<td>Read one byte (r:1...255 for bulk reads). <span>
</span></td>
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
<td>Value delimiter. Use a coma or space  to separate numbers. Any combination is fine, no delimiter is required  between non-number values: {0xa6,0, 0 16 5 0b111 0haF}.</td>
</tr>
<tr>
<td>&amp;</td>
<td>Delay 1uS. (&amp;:1…255 for multiple delays)</td>
</tr>
<tr>
<td>(#)</td>
<td>Run macro, (0) for macro list</td>
</tr>
</tbody></table>
<table border='0'>
<tbody>
<tr>
<td><strong>Macro</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>0</td>
<td>Macro menu</td>
</tr>
<tr>
<td>1</td>
<td>LCD reset.</td>
</tr>
<tr>
<td>2</td>
<td>Init LCD.</td>
</tr>
<tr>
<td>3</td>
<td>Clear LCD.</td>
</tr>
<tr>
<td>4</td>
<td>Cursor position ex:(4:0).</td>
</tr>
<tr>
<td>5</td>
<td>Write test text.</td>
</tr>
<tr>
<td>6</td>
<td>Write :number test numbers ex:(6:80).</td>
</tr>
<tr>
<td>7</td>
<td>Write :number test characters ex:(7:80).</td>
</tr>
<tr>
<td>8</td>
<td>Insert text at cursor.</td>
</tr>
</tbody></table>
<em><a>PC keyboard<br>
</a></em>

This library interfaces PC keyboards.
<table border='0'>
<tbody>
<tr>
<td><strong>Macro</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>0</td>
<td>Macro menu</td>
</tr>
<tr>
<td>1</td>
<td>Live keyboard monitor (v0h+)</td>
</tr>
</tbody></table>
<strong>----</strong>

<strong>The Bus Pirate pinout, menu, and command tables are released into the public domain.<br>
</strong>

<strong>This program and hardware is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of</strong> <strong>MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.<br>
</strong>