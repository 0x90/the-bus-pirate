<h1>Bus Pirate: Firmware upgrades for Windwos</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/07/overview.png?w=424&#038;h=231' alt='overview' height='231' width='424' title='overview' /></p>
<p>The Bus Pirate has a <a href='http://en.wikipedia.org/wiki/Booting#Boot_loader'>bootloader</a> that accepts software updates over the USB connection and writes them to the memory of the PIC 24FJ64GA002 microcontroller. Without a bootloader, we’d have update the firmware through the ICSP header using  a ‘real’ programmer like an ICD2 or PICKIT2.</p>
<p>This guide explains how to update the Bus Pirate firmware  using the bootloader and the Windows quick programmer utility.</p>

<p><span></span><strong>Before you begin</strong></p>
<p>Grab the latest firmware archive from the project <a href='http://code.google.com/p/the-bus-pirate/downloads/list'>download page</a>, extract it to a folder. The firmware archive has the quick programmer utility (P24QP.exe) and .HEX firmware files for each Bus Pirate version.</p>
<p>If you get an error about a missing comdlg32.ocx when you run the quick programmer, install the sample code from <a href='http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&amp;nodeId=1824&amp;appnote=en533906'>Microchip application note AN1157</a>.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/07/jumper.jpg?w=450&#038;h=245' alt='jumper' height='245' width='450' title='jumper' /></p>
<p>Connect the PGD and PGC pins of the ICSP header to trigger the bootloader (A). A standard 0.1″ jumper works best, but any conductive material will work. The PIC flips the PGD pin high and low 20 times, if PGC matches PGD then the bootloader starts. If there’s no connection between PGC and PGD, then the normal Bus Pirate firmware starts.</p>
<p><em>If there’s no firmware on the PIC, the bootloader starts automatically. You don’t need a jumper between the PGC and PGD pins on a ‘fresh’ chip.</em> <em><strong>This also applies to <span>Hack a Day v2go preorder 2</span></strong><strong>, which shipped with bootloader only.<br />

</strong></em></p>
<p>Bootloader V2 uses the mode LED present on all Bus Pirate hardware to indicate that the bootloader is active and ready for firmware (B).</p>
<p>If the bootloader accidentally starts without a connection, place a jumper between GND and PGC. This will hold PGC low and ensure a mismatch.</p>
<p><strong>Upgrading the firmware via bootloader</strong></p>
<p><strong><img src='http://wherelabs.files.wordpress.com/2009/07/overview.png?w=424&#038;h=231' alt='overview' height='231' width='424' title='overview' /><br />
</strong></p>
<p>1. Change the quick programmer COM port to match your Bus Pirate.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/07/com-select.png?w=446&#038;h=212' alt='com-select' height='212' width='446' title='com-select' /></p>
<p><a href='http://dangerousprototypes.com/2009/07/23/bus-pirate-101/'>Find the COM port number assigned to your Bus Pirate</a>. Right-click the quick programmer COM number and set the correct port. You can also try to <a href='http://dangerousprototypes.com/2009/07/25/bus-pirate-high-speed-firmware-updates/'>increase the programming speed</a>.</p>

<p>Disconnect the Bus Pirate from the USB cable or power supply if you haven’t already. Put a jumper between the PGC and PGD pins of the Bus Pirate ICSP header. Connect the Bus Pirate to the USB port.</p>
<p>2. Press the <em>connect to device</em> button to open a connection to the bootloader.</p>
<p>3. Click the <em>open HEX file</em> button. Find the firmware for your Bus Pirate version and load it.</p>
<p>4. Click <em>erase device</em> to clear the old firmware. Don’t skip this step or the new firmware might not work correctly.</p>

<p>5. Click <em>write device</em> to send new firmware to the Bus Pirate. This process will take about 3.5 minutes at 9600bps. Ignore verify errors between 0×400 and 0×0bfe, that’s the bootloader location and it doesn’t get updated.</p>
<p>Most PICs will <a href='http://dangerousprototypes.com/2009/07/25/bus-pirate-high-speed-firmware-updates/'>bootload  at higher speeds</a>, experiment with the speed setting to see the maximum rate you can achieve. We normally bootload at 115200bps.</p>
<p>6. Click <em>normal execution mode</em> to complete the update. Click yes to the warning, we re-enter the bootloader using the jumper.</p>

<p>7. Disconnect the Bus Pirate from the PC, remove the jumper that connects PGC and PGD, and then re-attach the Bus Pirate. This complete hardware reset returns any resources used by the bootloader to their default state. The firmware update is complete.</p>
<p><strong>Notes</strong></p>
<p>The bootloading process isn’t particularly perilous. The bootloader protects itself from being over written. If bootloading is interrupted or there’s an error, you can usually just start the process over again. There is a brief instant after pressing the play button when a fatal error could occur, but it’s difficult to make it happen in practice.</p>
<p>If you’re starting with a new PIC microcontroller, you’ll need to program the bootloader firmware first through the ICSP header using a ‘real’ programmer like an ICD2 or PICKIT2.</p>