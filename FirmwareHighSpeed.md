<h1>Bus Pirate: High-speed firmware updates</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/07/speed-up.png?w=454&#038;h=270' alt='speed-up' height='270' width='454' title='speed-up' /></p>
<p>Quality control tests on <a href='http://www.buspirate.com'>the Bus Pirate</a> <a href='http://hackaday.com/2009/06/25/bus-pirate-preorders-open/'>preorder 1</a> flagged about  50 out of 400 units as defective. The terminal interface worked fine, but the bootloader wouldn't connect.</p>
<p>The solution was to decrease the speed of the quick programmer utility to the Microchip recommended default, 9600bps. Unfortunately, it takes nearly 3.5minutes to update the firmware at 9600bps.</p>
<p>Most PICs, perhaps all, will work at higher speeds. Right click on the quick programmer speed setting for an options menu. Try connecting at different speeds until you find the highest reliable speed that works with your chip.</p>

<p>Read on for a detailed post-game analysis of the error, where it came from, the issues we faced, and the solution we ultimately chose.</p>
<p><span></span></p>
<p>The Bus Pirate project used Microchip's PIC24F bootloader example. The default speed of the Windows programmer utility is 9600bps, it takes about 3.5 minutes to upload a new firmware. The bootloader firmware on the PIC uses auto-baud to determine the UART speed, the quick programmer  sends 0×55 and the PIC UART calculates the baud rate. We increased the quick programmer speed setting to 115200bps and the PIC bootloader detected the correct speed and worked fine.</p>
<p>In many PICs (all of ours and 350/400 of preorder 1) this worked fine, but some PIC crystals are worse and the UART is out of specification at 115200bps. The problem was only evident because so many were made at once, we only caught it because of <a href='http://www.seeedstudio.com/depot/'>Seeed Studio's</a> excellent quality control and testing. Thank you Seeed!</p>
<p>The technically 'correct' solution is to use the high-resolution baud rate generator in the PIC (BRGH=1), then all PICs will work at 115200bps.  We used this setting in the  code for the Bus Pirate terminal, that's why the terminal worked and  the bootloader didn't.</p>

<p>Unfortunately, PIC24FJ64GA002 REV #3003 (B3) has a problem with auto-baud when BRGH=1. There is a work-around in errata but it didn't work consistently  enough for production.</p>
<p>That left  two options:</p>
<p>1. Make a new bootloader firmware that ignores the auto-baud byte and works at a fixed 115200bps/BRGH=1.</p>
<p>2. Reduce the speed of the upgrade utility back to the Microchip default.</p>
<p>The best solution was #2.  It's risky to introduce a largely untested firmware in the middle of production. Making it worse, a recently upgraded PIC C compiler introduced even more certainty. Also, it saved Seeed the effort of re-programming and testing 50 Bus Pirates.</p>
<p>The consequence is that bootloading is much slower, however, it is a rare operation so most people won't be too inconvenienced. You can also test your PIC at higher speeds. I haven't yet received a test case for analysis, but I hope all PICs work to at least 57600bps.</p>
<p>Having two versions of the bootloader in the wild would have been a support nightmare, there would have been no way to tell the difference between bootloaders without an ICSP programmer. Think about all the router and game console hacks that have extensive instructions for determining if you have the 'right' version of the hardware. PCB markings, chip date codes, etc, and even that's no guarantee. Now we know exactly how manufacturers get into this situation.</p>