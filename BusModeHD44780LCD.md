<h1>Bus Pirate:HD44780 LCD library</h1>

<p><strong>Bus:</strong> <a href='http://ouwehand.net/%7Epeter/lcd/lcd.shtml'>HD44780 LCD</a> test library.<br />

<strong>Connections: </strong>two pins (SDA/SCL) and ground.<br />
<strong>Output type: </strong><a href='http://en.wikipedia.org/wiki/High_impedence'>open drain/open collector</a> (<a href='http://dangerousprototypes.com/2009/07/27/bus-pirate-practical-guide-to-pull-up-resistors/'>pull-up resistors</a> required).<br />
<strong>Pull-up resistors: </strong>always required (2K – 10K).<br />
<strong>Maximum voltage: </strong>5.5volts (5volt safe).<strong></strong><br />

<strong>Adapter:</strong> <a href='http://hackaday.com/2008/12/27/parts-8bit-io-expander-pcf8574/'>PCF8574</a> I2C expander IC, (see our <a href='http://dangerousprototypes.com/2009/08/13/bus-pirate-hd44780-character-lcd-adapter/'>adapter board</a>).</p>
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
<td>{ or [</td>
<td>RS low. Next read/write is a COMMAND.</td>
</tr>
<tr>
<td>] or }</td>
<td>RS high. Next read/write is TEXT/DATA.</td>
</tr>
<tr>
<td>R or r</td>
<td>Read one byte (r:1…255 for bulk reads).</td>

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
<td>LCD reset.</td>
</tr>
<tr>
<td>2</td>
<td>Init LCD.</td>
</tr>
<tr>
<td>3</td>
<td>Clear LCD.</td>

</tr>
<tr>
<td>4</td>
<td>Cursor position ex:(4:0).</td>
</tr>
<tr>
<td>5</td>
<td>Write test text. (deprecated)</td>
</tr>
<tr>
<td>6</td>
<td>Write :number test numbers ex:(6:80).</td>

</tr>
<tr>
<td>7</td>
<td>Write :number test characters ex:(7:80).</td>
</tr>
<tr>
<td>8</td>
<td>Insert text at cursor.</td>
</tr>
</tbody>
</table>