<h1>Bus Pirate: UART guide</h1>

<p><strong>Bus:</strong> <a href='http://en.wikipedia.org/wiki/Serial_uart'>UART</a>, <a href='http://en.wikipedia.org/wiki/Musical_Instrument_Digital_Interface'>MIDI</a> (universal asynchronous receiver transmitter).<br />

<strong>Connections: </strong>two pins (RX/TX) and ground.<br />
<strong>Output types: </strong>3.3volt normal output, or<strong> </strong><a href='http://en.wikipedia.org/wiki/High_impedence'>open collector</a> (<a href='http://dangerousprototypes.com/2009/07/27/bus-pirate-practical-guide-to-pull-up-resistors/'>pull-up resistors</a> required).<br />
<strong>Pull-up resistors: </strong>required for open collector output mode (2K – 10K).<br />
<strong>Maximum Voltage: </strong>5.5volts (5volt safe).</p>

<p>UART is also known as the common PC serial port, though the PC serial port operates at full RS232 voltage levels (-13volts to +13volts).</p>
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
<td>Open UART, discard  received bytes.</td>
</tr>

<tr>
<td>{</td>
<td>Open UART, display data as it arrives asynchronously.</td>
</tr>
<tr>
<td>] or }</td>
<td>Close UART.</td>
</tr>
<tr>
<td>R or r</td>
<td>Check UART for byte, or fail if empty. Displays framing (-f) and parity (-p) errors, <a href='http://dangerousprototypes.com/2009/10/19/uart-mode-updates/'>more</a>. (r:1…255 for bulk reads)</td>

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
<td>Transparent UART bridge. Reset to exit.</td>
</tr>
<tr>
<td>2</td>
<td>Live raw UART monitor. Any key exits. <a href='http://http//dangerousprototypes.com/2009/10/19/uart-mode-updates/'>More</a></td>
</tr>
</tbody>
</table>
<p><strong>Configuration options</strong></p>

<p><em>Speed (bps) -</em> 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 31250 (v2.7+)<strong>.</strong></p>
<p><em>Data bits and parity -</em> 8/none, 8/even, 8/odd, 9/none.</p>
<p><em>Stop bits -</em> 1, 2.</p>
<p><em>Receive polarity -</em> idle 1, idle 0.</p>

<p><em>Output type -</em> open drain/open collector (high=Hi-Z, low=ground) , normal (high=3.3volts, low=ground). Use open drain/open collector output types with pull-up resistors for multi-voltage interfacing.</p>
<p><strong>Error display<br />
</strong></p>
<p>UART mode requires special handling compared to the other Bus Pirate modes because data can arrive at any time. UART mode displays framing and parity errors, and automatically clears buffer overruns.</p>
<p><em>Parity and framing errors</em></p>
<p>READ: -p -f 0×40 <strong><<<-p -f flag set<br />
</strong></p>
<p>The Bus Pirate reports framing errors (-f) and parity errors (-p) when reading a byte from the UART. It’s unlikely you’ll see these errors unless the UART speed is mismatched with the sender.</p>

<p><em>Buffer overrun errors</em></p>
<p>The Bus Pirate hardware has a four-byte UART buffer that holds data until you read it with an ‘r’ command, or until it can be printed to the terminal if live display is enabled with ‘['. After it fills, new data will be lost. This is called a buffer overrun.</p>
<p>READ: 0x40 <b>Bytes dropped</b><strong><<<bytes dropped error<br />
</strong></p>
<p>The Bus Pirate detects buffer errors, clears them, and alerts you of dropped bytes. The overrun bit is cleared any time you use the r, {, or <a href='.md'>commands. If you close the live UART display (</a>) and more than 5 bytes come in, the next read command (r) will clear the error and print the <b>bytes dropped</b> warning.</p>
<p>Prevent buffer problems by reducing the amount of data the Bus Pirate transfers over USB for each byte of UART data. Raw display mode reduces the four byte hex value 0×00 to a single raw byte value. A better way is to use macro (1) or (2) to view unformatted UART output, this is a 1:1 transfer of bytes that should work at the highest possible speeds.</p>
<p><strong>Transparent UART bridge</strong><em><br />
</em></p>
<p>UART>(1)<strong><<<macro 1, transparent UART bridge</strong><br />

UART bridge. Space continues, anything else exits.<br />
Reset to exit.</p>
<p>The transparent UART mode macro (1) creates a simple serial->USB bridge. The only way to exit this mode is to reset the Bus Pirate hardware.</p>
<p>Buffer overrun errors that occur during bridge mode are automatically cleared so that data continues as normal (firmware v3.0+). The MODE LED will turn off to alert you of the buffer overrun error.</p>
<p><strong>Live UART monitor</strong></p>
<p>UART>(2)<strong><<<macro 2, UART monitor</strong><br />
Raw UART input. Space to exit.<br />

UART></p>
<p>The UART monitor macro (2) shows a live display of UART input as raw byte values without any type of formatting. Press any key to exit the live monitor. This mode works best with a terminal that can display raw byte values in a variety of formats.</p>
<p>This macro is like the transparent UART macro (1) but without transmission abilities, and it can be exited with a key press. It’s useful for monitoring high-speed UART input that causes buffer overrun errors in other modes.</p>
<p><strong>MIDI</strong></p>
<p><a href='http://en.wikipedia.org/wiki/Musical_Instrument_Digital_Interface'>MIDI</a> is a command set used by electronic (music) instruments. It travels over a standard serial UART configured for 31250bps/8/n/1. Since firmware v2.7 MIDI is a speed option in the UART library.</p>
<p>MIDI is a ring network, each node has an input and output socket. Each node passes messages to the next in the ring. The input and outputs are opto-isolated. The signaling is at 5volts, 5ma (current-based signaling). An adapter is required: <a href='http://www.compuphase.com/electronics/midi_rs232.htm'>example 1</a>, <a href='http://www.midi.org/techspecs/electrispec.php'>example 2</a>.</p>