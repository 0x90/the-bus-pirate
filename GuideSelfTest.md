<h1>Bus Pirate: Self-test guide</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/07/bpv3v2go-pinout.png?w=430&#038;h=265' alt='BPv3v2go-pinout' height='265' width='430' title='BPv3v2go-pinout' /></p>

<p>In the past few days <a href='http://www.hackaday.com'>Hack a Day's</a> <a href='http://www.buspirate.com'>Bus Pirate</a> <a href='http://hackaday.com/2009/07/20/parts-unboxing-the-bus-pirate/'>preorders</a> have started to arrive all over the world. Broken units have been extremely rare, there's only been one <a href='http://whereisian.com/forum/index.php?topic=6.msg19#msg19'>manufacturing defect</a> and one <a href='http://whereisian.com/forum/index.php?topic=12.0'>broken FTDI chip</a> reported so far. <a href='http://www.seeedstudio.com/depot/'>Seeed Studio</a> tested the bootloader and terminal of each Bus Pirate, but problems can always occur in transit.</p>

<p><a href='http://dangerousprototypes.com/2009/07/26/bus-pirate-firmware-v2-0-released/'>Firmware v2.0</a> has a self-test routine that will help determine if your Bus Pirate v2go has a defect. <a href='http://dangerousprototypes.com/2009/07/24/bus-pirate-firmware-upgrades/'>Upgrade to the latest Bus Pirate firmware</a> before attempting the self-test. <a href='http://dangerousprototypes.com/2009/07/29/bus-pirate-v3-beating-the-shortage/'>Bus Pirate v3</a> will come with a power-on self-test mode.</p>
<p>Detailed self-test instructions and analysis follow the break.</p>

<p><strong>Performing the self-test</strong></p>
<p><strong><img src='http://wherelabs.files.wordpress.com/2009/07/bpv3v2go-pinout.png?w=430&#038;h=265' alt='BPv3v2go-pinout' height='265' width='430' title='BPv3v2go-pinout' /><br />
</strong></p>

<ol>
<li>Disconnect any devices from the Bus Pirate I/O header pins. An external device will interfere with the test, and could be damaged by the voltages used (+5volts) on some pins.</li>
<li>Make the self-test connections shown in the figure above. Connect the Vpullup (Vpu) pin to the +5V pin. Connect the ADC pin to the +3.3V pin.</li>
<li>To begin the self test, type ‘~' followed by <em>enter</em> in the terminal. Self-test is available in HiZ mode only.</li>
<li>You will be reminded to make the self-test connections and remove any external devices. Press any key to run the self-test.</li>
</ol>
<p>Here's the output from a self-test:</p>

<p>HiZ>~ <span><strong><<< self-test command</strong></span><br />
Disconnect any devices.<br />
Connect the Vpu pin to the +5V pin.<br />
Connect the ADC pin to the +3.3V pin.<br />
These results are experimental.<br />
Press any key to continue. <span><strong><<< follow the instructions to begin</strong></span><br />

Starting test.<br />
Control pin test…<br />
AUX PIN OK<br />
MODE LED PIN OK<br />
PULLUP PIN H OK<br />
PULLUP PIN L OK<br />
VREG PIN OK<br />
Analog pin and power supply test…<br />
5V(5.0) OK<br />

VPULLUP(5.0) OK<br />
3.3V(3.3) OK<br />
ADC(3.3) OK<br />
Bus pins, normal, high…<br />
MOSI PIN OK<br />
CLK PIN OK<br />
MISO PIN OK<br />
CS PIN OK<br />
Bus pins, open collector, low…<br />

MOSI PIN OK<br />
CLK PIN OK<br />
MISO PIN OK<br />
CS PIN OK<br />
Bus pins, open collector, high…<br />
MOSI PIN OK<br />
CLK PIN OK<br />
MISO PIN OK<br />
CS PIN OK<br />

HiZ></p>
<p>This Bus Pirate passed the self-test with no problems.</p>
<p><strong>What does it do?</strong></p>
<p>The self-test verifies that components connected to the PIC24FJ64GA002 respond as expected.</p>
<p>The self-test enables the auxiliary (AUX) pin, MODE LED, and voltage regulator control (VREG), and verifies that each pin went high. The CD4066 control pin (PULLUP) is held at 5volts with a pull-up resistor, so we test it high to see if the pull-up is working, and then low to see if the PIC pin is operating correctly.</p>
<ul>
<li>If pull-up high fails, check <a href='https://code.google.com/p/the-bus-pirate/source/detail?r=19'>R19</a>.</li>
<li>Other errors could be a soldering defect or broken microcontroller.</li>
</ul>
<p>The four analog voltage monitors and the two power supplies are tested. The 3.3volt and 5volt supplies are enabled and checked for  the correct  voltage. The ADC and Vpullup pin monitors are connected to the power supplies in order to test their function, as well as verify the results of the power supply monitors.</p>

<ul>
<li>If 5volt and Vpullup (or 3.3volts and ADC) both read 0volts, there could be a problem with the voltage regulator. Check VR3, VR4, C22, C24, <a href='https://code.google.com/p/the-bus-pirate/source/detail?r=18'>R18</a>.</li>
<li>If one shows a voltage, but the other doesn't, there could be a problem with the voltage monitor, the PIC microcontroller, or you forgot to connect the pins for self-test mode. Check <a href='https://code.google.com/p/the-bus-pirate/source/detail?r=10'>R10</a>-<a href='https://code.google.com/p/the-bus-pirate/source/detail?r=16'>R16</a>.</li>
</ul>
<p>The bus I/O pins and pull-up resistors are tested three ways. First, all bus pins are set high and verified without pull-up resistors. The pins then go low and the pull-up resistors are enabled to test open drain pin functionality. Finally, the pins are put in high-impedance mode to test the on-board pull-up resistors.</p>
<ul>
<li>Open collector high failures could indicate a problem with the on-board pull-up resistors, or you forgot to connect the 5volt and Vpullup pins. Check <a href='https://code.google.com/p/the-bus-pirate/source/detail?r=19'>R19</a>, <a href='https://code.google.com/p/the-bus-pirate/source/detail?r=20'>R20</a>-<a href='https://code.google.com/p/the-bus-pirate/source/detail?r=23'>R23</a>, IC3.</li>
<li>Other errors could be a soldering defect or broken microcontroller.</li>
</ul>
<p><strong>If your Bus Pirate fails the self-test…</strong></p>

<ul>
<li>Make sure that no device is connected to any of the pins</li>
<li>Ensure that the +5v pin is connected to the Vpullup pin</li>
<li>Check that the +3.3v pin is connected to ADC pin</li>
<li>Check for poor solder connections or solder bridges</li>
<li>Post the results of your test in our <a href='http://whereisian.com/forum/index.php?board=4.0'>unofficial Bus Pirate forum</a></li>
</ul>