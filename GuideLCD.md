<h1>Bus Pirate: HD44780 character LCD adapter</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/08/cover-ii.jpg?w=450&#038;h=229' alt='cover.ii' height='229' width='450' title='cover.ii' /></p>
<p>Cheap character LCDs based on the <a href='http://en.wikipedia.org/wiki/HD44780_Character_LCD'>HD44780 chipset</a> come in a variety of sizes: 2x16, 4x20, etc. These displays have two standard interface modes, <a href='http://home.iae.nl/users/pouweha/lcd/lcd0.shtml#_8bit-transfer'>4bit and 8bit parallel</a>. 8bit requires a total of 11 data lines, 4bit requires 7 (6 for write-only). Some LCDs support an additional serial data mode, like the <a href='http://hackaday.com/2009/07/13/parts-4x20-vfd-character-display-na204sd02/'>VFD Ian covered at Hack a Day</a>.</p>

<p><img src='http://wherelabs.files.wordpress.com/2009/08/adapter-mini-225.jpg?w=225&#038;h=132' alt='adapter-mini.225' height='132' width='225' title='adapter-mini.225' />HD44780 LCDs are generally 5volt parts with a separate supply for the back light. The <a href='http://www.buspirate.com'>Bus Pirate</a> only has five 5volt tolerant I/O pins, so we made a small adapter board with enough pins to control the LCD. The Bus Pirate controls the adapter board through its LCD interface library.</p>
<p>Continue reading about the Bus Pirate HD44780 character LCD adapter board and interface library after the break. We can have PCBs, kits, or assembled kits produced by <a href='http://www.seeedstudio.com/depot/'>Seeed Studio</a> for about $15, including worldwide shipping, <a href='http://whereisian.com/forum/index.php?topic=48.0'>more here</a>.<span></span></p>
<p><strong>Overview</strong></p>
<p><img src='http://wherelabs.files.wordpress.com/2009/08/overview-ii.png?w=450&#038;h=181' alt='overview.ii' height='181' width='450' title='overview.ii' /></p>
<p>In this article we outline an I2C adapter board for HD44780-based LCDs. We demonstrate it with a <a href='http://www.buspirate.com'>Bus Pirate universal serial interface</a>. The Bus Pirate <a href='http://code.google.com/p/the-bus-pirate/source/browse/trunk/source/HD44780.c'>source code for the I2C-based HD44780 interface library</a> is public domain, so it's free to adapt to your own projects.</p>

<p><strong>Hardware</strong></p>
<p><img src='http://wherelabs.files.wordpress.com/2009/08/cct-450.png?w=445&#038;h=139' alt='cct-450' height='139' width='445' title='cct-450' /></p>
<p><a href='http://wherelabs.files.wordpress.com/2009/08/cct.png'>Full size circuit image</a> <a href='PNG.md'>PNG</a>. The circuit and PCB were designed with the free version of <a href='http://www.cadsoft.de'>Cadsoft Eagle</a>. The design files can be downloaded from the <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/hardware/adapters/HD44780_LCD'>Bus Pirate SVN</a>. Before using the adapter board,<em> be sure to verify the datasheet for your LCD against the adapter pinout. Not all LCDs are the same.</em></p>
<p><img src='http://wherelabs.files.wordpress.com/2009/08/pcf8574-adapter.jpg?w=450&#038;h=263' alt='PCF8574-adapter' height='263' width='450' title='PCF8574-adapter' /></p>
<p><em>PCF8574 I/O expander IC</em></p>
<p>This is a simple 8 I/O expander chip that's controlled through the two-wire <a href='http://en.wikipedia.org/wiki/I%C2%B2C'>I2C</a> interface. The I2C interface is accessible from header JP1.</p>

<p>The PCF8574 works from 2.5 to 5volts. The I/O pins operate at the supply voltage, so if we feed it 5volts it interfaces the LCD at 5volts.  C1 (0.1uF) decouples the IC from fluctuations in the power supply.</p>
<p>One pin of the PCF8574 controls a 3mm LED (LED1) through current limiting resistor <a href='https://code.google.com/p/the-bus-pirate/source/detail?r=2'>R2</a> (1000 ohms). The LED lights to indicate successful communication between the Bus Pirate and the adapter. The PCF8574 can't source enough current to power the LED, so we power the LED from the 5volt supply and switch the ground.</p>
<p><em>LCD</em></p>
<p>The adapter board communicates with an HD44780-based character LCD in <a href='http://homepage.hispeed.ch/peterfleury/avr-lcd44780.html'>4bit parallel interface mode</a>. The 4bit interface pins – RS, RW, EN, and D4-D7 – are connected to seven of the PCF8574 I/O pins. We like to use 0.1″ male pin header to connect the adapter to an LCD, you can usually lean the LCD  against the pins to create sufficient contact for a quick test.</p>

<p>Trimmer resistor <a href='https://code.google.com/p/the-bus-pirate/source/detail?r=1'>R1</a> (10K) provides a contrast adjustment voltage to pin 3 of the LCD header.</p>
<p>We didn't connect the backlight pins because there's so many <a href='http://en.wikipedia.org/wiki/Backlight'> different  backlight styles</a>. Providing power for an LED backlight might damage a screen that requires a negative voltage supply.</p>
<p><em>Power supply</em></p>
<p>Most LCDs require 5volts, provide an external power supply through header JP2. We provided a second power supply pin to connect the Bus Pirate's pull-up resistors.</p>
<p><em>PCB</em></p>
<p><img src='http://wherelabs.files.wordpress.com/2009/08/brd.png?w=448&#038;h=256' alt='brd' height='256' width='448' title='brd' /></p>

<p>The circuit and PCB were designed with the free version of <a href='http://www.cadsoft.de/'>Cadsoft Eagle</a>. The design files can be downloaded from the <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/hardware/adapters/HD44780_LCD'>Bus Pirate SVN</a>. The PCB is a  single-sided, all through-hole design with a single jumper wire (shown in red).</p>
<p>We can have PCBs, kits, or assembled kits produced by <a href='http://www.seeedstudio.com/depot/'>Seeed Studio</a> for about $15, including worldwide shipping, <a href='http://whereisian.com/forum/index.php?topic=48.0'>more here</a>.</p>
<p><em>Partlist</em></p>
<table border='0'>
<tbody>

<tr>
<td><strong>Part</strong></td>
<td><strong>Value (all through-hole)</strong></td>
<td><strong>Quantity</strong></td>
</tr>
<tr>
<td>C1</td>
<td><a href='http://www.mouser.com/Search/ProductDetail.aspx?qs=9AX3phJxokWIpR5WRGtIJw%3d%3d'>0.1uF/10volts+</a></td>
<td>1</td>
</tr>
<tr>

<td><a href='https://code.google.com/p/the-bus-pirate/source/detail?r=1'>R1</a></td>
<td><a href='http://mouser.com/Search/ProductDetail.aspx?qs=sGAEpiMZZMukHu%252bjC5l7YS2smmOB11VuVOVCrPAWrUo%3d'>10000 (10K) ohm single turn trimmer/potentiometer, 6mm</a></td>
<td>1</td>
</tr>
<tr>
<td><a href='https://code.google.com/p/the-bus-pirate/source/detail?r=2'>R2</a></td>
<td><a href='http://mouser.com/Search/ProductDetail.aspx?qs=sGAEpiMZZMtMTfExsNintcCc6jzwa0q%252bpQDkpz%252bUuMc%3d'>1000 (1K) ohm resistor, 1/4 watt</a></td>
<td>1</td>
</tr>
<tr>
<td>LED1</td>

<td><a href='http://mouser.com/Search/ProductDetail.aspx?qs=sGAEpiMZZMtJ8nYvfCigMvPg4QhGrt1HXFfgGeSA%252bXg%3d'>3mm (T1) LED, red</a></td>
<td>1</td>
</tr>
<tr>
<td>JP1+JP2</td>
<td><a href='http://www.mouser.com/Search/ProductDetail.aspx?R=4-103329-0virtualkey57100000virtualkey571-41033290'>0.1″ male header, 5 pins</a></td>
<td>1</td>
</tr>
<tr>
<td>IC1</td>

<td><a href='http://mouser.com/Search/ProductDetail.aspx?qs=sGAEpiMZZMtNOfUcvFSN7O52Vpd2XwVhUEVSvjNYv8M%3d'>PCF8574N, 8bit I2C I/O expander DIP16</a></td>
<td>1</td>
</tr>
<tr>
<td>ICS1</td>
<td><a href='http://mouser.com/Search/ProductDetail.aspx?qs=sGAEpiMZZMvlX3nhDDO4AENRpMoVgxxl10BJ4%252brzULQ%3d'>16 pin DIP socket for IC1</a></td>
<td>1</td>
</tr>
</tbody>
</table>
<p><img src='http://wherelabs.files.wordpress.com/2009/08/render.jpg?w=450&#038;h=252' alt='render' height='252' width='450' title='render' /></p>
<p><strong>Demonstration</strong></p>

<p><strong>Device:</strong> HD44780 character LCD.<br />
<strong>Bus:</strong> 4bit parallel, with PCF8574 I2C adapter board.<br />
<strong>Power requirements:</strong> 5volts.<br />
<strong>References:</strong> <a href='http://www.sparkfun.com/datasheets/LCD/HD44780.pdf'>example datasheet</a> <a href='PDF.md'>PDF</a>, <a href='http://home.iae.nl/users/pouweha/lcd/lcd0.shtml#instruction_set'>HD44780 command reference</a>, <a href='http://home.iae.nl/users/pouweha/lcd/lcd.shtml'>HD44780 LCD uber-site.</a><br />

<a href='http://code.google.com/p/the-bus-pirate/source/browse/trunk/hardware/adapters/HD44780_LCD/HD44780.txt'>Complete Bus Pirate session log for this demonstration</a>.</p>
<p><em>Connections</em></p>
<table border='0'>
<tbody>
<tr>
<td><strong>Bus Pirate</strong></td>
<td><strong>LCD adapter</strong></td>
<td><strong>PCF8574 (pin #)</strong></td>
</tr>
<tr>
<td>MOSI</td>

<td>SDA</td>
<td>SDA (15)</td>
</tr>
<tr>
<td>CLK</td>
<td>SCL</td>
<td>SCL (14)</td>
</tr>
<tr>
<td>5volts</td>
<td>+5V</td>

<td>VCC (16)</td>
</tr>
<tr>
<td>GND</td>
<td>GND</td>
<td>GND (1,2,3,8)</td>
</tr>
<tr>
<td>Vpullup</td>
<td>+5V</td>
<td>–</td>

</tr>
</tbody>
</table>
<p>We designed the adapter for the LCD library of the <a href='http://www.buspirate.com'>Bus Pirate universal serial interface</a>, but it'll work with anything that can speak the I2C protocol. Take a look at the Bus Pirate source code for <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/hardware/adapters/HD44780_LCD'>an example I2C->HD44780 implementation</a>.</p>
<p>Connect the Bus Pirate to the adapter board as shown in the table. The table also shows the raw connections to the PCF8574 IC if you're following along without an adapter board.</p>
<p>Connect the adapter to a power supply sufficient for the LCD, generally 5volts. The I2C connection between the adapter and the Bus Pirate requires <a href='http://en.wikipedia.org/wiki/Pull-up_resistor'>pull-up resistors</a> between 2 and 10K. Here's more information about <a href='http://hackaday.com/2009/07/01/mixed-voltage-interfacing-with-the-bus-pirate/'>mixed voltage interfacing with pull-ups</a>, and the <a href='http://dangerousprototypes.com/2009/07/27/bus-pirate-practical-guide-to-pull-up-resistors/'>Bus Pirate on-board pull-up resistors</a>.</p>

<p><em>Interfacing</em></p>
<p>We've covered the adapter design and how to connect it to the Bus Pirate, now it's finally time to write something to the LCD.</p>
<p><span>Step 1. Setup library</span></p>
<p>HiZ>m<span><strong><<<set mode menu</strong></span><br />
1. HiZ<br />
…<br />
11. LCD<br />

12. HWI2C<br />
(1) >11<span><strong><<<LCD interface mode</strong></span><br />
MODE SET<br />
LCD type:<br />
1. HD44780 (using PCF8574 IO expander)<br />
(1) >1<span><strong><<<currently only supports HD44780 LCDs</strong></span><br />
HD44780 LCD TESTER<br />

REQUIRES PCF8574 I2C IO EXPANDER<br />
LCD>W<span><strong><<<big ‘W' turns on the power supplies</strong></span><br />
POWER SUPPLIES ON<br />
LCD>p<span><strong><<<configure the pull-up resistors</strong></span><br />
1. Pullup off<br />

2. Pullup on<br />
(1) >2<span><strong><<<turn the pull-ups on</strong></span><br />
PULLUP RESISTORS ON<br />
LCD>v<span><strong><<<get voltage report</strong></span><br />
VOLTAGE MONITOR: 5V: 4.9 | 3.3V: 3.3 | VPULLUP: 5.0<span><strong><<<check Vpu</strong></span><br />
LCD></p>

<p>Press ‘m' in the Bus Pirate terminal and choose the LCD library. It currently it only supports HD44780 character LCDs using the PFC8574 adapter described in the first half of this article (option 1).</p>
<p>Enable the power supplies (big ‘W') and pull-up resistors (menu ‘p').  Check the voltage monitor (menu ‘v') and make sure that the pull-up voltage (Vpullup) reads around 5volts.</p>
<p><span>Step 2. Reset &amp; initialization</span></p>

<p><span><img src='http://wherelabs.files.wordpress.com/2009/08/vfd-command-pg27.png?w=470&#038;h=197' alt='HD44780 command table' height='197' width='470' title='HD44780 command table' /></span></p>
<p>This table outlines the single-byte commands that control an HD44780 LCD, here's a <a href='http://home.iae.nl/users/pouweha/lcd/lcd0.shtml#instruction_set'>detailed reference</a>. These commands can be entered  from the Bus Pirate command line, but we've made macros for most of them  to save time.</p>
<p>LCD>(0)<span><strong><<<show macro menu</strong></span><br />
0.Macro menu<span><strong><<<this menu</strong></span><br />
1.LCD Reset<span><strong><<<reset the LCD</strong></span><br />

2.Init LCD<span><strong><<<reset and initialize the LCD</strong></span><br />
3.Clear LCD<span><strong><<<clear LCD, return cursor to 0</strong></span><br />
4.Cursor position ex:(4:0)<span><strong><<<set cursor postion</strong></span><br />
5.Write test text <span><strong><<<will be removed by firmware v2.1</strong></span><br />
6.Write :number test numbers ex:(6:80)<br />
7.Write :number test characters ex:(7:80)<br />
8.Insert text at cursor<br />

LCD></p>
<p>Macro 0 displays the macro menu for any Bus Pirate mode.</p>
<p><span><img src='http://wherelabs.files.wordpress.com/2009/08/reset-macro.jpg?w=450&#038;h=156' alt='reset-macro' height='156' width='450' title='reset-macro' /></span></p>
<p>LCD>(2) <span><strong><<<initialize LCD macro</strong><br />
</span> Display lines:<br />
1. 1<span><strong><<<single line display</strong></span><br />
2. Multiple<span><strong><<<multiple line display</strong></span><br />

(2) >2<span><strong></strong></span><br />
RESET<span><strong><<<macro 2 includes a reset sequence</strong></span><br />
INIT<span><strong><<<initialize the LCD</strong></span><br />
LCD></p>
<p>The <em>initialize LCD</em> macro (2) configures the screen for 4bit interface mode, enables cursor display, and sets a few other helpful options. <em>Configure the number of display lines, choose 1 for a single line display, or 2 for all other displays. </em></p>

<p>After initialization, the screen should be clear with a  cursor visible in the corner. If it didn't work, check the I2C connection, pull-up resistors, and power supply, then try again.</p>
<p>HD44780 LCDs need to  be reset with a special signal sequence before they can be initialized for 4bit or 8bit interface mode. Macro 1 creates this sequence. Macro 2 includes the reset sequence, so there's no need to use macro 1 before macro 2.</p>
<p><span>Step 3. Write test characters</span></p>
<p><span><img src='http://wherelabs.files.wordpress.com/2009/08/num-test.jpg?w=450&#038;h=160' alt='num-test' height='160' width='450' title='num-test' /><br />
</span></p>
<p>LCD>(6:80)<span><strong><<<write 80 numbers </strong></span><br />
LCD></p>
<p>The <em>write numbers</em> macro fills the LCD with test numbers between 0 and 9. The number after the colon tells the Bus Pirate how many test numbers to write, we're using a 4x20LCD, so we write 80 numbers to fill it. Notice that the cursor ends at position 0, under the first ‘0′.</p>

<p><img src='http://wherelabs.files.wordpress.com/2009/08/chara-test.jpg?w=450&#038;h=147' alt='chara-test' height='147' width='450' title='chara-test' /></p>
<p>LCD>(7:80)<span><strong><<<write 80 characters</strong></span><br />
LCD></p>
<p>The <em>write characters</em> macro fills the LCD with ASCII characters, enter the quantity after the colon. Notice that the fist line continues on the third, the third on the second, and the second on the last. The characters aren't continuous because  character LCDs don't wrap from one line to the next. We'll talk a little more about this in step 5.</p>
<p><span>Step 4. Clear LCD</span></p>

<p><span><img src='http://wherelabs.files.wordpress.com/2009/08/reset-macro.jpg?w=450&#038;h=156' alt='reset-macro' height='156' width='450' title='reset-macro' /><br />
</span></p>
<p>LCD>(3)<span><strong><<<clear the LCD</strong></span><br />
CLEARED<br />
LCD></p>
<p>The <em>clear LCD</em> macro sends the HD44780  command that erases the screen and returns the cursor to the first position.</p>
<p>You could also do any of these operations without the macros, refer to the command table at the beginning of this section. Enter ‘[0b1' in the Bus Pirate to set the interface to command mode ([) and send the HD44780 clear screen command (0b00000001) without a macro.</p>

<p><span>Step 5. Type text</span></p>
<p><span><img src='http://wherelabs.files.wordpress.com/2009/08/lcd1-text.jpg?w=450&#038;h=157' alt='LCD1-text' height='157' width='450' title='LCD1-text' /><br />
</span></p>
<p>LCD>(8)<span><strong><<<insert user text</strong></span><br />
Enter text to insert at the cursor position.<br />
HD44780 LCD demo<span><strong><<<we typed this</strong></span><br />
LCD></p>
<p>After clearing the LCD in step 4, the cursor is positioned  at the first block. We could also set it with the macro (4:0), which moves the cursor to the first character.</p>

<p>The <em>insert text at cursor</em> macro asks  for text input, and then copies it to the LCD when you press <em>enter</em>.</p>
<p>LCD>(4:0x40)<span><strong><<<position the cursor at 0x40</strong></span><br />
LCD>(8)<span><strong><<<insert  text</strong></span><br />
Enter text to insert at the cursor position.<br />

Bus Pirate v2go<span><strong><<<we typed this</strong></span><br />
LCD></p>
<p>Writing to the second line is a little more complicated, it actually starts at character 64 on a 4x20 LCD. If you continue writing from the end of line 1 (character 20) then you'll end up at the beginning of line three! <a href='http://ouwehand.net/~peter/lcd/lcd0.shtml#_4_line_displays'>This page</a> has a nice collection of memory maps for most character LCD sizes.</p>
<p>First, we position the cursor on the second line (4:0x40). Next, the 'insert text' macro grabs our input and copies it to the LCD.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/08/lcdall-text.jpg?w=450&#038;h=160' alt='LCDall-text' height='160' width='450' title='LCDall-text' /></p>
<p>LCD>(4:0x14)(8)(4:0x54)(8)<span><strong><<<multiple macro syntax</strong></span><br />

Enter text to insert at the cursor position.<br />
Firmware v2.0+<span><strong><<<we typed this</strong></span><br />
Enter text to insert at the cursor position.<br />
DangerousPrototypes<span><strong><<<we typed this</strong></span><br />
LCD></p>
<p>The Bus Pirate accepts multiple macros on the same line, so the entire screen can be written at once. We wrote to the last two lines with a single line of syntax.</p>
<p>We could  use '(3)(4:0)(8)(4:0x40)(8)(4:0x14)(8)(4:0x54)(8)' to clear the LCD and write all four lines with a single syntax entry.</p>
<p><span>Step 6. Reading from the LCD</span></p>

<p>The Bus Pirate and LCD adapter board can read from the LCD. We'll read the text we wrote to the screen (DDRAM), but you can also read settings and custom character ram (CGRAM) by setting the correct address.</p>
<p>LCD>[0b10000000 <span><strong><<<set the read pointer</strong></span><br />
HD44780 RS LOW, COMMAND MODE <span><strong><<<register select pin low</strong></span><br />
CMD WRITE: 0x80 <span><strong><<<wrote to LCD as command</strong></span><br />
LCD></p>
<p>First, we tell the Bus Pirate to send data to the LCD command register ([).  Next, we use the set DDRAM address command (0b1xxxxxxx) to set the read pointer to the beginning of the DDRAM (xxxxxxx=0000000).</p>
<p>LCD>]rrrrrrr <span><strong><<<read data memory</strong></span><br />

HD44780 RS HIGH, DATA MODE<span><strong><<<register select pin high</strong></span><br />
READ: 0x48<span><strong><<< ‘H'</strong><br />
</span>READ: 0x44<span><strong><<< ‘D'</strong></span><br />
READ: 0x34<span><strong><<< ‘4′</strong></span><br />

READ: 0x34<span><strong><<< ‘4′</strong></span><br />
READ: 0x37<span><strong><<< ‘7′</strong></span><br />
READ: 0x38<span><strong><<< ‘8′</strong></span><br />
READ: 0x30<span><strong><<< ‘0′</strong></span><br />

LCD></p>
<p>Finally, tell the Bus Pirate to read from data memory (]), and then read a few bytes (rrrrrrr). We got “HD44780″, the text we wrote to the screen in step 5.</p>
<p>You should also be able to use the shortcut r:7 to read seven bytes, but it's not working in the current firmware – we'll fix this prior to the next release.</p>
<p><strong>Doing more<br />
</strong></p>
<p>The HD44780 character LCD adapter is a handy accessory for the Bus Pirate. It can be used for a quick test, or more advanced logic development.</p>

<p>In addition to LCDs, the eight 2.5volt-5volt I/O pins might be useful for other high pin-count Bus Pirate applications.</p>
<p>We can have PCBs, kits, or assembled kits produced by <a href='http://www.seeedstudio.com/depot/'>Seeed Studio</a> for about $15, including worldwide shipping, <a href='http://whereisian.com/forum/index.php?topic=48.0'>more here</a>.</p>