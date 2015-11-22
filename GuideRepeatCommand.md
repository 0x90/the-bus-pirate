<h1>Bus Pirate: Repeat command</h1>

<p>RAW3WIRE>r:5<span><strong><<<read 5 bytes (DEC)</strong></span><br />
READ 0×05 BYTES:<br />
0×00 0×00 0x00 0x00 0x00<br />

RAW3WIRE>r:0x05<span><strong><<<read 5 bytes (HEX)</strong></span><br />
READ 0x05 BYTES:<br />
0x00 0x00 0x00 0x00 0x00<br />
RAW3WIRE>r:0b101<span><strong><<<read 5 bytes (BIN)</strong></span><br />

READ 0x05 BYTES:<br />
0x00 0x00 0x00 0x00 0x00<br />
RAW3WIRE></p>
<p>Many Bus Pirate commands can be repeated by adding ‘: ‘ to a command, followed by the number of times to repeat the command. To read five byte, enter r:5, etc. The repeat values can be <a href='http://dangerousprototypes.com/2009/09/01/bus-pirate-number-formats/'>HEX/DEC/BIN</a>. In the example above we read five bytes each time using a different number format.</p>

<p>RAW3WIRE>0x40:5<span><strong><<<write 0x40, repeat 5 times</strong></span><br />
WRITE: 0x40 , 0x05 TIMES<br />
RAW3WIRE>^:5<span><strong><<<send 5 clock ticks</strong></span><br />
0x05 CLOCK TICKS<br />

RAW3WIRE>&amp;:5<span><strong><<<delay 1uS, repeat 5 times</strong></span><br />
DELAY 0x05uS<br />
RAW3WIRE></p>
<p>Depending on the bus mode, you can repeat reads, writes, macros, clock ticks, delays, and more. Refer to the <a href='http://dangerousprototypes.com/bus-pirate-manual/'>Bus Pirate manual</a> for detailed command tables for each mode.</p>