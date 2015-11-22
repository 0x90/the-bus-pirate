<h1>Bus Pirate: 2K pull-up resistor mod</h1>


<a href='http://www.youtube.com/watch?feature=player_embedded&v=A4I9bhVSn2g' target='_blank'><img src='http://img.youtube.com/vi/A4I9bhVSn2g/0.jpg' width='425' height=344 /></a>

<p>The <a href='http://code.google.com/p/the-bus-pirate/'>Bus Pirate</a> v2go shipped with 10K ohm <a href='http://en.wikipedia.org/wiki/Pull-up_resistor'>pull-up resistors</a> (<a href='https://code.google.com/p/the-bus-pirate/source/detail?r=20'>R20</a>-23). We modded our Bus Pirate with a 2K pull-up resistor so we don't need an external resistor to work with 1-Wire devices. Pull-up resistors larger than 2.2K ohms don't provide enough current for parasitically powered 1-Wire parts. Since we only need the bigger resistor for the 1-Wire protocol, we only replaced the pull-up resistor on the MOSI pin (<a href='https://code.google.com/p/the-bus-pirate/source/detail?r=23'>R23</a>).</p>

<p>Read more about our mod after the break.</p>
<p><span></span></p>
<p>10K is a weak pull-up resistor, but it's worked for everything except parasitic 1-Wire devices that draw power from the pull-up resistor. The <a href='http://dangerousprototypes.com/2009/07/30/prototype-bus-pirate-3eeprom-explorer-board/'>3EEPROM explorer board demo</a> uses an external 1.8K ohm pull-up resistor to get around this limitation.</p>
<p>A CD4066 switch enables and disables the Bus Pirate's on-board pull-up resistors. We checked the <a href='http://sigma.octopart.com/39000/datasheet/Texas-Instruments-CD4066BE.pdf'>CD4066 datasheet</a> <a href='PDF.md'>PDF</a> to see now much current it can handle. It should be able to pass up to 10ma on any one pin.</p>
<p>We then used an <a href='http://www.ohmslawcalculator.com/ohms_law_calculator.php'>online Ohm's Law calculator</a> to find the amount of current that would go through the resistors if they were shorted directly to ground. We calculated currents for  the  maximum possible pull-up resistor voltage (5volts).</p>

<p>The existing 10K resistors pass a maximum of 0.5mA at 5volts, a 2K resistor allows 2.5mA through. Since we're only changing the MOSI pull-up resistor, 4mA  total draw should be well within the current handling abilities of the CD4066.</p>
<p>Finally, we used a soldering iron to heat both sides of <a href='https://code.google.com/p/the-bus-pirate/source/detail?r=23'>R23</a> until we could lift it from the PCB with tweezers. We replaced it with a <a href='http://www.mouser.com/Search/ProductDetail.aspx?qs=jBethxrBxZb5NLDetw123g=='>2K ohm 0805-sized resistor</a>. The left-over solder from the previous resistor was enough to hold the new resistor, we didn't need extra.</p>
<p>Please ignore our clumsy soldering in the video, it was hard to work around the tripod and camera. The noise is the fume extractor.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/09/2kmosi-450.jpg?w=450&#038;h=262' alt='2KMOSI.450' height='262' width='450' title='2KMOSI.450' /></p>
<p>This image shows the mod to <a href='https://code.google.com/p/the-bus-pirate/source/detail?r=23'>R23</a> (2001), and the three original 10K pull-up resistors (103).</p>
<p>Should the Bus Pirate v3 ship with a 2K ohm resistor on the MOSI pin for out-of-the-box compatibility with 1-wire devices?</p>