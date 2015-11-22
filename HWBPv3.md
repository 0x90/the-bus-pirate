<h1>Bus Pirate BPv3</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/09/sideiii-450.jpg?w=450&#038;h=245' alt='sideiii.450' height='245' width='450' title='sideiii.450' /></p>
<p>BPv3 is the latest hacking multi-tool from the <a href='http://code.google.com/p/the-bus-pirate/'>Bus Pirate project</a>. It connects to a USB port and interacts with electronics through a simple terminal interface.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/09/stack-example.jpg?w=204&#038;h=250' alt='stack-example' height='250' width='204' title='stack-example' />Use it to see how much of your private information <a href='http://dangerousprototypes.com/2009/08/31/bus-pirate-sle4442-smart-card-update/'>is stored on  smartcard SIM chips</a>. <a href='http://dangerousprototypes.com/2009/08/19/bus-pirate-wii-nunchuck-quick-guide/'>Explore the Wii Nunchuck over the I2C bus</a> like <a href='http://johnnylee.net/projects/wii/'>Johnny Lee</a>. <a href='http://dangerousprototypes.com/2009/07/30/prototype-bus-pirate-3eeprom-explorer-board/'>Read and write EEPROM chips</a> in consumer electronics at any voltage. Check out all the <a href='http://dangerousprototypes.com/bus-pirate-manual/#demos'>existing chip demonstrations</a>.</p>

<p>BPv3 has  features an intrepid hardware hacker might need to prototype their next great creation:</p>
<ul>
<li>Talk to 1-wire, I2C, UART (async serial), SPI, JTAG, MIDI, LCDs, PC keyboards, and a ton of generic serial devices from a terminal.</li>
<li><a href='http://dangerousprototypes.com/2009/10/09/bus-pirate-raw-bitbang-mode/'>Scriptable</a> from Python, <a href='http://dangerousprototypes.com/2009/10/12/bus-pirate-binmode-perl-test-script/'>Perl</a>, etc.</li>
<li>0-40MHz frequency counter, 0-4MHz pulse-width modulator.</li>
<li>0-6volt measurement probe.</li>
<li>3.3volt and 5volt power supplies with reset.</li>

<li><a href='http://dangerousprototypes.com/2009/07/27/bus-pirate-practical-guide-to-pull-up-resistors/'>On-board pull-up resistors</a> for multi-voltage interfacing.</li>
<li>Address scanners, chip dumpers, and <a href='http://dangerousprototypes.com/bus-pirate-manual/#syntax'>other helpful macros</a>.</li>
<li>USB interface, power. USB <a href='http://dangerousprototypes.com/2009/07/24/bus-pirate-firmware-upgrades/'>firmware updates</a>.</li>
<li>Translations (currently Spanish and Italian, <a href='http://whereisian.com/forum/index.php?topic=70.0'>add your own</a>).</li>
</ul>

<p><a href='http://www.seeedstudio.com/depot/preorder2-bus-pirate-v3-assembled-p-523.html'>Get an assembled <strong><span>red</span></strong> BPv3 for $30</a>, including worldwide shipping, thanks to Seeed Studio. You can also grab the plans from the <a href='http://code.google.com/p/the-bus-pirate/'>Bus Pirate project page</a> and build your own.</p>
<p>This article introduces BPv3, the latest hardware from the <a href='http://code.google.com/p/the-bus-pirate/'>Bus Pirate project</a>.  We'll look at the history of the design, share our experience organizing the production of <a href='http://hackaday.com/2009/06/25/how-to-the-bus-pirate-v2-with-usb/'>Bus Pirate v2go</a><a href='http://www.hackaday.com'></a>, and talk  about issues that influenced hardware version 3.</p>
<p><span></span></p>

<p><strong>History of the Bus Pirate universal serial interface</strong></p>
<p>We made the first Bus Pirate to deal with a particularly difficult chip that didn't behave as expected. We wanted to send SPI commands through a serial terminal so we could test the chip without compiling a firmware to implement each small change.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/09/v0-ii-450.jpg?w=450&#038;h=288' alt='v0.ii.450' height='288' width='450' title='v0.ii.450' /></p>
<p>Bus Pirate V0 was based on an USB-enabled <a href='http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en010280'>PIC 18F2550</a> microcontroller. It operated at 5volts only, and didn't have on-board power supplies. V0 was published on a personal blog under the GPL, sometime around 2004. Along with some very poor soldering,  you can see the first use of the Bus Pirate name etched into the copper.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/09/v0a-450.jpg?w=450&#038;h=304' alt='v0a.450' height='304' width='450' title='v0a.450' /></p>
<p><a href='http://hackaday.com/2008/11/19/how-to-the-bus-pirate-universal-serial-interface/'>Bus Pirate V0a</a> upgraded to a 16bit <a href='http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en026374'>PIC 24FJ64GA002</a>, but traded USB for a serial interface.  This version also added 3.3volt and 5volt power supplies, and two 3.3volt software-controlled <a href='http://en.wikipedia.org/wiki/Pull-up_resistor'>pull-up resistors</a>.</p>

<p>Microchip's new low-pincount PICs are perfect for the Bus Pirate because of a feature called peripheral pin select. Many microcontrollers have hard-wired  pin assignments, but PPS assigns some features to any pins we like. The PIC 24FJ is a better choice than the dsPIC33-series because the pins can source/sink more current (20mA vs 4mA).</p>
<p>We used a rare and expensive RS232 transceiver from our parts box in this design because it was intended for 'in house' use. We released this design into the public domain, and Hack a Day later published an article  about it as a stop-gap when other content wasn't  ready.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/09/v1-4501.jpg?w=450&#038;h=271' alt='v1.450' height='271' width='450' title='v1.450' /></p>
<p><a href='http://hackaday.com/2009/01/22/how-to-bus-pirate-v1-improved-universal-serial-interface'>Bus Pirate V1a</a> was another serial interface design, but this version used mostly  surface mount parts. We replaced the expensive RS232 transceiver with a cheap, common SMD version. The power supplies were upgraded to 800mA switchable regulators that can be reset from within the terminal. V1a ditched the software controlled pull-up resistors, and used jumpers to connect pull-ups to the four bus pins. This version added voltage monitoring probes using extra analog to digital converter pins on the PIC.</p>
<p>The v1a Bus Pirate was also released into the public domain, and we wrote an article about it that was published on Hack a Day. Fundamental logic revised the v1 design and released a through-hole serial port Bus Pirate kit (also public domain). You might still be able to <a href='http://store.fundamentallogic.com/ecom/index.php?main_page=product_info&amp;cPath=26&amp;products_id=474&amp;zenid=c06b8f01320c49219c3d0f8af70e4659'>buy the kit for $20</a>.</p>

<p><img src='http://wherelabs.files.wordpress.com/2009/09/v2-ssii-450.jpg?w=450&#038;h=242' alt='v2-ssii.450' height='242' width='450' title='v2-ssii.450' /></p>
<p><a href='http://hackaday.com/2009/06/25/how-to-the-bus-pirate-v2-with-usb/'>Bus Pirate V2</a> is the current king of the Bus Pirate designs, it's the first of the modern 16bit designs to have a USB interface (via an <a href='http://www.ftdichip.com/Products/FT232R.htm'>FTDI serial-&gt;USB chip</a>). V2a was an early revision (left), v2go was the final version of the V2 family (right). V2 swaps in smaller, cheaper, and awesomer power supplies (<a href='http://www.micrel.com/page.do?page=/product-info/products/mic5205.shtml'>MIC5205</a>) recommended by <a href='http://www.sparkfun.com/commerce/account.php?id=7185'>Nate</a> at SparkFun. We finally brought software switchable pull-up resistors to all four main bus pins via a <a href='http://docs.google.com/gview?a=v&amp;q=cache:69M9bxjzQ8UJ:www.fairchildsemi.com/ds/CD%252FCD4066BC.pdf+cd4066+fairchild&amp;hl=en&amp;sig=AFQjCNED6E-zJD_gBKYsFh1DiqauUP4krA'>CD4066</a> IC.</p>

<p>The Bus Pirate project was approached by a company that wanted to sell the v2 design, but complications and time constraints got in the way. Instead, we ran a <a href='http://hackaday.com/2009/06/25/bus-pirate-preorders-open/'>group preorder</a> as a fundraiser for Hack a Day, and got some experience with the manufacturing process.</p>
<p>Almost 1000 Bus Pirates <a href='http://hackaday.com/2009/07/16/bus-pirate-preorder-1-ships/'>sold in 10 days</a>, with all proceeds going to <a href='http://www.mahalo.com/'>Mahalo</a>, the company that operates Hack a Day. So many sold that we had supply problems,  Seeed Studio <a href='http://hackaday.com/2009/06/30/bus-pirate-preorder-update/'>couldn't find enough PIC 24FJ64GA002-SO</a> to fill the order.</p>
<p><strong><img src='http://wherelabs.files.wordpress.com/2009/09/sideiii-450.jpg?w=450&#038;h=245' alt='sideiii.450' height='245' width='450' title='sideiii.450' /></strong></p>
<p>BPv3 is designed to address supply and manufacturing problems encountered during the v2go preorder. v2go would have been the final Bus Pirate, but we learned so much during manufacturing that we wanted to apply it to  an updated design. For V3 we did  a full, scratch redesign of the PCB that went through two revisions.</p>

<p><em>If you've got a Bus Pirate v2go, don't  worry because it's functionally equivalent to v3. V2go and V3 will even bootload and run the same firmware.</em> In retrospect, v2go was a cute-but-poor version choice. Where do you go from there? v2go+1=? We chose V3.</p>
<p><strong>Updates to BPv3</strong></p>
<p><strong><img src='http://wherelabs.files.wordpress.com/2009/10/bpv3cct-450.png?w=450&#038;h=152' alt='bpv3cct.450' height='152' width='450' title='bpv3cct.450' /><br />
</strong></p>
<p><a href='http://wherelabs.files.wordpress.com/2009/10/bpv3cct.png'>Click here for a full size schematic image</a> <a href='PNG.md'>PNG</a>. The schematic and PCB were designed with the free version of <a href='http://www.cadsoft.de'>Cadsoft Eagle</a>, the latest design files are on the <a href='http://code.google.com/p/the-bus-pirate/'>project page</a> at Google Code.</p>

<p>The basic Bus Pirate design has been covered extensively at Hack a Day, we won't duplicate that here. Refer to these fantastic Bus Pirate articles: <a href='http://hackaday.com/2009/06/25/how-to-the-bus-pirate-v2-with-usb/'>v2</a>, <a href='http://hackaday.com/2009/01/22/how-to-bus-pirate-v1-improved-universal-serial-interface'>v1</a>, <a href='http://hackaday.com/2008/11/19/how-to-the-bus-pirate-universal-serial-interface/'>v0</a>.</p>
<p><em>Resolve manufacturing issues</em></p>
<p><em><img src='http://wherelabs.files.wordpress.com/2009/09/compare-450.jpg?w=450&#038;h=178' alt='compare.450' height='178' width='450' title='compare.450' /><br />
</em></p>
<p>Hack a Day's Bus Pirate preorder had to be split due to a shortage of SOIC-size PIC microcontrollers. BPv3 uses the smaller, more common SSOP-size (IC1). The smaller chip also allowed a reduction in  PCB size and a few other tweaks.</p>
<p>The programming pins on v2 were swapped from the normal PICkit2 order. Seeed had to use an adapter to program the v2go Bus Pirates, BPv3 has the correct pin order for easier manufacturing. Bootloaders for V2go and v3 are not interchangeable because of this modification.</p>

<p>Manufactured BPv3s will be programmed with the latest bootloader and firmware, which contains a <a href='http://dangerousprototypes.com/2009/07/28/bus-pirate-self-test-guide/'>self-test</a> for better quality control.</p>
<p><em>Circuit updates</em></p>
<p><img src='http://wherelabs.files.wordpress.com/2009/09/ftdi-450.jpg?w=450&#038;h=160' alt='FTDI.450' height='160' width='450' title='FTDI.450' /></p>
<p>The <a href='http://www.ftdichip.com/Products/FT232R.htm'>FTDI 232R USB-&gt;serial converter's</a> (IC2) IO pins are now driven by the main supply regulator, which is probably better than running it from the internal regulator as in v2go. The FTDI enable pin could be connected to the 3.3volt supply regulator (VR2) enable to make a fully USB sleep compliant device, but we didn't because the routing was too complicated.</p>
<p>We added a 0.1uF capacitor (C6) to decouple the VCCIO supply pin, the datasheet wasn't clear if this is required but it's probably best practice.</p>

<p>The header (ST) that taps the serial connection between the FTDI232R (IC2) and the PIC (IC1) was removed. A poll of developers found that none had ever used it, and the routing is cleaner  without it.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/09/solder-bridge-4501.jpg?w=450&#038;h=200' alt='solder-bridge.450' height='200' width='450' title='solder-bridge.450' /></p>
<p>The interior connection between two adjacent ground pins on IC3 was removed because so many people thought it was a solder bridge. (It's not.)</p>
<p><em>Tweaks</em></p>
<p><em><img src='http://wherelabs.files.wordpress.com/2009/09/bpv3-stripiii.jpg?w=450&#038;h=228' alt='bpv3-stripiii' height='228' width='450' title='bpv3-stripiii' /><br />
</em></p>
<p>We tweaked part placement during the PCB redesign. The USB jack (J1) is centered. The  CD4066 (IC3) is rotated  for better clearance around the IO header.</p>
<p>We moved the USB activity LED to the top of the PCB. LED labels are bolder, easier to read.</p>
<p>Traces that carry power are fatter, and have bigger  vias. We used wider 12mil trace/space wherever possible to improve PCB yield. The ground plane is reinforced with more and larger vias in important areas.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/09/io-450.jpg?w=450&#038;h=138' alt='io.450' height='138' width='450' title='io.450' /></p>

<p>The tighter placement required us to swap the 3.3volt and ADC pins on the I/O header. This is easier to route, and the ribbon cable pinout is more logical: ADC-5.0-3.3-GND.</p>
<p><strong>PCB</strong></p>
<p><strong><img src='http://wherelabs.files.wordpress.com/2009/09/buspirate-v3e-renderii-450.jpg?w=450&#038;h=243' alt='BusPirate-v3e-renderii.450' height='243' width='450' title='BusPirate-v3e-renderii.450' /><br />
</strong></p>
<p>We used  the freeware version of <a href='http://www.cadsoft.de/'>Cadsoft Eagle</a> to make the schematic and PCB. Download the latest designs and firmware from the <a href='http://code.google.com/p/the-bus-pirate/'>project  Google Code page</a>.</p>
<p>The PCB is small and tightly packed. It's a challenging board that takes us an hour to solder from memory. Seeed Studio sells the <a href='http://www.seeedstudio.com/depot/propaganda-service-propaganda-pcbs-c-64_33.html'>extra PCBs from our  order</a>.<strong><br />

</strong></p>
<p><em>Partslist</em></p>
<p><em><img src='http://wherelabs.files.wordpress.com/2009/09/brdii-450.png?w=457&#038;h=294' alt='brdii.450' height='294' width='457' title='brdii.450' /><br />
</em></p>
<p><a href='http://wherelabs.files.wordpress.com/2009/09/brdii.png'>Click for a full size placement image</a> <a href='PNG.md'>PNG</a>.</p>
<table border='0'>
<tbody>
<tr>
<td><strong>Name</strong></td>
<td><strong>Value (size)</strong></td>
<td><strong>Notes</strong></td>

</tr>
<tr>
<td>IC1</td>
<td><a href='http://www2.mouser.com/ProductDetail/Microchip-Technology/PIC24FJ64GA002-I-SS/?qs=sGAEpiMZZMvu0Nwh4cA1wYT5QXUmO9dmYmbTzatGY%2fI%3d'>PIC24J64GA002-SS</a> (SSOP)</td>
<td>Changed to SSOP</td>
</tr>
<tr>
<td>IC2</td>
<td><a href='http://www.sparkfun.com/commerce/product_info.php?products_id=650'>FT232RL</a> (SSOP)</td>

<td></td>
</tr>
<tr>
<td>IC3</td>
<td><a href='http://search.digikey.com/scripts/DkSearch/dksus.dll?Detail&amp;name=CD4066BCM-ND'>CD4066D</a> (SOIC-N)</td>
<td></td>
</tr>
<tr>
<td>C1-6</td>
<td><a href='https://www.mouser.com/Search/ProductDetail.aspx?R=C0805C104M5RACTUvirtualkey64600000virtualkey80-C0805C104M5R'>0.1uF capacitor</a> (0805)</td>

<td>Added C6</td>
</tr>
<tr>
<td>C20-24</td>
<td><a href='http://www.mouser.com/Search/ProductDetail.aspx?R=293D106X96R3A2TE3virtualkey61320000virtualkey74-293D106X96R3A2TE3'>10uF tantalum capacitor</a> (SMC-A)</td>
<td></td>
</tr>
<tr>
<td>ICSP, IO</td>
<td><a href='http://www.mouser.com/Search/ProductDetail.aspx?R=9-146278-0virtualkey57100000virtualkey571-9-146278-0'>0.1" pin header</a> (3×05)</td>

<td></td>
</tr>
<tr>
<td>J1</td>
<td><a href='http://www.sparkfun.com/commerce/product_info.php?products_id=587'>USB MINI-B</a> (SMD)</td>
<td>J2 renamed J1</td>
</tr>
<tr>
<td>L1</td>
<td><a href='http://www.mouser.com/Search/ProductDetail.aspx?R=BLM21PG331SN1Dvirtualkey64800000virtualkey81-BLM21P331SG'>1000ma+ ferrite bead</a> (0805)</td>

<td></td>
</tr>
<tr>
<td>LED1-4</td>
<td><a href='http://www2.mouser.com/ProductDetail/Dialight/598-8110-107F/?qs=sGAEpiMZZMuus4pmcqQnzm2UNk7a5HnUwLua0TbMZKg%3d'>LED</a> (0805)</td>
<td></td>
</tr>
<tr>
<td><a href='https://code.google.com/p/the-bus-pirate/source/detail?r=1'>R1</a></td>
<td><a href='http://www.mouser.com/Search/ProductDetail.aspx?qs=jBethxrBxZb5NLDetw123g=='>2000 ohm resistor</a> (0805)</td>

<td></td>
</tr>
<tr>
<td><a href='https://code.google.com/p/the-bus-pirate/source/detail?r=2'>R2</a>,3</td>
<td><a href='http://www.mouser.com/Search/ProductDetail.aspx?qs=DZvKvnD5UYWyFJjgnPvJ4g%3d%3d'>1100 ohm resistor</a> (0805)</td>
<td><a href='https://code.google.com/p/the-bus-pirate/source/detail?r=30'>R30</a> renamed <a href='https://code.google.com/p/the-bus-pirate/source/detail?r=2'>R2</a></td>
</tr>
<tr>
<td><a href='https://code.google.com/p/the-bus-pirate/source/detail?r=10'>R10</a>-17, 19-23</td>
<td><a href='http://www.mouser.com/Search/ProductDetail.aspx?qs=sGAEpiMZZMtlubZbdhIBIADEshVnklemK%252bhrLNEuMe8%3d'>10000 ohm resistor</a> (0805)</td>

<td>Removed <a href='https://code.google.com/p/the-bus-pirate/source/detail?r=18'>R18</a></td>
</tr>
<tr>
<td><a href='https://code.google.com/p/the-bus-pirate/source/detail?r=31'>R31</a>,32</td>
<td><a href='http://www.mouser.com/Search/ProductDetail.aspx?qs=2BMLUTrrT4P7Xm58YbKmPg=='>390 ohm resistor</a> (0805)</td>
<td></td>
</tr>
<tr>
<td>VR2,3</td>
<td><a href='http://search.digikey.com/scripts/DkSearch/dksus.dll?Detail&amp;name=576-1259-1-ND'>MIC5205 3.3volt regulator</a> (SOT23-5)</td>

<td></td>
</tr>
<tr>
<td>VR4</td>
<td><a href='http://search.digikey.com/scripts/DkSearch/dksus.dll?Detail&amp;name=576-1261-1-ND'>MIC5205 5volt regulator</a> (SOT23-5)</td>
<td></td>
</tr>
<tr>
<td></td>
<td></td>
<td></td>
</tr>
</tbody>

</table>
<p><strong>Taking it further</strong></p>
<p>Check the <a href='http://dangerousprototypes.com/bus-pirate-manual/'>Bus Pirate manual</a> for usage examples, pin diagrams, connection tables, syntax guides, and more.</p>
<p>We're happy with the current hardware features. Future updates will focus on improving the firmware, and adding features via the firmware and <a href='http://dangerousprototypes.com/category/bus-pirate-accessories/'>break-out boards</a>.</p>
<p>You can discuss the project in <a href='http://whereisian.com/forum/index.php?board=4.0'>the forum</a>, or join us on the <a href='http://code.google.com/p/the-bus-pirate/'>Google Code Bus Pirate project</a>.</p>

<p><strong>Get one!</strong></p>
<p><a href='http://www.seeedstudio.com/depot/preorder2-bus-pirate-v3-assembled-p-523.html'>Get an assembled <strong><span>red</span></strong> BPv3 for $30</a>, including worldwide shipping, thanks to Seeed Studio. You can also grab the plans from the <a href='http://code.google.com/p/the-bus-pirate/'>Bus Pirate project page</a> and build your own.</p>
<p><strong>Producing the Bus Pirate<br />
</strong></p>
<p><a href='http://www.seeedstudio.com/depot/'>Seeed Studio</a> made it really easy to sell a project without worrying about a website, billing, shipping, etc. We're working with them again on <a href='http://www.seeedstudio.com/depot/preorder-bus-pirate-v3-assembled-p-522.html'>BPv3</a> and the <a href='http://dangerousprototypes.com/2009/09/10/prototype-twitter-watcher-the-twatch/'>#twatch ethernet LCD backpack</a>.</p>

<p><img src='http://wherelabs.files.wordpress.com/2009/09/bpv3-take1-250.jpg?w=250&#038;h=111' alt='bpv3-take1.250' height='111' width='250' title='bpv3-take1.250' />To manufacture a project, you need to submit design files, a part list, and a firmware file.</p>
<p>We design circuit boards in <a href='http://www.cadsoft.de'>Cadsoft Eagle</a> and <a href='http://hackaday.com/2009/01/15/how-to-prepare-your-eagle-designs-for-manufacture/'>create gerber design files</a>, but many board houses now accept Eagle .brd files too. We send the gerbers to a board house and test the PCB. We order revisions and test again, if required.</p>
<p>Assembling a part list  can be fairly involved. At minimum, we specify part type, value, and size. Elaborate as much as possible on critical values or custom parts. For a 10uF capacitor, what type and how many volts max? If a 1% tolerance resistor is required, it needs to be specified.</p>
<p>Our best advise is to design with common parts. Check <a href='http://www.digikey.com/'>DigiKey</a> and <a href='http://www.mouser.com'>Mouser</a> (or better, <a href='http://octopart.com/'>Octopart</a>), be sure you can get a few hundred of your critical part from several suppliers. Check the supply of any specific microcontroller or IC that could hold up production.</p>

<p><img src='http://wherelabs.files.wordpress.com/2009/09/v2go-250.jpg?w=250&#038;h=203' alt='v2go-250' height='203' width='250' title='v2go-250' />Seeed was able to locate 300 PIC 24FJ64GA002-SO microcontrollers prior to the Hack a Day preorder. When orders took off, the initial 300 were gone within 48 hours. In the end, nearly 1000 Bus Pirates were sold. The extra 700 PICs took almost 2 months to source.</p>
<p>It's important to plan for production programming. The Bus Pirate uses a two part firmware, a bootloader and a main program. The normal programing method is to burn the bootloader and then upload a main program over USB. This is too slow for manufacturing, so we created a complete, bootloaded PIC firmware dump that combines both parts into a single image.</p>
<p>When manufacturing starts, be prepared for issues that hardly ever happen in a single chip, but occur quite frequently in 1000. Around 15% of v2gos failed initial quality control tests. They wouldn't connect to the bootloader at the default speed (115200bps). The bug turned out to be a baud rate setting that wasn't precise enough due to the inaccuracy of the internal crystal. The remaining boards worked after reducing the bootloader speed on the PC to 9600bps.</p>
<p>The members of the Bus Pirate project team learned a lot producing v2go with Seeed Studio. It wasn't without problems, but we used that experience to refine the hardware design. We hope this background  information helps you  produce your first widget, be sure to <a href='http://www.whereisian.com/'>let us know</a> when it debuts.</p>
<p><strong>Get one!</strong></p>

<p><a href='http://www.seeedstudio.com/depot/preorder2-bus-pirate-v3-assembled-p-523.html'>Get an assembled <strong><span>red</span></strong> BPv3 for $30</a>, including worldwide shipping, from Seeed Studio. You can also grab the plans from the <a href='http://code.google.com/p/the-bus-pirate/'>Bus Pirate project page</a> and build your own.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/09/sideiii-450.jpg?w=450&#038;h=245' alt='sideiii.450' height='245' width='450' title='sideiii.450' /></p>