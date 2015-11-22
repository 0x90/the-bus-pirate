<h1>Bus Pirate: raw 3-wire guide</h1>

<p><strong>Bus:</strong> general purpose 3-wire library with bitwise pin control.<br />
<strong>Connections: </strong>four pins (MOSI/MISO/CLOCK/CS) and ground.<br />

<strong>Output types:</strong> 3.3volt normal, or <a href='http://en.wikipedia.org/wiki/High_impedence'>open drain/open collector</a> (<a href='http://dangerousprototypes.com/2009/07/27/bus-pirate-practical-guide-to-pull-up-resistors/'>pull-up resistors</a> required).<br />
<strong>Pull-up resistors: </strong>required for open drain output mode (2K – 10K).<br />
<strong>Maximum voltage: </strong>5.5volts (5volt safe).</p>
<p>The raw 3 wire library is like SPI, but includes bitwise pin control.</p>

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
<tr>
<td><em>Bitwise</em></td>

<td></td>
</tr>
<tr>
<td>^</td>
<td>Send one clock tick. (^:1…255 for multiple clock ticks)</td>
</tr>
<tr>
<td>/ or \</td>
<td>Toggle clock level high (/) and low (\). Includes clock delay (100uS).</td>
</tr>
<tr>
<td>- or <i></td></i>

<td>Toggle data state high (-) and low (<i>). Includes data setup delay (20uS).</td>
</tr></i><tr>
<td>!</td>
<td>Read one bit with clock.</td>
</tr>
<tr>
<td>.</td>
<td>Read data pin state (no clock).</td>
</tr>
</tbody>
</table>

<p><strong>Configuration options:</strong></p>
<p><em> </em></p>
<p><em>Speed </em>- high (~50kHz) and low (~5kHz).</p>
<p><em>Output type -</em> open drain/open collector (high=Hi-Z, low=ground) , normal (high=3.3volts, low=ground). Use open drain/open collector output types with pull-up resistors for multi-voltage interfacing.</p>