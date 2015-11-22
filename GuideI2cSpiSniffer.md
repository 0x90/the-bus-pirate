<h1>Bus Pirate I2C, SPI sniffer updates</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/11/sniffer.png?w=329&#038;h=112' alt='sniffer' height='112' width='329' title='sniffer' /></p>
<p>With aphoticjezter's <a href='http://dangerousprototypes.com/2009/11/05/bus-pirate-i2c-sniffer-working/'>confirmation that the undocumented I2C sniffer actually works</a>, we tweaked the code to help get around the UART speed limitations. These updates are in the latest <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/firmware/'>nightly build</a>.</p>
<p>The I2C and SPI sniffers now use a 4096byte output <a href='http://en.wikipedia.org/wiki/Circular_buffer'>ring buffer</a>. Sniffer output goes into the ring buffer and gets pushed to the PC when the UART is free. This should eliminate problems with dropped bytes, regardless of UART speed or display mode. A long enough stream of data will eventually overtake the buffer, after which new bytes will be dropped until space is available.</p>

<p>Sniffer demos and documentation after the break.</p>
<p><span></span><strong>I2C sniffer</strong></p>
<p>The I2C sniffer is implemented in software and <em><strong>seems to work up to 70kHz</strong></em>. It's still very beta, improvements are probably possible.</p>
<ul>
<li>[/]  – Start/stop bit</li>
<li>+/-  – ACK/NACK</li>

</ul>
<p>I2C start and stop bits are represented by the normal Bus Pirate syntax.</p>
<p>I2C>(2)<br />
I2C bus sniffer, press any key to exit<br />
[0x40-][0x40-0x40-0x30-0x56-0x77-]<br />
I2C></p>
<p>Sniffed data values are always HEX formatted in user mode. Press any key to exit the sniffer.</p>
<p>See <a href='http://dangerousprototypes.com/2009/10/14/bus-pirate-binary-i2c-mode/'>here</a> for more about the I2C sniffer in I2C binary mode.</p>

<p><strong>SPI sniffer</strong></p>
<p>The SPI sniffer is implemented in hardware and should work up to 10MHz. It follows the configuration settings you entered for SPI mode.</p>
<ul>
<li>[/]  – CS enable/disable</li>
<li>0xXX – MOSI read</li>
<li>(0xXX)  – MISO read</li>

</ul>
<p>SPI CS pin transitions are represented by the normal Bus Pirate syntax. The byte sniffed on the MISO pin is displayed inside ().</p>
<p>SPI>(1)<br />
Sniff when:<br />
1. CS low<br />
2. CS high<br />
3. All traffic<br />
(1) ><br />
SPI bus sniffer, any key exists<br />

[0x30(0x00)0xff(0x12)0xff(0x50)][0x40(0x00)]</p>
<p>The SPI sniffer can read all traffic, or filter by the state of the CS pin. The byte sniffed on the MOSI pin is displayed as a HEX formatted value, the byte sniffed on the MISO pin is inside the ().</p>
<p>See <a href='http://dangerousprototypes.com/2009/10/08/bus-pirate-raw-spi-mode/'>here</a> for more about the SPI sniffer in SPI binary mode.</p>
<p><strong>Notes</strong></p>
<p>Both sniffers use the user input buffer as a ring buffer. Any commands entered after the sniffer macro will be lost.</p>
<p>If the ring buffer is full, bytes are simply dropped until there's free space. The MODE LED turns off if this happens.</p>