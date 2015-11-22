<h1>Bus Pirate: Binary raw-wire mode</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/10/raw-wire.png?w=423&#038;h=125' alt='raw-wire' height='125' width='423' title='raw-wire' /></p>
<p>Raw-wire binary mode provides access to the Bus Pirate's raw 2- and 3-wire libraries. This new mode will make it easier to script operations on arbitrary serial protocols used by devices like smart cards, shift registers, etc. A completed raw-wire binary mode will be in the next firmware release, for now you can grab the <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/firmware/v2-nightly'>latest v2.9 nightly compile</a>.</p>
<p>Here’s <a href='http://dangerousprototypes.com/category/binmode/'>all the binmode documentation</a> so far. Binary raw-wire mode specification follows after the break.</p>
<p><span></span></p>

<p><strong>Commands</strong></p>
<ul>
<li>00000000 – Enter raw bitbang mode, reset to raw bitbang mode</li>
<li>00000001 – Mode version string (RAW1)</li>
<li>0000001x - I2C-style start (0) / stop (1) bit</li>
<li> 0000010x- CS low (0) / high (1)</li>
<li> 00000110 - Read byte</li>

<li> 00000111 - Read bit</li>
<li> 00001000 - Peek at input pin</li>
<li> 00001001 - Clock tick</li>
<li> 0000101x - Clock low (0) / high (1)</li>

<li> 0000110x - Data low (0) / high (1)</li>
<li> 0001xxxx – Bulk transfer, send 1-16 bytes (0=1byte!)</li>
<li> 0010xxxx - Bulk clock ticks, send 1-16 ticks</li>
<li> 0100wxyz – Configure peripherals, w=power, x=pullups, y=AUX, z=CS</li>
<li> 0110000x – Set speed, low (0=~5kHz) / high (1=~50kHz)</li>

<li> 1000wxyz – Configure mode, w=output type, x=2/3wire, y=msb/lsb, z=n/a</li>
</ul>
<p>Enter binary  raw-wire mode by first <a href='http://dangerousprototypes.com/2009/10/09/bus-pirate-raw-bitbang-mode/'>entering bitbang mode</a>, then send 0×05 to enter raw-wire mode.</p>
<p>Most commands are a single byte. Commands generally return 1 for success, 0 for failure.</p>
<p><em>00000000 – Exit to bitbang mode, responds “BBIOx”</em></p>
<p>This command resets the Bus Pirate into raw bitbang mode from the user terminal. It also resets to raw bitbang mode from any protocol mode. This command always returns a five byte bitbang version string “BBIOx”, where x is the current bitbang protocol version (currently 1).</p>
<p><em>00000001 – Display mode version string, responds “RAWx”</em></p>
<p>Once in binary raw-wire mode, send 0×01 to get the current mode version string. The Bus Pirate responds ‘RAWx’, where x is the protocol version (currently 1). Get the version string at any time by sending 0×01 again. This command is the same in all binary modes, the current mode can always be determined by sending 0×01.</p>

<p><em>0000001x - I2C-style start (0) / stop (1) bit</em></p>
<p>Send an I2C start or stop bit. Responds 0×01. Useful for I2C-like 2-wire protocols, or building a custom implementation of I2C using the raw-wire library.</p>
<p><em>0000010x- CS low (0) / high (1)</em></p>
<p>Toggle the Bus Pirate chip select pin, follows HiZ configuration setting. CS high is pin output at  3.3volts, or HiZ. CS low is pin output at  ground. Bus Pirate responds 0×01.</p>
<p><em>00000110 - Read byte</em></p>
<p>Reads a byte from the  bus, returns the byte. Writes 0xff to bus in 3-wire mode.</p>
<p><em>00000111 - Read bit</em></p>

<p>Read a single bit from the bus, returns the bit value.</p>
<p><em>00001000 - Peek at input pin</em></p>
<p>Returns the state of the data input pin without sending a clock tick.</p>
<p><em>00001001 - Clock tick</em></p>
<p>Sends one clock tick (low->high->low). Responds 0x01.</p>

<p><em>0000101x - Clock low (0) / high (1)</em></p>
<p>Set clock signal low or high. Responds 0x01.</p>
<p><em>0000110x - Data low (0) / high (1)</em></p>
<p>Set data signal low or high. Responds 0x01.</p>
<p><em>0001xxxx – Bulk transfer, send 1-16 bytes (0=1byte!)</em></p>
<p>Bulk write transfers a packet of xxxx+1 bytes to the bus. Up to 16 data bytes can be sent at once. Note that 0000 indicates 1 byte because there’s no reason to send 0. BP replies 0×01 to each byte.</p>

<p><em>0010xxxx - Bulk clock ticks, send 1-16 ticks</em></p>
<p>Create bulk clock ticks on the bus. Note that 0000 indicates 1 clock tick because there’s no reason to send 0. BP replies 0×01.</p>
<p><em>0100wxyz – Configure peripherals w=power, x=pullups, y=AUX, z=CS</em></p>
<p>Enable (1) and disable (0) Bus Pirate peripherals and pins. Bit w enables the power supplies, bit x toggles the on-board pull-up resistors, y sets the state of the auxiliary pin, and z sets the chip select pin. Features not present in a specific hardware version are ignored. Bus Pirate responds 0×01 on success.</p>
<p>Note: CS pin always follows the current HiZ pin configuration. AUX is always a normal pin output (0=GND, 1=3.3volts).</p>
<p>A read command is planned but not implemented in this version.</p>
<p><em>0110000x – Set speed, 1=high (50kHz) 0=low (5kHz)</em></p>
<p>The last bit of the speed command determines the bus speed. Startup default is high-speed. Bus Pirate responds 0×01.</p>

<p>A read command is planned but not implemented in this version.</p>
<p><em>1000wxyz – Config, <em>w=HiZ/3.3v</em>, x=2/3wire, y=msb/lsb, z=not used<br />
</em></p>
<p>Configure the raw-wire mode settings. w= pin output type HiZ(0)/3.3v(1). x= protocol wires (0=2, 1=3), toggles between a shared input/output pin (raw2wire), and a separate input pin (raw3wire). y= bit order (0=MSB, 1=LSB). The Bus Pirate responds 0×01 on success.</p>
<p>Default raw startup condition is 000z. HiZ mode configuration applies to the data pins and the CS pin, but not the AUX pin.</p>
<p>A read command is planned but not implemented in this version.</p>