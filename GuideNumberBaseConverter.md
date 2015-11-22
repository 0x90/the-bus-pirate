<h1>Bus Pirate HEX/DEC/BIN converter</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/08/logic.png?w=450&#038;h=69' alt='logic' height='69' width='450' title='logic' /></p>
<p>Converting between hexadecimal, decimal, and binary is a pretty constant activity when you work with a new microchip.</p>
<p>HiZ>=<span><strong><<<HEX/DEC/BIN converter command</strong></span><br />
CONVERT (1) >0b1010 <span><strong><<<convert this value</strong><br />
</span> 0x0A <span><strong><<<HEX equivalent</strong></span><br />

10<span><strong><<<DEC equivalent</strong></span><br />
0b00001010<span><strong><<<BIN equivalent</strong></span><br />
HiZ>=<span><strong><<<HEX/DEC/BIN converter command</strong></span><br />
CONVERT (1) >0xf<br />
0x0F<br />
15<br />

0b00001111<br />
HiZ></p>
<p>The latest Bus Pirate nightly firmware compile (v2.1-RC3+) adds a much-needed base conversion command, available in all modes. Press ‘=' and enter any byte value to see the HEX/DEC/BIN equivalent.</p>
<p><span></span></p>
<p>HiZ>=<br />
CONVERT (1) >0<br />
INVALID, TRY AGAIN></p>

<p>The prompt function sees 0 as an invalid option. Converting zero remains an exercise for the reader. You may also refer to the chart below:</p>
<table border='0'>
<tbody>
<tr>
<td><strong>HEX</strong></td>
<td><strong>DEC</strong></td>
<td><strong>BIN</strong></td>
</tr>
<tr>
<td>0x00</td>
<td>0</td>

<td>0b00000000</td>
</tr>
</tbody>
</table>
<p>Just a reminder: The Bus Pirate accepts HEX/DEC/BIN formatted input, and the output display can be toggled between these formats as well (o menu). See <a href='http://dangerousprototypes.com/bus-pirate-manual/'>the Bus Pirate manual</a> for more info.</p>
<p>Image:</p>
<div><a href='http://www.flickr.com/photos/julianbleecker/'><a href='http://www.flickr.com/photos/julianbleecker/'>http://www.flickr.com/photos/julianbleecker/</a></a> / <a href='http://creativecommons.org/licenses/by-nc-nd/2.0/'>CC BY-NC-ND 2.0</a></div>