<h1>Bus Pirate: Fast upgrades on slow chips</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/07/speed-up.png?w=454&#038;h=270' alt='speed-up' height='270' width='454' title='speed-up' /></p>
<p>The individual PIC chip we used on the Bus Pirate v3 is among those <a href='http://dangerousprototypes.com/2009/07/25/bus-pirate-high-speed-firmware-updates/'>that won't bootload at 115200bps</a>. Our <a href='http://dangerousprototypes.com/2009/07/24/bus-pirate-firmware-upgrades/'>upgrade recommendation</a> until now has been to bootload firmware at 9600bps, or faster if your PIC will allow.</p>
<p>After working with one of these 'slow' chips, we've found two methods to connect to the bootloader at full speed:</p>

<ol>
<li>Connect to the Bus Pirate with the quick programmer utility at   9600bps, then disconnect. Adjust the speed to 115200bps and connect again. This time the slow PIC should respond fine at 115200bps.</li>
<li>We've also had success connecting to a slow PIC at 115200bps if we put the bootloader jumper between the PGC and PGD pins while it's running, and then reset the Bus Pirate from within the terminal with the reset command (#). Disconnect your terminal program and connect with the quick programmer utility at 115200bps. Running correctly at 115200bps before talking to the bootloader seems to nudge slower PICs into the correct timing.</li>
</ol>
<p>Good luck. If you have a 'slow' PIC, please let us know if this helped you upgrade at higher speeds.</p>

