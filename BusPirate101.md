<h1>Bus Pirate 101 Tutorial</h1>

<img src='http://wherelabs.files.wordpress.com/2009/07/bpv3-101.jpg?w=450&h=311' />
<p>In this introductory tutorial we cover the basics of the <a href='http://www.buspirate.com'>Bus Pirate universal serial interface</a>. First, we identify the different parts of the Bus Pirate and explain their function. Next, we cover  driver installation and terminal configuration. Finally, we explain the user interface and demonstrate some basic terminal menu commands. There's  links to   everything you need to start hacking with the Bus Pirate.</p>

<h2>Bus Pirate parts</h2>
<img src='http://wherelabs.files.wordpress.com/2009/07/bp-overview.jpg?w=450&h=341' />

<p><em>1. Mini-B USB port.</em> Connects the Bus Pirate to a PC. The Bus Pirate draws power from the USB port, and uses the data connection to communicate with the PC.</p>

<p><em>2. USB transmit indicator.</em> This LED flashes when there's traffic from the PIC to the PC.</p>
<p><em>3. Power indicator.</em> This LED lights when the Bus Pirate is powered by the USB supply.</p>
<p><em>4. Mode indicator.</em> This LED lights when the Bus Pirate is configured for a protocol mode from the user terminal (menu ‘m'). The I/O pins might be active when the mode indicator is on. The pins should be in a safe, non-powered, high-impedance state when the mode LED is off.</p>
<p><em>5. Voltage regulator indicator.</em> This LED lights when the on-board power supplies have been activated from the user terminal (command capital ‘W' ).</p>

<p><em>6. I/O pins.</em> This 2x5 block of 0.1″ pin header connects the Bus Pirate to external circuits. See I/O header pin descriptions under the Reference Section for a ful explanation.</p>

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



<p>Notes: **TX moved from CS to MOSI in firmware v0g.</p>**<p><em>7. In circuit serial programming (ICSP) header.</em> This 1x5 block of 0.1″ pin header is the programming connection for the PIC 24FJ64GA002 microcontroller. These pins can be used to write new firmware to the microcontroller with a programmer like the PICKIT2 or ICD2 . The Bus Pirate firmware can also be updated over the USB connection using a bootloader, so the ICSP header is normally only used to program it the first time at the factory. Put a jumper between the PGC and PGD pins to trigger the on-board bootloader for firmware updates.</p>

<p><em>8. Serial terminal (ST) header.</em> <em>Version v2go only</em>. This unpopulated header is a tap into the UART connection between the PIC microcontroller and the FTDI 232BL chip that provides the USB connection. The Bus Pirate firmware defaults to a  115200bps/8/N/1 UART.</p>
<h2><strong>FTDI driver install and configuration<br />
</strong></h2>
<p><img src='http://wherelabs.files.wordpress.com/2009/07/ftdi-driver.png?w=339&#038;h=143' alt='ftdi-driver' height='143' width='339' title='ftdi-driver' /></p>
<p>Windows will request a driver the first time the Bus Pirate connects to a PC. Extract the latest <a href='http://www.ftdichip.com/Drivers/VCP.htm'>virtual com port drivers from FTDI</a> into a folder and browse to them using the ‘Found New Hardware' wizard. Install guides and drivers for other systems are also available on the FTDI driver download page.</p>

<p><img src='http://wherelabs.files.wordpress.com/2009/07/com-port.png?w=287&#038;h=91' alt='com-port' height='91' width='287' title='com-port' /></p>
<p>To find the COM port number assigned to the Bus Pirate go to the Windows device manager (<em>Start->Settings->Control panel->System->Hardware->Device manager</em>). Look in ‘Ports (COM &amp; LPT)'  for ‘USB Serial Port', ours is COM5.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/07/com-port-change-ii.png?w=422&#038;h=150' alt='com-port-change.ii' height='150' width='422' title='com-port-change.ii' /></p>

<p>You can change the serial port assigned to the FTDI chip. Go to <em>USB Serial Port properties->Port settings tab->Advanced</em>, change the COM port in the drop-down box.</p>
<h2><strong>Terminal setup</strong></h2>
<p>Windows terminal is cranky, but <a href='http://whereisian.com/forum/index.php?topic=4.0'>it appears to work</a> with the Bus Pirate when VT100 emulation is enabled. We highly recommend a better terminal, we like <a href='http://www.ayera.com/teraterm/'>Tera Term Pro</a> for Windows.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/07/tt-setup1.png?w=291&#038;h=176' alt='tt-setup1' height='176' width='291' title='tt-setup1' /></p>

<p>First, configure the correct COM port and settings. The Bus Pirate operates at 115200bps/8/N/1 on the COM port assigned by Windows. <span><em>Flow control is not required for normal operation, it is currently only used by the JTAG programmer.</em></span></p>
<p><img src='http://wherelabs.files.wordpress.com/2009/07/tt-setup2.png?w=371&#038;h=185' alt='tt-setup2' height='185' width='371' title='tt-setup2' /></p>
<p>Next, check the terminal setup. Turn off local echo and use a VT100 terminal type. The Bus Pirate should work with any type of new-line character, but we use the CR setting.</p>
<h2><strong>Get to know the terminal interface</strong></h2>
<p><strong><img src='http://wherelabs.files.wordpress.com/2009/07/help.png?w=447&#038;h=512' alt='help' height='512' width='447' title='help' /><br />
</strong></p>
<p>The Bus Pirate is controlled by text commands entered through the serial terminal. If the terminal is blank, press <em>enter</em> to show the command prompt. Press ‘?', followed by <em>enter</em>, to show the help menu.</p>

<ul>
<li><strong>Menus</strong> configure various Bus Pirate options like pull-up resistors, terminal speed, data display format (DEC, HEX, BIN), etc. Type the menu command, followed by <em>enter</em>, to display the options.</li>
<li><strong>Syntax</strong> is used to interact with a device connected  over a bus. Commands are mostly single characters, such as ‘r' to read a byte. Enter up to 4000 characters of syntax, press <em>enter</em> to execute the sequence.</li>

</ul>
<p>Each menu and syntax option is documented fully in the <a href='http://dangerousprototypes.com/bus-pirate-manual/'>Bus Pirate manual</a>.</p>
<p>Most menus have a default option shown in () before the prompt:</p>
<p>Output type:<br />
1. High-Z outputs (H=input, L=GND)<br />
2. Normal outputs (H=Vcc, L=GND)<br />
(1) > <span><strong><<< option 1 is the default</strong></span></p>

<p>Press <em>enter</em> to select the default option.</p>
<p><strong>Bus modes, protocol libraries</strong></p>
<p>HiZ>M <span><strong><<< bus mode menu</strong></span><br />
1. HiZ<br />
2. 1-WIRE<br />
3. UART<br />

4. I2C<br />
5. SPI<br />
6. JTAG<br />
7. RAW2WIRE<br />
8. RAW3WIRE<br />
9. PC KEYBOARD<br />
10. MIDI<br />
11. LCD<br />
(1) >5 <strong><span><<< enter SPI bus mode</span><br />

</strong></p>
<p>The ‘bus mode' menu (M) configures the Bus Pirate for a specific protocol, like 1-Wire, I2C, SPI, etc. The default start-up mode is HiZ, all pins are inputs and all power supplies are off.</p>
<p>Most modes have additional options, like <a href='http://hackaday.com/2009/07/01/mixed-voltage-interfacing-with-the-bus-pirate/'>open drain outputs</a> or speed settings. Each bus mode is documented in the <a href='http://dangerousprototypes.com/bus-pirate-manual/'>Bus Pirate manual</a><a href='http://www.buspirate.com/'></a>.</p>
<p>SPI READY<br />
SPI>p <span><strong><<< pull-up configuration menu</strong></span><br />

1. Pullup off<br />
2. Pullup on<br />
(1) >2 <span><strong><<< pull-up on</strong></span><br />
PULLUP RESISTORS ON<br />
SPI>W <span><strong><<< power supplies ON syntax</strong></span><br />
POWER SUPPLIES ON<br />

SPI>v <span><strong><<< check power supply output</strong></span><br />
VOLTAGE MONITOR: 5V: 4.9 | 3.3V: 3.3 | VPULLUP: 0.0 |<br />
SPI></p>
<p>Once a mode is configured, you can enable other options.  Turn on the on-board voltage regulators (capital ‘W') and check the output levels (v). Configure the <a href='http://dangerousprototypes.com/2009/07/27/bus-pirate-practical-guide-to-pull-up-resistors/'>pull-up resistors</a> (p).</p>

<h2><strong>Taking it further</strong></h2>

<p>Now might be a good time to run a <a href='http://dangerousprototypes.com/2009/07/28/bus-pirate-self-test-guide/'>hardware self-test</a> and update to the latest firmware (<a href='http://dangerousprototypes.com/2009/07/24/bus-pirate-firmware-upgrades/'>Windows</a>, <a href='http://dangerousprototypes.com/2009/10/24/bus-pirate-firmware-updates-on-osx/'>OSX</a>, <a href='http://dangerousprototypes.com/2009/08/06/bus-pirate-firmware-upgrades-on-linux-osx/'>Python</a>).</p>
<p>For lots of device demonstrations, and to learn more about the Bus Pirate syntax, menus, pinout, modes, and more, check the  <a href='http://dangerousprototypes.com/bus-pirate-manual/'>Bus Pirate manual</a> and the <a href='http://whereisian.com/forum/index.php?board=4.0'>Bus Pirate forum</a>.</p>

<p><strong>Part 2</strong></p>
<p>Continue reading Bus Pirate 102.</p>
