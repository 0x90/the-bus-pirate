<h1>Bus Pirate: Binary 1-Wire mode</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/10/1w01.png?w=450&#038;h=114' alt='1w01' height='114' width='450' title='1w01' /></p>
<p>The Bus Pirate’s new binary modes provide a consistent, logical way to script actions from Python, Perl, etc. We've already introduced the new binary <a href='http://dangerousprototypes.com/2009/10/09/bus-pirate-raw-bitbang-mode/'>bitbang</a>, <a href='http://dangerousprototypes.com/2009/10/08/bus-pirate-raw-spi-mode/'>SPI</a>, <a href='http://dangerousprototypes.com/2009/10/14/bus-pirate-binary-i2c-mode/'>I2C</a>, and <a href='http://dangerousprototypes.com/2009/10/19/bus-pirate-binary-uart-mode/'>UART</a> modes. This post outlines the last planned binmode addition, 1-Wire functions. A completed binary mode will be in the next firmware release, for now you can <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/firmware/v2-nightly'>grab the latest v2.7 nightly compile</a>.</p>

<p>We want your scripts! If you script something for any of the new modes, in any language, we’d like to host it in the <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/scripts'>example scripts folder</a>. We’ll send Bus Pirate probe cable kits to two authors of Bus Pirate binary mode scripts posted by the end of next week (October 24th, 2009). Here’s <a href='http://dangerousprototypes.com/category/binmode/'>all the binmode documentation</a> so far.</p>
<p>Binary 1-Wire mode specification follows after the break.</p>
<p><span></span></p>
<p><strong>Binary 1-Wire mode command table</strong></p>
<ul>
<li>00000000 – Exit to bitbang mode, responds “BBIOx”</li>
<li>00000001 – Mode version string (1W01)</li>

<li>00000010 – 1-Wire reset</li>
<li>00000100 – Read byte</li>
<li>00001000 – ROM search macro (0xf0)</li>
<li>00001001 - ALARM search macro (0xec)</li>
<li>0001xxxx – Bulk write, write 1-16 bytes (0=1byte!)</li>
<li>0100wxyz – Configure peripherals, w=power, x=pullups, y=AUX, z=CS</li>
<li>0101wxyz – Read peripherals (planned, not implemented)</li>
</ul>

<p>Enter binary 1-Wire mode by first <a href='http://dangerousprototypes.com/2009/10/09/bus-pirate-raw-bitbang-mode/'>entering bitbang mode</a>, then send 0×04 to enter 1-Wire mode.</p>
<p>Most commands are a single byte. Commands generally return 1 for success, 0 for failure.</p>
<p><em>00000000 – Exit to bitbang mode, responds “BBIOx”</em></p>
<p>This command resets the Bus Pirate into raw bitbang mode from the user terminal. It also resets to raw bitbang mode from any protocol mode. This command always returns a five byte bitbang version string “BBIOx”, where x is the current bitbang protocol version (currently 1).</p>
<p><em>00000001 – Display mode version string, responds “1Wxx”</em></p>
<p>Once in binary 1-Wire mode, send 0×01 to get the current mode version string. The Bus Pirate responds ‘1Wxx’, where xx is the protocol version (currently 01). Get the version string at any time by sending 0×01 again. This command is the same in all binary modes, the current mode can always be determined by sending 0×01.</p>
<p><em>00000010 – 1-Wire reset<br />
</em></p>

<p>Send a 1-Wire reset. Responds 0×01.</p>
<p><em>00000100 – Read byte</em></p>
<p>Reads a byte from the  bus, returns the byte.</p>
<p><em>00001000 - ROM search macro (0xf0)<br />
00001001 - ALARM search macro (0xec)</em></p>
<p>Search macros are special 1-Wire procedures that determine device addresses. The command returns 0x01, and then each 8-byte 1-Wire address located. Data ends with 8 bytes of 0xff.</p>

<p><em>0001xxxx – Bulk 1-Wire write, send 1-16 bytes (0=1byte!)</em></p>
<p>Bulk write transfers a packet of xxxx+1 bytes to the 1-Wire bus. Up to 16 data bytes can be sent at once. Note that 0000 indicates 1 byte because there’s no reason to send 0. BP replies 0×01 to each byte.</p>
<p><em>0100wxyz – Configure peripherals w=power, x=pullups, y=AUX, z=CS</em></p>
<p>Enable (1) and disable (0) Bus Pirate peripherals and pins. Bit w enables the power supplies, bit x toggles the on-board pull-up resistors, y sets the state of the auxiliary pin, and z sets the chip select pin. Features not present in a specific hardware version are ignored. Bus Pirate responds 0×01 on success.</p>
<p>Note: CS pin always follows the current HiZ pin configuration. AUX is always a normal pin output (0=GND, 1=3.3volts).</p>
<p>A read command is planned but not implemented in this version.</p>