<h1>Bus Pirate: Number formats</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/09/hexdecbin.png?w=322&#038;h=220' alt='hexdecbin' height='220' width='322' title='hexdecbin' /></p>
<p>The Bus Pirate terminal interface accepts numbers in three formats: <a href='http://en.wikipedia.org/wiki/Hexadecimal'>hexadecimal</a>, <a href='http://en.wikipedia.org/wiki/Decimal'>decimal</a>, and <a href='http://en.wikipedia.org/wiki/Binary_numeral_system'>binary</a>. It also displays values in HEX/DEC/BIN and a raw byte format. This short guide explains how to enter number values into the Bus Pirate, and how to adjust the Bus Pirate number display format.</p>
<p><span></span></p>
<p>The maximum value you can enter in any format is currently 255 (8bits/1byte).</p>

<p>0x0, 0x18, 0x4A, 0xFF</p>
<p><a href='http://en.wikipedia.org/wiki/Hexadecimal'>Hexadecimal</a> values are base 16 numbers that use a-f for the numbers 10-15, this format is very common in computers and electronics. Enter HEX values as shown above, precede the value with 0x or 0h. Single digit numbers don't need 0 padding, 0x01 and 0x1 are interpreted the same.</p>
<p>0, 24, 74, 255</p>
<p><a href='http://en.wikipedia.org/wiki/Decimal'>Decimal</a> values are common base 10 numbers. Just enter the value, no special designator is required.</p>

<p>0b0, 0b11000, 0b1001010, 0b11111111</p>
<p><a href='http://en.wikipedia.org/wiki/Binary_numeral_system'>Binary</a> values are commonly used in electronics because the 1's and 0's correspond to register 'switches' that control various aspects of a device. Enter a binary number as 0b and then the bits. Padding 0's are not required, 0b00000001=0b1.</p>
<p>HiZ>=<br />
CONVERT (1) >0x45<br />

0x45<br />
69<br />
0b01000101<br />
HiZ></p>
<p><a href='http://dangerousprototypes.com/2009/08/27/bus-pirate-hexdecbin-converter/'>The = command</a> (firmware v2.1+) converts between number formats.</p>
<p>HiZ>o<br />
1. HEX<br />

2. DEC<br />
3. BIN<br />
4. RAW<br />
(1) >1<br />
Display format set<br />
HiZ></p>
<p>The Bus Pirate terminal will display values  in BIN/HEX/DEC. Change the setting in the data display format menu (o). The default display format is HEX.</p>
<p>The RAW display mode sends values to the terminal as raw byte values without any text conversion. This is useful for bus sniffers and other high-speed functions where converting raw bytes to text takes too much time. Adjust the display format in your serial terminal to see the raw values as HEX/DEC/BIN.</p>