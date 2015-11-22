<h1>Scan for I2C read and write addresses</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/09/i2c-scan.png?w=345&#038;h=221' alt='i2c-scan' height='221' width='345' title='i2c-scan' /></p>
<p>You can find the <a href='http://en.wikipedia.org/wiki/I%C2%B2C'>I2C</a> address for most I2C-compatible chips in the datasheet. But what if you're working with an unknown chip, a dated chip with no datasheet, or you're just too lazy to look it up?</p>
<p>The <a href='http://dangerousprototypes.com/bus-pirate-manual/'>Bus Pirate</a> has a built-in address scanner that checks every possible I2C address for a response. This brute force method is a fast and easy way to see if any chips are responding, and to uncover undocumented access addresses.</p>

<p><img src='http://wherelabs.files.wordpress.com/2009/09/i2c-scan-thumb.jpg?w=200&#038;h=128' alt='i2c-scan-thumb' height='128' width='200' title='i2c-scan-thumb' />I2C chips respond to a  7bit address, so up to 128 devices can share the same two communication wires. An additional bit of the address determines if the operation is a write to the chip (0), or a read from the chip (1).</p>
<p>We connected the Bus Pirate to the <a href='http://dangerousprototypes.com/2009/07/30/prototype-bus-pirate-3eeprom-explorer-board/'>3EEPROM explorer board</a>. The 7bit base address for the 24LC/AA I2C EEPROM is 0101000 (0x50 in HEX). It answers at the write address 0101000<span><strong>0</strong></span> (0xA0) and the read address 0101000<span><strong>1</strong></span> (0xA1).</p>
<p>I2C>(1)<span><strong><<<I2C search macro</strong></span><br />

Searching 7bit I2C address space.<br />
Found devices at:<br />
0xA0(0x50 W) 0xA1(0x50 R)<br />
I2C></p>
<p>Macro 1 in the I2C library runs the  address scanner. The scanner displays  the raw addresses the chip acknowledged (0xA0, 0xA1), and the 7bit address equivalent (ox50) with write or read bit indicators (W/R). Datasheets usually list the 7bit address, but the 8bit value is more recognizable on a logic analyzer, snooper, debugger, etc.</p>