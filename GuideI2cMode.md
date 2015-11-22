<h1>Bus Pirate: I2C updates in firmware v2.1</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/08/v21-i2c.png?w=401&#038;h=235' alt='v21-i2c' height='235' width='401' title='v21-i2c' /></p>
<p>The <a href='http://en.wikipedia.org/wiki/I%C2%B2C'>I2C</a> mode in <a href='http://code.google.com/p/the-bus-pirate/'>Bus Pirate</a> firmware prior to v2.1 has a major deficiency, <strong>an <a href='http://dangerousprototypes.com/2009/08/21/bus-pirate-firmware-v2-1-rc2/'>upgrade to v2.1-RC2</a> or later is highly recommended</strong>.</p>

<p>The Bus Pirate I2C library underwent major changes between v2.0 and v2.1. We added a hardware I2C mode, and squashed a huge bug in the way the Bus Pirate reads from devices and scans for  addresses on the I2C bus. This guide details the updated I2C library.</p>
<p><span></span></p>
<p><strong>Software and Hardware I2C modes</strong></p>
<p>I2C has a new configuration option that selects between software or hardware I2C mode.<strong><br />
</strong></p>
<p>HiZ>m<span><strong><<<open the mode menu</strong></span><br />
1. HiZ<br />
…<br />
4. I2C<br />

…<br />
(1) >4<span><strong><<<choose I2C mode</strong></span><br />
MODE SET<br />
I2C mode:<br />
1. Software<br />
2. Hardware<br />
(1) >1<span><strong><<<select software  I2C</strong></span><br />

Set speed:<br />
1. Slow(~5KHz)<br />
2. Fast(~50KHz)<br />
(1) >1<span><strong><<<choose software I2C speed</strong></span><br />
I2C READY<br />
I2C></p>
<p>Software I2C mode uses a new public domain <a href='http://en.wikipedia.org/wiki/Bit-banging'>bit-bang</a> library. The centralized bit-bang functions provide all software libraries with a speed option (~5KHz and ~50KHz).</p>

<p>MODE SET<br />
I2C mode:<br />
1. Software<br />
2. Hardware<br />
(1) >2<span><strong><<<select hardware I2C</strong></span><br />
WARNING: Hardware I2C is broken on this PIC! (REV A3)<span><strong><<<warning</strong></span><br />
Set speed:<br />

1. 100KHz<br />
2. 400KHz<br />
3. 1MHz<br />
(1) >2<span><strong><<<choose hardware I2C speed</strong></span><br />
HARDWARE I2C READY<br />
I2C></p>
<p>We added a hardware I2C mode for <a href='http://dangerousprototypes.com/2009/08/07/find-your-bus-pirates-pic-revision/'>PICs that support it</a>.  PICs prior to revision B4 have a flaky I2C module, a warning is displayed if you use the hardware option on a broken chip. <a href='http://whereisian.com/forum/index.php?topic=59.msg301#msg301'>Some have reported success</a> using the hardware I2C library on <a href='https://code.google.com/p/the-bus-pirate/source/detail?r=3'>revision 3</a> hardware.</p>

<p><strong>I2C address search scanner update</strong></p>
<p>Some chips produced ghost addresses during a search. We updated the search routine to read a byte and send a NACK bit if the detected address is a read address. Searches now appear to be rock solid.</p>
<p>I2C>(1)<span><strong><<<search for I2C addresses</strong></span><br />
Searching 7bit I2C address space.<br />
Found devices at:<br />
0xD0(0x68W) 0xD1(0x68R)<br />
I2C></p>

<p>Here's the new address scanner layout. In addition to the raw bus byte addresses (0xd0, 0xd1), the scanner now displays the 7bit I2C (R) and write (W) addresses. It'll be easier to  line up the output with a datasheet or logic analyzer, without manually converting the addresses.</p>
<p><strong>ACK/NACK management, major bug fix</strong></p>
<p>These examples read and write from the RAM of a DS1307 RTC chip.</p>
<p>I2C> <a href='.md'>0xd1 rrrr</a><br />
I2C START CONDITION<br />
WRITE: 0xD1 GOT ACK: YES<span><strong><<<read address</strong></span><br />

READ: 0x07 ACK <span><strong><<<sent ACK</strong>[</span><br />
READ: 0x06 ACK<br />
READ: 0x05 ACK<br />
READ: 0x04 NACK <span><strong><<<last read before STOP,  sent NACK</strong></span><br />
I2C STOP CONDITION<br />
I2C></p>
<p>The new I2C library  doesn't  ACK/NACK a read operation until the next command.  If the next command is a STOP (or START) the Bus Pirate sends a NACK bit. On all other commands it sends an ACK bit. The terminal output displays the (N)ACK status.</p>

<p>Nothing changes for write commands because the slave ACKs to the Bus Pirate during writes.</p>
<p>I2C> <a href='0xd1.md'>r:5</a><br />
I2C START CONDITION<br />
WRITE: 0xD1 GOT ACK: YES<br />
BULK READ 0x05 BYTES:<br />
0x07 ACK 0x06 ACK 0x05 ACK 0x04 ACK 0x03 NACK<br />

I2C STOP CONDITION<br />
I2C></p>
<p>Here's an example using the bulk read command (r:5).</p>
<p>I2C>[0xd1 r <span><strong><<<setup and read one byte</strong></span><br />
I2C START CONDITION<br />
WRITE: 0xD1 GOT ACK: YES<br />
READ: 0x07 <b>(N)ACK PENDING</b><span><strong><<<no ACK sent yet</strong></span><br />

I2C>r<span><strong><<<read another byte</strong></span><br />
ACK <span><strong><<<ACK for previous byte</strong></span><br />
READ: 0x06 <b>(N)ACK PENDING</b><span><strong> <<<no ACK yet</strong></span><br />
I2C>] <span><strong><<<STOP command</strong></span><br />
NACK <strong><span><<<next command is STOP, so NACK<br />

</span></strong> I2C STOP CONDITION<br />
I2C></p>
<p>A consequence of the delayed ACK/NACK system is that partial transactions will leave read operations incomplete.</p>
<p>Here, we setup a read operation ([0xd1) and read a byte (r). Since the Bus Pirate has no way of knowing  if the next operation will be another read (r) or a stop condition (]), it leaves the ninth bit hanging. The warning “**(N)ACK PENDING” alerts you to this state.</p>**<p>Our next command is another read (r), so the Bus Pirate ACKs the previous read and gets another byte. Again, it leaves the (N)ACK bit pending until the next command.</p>
<p>The final command is STOP (]). The Bus Pirate ends the read with a NACK and then sends the stop condition.</p>
<p><strong>Incident analysis</strong></p>

<p>There were several large bugs in the Bus Pirate I2C library prior to version 2.1, so we thought a debriefing was in order.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/08/i2cbug-ii.png?w=470&#038;h=75' alt='i2cbug.ii' height='75' width='470' title='i2cbug.ii' /></p>
<p>Prior to firmware v2.1, the Bus Pirate used a GPL I2C library from outside the project. Our implementation of the library always acknowledged byte reads with a low bit called an ACK (top transaction). The I2C specification, however, requires that the final byte read should be ‘not acknowledged' with a high bit called a NACK (bottom transaction). When the slave sees the NACK bit it stops sending data.</p>
<p>All I2C slave chips are supposed to shut down when they see a STOP condition on the I2C pins. Even though the old firmware ACKed every byte, the STOP signal should shut down the chip anyway. However, if the slave is sending data during a read operation, and the first bit is 0, then it can't see the STOP signal because the bus is busy. This is called <a href='http://en.wikipedia.org/wiki/Bus_contention'>bus contention</a>.</p>
<p>There's several reasons we didn't catch this bug sooner. First, the method outlined above actually works for many chips because of chance bit-order or bus contention detection features. Second, our short demonstrations usually involved a single read operation at their conclusion, so we never saw the problems that were revealed with extended use.</p>

<p>The new delayed (N)ACK method should work fine for every chip we've tested or demoed in the past. It might have issues if there's protocols that switch reads and writes between START ([) and STOP (]) bits, but we're not aware of anything that does this.</p>
<p>The address scanner ghosting was related to the read NACK problem. When the address scanner sends a read address, some chips go immediately into read mode and create bus contention that prevents us from making the stop condition. That's why there's sometimes an extra address after the read address during an address search. When we send the read address, the chip clocks out 8bits before it gets a NACK on the final byte.</p>