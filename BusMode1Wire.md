<h1>Bus Pirate: 1-Wire </h1>

<p><strong>Bus:</strong> <a href='http://en.wikipedia.org/wiki/1-Wire'>1-Wire</a> (Dallas/Maxim 1-Wire protocol).<br />

<strong>Connections: </strong>one pin (OWD) and ground.<br />
<strong>Output types: </strong><a href='http://en.wikipedia.org/wiki/High_impedence'>open drain/open collector</a> (<a href='http://dangerousprototypes.com/2009/07/27/bus-pirate-practical-guide-to-pull-up-resistors/'>pull-up resistor</a> required).<br />
<strong>Pull-up resistors: </strong>always required (2K – 10K, 2K or less for parasitic power parts).<br />
<strong>Maximum voltage: </strong>5.5volts (5volt safe).</p>

<p>1-Wire uses a single data signal wire. Most devices also require a power and ground connection. Some parts draw power parasitically through the 1-Wire bus and don't require a separate power source.</p>
<table border='0'>
<tbody>
<tr>
<td width='46'><strong>Syntax</strong></td>
<td width='611'><strong>Description</strong></td>
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
<td>{ or [</td>
<td>1-Wire bus reset.</td>

</tr>
<tr>
<td>] or }</td>
<td>–</td>
</tr>
<tr>
<td>R or r</td>
<td>Read one byte. (r:1…255 for bulk reads)</td>
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
<tr>
<td><em>Bitwise</em></td>
<td></td>

</tr>
<tr>
<td>^</td>
<td>One clock tick, use data state from previous – or <i>operation. (^:1…255 for multiple clock ticks)</td>
</tr></i><tr>
<td>/ or \</td>
<td>–</td>
</tr>
<tr>
<td>- or <i></td></i><td>Send 1-Wire 1 (-) or 0 (<i>) bit.</td></i>

</tr>
<tr>
<td>!</td>
<td>Read one bit with clock.</td>
</tr>
<tr>
<td>.</td>
<td>–</td>
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
<td>1-50</td>
<td>Reserved for device address shortcuts.</td>

</tr>
<tr>
<td>51</td>
<td>READ ROM (0×33) <b>for single device bus</td>
</tr></b><tr>
<td>85</td>
<td>MATCH ROM (0×55) <b>followed by 64bit address</td>
</tr></b><tr>
<td>204</td>
<td>SKIP ROM (0xCC) <b>followed by command</td></b>

</tr>
<tr>
<td>236</td>
<td>ALARM SEARCH (0xEC)</td>
</tr>
<tr>
<td>240</td>
<td>SEARCH ROM (0xF0)</td>
</tr>
</tbody>
</table>
<p><strong>Notes:</strong></p>

<p>1-Wire specifies a 2K or smaller resistor when working with parasitically powered devices. The Bus Pirate on-board pull-up resistors are 10K, so use an external pull-up resistor when working with these devices. Parasitically powered parts may appear to work with resistors larger than 2K ohms, but will fail certain operations (like EEPROM writes).</p>