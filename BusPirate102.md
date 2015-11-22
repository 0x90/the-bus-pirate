<h1>Bus Pirate 201 Tutorial</h1>

<img src='http://wherelabs.files.wordpress.com/2009/11/bpv3-unbox3.jpg?w=450&h=338' />

<p>By popular demand, here's a second part to the original <a href='http://dangerousprototypes.com/2009/07/23/bus-pirate-101/'>Bus Pirate 101 tutorial</a>. This time we walk through the Bus Pirate user interface and demonstrate some basic stuff like bus modes, power supplies, pull-up resistors, and number entry. Even if you've worked with the Bus Pirate for a while, you might learn some new tricks in this detailed use tutorial written by the primary developer.</p>

<p>Unboxing photo by <a href='http://img338.imageshack.us/img338/2870/pb130503.jpg'>Uwe Bannow</a>, thanks!</p>

<p><strong>Enter a bus mode</strong></p>
<p><b>Syntax error, type ? for help</b><br />
HiZ>W<br />
No mode set, M for mode <strong><<<not allowed in HiZ</strong><br />
HiZ></p>
<p>The Bus Pirate always starts in <a href='http://en.wikipedia.org/wiki/High_impedance'>high impedance</a> mode (HiZ), a safe mode with all outputs disabled. It’s intended to protect any connected devices from conditions beyond their specifications. If your terminal is blank, press enter to see the command prompt. Type ‘?' to see a complete list of menu options and syntax available for the current hardware and software.</p>

<p>HiZ>m <span><strong><<<configure bus mode</strong><br />
</span>1. HiZ<br />
…<br />
4. I2C<br />
…<br />
10. LCD<br />
(1) >4 <span><strong><<< select I2C (option 4)</strong></span><br />

READY<br />
I2C></p>
<p>We'll be using a 24AA I2C <a href='http://en.wikipedia.org/wiki/EEPROM'>EEPROM</a> (data storage chip) on the <a href='http://dangerousprototypes.com/2009/07/30/prototype-bus-pirate-3eeprom-explorer-board/'>3EEPROM explorer board</a> to demonstrate some features. <em>You don't need the chip to follow along, you won't damage anything by following the tutorial without a chip. </em></p>
<p><em></em>Press ‘M' to configure a bus mode. Choose the I2C bus, configure it for software mode, high speed.</p>

<p><strong>Power supplies</strong></p>
<p>The on-board power supplies can be activated outside of HiZ mode.</p>
<p>I2C>w<span><strong><<<power supplies off</strong></span><br />
POWER SUPPLIES OFF<br />
I2C>v<strong><span><strong><<<voltage report</strong></span></strong><br />
Voltage monitors: 5V: 0.0 | 3.3V: 0.0 | VPULLUP: 0.0 |<br />
I2C>W<span><strong><<<power supplies on</strong></span><br />

POWER SUPPLIES ON<br />
I2C>v<span><strong><<<voltage monitor report</strong></span><br />
Voltage monitors: 5V: 4.9 | 3.3V: 3.2 | VPULLUP: 0.0 |<br />
I2C></p>
<p>Capital ‘W' activates the on-board supplies, small ‘w' turns them off. Turn the power supplies on, then press v to show a power supply voltage report.</p>

<p>Note that W is syntax and not a menu option, it can be used with other syntax to toggle the power in the middle of complex bus operations.</p>
<p><strong>Pull-up resistors</strong></p>
<p>Some bus types, such as I2C, require a resistor to create a ‘1′ on the bus. This is called an <a href='http://hackaday.com/2009/07/01/mixed-voltage-interfacing-with-the-bus-pirate/'>open collector or open drain bus</a>. Without a <a href='http://en.wikipedia.org/wiki/Pull-up_resistor'>pull-up resistor</a>, the bus will only read ‘0′. Some bus modes are open collector only (1-Wire, I2C), most have an open collector option.</p>
<p>I2C>v <span><strong><<<voltage monitor report</strong></span><br />

Voltage monitors: 5V: 4.9 | 3.3V: 3.2 | VPULLUP: 4.9 |<br />
I2C></p>
<p>Connect the Vpu pin of the IO header to a voltage. The on-board pull-up resistors apply the voltage connected to the Vpu pin to the bus pins through 10Kohm resistors. Press v and verify that the Vpullup voltage shows the desired value.</p>
<p>I2C>p <span><strong><<<configure pull-up resistors</strong></span><br />
1. Pull-ups off<br />
2. Pull-ups on<br />
(1) >2 <span><strong><<<enable </strong><br />

</span>Pull-up resistors ON<br />
I2C></p>
<p>Press p to configure the on-board pull-up resistors, enable them. For more, see the <a href='http://dangerousprototypes.com/2009/07/27/bus-pirate-practical-guide-to-pull-up-resistors/'>practical guide to Bus Pirate pull-up resistors</a>.</p>
<p><strong>Macros</strong></p>
<p>Macros are preprogrammed shortcuts. Some of the macros available include: smart card interrogation, I2C address scanners, JTAG chain probes, transparent UART bridges, LCD initialization, and bus sniffers.</p>
<p>I2C>(0)<span><strong><<< show macro menu</strong></span><br />

0.Macro menu<br />
1.7bit address search<br />
2.I2C sniffer<br />
I2C>(1)<strong><span><<< macro 1, I2C address search</span></strong><br />
Searching 7bit I2C address space.<br />
Found devices at:<br />
0xA0(0x50 W) 0xA1(0x50 R)<br />

I2C></p>
<p>Type (0) to get a list of macros in any mode. The macro number can be entered in any format, (0x00) and (0b0) are also valid macro entries.</p>
<p>I2C devices respond to a 7bit address. We could look up the address in the datasheet, but instead we'll use the address scanner macro (1). The Bus Pirate scaned all possible addresses and found the chip at 0x50 (0xa0/0xa1).</p>
<p>If you don't have an I2C chip attached for this tutorial, the Bus Pirate won't find any I2C devices. If it finds devices at every address, make sure there's powered pull-up resistors on the I2C bus pins.</p>
<p>Read more about the <a href='http://dangerousprototypes.com/2009/09/07/scan-for-i2c-read-and-write-addresses/'>I2C address scan</a>.</p>

<p><strong>Number entry and formats</strong></p>
<p>Numbers can be entered as <a href='http://en.wikipedia.org/wiki/Binary_numeral_system'>binary</a>, <a href='http://en.wikipedia.org/wiki/Decimal'>decimal</a>, or <a href='http://en.wikipedia.org/wiki/Hexadecimal'>hexadecimal</a> values, mix and match, use whatever best suits the datasheet or task.</p>
<p>I2C>= <span><strong><<<convert number formats</strong></span><br />
CONVERT (1) >10 <span><strong><<<enter value in any format</strong></span><br />

0x0A<br />
10<br />
0b00001010<br />
I2C></p>
<p>Use the ‘=' menu to convert between formats. Decimal 10 is equivalent to 0x0a (HEX) and 0b1010 (BIN). <a href='http://dangerousprototypes.com/2009/08/27/bus-pirate-hexdecbin-converter'>More about the value converter</a>.</p>

<p>CONVERT (1) >0x0f<br />
0x0F<br />
15<br />
0b00001111</p>
<p>0x0f is a HEX formatted value. The leading 0 is optional for values less than 0x10, 0xf is also valid. HEX can also be entered as 0h0f, if that's more familiar.</p>
<p>CONVERT (1) >0b11<br />

0x03<br />
3<br />
0b00000011</p>
<p>0b11 is a binary 3. It can also be entered with or without leading 0s: 0b00000011, 0b011, etc. <a href='http://dangerousprototypes.com/2009/09/01/bus-pirate-number-formats/'>More about number entry and output display</a>.</p>
<p><strong>Repeat command</strong></p>
<p>Most syntax can be repeated by appending ‘:' and a repeat value, the repeat value can be in any number format.</p>

<p>I2C>0b10:0x03<br />
WRITE: 0x02 , 0x03 TIMES ACK <span><strong><<<'0b10′ three times</strong></span><br />
I2C></p>
<p>0b10:0x03 uses the repeat command(:) to write 2 (0b10) to the I2C bus three times (:0x03).</p>

<p>I2C><a href='0xa1.md'>r r r:3</a><br />
I2C START BIT<br />
WRITE: 0xA1 ACK<br />
READ: 0x0F ACK<span><strong><<< read a single byte</strong></span><br />
READ: 0x0E ACK<span><strong><<< read a single byte</strong></span><br />

READ 0x03 BYTES:<span><strong><<< read multiple bytes</strong></span><br />
0x03 ACK 0x0E ACK 0x02 NACK<br />
I2C STOP BIT<br />
I2C></p>
<p>r is the generic command to read a single byte in all bus modes, it can also be repeated with the ‘:' command (r:3). The Bus Pirate output is HEX formatted by default, but you can change it to binary or decimal from the output mode menu ‘o'.</p>

<p><strong> When you're done</strong></p>
<p>I2C>m<span><strong><<<mode menu</strong></span><br />
1. HiZ<br />
…<br />
10. LCD<br />
(1) ><span><strong><<<HiZ is the default</strong></span><br />
Mode selected<br />

HiZ></p>
<p>When you're done, press ‘m'. The Bus Pirate immediately turns off all outputs, power supplies, and pull-up resistors, and prompts for a new mode. Choose 1 (or just press enter for the default option) to return to HiZ mode.</p>
<p><strong>Taking it further</strong></p>
<p>In <a href='http://dangerousprototypes.com/2009/07/23/bus-pirate-101/'>Bus Pirate 101</a> we looked at the Bus Pirate hardware, installed the driver, and configured the serial terminal. In Bus Pirate 102 we entered a bus mode and demonstrated some basic commands.</p>
<p>Now you're ready to interface some <a href='http://dangerousprototypes.com/bus-pirate-manual/#demos'>devices</a>. The <a href='http://dangerousprototypes.com/2009/07/30/prototype-bus-pirate-3eeprom-explorer-board/'>3EEPROM explorer board</a> might be a good place to start, it has three common EEPROM chips with three popular buses (1-Wire, I2C and SPI).</p>

<p>The <a href='http://dangerousprototypes.com/bus-pirate-manual/'>Bus Pirate manual</a> is continuously updated. Check out the expanded <a href='http://dangerousprototypes.com/bus-pirate-manual/#ioheader'>IO header pin reference</a>, complete <a href='http://dangerousprototypes.com/bus-pirate-manual/#menus'>menu options guide</a>, and individual <a href='http://dangerousprototypes.com/bus-pirate-manual/#busmodes'>bus mode documentation</a>.</p>
<p>If you program on a PC, you could automate your work with a script for the Bus Pirate <a href='http://dangerousprototypes.com/2009/10/09/bus-pirate-raw-bitbang-mode/'>binary interface mode</a>. There's <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/scripts'>a bunch of examples</a> to get you started.</p>

<p>There's also an active <a href='http://whereisian.com/forum/index.php?board=4.0'>Bus Pirate forum</a>.</p>
