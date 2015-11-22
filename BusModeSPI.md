<h1>Bus Pirate: SPI guide</h1>

<p><strong>Bus:</strong> <a href='http://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus'>SPI</a> (serial peripheral interface).<br />

<strong>Connections: </strong>four pins (MOSI/MISO/CLOCK/CS) and ground.<br />
<strong>Output type:</strong> 3.3volt normal, or <a href='http://en.wikipedia.org/wiki/High_impedence'>open collector</a> (<a href='http://dangerousprototypes.com/2009/07/27/bus-pirate-practical-guide-to-pull-up-resistors/'>pull-up resistors</a> required).<br />
<strong>Pull-up resistors: </strong>required for open drain output mode (2K – 10K).<br />
<strong>Maximum voltage: </strong>5.5volts (5volt safe).</p>

<table border='0'>
<tbody>
<tr>
<td><strong>Syntax</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>A/a/@</td>
<td>Toggle auxiliary pin. Capital “A” sets AUX high, small “a” sets to ground. @ sets aux to input (high impedance mode) and reads the pin value.</td>
</tr>
<tr>
<td>D/d</td>

<td>Measure voltage on the ADC pin (v1+ hardware only).</td>
</tr>
<tr>
<td>W/w</td>
<td>Capital ‘W’ enables the on-board power supplies. Small ‘w’ disables them. (v1+ hardware only).</td>
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
<td>Read one byte by sending dummy byte (0xff). (r:1…255 for bulk reads)</td>
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

<td>Value delimiter. Use a coma or space to separate numbers. Any combination is fine, no delimiter is required between non-number values: {0xa6,0, 0 16 5 0b111 0haF}.</td>
</tr>
<tr>
<td>&</td>
<td>Delay 1uS. (&:1…255 for multiple delays)</td>
</tr>
<tr>
<td>(#)</td>
<td>Run macro, (0) for macro list</td>
</tr>
</tbody>
</table>

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
</tbody>
</table>
<p><strong>Configuration options</strong></p>
<p><em>Speed -</em> 30kHz, 125kHz, 250kHz, 1MHz.</p>
<p><em>Clock polarity -</em> idle low, idle high.</p>
<p><em>Output clock edge -</em> idle to active, active to idle.</p>

<p><em>Input sample phase</em> - middle, end.</p>
<p><em>Output type -</em> open drain/open collector (high=Hi-Z, low=ground) , normal (high=3.3volts, low=ground). Use open drain/open collector output types with pull-up resistors for multi-voltage interfacing.</p>
<p><strong>SPI Bus sniffer</strong></p>
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