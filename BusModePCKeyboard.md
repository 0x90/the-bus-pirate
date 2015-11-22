<h1>Bus Pirate: keyboard guide</h1>

<p><strong>Bus:</strong> PC keyboard interface library.<br />
<strong>Connections: </strong>two pins (KBD/KBC) and ground.<br />

<strong>Output type: </strong><a href='http://en.wikipedia.org/wiki/High_impedence'>open drain/open collector</a>.<br />
<strong>Pull-up resistors: </strong><span><em>NONE</em></span>, keyboard has internal pull-ups.<br />
<strong>Maximum voltage: </strong>5volts.</p>
<p>This library interfaces PC keyboards. A PC keyboard operates at 5volts, and has it’s own internal pull-up resistors to 5volts. The keyboard issues a clock signal that drives all transactions, the library includes a time-out (v0h+) so the Bus Pirate won’t freeze if the keyboard doesn’t respond.</p>
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
<td>R or r</td>
<td>Read one byte with timeout. (r:1…255 for bulk reads)</td>
</tr>
<tr>
<td>0b</td>
<td>Write this binary value with timeout. Format is 0b00000000 for a byte, but partial bytes are also fine: 0b1001.</td>
</tr>
<tr>
<td>0h/0x</td>

<td>Write this HEX value with timeout. Format is 0h01 or 0×01. Partial bytes are fine: 0xA. A-F can be lower-case or capital letters.</td>
</tr>
<tr>
<td>0-255</td>
<td>Write this decimal value with timeout. Any number not preceded by 0x, 0h, or 0b is interpreted as a decimal value.</td>
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
<td>Live keyboard monitor (v0h+)</td>
</tr>
</tbody>
</table>