<h1>UART mode updates</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/10/uart-sl.png?w=450&#038;h=139' alt='uart-sl' height='139' width='450' title='uart-sl' /></p>
<p>UART mode requires special handling compared to the other Bus Pirate modes because data can arrive at any time. Displaying data as it arrives is a unique challenge because it has to be converted to ASCII and sent to the user terminal. Each incoming byte takes about 10 bytes to display on the PC.</p>
<p>The UART library has been largely neglected since early releases. This post outlines changes in the v2.7 release that  solve a number of issues that were plaguing the UART library, including <a href='http://dangerousprototypes.com/2009/10/07/bus-pirate-major-uart-fix/'>speed setting problems</a> and <a href='http://whereisian.com/forum/index.php?topic=102.msg654#msg654'>buffer errors</a>.</p>
<p><span></span><em>Parity and framing errors</em></p>

<p>READ: -p -f 0x40 <span><strong><<<-p -f flag set<br />
</strong></span></p>
<p>The Bus Pirate now reports framing errors (-f) and parity errors (-p) when reading a byte from the UART. It's unlikely you'll see these errors unless the UART speed is mismatched with the sender.</p>
<p><em>Buffer overrun errors</em></p>
<p>The Bus Pirate hardware has a four-byte UART buffer that holds data until you read it with an ‘r' command, or until it can be printed to the terminal if live display is enabled with ‘['. After it fills, new data will be lost. This is called a buffer overrun.</p>

<p>READ: 0x40 <b>Bytes dropped</b><span><strong><<<bytes dropped error<br />
</strong></span></p>
<p>The Bus Pirate now detects buffer errors, clears them, and alerts you of dropped bytes. The overrun bit is cleared any time you use the r, {, or <a href='.md'>commands. If you close the live UART display (</a>) and more than 5 bytes come in,  the next read command (r) will clear the error and print the <b>bytes dropped</b> warning.</p>
<p>Prevent buffer problems by reducing the amount of data the Bus Pirate transfers over USB for each byte of UART data. Raw display mode reduces the four byte hex value 0×00 to a single raw byte value. A better way is to use macro (1) or (2) to view unformatted UART output, this is a 1:1 transfer of bytes that should work at the highest possible speeds.</p>
<p><em>Macro additions, changes</em></p>
<p>UART>(1)<span><strong><<<macro 1, transparent UART bridge</strong></span><br />
UART bridge. Space continues, anything else exits.<br />

Reset to exit.</p>
<p>The transparent UART mode macro (1) clears any buffer errors before starting. This should eliminate garbage data  problems.</p>
<p>Buffer errors that occur during bridge mode are <em>NOT</em> cleared. A stream of the same byte will alert you to a buffer problem. A future update will probably clear the error but dim the MODE LED to alert you of the error.</p>
<p>UART>(2)<span><strong><<<macro 2, UART monitor</strong></span><br />
Raw UART input. Space to exit.<br />
UART></p>

<p>The new UART monitor macro (2) shows a live display of UART input as raw byte values without any type of formatting. Press any key to exit the live monitor. This mode works best with a terminal that can display raw byte values in a variety of formats.</p>
<p>This macro is like the transparent UART macro (1) but without transmission abilities, and it can be exited with a key press. It's useful for  monitoring high-speed UART input that causes buffer overrun errors in other modes.</p>