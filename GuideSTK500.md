<h1>Bus Pirate: STK500v2 AVR programmer firmware</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/11/mplab-avrstudio.jpg?w=450&#038;h=303' alt='' height='303' width='450' title='MPLAB-avrstudio' /></p>
<p><a href='http://code.google.com/p/the-bus-pirate/downloads/detail?name=AVR-STK500-v2-clone-v0a.zip'>Here's an alternate firmware</a> for the <a href='http://dangerousprototypes.com/bus-pirate-manual/'>Bus Pirate</a> that clones an <a href='http://en.wikipedia.org/wiki/Atmel_AVR#STK500_Starter_Kit'>STK500</a> programmer for AVR microcontrollers. We ported the GPL'd source from Guido Socher's <a href='http://www.tuxgraphics.org/electronics/200510/article05101.shtml'>AvrUSB500</a> ATMEGA8-based programmer to the PIC.</p>

<p>The firmware should work with any applications that support the STK500 v2 protocol. We used it to program the <a href='http://dangerousprototypes.com/2009/11/16/prototype-christmas-card-ornament/'>Hackable Christmas card's</a> ATtiny13A from the latest version of <a href='http://www.atmel.com/dyn/Products/tools_card.asp?tool_id=2725'>AVR Studio</a>. You could also use it for things like programming the bootloader into an Arduino.</p>
<p>You can buy the <a href='http://www.seeedstudio.com/depot/preorderled-christmas-card-ornament-kit-p-573.html'>Hackable Christmas card</a> ($12 kit, <a href='http://www.seeedstudio.com/depot/preoerderled-christmas-card-ornament-assembled-p-574.html'>$15 assembled</a>) and <a href='http://www.seeedstudio.com/depot/preorder2-bus-pirate-v3-assembled-p-523.html'>the Bus Pirate v3</a> ($30, assembled with shipping) at Seeed Studio.</p>

<p>More about using the programmer, and it's limitations, after the break.</p>
<p><span></span><strong>Firmware swap</strong></p>
<p>The STK500 firmware (vx-STK500-vx.hex) is a replacement for the normal Bus Pirate firmware. Bootload it to the Bus Pirate using your <a href='http://dangerousprototypes.com/bus-pirate-manual/'>normal upgrade procedure</a>. You can change back to the regular Bus Pirate firmware at any time.</p>
<p><strong>Connection table</strong></p>
<table border='0'>
<tbody>
<tr>
<td><strong>Bus Pirate</strong></td>
<td><strong>AVR ISP</strong></td>

</tr>
<tr>
<td>MOSI</td>
<td>MOSI</td>
</tr>
<tr>
<td>CLK</td>
<td>SCK</td>
</tr>
<tr>
<td>MISO</td>
<td>MISO</td>

</tr>
<tr>
<td>CS</td>
<td>/RESET</td>
</tr>
<tr>
<td>Ground</td>
<td>Ground</td>
</tr>
<tr>
<td>3.3v/5v</td>
<td>Vcc (optional)</td>

</tr>
<tr>
<td></td>
<td></td>
</tr>
</tbody>
</table>
<p><strong>Notes</strong></p>
<p>The v0a release has a few limitations:</p>
<ol>
<li>Power supplies are always on. Use them if you like, or not.</li>
<li>Pin output is currently fixed at 3.3volts. The Bus Pirate pins are 5volt tolerant, but we haven't tested it with a target running at 5volts - it may or may not work, but it shouldn't damage the Bus Pirate.</li>

<li>Extremely slow programming modes may not work, the lowest programming speed is 30KHz (the fastest is 1MHz).</li>
<li>It's unlikely that STK500 compatibility will be integrated into the main Bus Pirate firmware. It would be tough to get all the different modes to play well together. For now we'll release it as a separate firmware.</li>
<li>Tested on v3 hardware, others untested.</li>
<li><span><em>V2go and v3 hardware use the same firmware.</em></span></li>
</ol>
<p>The image at the top shows MPLAB running the PIC microcontroller in debug while AVR Studio connects to it in in the background. You can also see a live display of serial communication on Portmon in the middle.</p>