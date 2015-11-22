<h1>Bus Pirate: Practical guide to pull-up resistors</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/07/pullups-ii.png?w=450&#038;h=215' alt='pullups.ii' height='215' width='450' title='pullups.ii' /></p>
<p>There's often some confusion about how the <a href='http://www.buspirate.com'>Bus Pirate's</a> on-board <a href='http://en.wikipedia.org/wiki/Pull-up_resistor'>pull-up resistors</a> work. It doesn't help that the implementation changes drastically from one hardware revision to the next, a lot of the original device tutorials are difficult to follow if you have a Bus Pirate v2go.</p>

<p>The figure outlines the basic parts of the Bus Pirate v2go on-board pull-up resistors. A pull-up (or pull-down) voltage supplied through the Vpullup (Vpu) pin is fed into a  <a href='http://focus.ti.com/docs/prod/folders/print/cd4066b.html'>CD4066 analog switch</a> (IC3). The 4066 distributes the pull-up voltage to four 10K resistors (<a href='https://code.google.com/p/the-bus-pirate/source/detail?r=20'>R20</a>-23) that connect to the MOSI, CLOCK, MISO, and CS bus pins.</p>
<p>Continue reading our practical guide to the Bus Pirate v2go's pull-up resistors after the break.</p>
<p><span></span></p>
<p>I2C>v <span><strong><<< voltage monitor report</strong><br />
</span>VOLTAGE MONITOR: 5V: 5.0 | 3.3V: 3.3 | VPULLUP: 5.0 |<br />
I2C></p>

<p><strong><em>You must connect the Vpullup pin to a voltage.</em></strong> The pull-up resistors aren't hard-wired to a power supply, you can apply any voltage level that's needed (from ground to +5volts). Type ‘V' in the Bus Pirate terminal to see the current voltage on the Vpullup pin.</p>
<p>When the main microcontroller (IC1) holds the 4066 enable pin at 0volts the pull-up voltage is blocked and nothing goes through the resistors. When the enable pin is high, the pull-up voltage is allowed through the 4066 and the resistors  hold the bus pins at the level of the Vpullup pin.</p>
<p>I2C>p <span><strong><<< pull-up resistor menu</strong></span><br />
1. Pullup off<br />

2. Pullup on<br />
(1) >2 <span><strong><<< enable pull-up resistors</strong></span><br />
PULLUP RESISTORS ON<br />
I2C></p>
<p>Use the ‘p' menu in the Bus Pirate terminal to configure the pull-up resistors. Option 2 enables the 4066, and the voltage on the Vpullup pin is applied to the 10K pull-up resistors.</p>
<p>Read more about pull-up resistors and the Bus Pirate's open collector output mode (HiZ) at Hack a Day: <a href='http://hackaday.com/2009/07/01/mixed-voltage-interfacing-with-the-bus-pirate/'>Mixed voltage interfacing with the Bus Pirate</a>.</p>