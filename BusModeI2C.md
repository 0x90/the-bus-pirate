<h1>Bus Pirate: I2C guide</h1>

<p><strong>Bus:</strong> <a href='http://en.wikipedia.org/wiki/I2c'>I2C</a> (eye-squared-see or eye-two-see)<br />

<strong>Connections: </strong>two pins (SDA/SCL) and ground<br />
<strong>Output types: </strong><a href='http://hackaday.com/2009/07/01/mixed-voltage-interfacing-with-the-bus-pirate/'>open drain/open collector</a><br />
<strong>Pull-up resistors:</strong> <a href='http://dangerousprototypes.com/2009/07/27/bus-pirate-practical-guide-to-pull-up-resistors/'>pull-ups</a> always required (2K-10K ohms)<br />
<strong>Maximum voltage: </strong>5.5volts (5volt safe)</p>

<p>I2C is a common 2-wire bus for low speed interfaces.</p>
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
<td>Issue I2C start condition.</td>
</tr>

<tr>
<td>] or }</td>
<td>Issue I2C stop condition.</td>
</tr>
<tr>
<td>R or r</td>
<td>Read one byte, send ACK. (r:1…255 for bulk reads)</td>
</tr>
<tr>
<td>0b</td>
<td>Write this binary value, check ACK. Format is 0b00000000 for a byte, but partial bytes are also fine: 0b1001.</td>

</tr>
<tr>
<td>0h/0x</td>
<td>Write this HEX value, check ACK. Format is 0h01 or 0×01. Partial bytes are fine: 0xA. A-F can be lower-case or capital letters.</td>
</tr>
<tr>
<td>0-255</td>
<td>Write this decimal value, check ACK. Any number not preceded by 0x, 0h, or 0b is interpreted as a decimal value.</td>
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
<td>7bit address search. Find all connected devices by brute force.</td>

</tr>
<tr>
<td>2</td>
<td>I2C snooper (alpha testing, unlisted) v2.1+</td>
</tr>
</tbody>
</table>
<p><strong>Configuration options</strong></p>
<p><em>Hardware or software I2C </em>- Choose software or hardware I2C modes. Hardware has higher speeds, but doesn't work perfectly with PIC chip revisions A3 and A4.</p>
<p><em>Speed </em>- Software mode has two speed options: high (~50kHz) and low (~5kHz). Hardware I2C has three speed options: 100kHz, 400kHz, and 1MHz.</p>

<p><strong>Software and Hardware I2C modes</strong></p>
<p>I2C has a software and hardware mode.<strong><br />
</strong></p>
<p>HiZ>m<strong><<<open the mode menu</strong><br />
1. HiZ<br />
…<br />
4. I2C<br />
…<br />

(1) >4<strong><<<choose I2C mode</strong><br />
MODE SET<br />
I2C mode:<br />
1. Software<br />
2. Hardware<br />
(1) >1<strong><<<select software  I2C</strong><br />
Set speed:<br />

1. Slow(~5KHz)<br />
2. Fast(~50KHz)<br />
(1) >1<strong><<<choose software I2C speed</strong><br />
I2C READY<br />
I2C></p>
<p>Software I2C mode uses a software <a href='http://en.wikipedia.org/wiki/Bit-banging'>bit-bang</a> library with two speed options (~5KHz and ~50KHz).</p>

<p>MODE SET<br />
I2C mode:<br />
1. Software<br />
2. Hardware<br />
(1) >2<strong><<<select hardware I2C</strong><br />
WARNING: Hardware I2C is broken on this PIC! (REV A3)<strong><<<warning</strong><br />
Set speed:<br />

1. 100KHz<br />
2. 400KHz<br />
3. 1MHz<br />
(1) >2<strong><<<choose hardware I2C speed</strong><br />
HARDWARE I2C READY<br />
I2C></p>
<p>Hardware I2C mode works best with PIC revision <a href='http://dangerousprototypes.com/2009/08/07/find-your-bus-pirates-pic-revision/'>B4 and later</a>. PICs prior to revision B4 have a flaky I2C module, a warning is displayed if you use the hardware option on a broken chip. <a href='http://whereisian.com/forum/index.php?topic=59.msg301#msg301'>Some have reported success</a> using the hardware I2C library on revision A3/4 hardware.</p>

<p><strong>ACK/NACK management</strong></p>
<p>These examples read and write from the RAM of a DS1307 RTC chip.</p>
<p>I2C> <a href='.md'>0xd1 rrrr</a><br />
I2C START CONDITION<br />
WRITE: 0xD1 GOT ACK: YES<strong><<<read address</strong><br />
READ: 0×07 ACK <strong><<<sent ACK</strong>[<br />

READ: 0x06 ACK<br />
READ: 0x05 ACK<br />
READ: 0x04 NACK <strong><<<last read before STOP,  sent NACK</strong><br />
I2C STOP CONDITION<br />
I2C></p>
<p>I2C read operations must be ACKed or NACKed by the host (the Bus Pirate). The Bus Pirate automates this, but you should know a few rules about how it works.</p>
<p>The I2C library doesn't ACK/NACK a read operation until the following command. If the next command is a STOP (or START) the Bus Pirate sends a NACK bit. On all other commands it sends an ACK bit. The terminal output displays the (N)ACK status.</p>
<p>I2C> <a href='0xd1.md'>r:5</a><br />

I2C START CONDITION<br />
WRITE: 0xD1 GOT ACK: YES<br />
BULK READ 0×05 BYTES:<br />
0×07 ACK 0×06 ACK 0×05 ACK 0×04 ACK 0×03 NACK<br />
I2C STOP CONDITION<br />
I2C></p>
<p>Nothing changes for write commands because the slave ACKs to the Bus Pirate during writes. Here’s an example using the bulk read command (r:5).</p>
<p>I2C>[0xd1 r <strong><<<setup and read one byte</strong><br />

I2C START CONDITION<br />
WRITE: 0xD1 GOT ACK: YES<br />
READ: 0x07 <b>(N)ACK PENDING</b><strong><<<no ACK sent yet</strong><br />
I2C>r<strong><<<read another byte</strong><br />
ACK <strong><<<ACK for previous byte</strong><br />
READ: 0x06 <b>(N)ACK PENDING</b><strong> <<<no ACK yet</strong><br />

I2C>] <strong><<<STOP command</strong><br />
NACK <strong><<<next command is STOP, so NACK<br />
</strong> I2C STOP CONDITION<br />
I2C></p>
<p>A consequence of the delayed ACK/NACK system is that partial transactions will leave read operations incomplete.</p>
<p>Here, we setup a read operation ([0xd1) and read a byte (r). Since the Bus Pirate has no way of knowing if the next operation will be another read (r) or a stop condition (]), it leaves the ninth bit hanging. The warning “**(N)ACK PENDING” alerts you to this state.</p>**<p>Our next command is another read (r), so the Bus Pirate ACKs the previous read and gets another byte. Again, it leaves the (N)ACK bit pending until the next command.</p>

<p>The final command is STOP (]). The Bus Pirate ends the read with a NACK and then sends the stop condition.</p>
<p><strong>I2C address search scanner macro<br />
</strong></p>
<p>I2C>(1)<strong><<<search for I2C addresses</strong><br />
Searching 7bit I2C address space.<br />
Found devices at:<br />
0xD0(0×68W) 0xD1(0×68R)<br />
I2C></p>

<p>The address scanner sends every possible I2C address and looks for ACKnowledgments. The scanner displays raw bus byte addresses (0xd0, 0xd1) and the 7bit I2C read (R) and write (W) addresses.</p>
<p><strong>I2C Bus Sniffer macro</strong></p>
<p>The I2C sniffer is implemented in software and <em><strong>seems to work up to 70kHz</strong></em>. It’s still very beta, improvements are probably possible.</p>
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