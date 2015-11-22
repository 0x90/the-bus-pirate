<h1>Bus Pirate: Binary bitbang mode</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/10/rawspi.png?w=425&#038;h=260' alt='rawspi' height='260' width='425' title='rawspi' /></p>
<p>There's two new binary I/O libraries in the v2.3 Bus Pirate firmware. Raw bitbang mode provides direct control over the Bus Pirate pins and hardware using a simple single-byte protocol. We discussed the new <a href='http://dangerousprototypes.com/2009/10/08/bus-pirate-raw-spi-mode/'>raw SPI mode</a> yesterday.</p>
<p>Hopefully the raw access modes inspire some interesting new Bus Pirate tools using PC software. There's already <a href='http://dangerousprototypes.com/2009/10/08/avrdude-patch-program-avrs-with-the-bus-pirate/'>a patch for AVRDude</a> AVR programmer in the works.</p>

<p>Full documentation of the raw bitbang binary I/O mode after the break.</p>
<p><span></span></p>
<p><strong>Commands</strong></p>
<ul>
<li>00000000 - Reset, responds “BBIO1"</li>
<li>00000001  - Enter <a href='http://dangerousprototypes.com/2009/10/08/bus-pirate-raw-spi-mode/'>binary SPI mode</a>, responds “SPI1"</li>

<li>00000010 - Enter <a href='http://dangerousprototypes.com/2009/10/14/bus-pirate-binary-i2c-mode/'>binary I2C mode</a>, responds “I2C1"</li>
<li>00000011 - Enter <a href='http://dangerousprototypes.com/2009/10/19/bus-pirate-binary-uart-mode/'>binary UART mode</a>, responds “ART1"</li>
<li>00000100 - Enter <a href='http://dangerousprototypes.com/2009/10/20/bus-pirate-binary-1-wire-mode/'>binary 1-Wire mode</a>, responds “1W01"</li>

<li>00000101 - Enter <a href='http://dangerousprototypes.com/2009/10/27/binary-raw-wire-mode/'>binary raw-wire mode</a>, responds “RAW1"</li>
<li>0000xxxx - Reserved for future raw protocol modes</li>
<li>00001111 - Reset Bus Pirate (returns to user terminal)</li>
<li>00010000 - Short <a href='http://dangerousprototypes.com/2009/10/16/self-test-in-binary-mode/'>binary mode self-test</a></li>

<li>00010001 - Long test (requires jumpers between +5 and Vpu, +3.3 and ADC)</li>
<li>00010010 - Setup pulse-width modulation (requires 5 byte setup)</li>
<li>00010011 - Clear/disable PWM</li>
<li>00010100 - Take voltage probe measurement (returns 2 bytes)</li>
<li>010xxxxx  - Set pins as input(1) or output(0), responds with read</li>

<li>1xxxxxxx  - Set pins high (1) or low (0), responds with read</li>
</ul>
<p>The bitbang protocol uses a single byte for all commands. The default start-up state is pin input (HiZ).</p>
<p><em>00000000 - Reset, responds “BBIO1"</em></p>
<p>This command resets the Bus Pirate into raw bitbang mode from the user terminal. It also resets to raw bitbang mode from raw SPI mode, or any other protocol mode. This command always returns a five byte bitbang version string “BBIOx", where x is the current protocol version (currently 1).</p>
<p>Some terminals send a NULL character (0x00) on start-up, causing the Bus Pirate to enter binary mode when it wasn't wanted. To get around this, you must now enter 0x00 <strong>at least 20 times</strong> to enter raw bitbang mode.</p>

<p><em>Note:</em> The Bus Pirate user terminal could be stuck in a configuration menu when your program attempts to enter binary mode. One way to ensure that you're at the command line is to send <br>
<br>
<enter><br>
<br>
 at least 10 times, and then send '#' to reset. Next, send 0x00 to the command line 20+ times until you get the BBIOx version string.<br>
<br>
Unknown end tag for </p><br>
<br>
<br>
<p><em>00000001  - Enter binary SPI mode, responds “SPI1"</em></p>

<p>After entering bitbang mode, you can  enter other binary protocol modes. <a href='http://dangerousprototypes.com/2009/10/08/bus-pirate-raw-spi-mode/'>Binary SPI mode is documented here</a>.</p>
<p>00000010 - Enter binary I2C mode, responds “I2C1"</p>
<p><a href='http://dangerousprototypes.com/2009/10/14/bus-pirate-binary-i2c-mode/'>Binary I2C mode is documented here</a>.</p>
<p>00000011 - Enter binary UART mode, responds “ART1"</p>

<p><a href='http://dangerousprototypes.com/2009/10/19/bus-pirate-binary-uart-mode/'>Binary UART mode is documented here</a>.</p>
<p>00000100 - Enter binary 1-Wire mode, responds “1W01"</p>
<p><a href='http://dangerousprototypes.com/2009/10/20/bus-pirate-binary-1-wire-mode/'>Binary 1-Wire mode is documented here</a>.</p>
<p>00000101 - Enter binary raw-wire mode, responds “RAW1"</p>
<p><a href='http://dangerousprototypes.com/2009/10/27/binary-raw-wire-mode/'>Binary raw-wire mode is documented here</a>.</p>

<p>00001111 - Reset Bus Pirate</p>
<p>The Bus Pirate responds 0x01 and then performs a complete hardware reset. The hardware and firmware version is printed (same as the 'i' command in  the terminal), and the Bus Pirate returns to the user terminal interface. Send 0x00 20 times to enter binary mode again.</p>
<p>Note: there may be garbage data between the 0x01 reply and the version information as the PIC UART initializes.</p>
<p>0001000x - Bus Pirate self-tests</p>

<p><a href='http://dangerousprototypes.com/2009/10/16/self-test-in-binary-mode/'>Binary self tests are documented here</a>. Available only in v2go and v3 hardware.</p>
<p>00010010 - Setup pulse-width modulation (requires 5 byte setup)</p>
<p>Configure and enable pulse-width modulation output in the AUX pin. Requires a 5 byte configuration sequence. Responds 0x01 after a <em>complete sequence</em> is received. <span><em>The PWM remains active after leaving binary bitbang mode!</em></span></p>
<p>Equations to calculate the PWM frequency and period are in the <a href='http://ww1.microchip.com/downloads/en/DeviceDoc/39706a.pdf'>PIC24F output compare manual</a>. Bit 0 and 1 of the first configuration byte set the prescaler value. The Next two bytes set the duty cycle register, high 8bits first. The final two bytes set the period register, high 8bits first.</p>

<p>00010011 - Clear/disable PWM</p>
<p>Clears the PWM, disables PWM output. Responds 0x01.</p>
<p>00010100 - Take voltage probe measurement (returns 2 bytes)</p>
<p>Take a measurement from the Bus Pirate voltage probe. Returns a 2 byte ADC reading, high 8bits come first. To determine the actual voltage measurement: (ADC/1024)<b>3.3volts*2; or simply (ADC/1024)</b>6.6.</p>
<p>010xxxxx  - Configure  pins as input(1) or output(0): AUX|CS|MISO|CLK|MOSI</p>

<p>Configure pins as an input (1) or output(0). The pins are mapped to the lower five bits in this order:</p>
<p>AUX|CS|MISO|CLK|MOSI.</p>
<p>The Bus pirate responds to each direction update with a byte showing the current state of the pins, regardless of direction. This is useful for open collector I/O modes.</p>
<p>1xxxxxxx   - Set on (1) or off (0): POWER|PULLUP|AUX|CS|MISO|CLK|MOSI</p>
<p>The lower 7bits of the command byte control the Bus Pirate pins and peripherals. Bitbang works like a <a href='http://hackaday.com/2009/09/22/introduction-to-ftdi-bitbang-mode/'>player piano or bitmap</a>. The  Bus Pirate pins map to the bits in the command byte as follows:</p>
<p>1|POWER|PULLUP|AUX|CS|MISO|CLK|MOSI</p>
<p>The Bus pirate responds to each update with a byte in the same format that shows the current state of the pins.</p>

<p><strong>Key Points</strong></p>
<ul>
<li>Send 0x00 to the user terminal <strong>20 times</strong> to enter the raw binary bitbang mode.</li>
<li>Send 0x0F to exit raw bitbang mode and reset the Bus Pirate.</li>
<li>Other raw protocol modes are accessible from within bitbang mode, 0x00 always returns to raw bitbang mode and prints the version string.</li>
<li>There is a slight settling delay between pin updates, currently about 5us.</li>

</ul>
<p><strong>Updates</strong></p>
<ul>
<li><a href='http://dangerousprototypes.com/2009/10/12/bus-pirate-binmode-perl-test-script/'>Here's a test script in Perl</a>.</li>
</ul>