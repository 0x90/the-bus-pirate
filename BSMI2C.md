<h1>Bus Pirate: Binary I2C mode</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/10/binic2.png?w=450&#038;h=276' alt='binic2' height='276' width='450' title='binic2' /></p>
<p>The Bus Pirate's new binary modes provide a consistent, logical way to script actions from Python, Perl, etc. We already introduced the new binary <a href='http://dangerousprototypes.com/2009/10/09/bus-pirate-raw-bitbang-mode/'>bitbang</a> and <a href='http://dangerousprototypes.com/2009/10/08/bus-pirate-raw-spi-mode/'>SPI</a> modes, today we'll document the binary I2C mode. Binary I2C will be in the v2.6 firmware release, for now you can <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/firmware/v2-nightly'>grab the v2.6 nightly compile</a>.</p>

<p>We want your scripts! If you script something for any of the new modes, in any language, we'd like to host it in the <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/scripts'>example scripts folder</a>. We'll send Bus Pirate probe cable kits to two authors of  Bus Pirate binary mode scripts posted by the end of next week (October 24th, 2009).</p>
<p>Binary I2C mode specification follows after the break.</p>
<p><span></span><strong>Binary I2C mode command table</strong></p>
<ul>
<li>00000000 - Exit to bitbang mode, responds 'BBIOx'</li>
<li>00000001 – Mode version string (I2C1)</li>

<li>00000010 – Send I2C start bit</li>
<li>00000011 – Send I2C stop bit</li>
<li>00000100 - I2C read byte</li>
<li>00000110 - Send I2C ACK bit</li>
<li>00000111 - Send I2C NACK bit</li>
<li>00001111 - Start bus sniffer</li>

<li>0001xxxx – Bulk transfer, send 1-16 bytes (0=1byte!)</li>
<li>0100wxyz – Configure peripherals w=power, x=pullups, y=AUX, z=CS</li>
<li>0101wxyz – Read peripherals (planned, not implemented)</li>
<li>0110000x - Set I2C speed, 1=high (50kHz) 0=low (5kHz)</li>
<li>0111000x - Read speed (planned, not implemented)</li>
</ul>
<p>Enter binary I2C mode by first <a href='http://dangerousprototypes.com/2009/10/09/bus-pirate-raw-bitbang-mode/'>entering bitbang mode</a>, then send 0x02 to enter I2C mode.</p>

<p>Most I2C mode commands are a single byte. Commands generally return 1 for success, 0 for failure.</p>
<p><em>00000000 - Exit to bitbang mode, responds 'BBIOx'</em></p>
<p>This command resets the Bus Pirate into raw bitbang mode from the user terminal. It also resets to raw bitbang mode from raw I2C mode, or any other protocol mode. This command always returns a five byte bitbang version string 'BBIOx', where x is the current bitbang protocol version (currently 1).</p>
<p><em>00000001 – Display mode version string, responds 'I2Cx'</em></p>
<p>Once in binary I2C mode, send 0×01 to get the current mode version string.  The Bus Pirate responds ‘I2Cx’, where x is the raw I2C protocol version (currently 1). Get the version string at any time by sending 0×01 again. This command is the same in all binary modes, the current mode can always be determined by sending 0x01.</p>

<p><em>00000010 – I2C start bit</em></p>
<p>Send an I2C start bit. Responds 0x01.</p>
<p><em>00000011 – I2C stop bit</em></p>
<p>Send an I2C stop bit. Responds 0x01.</p>
<p><em>00000100 - I2C read byte</em></p>
<p>Reads a byte from the I2C bus, returns the byte. <em>You must ACK or NACK each byte manually!</em></p>

<p><em>00000110 - ACK bit</em></p>
<p>Send an I2C ACK bit after reading a byte. Tells a slave device that you will read another byte. Responds 0x01.</p>
<p><em>00000111 - NACK bit</em></p>
<p>Send an I2C NACK bit after reading a byte. Tells a slave device that you will stop reading, next bit should be an I2C stop bit. Responds oxo1.</p>
<p><em>00001111 - Start bus sniffer</em></p>

<p>Sniff traffic on an I2C bus.</p>
<ul>
<li>[/]  - Start/stop bit</li>
<li>\ - escape character precedes a data byte value</li>
<li>+/-  - ACK/NACK</li>
</ul>
<p>Sniffed traffic is encoded according to the table above. Data bytes are escaped with the '\' character. Send a single byte to exit, Bus Pirate responds 0x01 on exit.</p>

<p><em>0001xxxx – Bulk I2C write, send 1-16 bytes (0=1byte!)</em></p>
<p>Bulk I2C allows multi-byte writes. The Bus Pirate expects xxxx+1 data bytes. Up to 16 data bytes can be sent at once. Note that 0000 indicates 1 byte because there’s no reason to send 0.</p>
<p>BP replies 0×01 to the bulk I2C command. After each data byte the Bus Pirate returns the ACK (0x00) or NACK (0x01) bit from the slave device.</p>
<p><em>0100wxyz – Configure peripherals w=power, x=pullups, y=AUX, z=CS</em></p>
<p>Enable (1) and disable (0) Bus Pirate peripherals and pins. Bit w enables the power supplies, bit x toggles the on-board pull-up resistors, y sets the state of the auxiliary pin, and z sets the chip select pin. Features not present in a specific hardware version are ignored. Bus Pirate responds 0×01 on success.</p>
<p>Note: CS pin always follows the current HiZ pin configuration. AUX is always a normal pin output (0=GND, 1=3.3volts).</p>
<p>A read command is planned but not implemented in this version.</p>
<p><em>NOTE: due to a typo this was previously command 0110.</em></p>

<p><em>0110000x - Set I2C speed, 1=high (50kHz) 0=low (5kHz)</em></p>
<p>The last bit of the speed command determines the I2C bus speed. Binary mode currently uses the software I2C library, though it may be configurable in a future update. Startup default is high-speed. Bus Pirate responds 0×01 on success.</p>
<p>A read command is planned but not implemented in this version.</p>
<p><em>NOTE: due to a typo this was previously command 0100.</em></p>