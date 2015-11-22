<h1>Bus Pirate: Raw SPI mode</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/10/rawspi.png?w=425&#038;h=260' alt='rawspi' height='260' width='425' title='rawspi' /></p>
<p>Raw SPI is a new mode that provides high-speed access to the <a href='http://dangerousprototypes.com/bus-pirate-manual/'>Bus Pirate</a> SPI hardware. It was <a href='http://dangerousprototypes.com/2009/10/08/avrdude-patch-program-avrs-with-the-bus-pirate/'>developed in conjunction with Michal Ludvig</a>, so that <a href='http://www.nongnu.org/avrdude/'>AVRDude</a> can use the  Bus Pirate to program AVR microcontrollers and EEPROMs.</p>
<p><a href='http://dangerousprototypes.com/2009/10/07/bus-pirate-major-uart-fix/'>Firmware v2.3</a> includes two new raw I/O modes that give computer software and scripts direct access to  the Bus Pirate hardware. Hopefully this opens the door to a whole new class of Bus Pirate applications, like chip programmers. In this post we describe the raw SPI access mode. We'll describe the raw bigbang mode in a few days. The protocol is documented below the break.</p>

<p><span></span></p>
<p><strong>Raw SPI mode command table<br />
</strong></p>
<ul>
<li>00000000 - Enter raw bitbang mode, reset to raw bitbang mode</li>
<li> 00000001 – SPI mode/rawSPI version string (SPI1)</li>
<li>00000010 – CS low (0)</li>
<li>00000011 – CS high (1)</li>
<li>00001101 - Sniff all SPI traffic</li>

<li>00001110 - Sniff when CS low</li>
<li>00001111 - Sniff when CS high</li>
<li>0001xxxx – Bulk SPI transfer, send 1-16 bytes (0=1byte!)</li>
<li>0010xxxx – Low 4 bits of byte + single byte write/read</li>
<li>0011xxxx – High 4 bits of byte</li>
<li>0100wxyz – Configure peripherals, w=power, x=pullups, y=AUX, z=CS</li>
<li>01010000 – Read peripherals</li>

<li>01100xxx – Set SPI speed, 30, 125, 250khz; 1, 2, 2.6, 4, 8MHz</li>
<li>01110000 – Read SPI speed</li>
<li>1000wxyz – SPI config, w=output type, x=idle, y=clock edge, z=sample</li>
<li>10010000 – Read SPI config</li>
</ul>
<p>Commands are a single byte, except bulk SPI transfers. The Bus Pirate responds to SPI write commands with the data read from the SPI bus during the write. Most other commands return 0x01 for success, or 0x00 for failure/unknown command.</p>
<p><strong>Key points<br />
</strong></p>
<ul>

<li>Send the raw byte value 0x00 into the user command prompt <strong>20 times</strong> to enter bitbang mode.</li>
<li>Enter 0x01 in bitbang mode to enter raw SPI mode.</li>
<li>Return to raw bitbang mode from raw SPI mode by sending 0x00 <strong>one time</strong>.</li>
<li>Operations that write a byte to the SPI bus also return a byte read from the SPI bus.</li>
<li>Hex values shown here, like 0x00, represent actual byte values; not typed ASCII entered into a terminal.</li>

<li>Other values are shown as 8bit binary numbers. Here's a <a href='http://www.mathsisfun.com/binary-decimal-hexadecimal-converter.html'>binary->decimal->hex converter</a>.</li>
</ul>
<p><strong>Commands</strong></p>
<p><em>00000000 - Enter raw bitbang mode, reset to raw bitbang mode </em></p>
<p>This command has two purposes. First, send it to the command line interface 20 times to enter the raw bitbang binary mode. It's also used to exit the raw SPI mode and return to raw bitbang mode.</p>

<p>Send the value 0x00 to the Bus Pirate command line interface <strong>20 times</strong> to enter raw bitbang mode. The Bus Pirate replies 'BBIOx', where x is the raw bitbang version number (currently 1).</p>
<p>Once in raw SPI mode (see command 00000001), the 0x00 command returns to raw bitbang mode. Send 0x00 <strong>once</strong> to return to raw bitbang mode.</p>
<p><em>00000001 - Enter raw SPI mode, display version string</em></p>

<p>Once in raw bitbang mode, send 0x01 to enter raw SPI mode. The Bus Pirate responds 'SPIx', where x is the raw SPI protocol version (currently 1). Get the version string at any time by sending 0x01 again.</p>
<p><em>0000001x - CS high (1) or low (0) </em></p>
<p>Toggle the Bus Pirate chip select pin, follows HiZ configuration setting. CS high is pin output at  3.3volts, or HiZ. CS  low is pin output at  ground. Bus Pirate responds 0x01.</p>
<p><em>00001101 - Sniff all SPI traffic, 0000111x - Sniff when CS low(0)/high(1)</em></p>

<p>The SPI sniffer is implemented in hardware and should work up to 10MHz. It follows the configuration settings you entered for SPI mode. The sniffer can read all traffic, or filter by the state of the CS pin.</p>
<ul>
<li>[/]  - CS enable/disable</li>
<li>\ - escape character precedes a data byte value</li>
<li>(\x)  - MISO read</li>
</ul>
<p>Sniffed traffic is encoded according to the table above. The byte sniffed on the MISO pin is displayed inside (). Data bytes are escaped with the '\' character.</p>

<p>Send a single byte to exit, Bus Pirate responds 0x01 on exit.</p>
<p><em>0001xxxx - Bulk SPI transfer, send/read 1-16 bytes (0=1byte!)</em></p>
<p>Bulk SPI allows direct byte reads and writes. The Bus Pirate expects xxxx+1 data bytes. Up to 16 data bytes can be sent at once, each returns a byte read from the SPI bus during the write.</p>
<p>Note that 0000 indicates 1 byte because there's no reason to send 0. BP replies 0x01 to the bulk SPI command, and returns the value read from SPI after each data byte write.</p>
<p><em>0100wxyz - Configure peripherals w=power, x=pull-ups, y=AUX, z=CS</em></p>

<p>Enable (1) and disable (0) Bus Pirate peripherals and pins. Bit w enables the power supplies, bit x toggles the on-board pull-up resistors, y sets the state of the auxiliary pin, and z sets the chip select pin. Features not present in a specific hardware version are ignored. Bus Pirate responds 0x01 on success.</p>
<p>Note: CS pin always follows the current HiZ pin configuration. AUX is always a normal pin output (0=GND, 1=3.3volts).</p>
<p>Read the current settings by sending 01010000.</p>
<p><em>01100xxx -  SPI speed </em></p>
<p>000=30kHz, 001=125kHz, 010=250kHz, 011=1MHz, 100=2MHz, 101=2.6MHz, 110=4MHz, 111=8MHz</p>
<p>This command sets the SPI bus speed according to the values shown. Default startup speed is 000 (30kHz).</p>
<p>Read the current settings by sending 01110000.</p>
<p><em>1000wxyz - SPI config, w=HiZ/3.3v, x=CKP idle, y=CKE edge, z=SMP sample</em></p>

<p>This command configures the SPI settings. Options and start-up defaults are the same as the user terminal SPI mode. w= pin output HiZ(0)/3.3v(1), x=CKP clock idle phase (low=0), y=CKE clock edge (active to idle=1), z=SMP sample time (middle=0). The Bus Pirate responds 0x01 on success.</p>
<p>Default raw SPI startup condition is 0010. HiZ mode configuration applies to the SPI pins and the CS pin, but not the AUX pin. See the <a href='http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en026374'>PIC24FJ64GA002 datasheet</a> and the <a href='http://ww1.microchip.com/downloads/en/DeviceDoc/39699b.pdf'>SPI section</a><a href='PDF.md'>PDF</a> of the <a href='http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&amp;nodeId=2575'>PIC24 family manual</a> for more about the SPI configuration settings.</p>
<p>Read the current settings by sending 10010000.</p>
<p><em>0010xxxx, 0011yyyy - Enter SPI data byte in nibbles, read SPI byte</em></p>

<p>Data bytes can also be entered in two nibbles using this pair of commands. 0011yyyy loads the upper 4 bits of a data byte. 0010xxxx loads the  lower 4 bits of the data byte, and writes it to the SPI bus. The bus write returns a byte read.</p>
<p>A byte is transmitted over SPI each time the low bits are sent. Be sure to send the upper bits first, then send the lower bits to complete the data and transmit it. If the upper four bits are the same as the previous byte, then you can increase speed by  sending just the lower four bits.</p>
<p>Entering the upper 4 bits returns 1 for success, or 0 for failure. Entering the low bits returns a byte read from the SPI bus.</p>
<div>

<hr />

<p><strong>Possibly related posts: (automatically generated)</strong></p><ul><li><a href='http://ankiit.wordpress.com/2009/05/24/spi-serial-peripheral-interface/'>SPI : Serial Peripheral Interface</a></li><li><a href='http://thexmoschallenge.wordpress.com/2009/10/01/pcb-design-getting-there/'>PCB Design getting there</a></li></ul>