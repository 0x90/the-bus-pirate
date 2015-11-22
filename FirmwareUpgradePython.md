<h1>Bus Pirate:  Firmware upgrades on Linux, OSX</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/08/p24qp-tux-ii.jpg?w=450&#038;h=324' alt='p24qp-tux.ii' height='324' width='450' title='p24qp-tux.ii' /></p>
<p>Bus Pirate <a href='http://dangerousprototypes.com/2009/07/24/bus-pirate-firmware-upgrades/'>firmware updates</a> can  be done from Linux or OSX using the Python PIC24F programmer <a href='http://whereisian.com/forum/index.php?topic=10.0'>developed by <em>broeggle</em> and <em>JoseJX</em></a>. The programmer works on all operating systems that support <a href='http://www.python.org/download/releases/2.6.2/'>Python</a> and <a href='http://pyserial.sourceforge.net/'>pySerial</a>: Linux, OSX, and Windows, too. Thanks for a great script!</p>

<p>Our step-by-step guide to the Python PIC24F programmer continues after the break.</p>
<p><span></span></p>
<p>Here’s some key stuff to get:</p>
<ol>
<li> The programmer works with <a href='http://www.python.org/download/releases/2.6.2/'>Python 2.x</a>, not 3.x.</li>
<li> Get the <a href='http://sourceforge.net/projects/pyserial/files/'>pySerial module</a> to give Python serial port access.</li>

<li>Download the latest <a href='http://the-bus-pirate.googlecode.com/svn/trunk/firmware/v2-nightly/P24qp.py'>Python PIC24F programmer script</a>. Future firmware releases (&gt;2.0) will include the Python programmer script.</li>
<li><a href='http://code.google.com/p/the-bus-pirate/downloads/list'>Download the latest firmware</a>. Copy the P24qp.ini configuration file and firmware .HEX to the same directory as the programmer script.</li>
<li>Get a 0.1″ jumper to place between the PGC and PGD pins, as described in the <a href='http://dangerousprototypes.com/2009/07/24/bus-pirate-firmware-upgrades/'>Windows quick programmer tutorial</a>.</li>
</ol>
<p>Install Python 2.x and the pySerial module. Download the firmware and programmer, move the required files into a convenient directory.</p>

<p><img src='http://wherelabs.files.wordpress.com/2009/07/jumper.jpg?w=450&#038;h=245' alt='jumper' height='245' width='450' title='jumper' /></p>
<p>Disconnect the Bus Pirate from the USB cable (and power supply if applicable). <strong>Place a jumper between the PGC and PGD pins (A)</strong>, as described in the <a href='http://dangerousprototypes.com/2009/07/24/bus-pirate-firmware-upgrades/'>Windows quick programmer tutorial</a>. Plug the Bus Pirate back in.</p>
<p>C:\&gt;cd python26</p>
<p>C:\Python26&gt;python P24qp.py<br />
Bus Pirate Programmer v1.0</p>
<p>P24qp &lt;command&gt;<br />

-a –auto=FILE          – Erase, Program and Quit the Bootloader<br />
-c –config=FILE        – P24qp compatible configuration file<br />
(Default: ./P24qp.ini)<br />
-e –erase              – Erase the flash programming<br />

-f –finalize   – Finalize the programming and go to user mode<br />
-i –info               – Information about the bootloader<br />
-q –quiet              – Quiet messages about writing progress<br />
-r –read=FILE          – Read programming from flash<br />

-s –serial=DEVICE      – Override serial device path<br />
-t –reset              – Reset the bootloader<br />
-v                      – Enable verification of write commands<br />
-w –write=FILE – Write programming file to flash</p>

<p>C:\Python26&gt;</p>
<p>Run the programmer from the command prompt for a short description of the flags and options.</p>
<p>JoseJX <a href='http://whereisian.com/forum/index.php?topic=10.msg117#msg117'>recommends</a> auto mode with verify, using the command:</p>
<p>P24qp.py -a &lt;hexfile&gt; -s &lt;serial port&gt; -v</p>

<p>Substitute &lt;hexfile&gt; with the name of the firmware .HEX file, something like v25-Firmware-v2.hex for the Bus Pirate v2go. Replace &lt;serial port&gt; with the device name you system assigned to the Bus Pirate’s FTDI USB-&gt;serial converter chip.</p>
<ul>
<li>Linux: /dev/ttyUSBx (/dev/ttyUSB0) or /dev/ttySx (/dev/ttyS1)</li>
<li>OSX(?): /dev/cu.KeySerialx (/dev/cu.KeySerial1)</li>
<li>Windows: COMx (COM3)</li>

</ul>
<p>The serial port name can be tricky, hopefully these examples help. Replace ‘x’ with the number for your system. <a href='http://whereisian.com/forum/index.php?topic=10.msg120#msg120'>Look in the system dmesg</a> to find the Bus Pirate on Linux, or in the control panel on Windows.</p>
<p>C:\Python26&gt;python P24qp.py -a v25-Firmware-v2.hex -s COM5 -v<br />
Using Serial Port COM5 @ 115200<br />
Reading 4 bytes from address 0x00FF0000<br />

Found PIC24FJ64GA002<br />
Erase Flash:<br />
Erasing 43 pages, starting at 0x00000000<br />
Erase complete<br />
Writing 256 bytes to address 0x00000000<br />
Reading 256 bytes from address 0x00000000<br />
Verification failed at 0x00000000: 0 != 4<br />

Verification failed at 0x00000001: 4 != 12<br />
Writing 256 bytes to address 0x00000080<br />
Reading 256 bytes from address 0x00000080<br />
Writing 256 bytes to address 0x00000100<br />
…<span><strong>&lt;&lt;&lt; This continues for awhile</strong></span><br />
Reading 256 bytes from address 0x0000AA80<br />

Writing 256 bytes to address 0x0000AB00<br />
Reading 256 bytes from address 0x0000AB00<br />
Writing 256 bytes to address 0x0000AB80<br />
Reading 256 bytes from address 0x0000AB80<br />
Verified Okay.<br />
Verification complete, switching to user mode</p>
<p>C:\Python26&gt;</p>

<p>Ignore any verify errors at the beginning (0x0, 0x1) and between 0x400 and 0xbff, these are bootloader protected locations. A really nice thing about the Python programmer is that it knows to ignore errors in the protected bootloader section.</p>
<p>[<a href='http://commons.wikimedia.org/wiki/File:Tux.png'>Tux image</a>]</p>