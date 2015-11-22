<h1>Bus Pirate: Compile the firmware</h1>


<p><img src='http://wherelabs.files.wordpress.com/2009/09/mplab.png?w=450&#038;h=333' alt='mplab' height='333' width='450' title='mplab' /></p>
<p>You don't need a Microchip programmer to develop firmware for the <a href='http://code.google.com/p/the-bus-pirate/'>Bus Pirate</a>. You can use Microchip's free development tools and upload code through the USB bootloader.  It's a mini PIC 24F development board!</p>
<p>First, download and install Microchip's <a href='http://en.wikipedia.org/wiki/Integrated_development_environment'>IDE</a> called <a href='http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&amp;nodeId=1406&amp;dDocName=en019469&amp;part=SW007002'>MPLAB</a>, and the free demonstration <a href='http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&amp;nodeId=1406&amp;dDocName=en535364'>C30 compiler</a>. Next, download a Bus Pirate <a href='http://code.google.com/p/the-bus-pirate/downloads/list'>source code archive</a>, or get the latest <a href='http://code.google.com/p/the-bus-pirate/source/checkout'>development version</a> from <a href='http://en.wikipedia.org/wiki/Subversion_%28software%29'>SVN</a> with a program like <a href='http://tortoisesvn.net/'>TortoiseSVN</a>.</p>

<p>Open the Bus Pirate project in MPLAB.</p>
<p>Uncomment the correct Bus Pirate hardware version and language in base.h. Compile the project. You may need to modify the compiler location when prompted, but MPLAB is getting better about making these changes automatically.</p>
<p>The compiled firmware must be exported in order to work with the bootloader. In MPLAB, go to <em>File->Export...</em> Make sure that the <em>Program Memory</em> and <em>Configuration Bits</em> boxes are checked. Make sure INHX32 (Intel 32bit HEX) is selected on the <em>File Format</em> tab. Click OK to export the firmware.</p>

<p>Bootload the firmware following <a href='http://dangerousprototypes.com/2009/07/24/bus-pirate-firmware-upgrades/'>your normal upgrade process</a> (<a href='http://dangerousprototypes.com/2009/08/06/bus-pirate-firmware-upgrades-on-linux-osx/'>Linux, OSX</a>).</p>
<p>After the break, learn how to use TortoiseSVN to check out the Bus Pirate source on Windows.</p>
<p><span></span>If you have Tortoise SVN on Windows:</p>
<ol>
<li><em>R</em><em>ight click->SVN checkout</em> on your desktop or Windows file explorer.</li>

<li>Enter the SVN address (<a href='http://the-bus-pirate.googlecode.com/svn'>http://the-bus-pirate.googlecode.com/svn</a>) and a directory to use. Choose anonymous check out.</li>
<li>If you have commit permissions (you've been added as a developer on the Bus Pirate project), then use the secure SVN address (<a href='https://the-bus-pirate.googlecode.com/svn'>https://the-bus-pirate.googlecode.com/svn</a>). Give Tortoise your email address  when prompted, <span><em><strong>your Google SVN password is different than your account password</strong></em></span> – <a href='http://code.google.com/hosting/settings'>get your Google SVN password here</a>.</li>
<li>TortoiseSVN will download the source.</li>
<li>The developers work in the TRUNK folder. If you're contributing to the project, make your  changes, then right click on the modified file and choose SVN commit. If you added new files, first use SVN add, then use SVN commit.</li>