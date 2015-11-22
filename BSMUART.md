<h1>Bus Pirate: Binary UART mode</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/10/binuart.png?w=450&#038;h=278' alt='binuart' height='278' width='450' title='binuart' /></p>
<p>The Bus Pirate's new binary modes provide a consistent, logical way to script actions from Python, Perl, etc. We already introduced the new binary <a href='http://dangerousprototypes.com/2009/10/09/bus-pirate-raw-bitbang-mode/'>bitbang</a>, <a href='http://dangerousprototypes.com/2009/10/08/bus-pirate-raw-spi-mode/'>SPI</a>, and <a href='http://dangerousprototypes.com/2009/10/14/bus-pirate-binary-i2c-mode/'>I2C</a> modes. This post outlines the binary UART functions. A UART is like a PC serial port. Binary mode will be complete in the next firmware release, for now you can <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/firmware/v2-nightly'>grab the latest v2.7 nightly compile</a>.</p>

<p>We want your scripts! If you script something for any of the new modes, in any language, we'd like to host it in the <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/scripts'>example scripts folder</a>. We'll send Bus Pirate probe cable kits to two authors of  Bus Pirate binary mode scripts posted by the end of next week (October 24th, 2009). Here’s <a href='http://dangerousprototypes.com/category/binmode/'>all the binmode documentation</a> so far.</p>
<p>Binary UART mode specification follows after the break.</p>
<p><span></span><strong>Binary UART mode command table</strong></p>
<ul>
<li>00000000 - Exit to bitbang mode, responds "BBIOx"</li>

<li>00000001 – Mode version string (ART1)</li>
<li>00000010 – Start echo UART RX</li>
<li>00000011 – Stop echo UART RX</li>
<li>00000111 - Manual baud rate config, send 2 bytes</li>
<li>00001111 - UART bridge mode (reset to exit)</li>
<li>0001xxxx – Bulk transfer, send 1-16 bytes (0=1byte!)</li>
<li>0100wxyz – Configure peripherals, w=power, x=pullups, y=AUX, z=CS</li>

<li>0101wxyz – Read peripherals (planned, not implemented)</li>
<li>0110xxxx - Set speed (see options)</li>
<li>0111000x - Read speed (planned, not implemented)</li>
<li>100wxxyz – Config, w=output type, xx=databits and parity, y=stop bits, z=RX polarity</li>
<li>101wxxyz – Read config (planned, not implemented)</li>
</ul>
<p>Enter binary UART mode by first <a href='http://dangerousprototypes.com/2009/10/09/bus-pirate-raw-bitbang-mode/'>entering bitbang mode</a>, then send 0x03 to enter UART mode.</p>

<p>Most commands are a single byte. Commands generally return 1 for success, 0 for failure.</p>
<p><em>00000000 - Exit to bitbang mode, responds "BBIOx"</em></p>
<p>This command resets the Bus Pirate into raw bitbang mode from the user terminal. It also resets to raw bitbang mode from  any  protocol mode. This command always returns a five byte bitbang version string "BBIOx", where x is the current bitbang protocol version (currently 1).</p>
<p><em>00000001 – Display mode version string, responds "ARTx"</em></p>
<p>Once in binary UART mode, send 0×01 to get the current mode version string.  The Bus Pirate responds ‘ARTx’, where x is the binary UART protocol version (currently 1). Get the version string at any time by sending 0×01 again. This command is the same in all binary modes, the current mode can always be determined by sending 0x01.</p>

<p><em>0000001x – Start (0)/stop(1) echo UART RX</em></p>
<p>In binary UART mode the UART is always active and receiving. Incoming data is only copied to the USB side if UART RX echo is enabled. This allows you to configure and control the UART mode settings without  random data colliding with response codes. UART mode starts with echo <em>disabled</em>. This mode has no impact on data transmissions.</p>
<p>Responds 0x01. Clears buffer overrun bit.</p>
<p><em>00000111 – Manual baud rate configuration, send 2 bytes</em></p>
<p>Configures the UART using custom baud rate generator settings. This command is followed by two data bytes that represent the BRG register value. Send the high 8 bits first, then the low 8 bits.</p>
<p>Use the <a href='http://ww1.microchip.com/downloads/en/DeviceDoc/39708B.pdf'>UART manual</a> <a href='PDF.md'>PDF</a> or an online calculator to find the correct value (key values: fosc 32mHz, clock divider = 2, BRGH=1) . Bus Pirate responds 0x01 to each byte. Settings take effect immediately.</p>

<p><em>00001111 - UART bridge mode (reset to exit)</em></p>
<p>Starts a transparent UART bridge using the current configuration. Unplug the Bus Pirate to exit.</p>
<p><em>0001xxxx – Bulk UART write, send 1-16 bytes (0=1byte!)</em></p>
<p>Bulk write transfers a packet of  xxxx+1 bytes to the UART. Up to 16 data bytes can be sent at once. Note that 0000 indicates 1 byte because there’s no reason to send 0. BP replies 0×01 to each byte.</p>
<p><em>0100wxyz – Configure peripherals w=power, x=pullups, y=AUX, z=CS</em></p>
<p>Enable (1) and disable (0) Bus Pirate peripherals and pins. Bit w enables the power supplies, bit x toggles the on-board pull-up resistors, y sets the state of the auxiliary pin, and z sets the chip select pin. Features not present in a specific hardware version are ignored. Bus Pirate responds 0×01 on success.</p>
<p>Note: CS pin always follows the current HiZ pin configuration. AUX is always a normal pin output (0=GND, 1=3.3volts).</p>
<p>A read command is planned but not implemented in this version.</p>

<p><em>0110xxxx - Set UART speed</em></p>
<p>Set the UART at a preconfigured speed value: 0000=300, 0001=1200, 0010=2400,0011=4800,0100=9600,0101=19200,0110=31250 (MIDI), 0111=38400,1000=57600,1010=115200</p>
<p>Start default is 300 baud. Bus Pirate responds 0×01 on success. A read command is planned but not implemented in this version.</p>
<p><em>100wxxyz – Configure UART settings</em></p>
<ul>
<li>w= pin output HiZ(0)/3.3v(1)</li>
<li>xx=databits and parity  8/N(0), 8/E(1), 8/O(2), 9/N(3)</li>
<li>y=stop bits 1(0)/2(1)</li>

<li>z=RX polarity idle 1 (0), idle 0 (1)</li>
</ul>
<p>Startup default is 00000. Bus Pirate responds 0x01 on success. A read command is planned but not implemented in this version.</p>
<p><em>Note that this command code is three bits because the databits and parity setting consists of two bits. It is not quite the same as the binary SPI mode configuration command code.</em></p>
<p><em>Thanks to audiohacked for helping develop these specifications <a href='http://whereisian.com/forum/index.php?topic=104.msg670#msg670'>in the forum</a>.<br />
</em></p>