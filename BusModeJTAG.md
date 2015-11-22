<h1>Bus Pirate: JTAG guide</h1>

<p><strong>Bus:</strong> <a href='http://en.wikipedia.org/wiki/Joint_Test_Action_Group'>JTAG</a> (Joint Test Action Group).<br />

<strong>Connections: </strong> 4 connections (TDI, TCK, TDO, TMS) and ground.<br />
<strong>Output type:</strong> 3.3volt normal, or <a href='http://en.wikipedia.org/wiki/High_impedence'>open collector</a> (<a href='http://dangerousprototypes.com/2009/07/27/bus-pirate-practical-guide-to-pull-up-resistors/'>pull-up resistors</a> required).<br />
<strong>Pull-up resistors: </strong>required for open collector output mode (2K – 10K).<br />

<strong>Maximum voltage: </strong>5.5volts (5volt safe).</p>
<p>JTAG is actually a protocol over SPI. This library performs common JTAG functions and manages the JTAG state machine. <a href='http://hackaday.com/2008/12/01/bus-pirate-firmware-update-v0c-jtag-and-more/'>Read more about JTAG mode here</a>.</p>
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

<td>Move JTAG state machine (SM) to INSTRUCTION register. Last bit of byte writes is delayed until leaving the INSTRUCTION register.</td>
</tr>
<tr>
<td>{</td>
<td>Move JTAG SM to DATA register.</td>
</tr>
<tr>
<td>] or }</td>
<td>Move JTAG SM to IDLE register.</td>
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
<td>Send one clock tick. (^:1…255 for multiple clock ticks)</td>
</tr>
<tr>
<td>/ or \</td>

<td>Toggle clock level high (/) and low (\). Includes clock delay (100uS).</td>
</tr>
<tr>
<td>- or <i></td></i><td>Toggle data state high (-) and low (<i>). Includes data setup delay (20uS).</td>
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
<td>Reset chain</td>
</tr>
<tr>
<td>2</td>
<td>Probe chain</td>
</tr>
<tr>
<td>3</td>
<td><span>XSVF player. JTAG programmer.</span> (deprecated)</td>

</tr>
</tbody>
</table>
<p><strong>Configuration options:</strong></p>
<p><em> </em></p>
<p><em> </em></p>
<p><em>Output type -</em> open drain/open collector (high=Hi-Z, low=ground) , normal (high=3.3volts, low=ground). Use open drain/open collector output types with pull-up resistors for multi-voltage interfacing.</p>