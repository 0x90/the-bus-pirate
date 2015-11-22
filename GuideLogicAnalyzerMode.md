<h1>Bus Pirate: logic analyzer mode</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/10/sump-dataii.png?w=450&#038;h=225' alt='sump-dataii' height='225' width='450' title='sump-dataii' /></p>
<p><em>This is an updated guide to the Bus Pirate logic analyzer mode, it expands on the initial documentation posted earlier.</em></p>
<p>Bus Pirate firmware v3.0 introduced a logic analyzer mode that works with the <a href='http://www.sump.org/projects/analyzer/client/'>SUMP open source logic analyzer client</a>. The logic analyzer can record 4096 samples at up to 1MHz, each channel has a selectable sample trigger.</p>
<p><em><strong><b>BIG WARNING</b></strong></em> The Bus Pirate will never be a substitute for a 'proper' logic analyzer, the hardware isn't designed for it. The Bus Pirate can't store a lot of samples, it can't feed live samples very fast, and speeds are in the kHz range, not MHz.</p>

<p>Despite the limitations of the Bus Pirate hardware, the logic analyzer worked well enough to examine decoded IR remote signals. It's also well suited to debug environments where you can control the bus speed (and the Bus Pirate may already be connected for other reasons). It should also be able to look at most I2C traffic (400kHz clock).</p>
<p>Documentation below. There’s still time to get a Bus Pirate v3, <a href='http://www.seeedstudio.com/depot/preorder2-bus-pirate-v3-assembled-p-523.html'>$30 including worldwide shipping</a>.</p>
<p><span></span><strong> </strong></p>
<p><strong>Logic analyzer specs</strong></p>
<ul>
<li>4096 samples (4K)</li>
<li>10Hz to ~1MHz low-speed sample rate</li>
<li>Selectable sampling trigger on each pin</li>

<li><a href='http://www.sump.org/projects/analyzer/client/'>SUMP</a> compatible</li>
</ul>
<p>The five major IO pins are included in analyzer output:</p>
<ul>
<li>chan0 - CS</li>
<li>chan1 - MISO</li>
<li>chan2 - CLK</li>

<li>chan3 - MOSI</li>
<li>chan4 - AUX</li>
</ul>
<p>SUMP follows a <a href='http://www.sump.org/projects/analyzer/protocol/'>simple protocol</a>. We've only implemented the minimum command set: reset, run, ID, speed (divider), samples, and trigger. Other commands are received, but the contents are ignored. Trigger direction, pre-sampling, and other advanced features could be handled with an update.</p>
<p><strong>What you'll need</strong></p>

<ul>
<li><a href='http://www.sump.org/projects/analyzer/client/'>SUMP</a> open source logic analyzer client</li>
<li>Bus Pirate firmware v3.0 or later</li>
</ul>
<p>Update to the latest <a href='http://code.google.com/p/the-bus-pirate/'>Bus Pirate firmware</a> using your normal <a href='http://dangerousprototypes.com/2009/07/24/bus-pirate-firmware-upgrades/'>Windows</a> or <a href='http://dangerousprototypes.com/2009/08/06/bus-pirate-firmware-upgrades-on-linux-osx/'>Python</a> (MAC <a href='http://dangerousprototypes.com/2009/10/24/bus-pirate-firmware-updates-on-osx/'>OSX</a>/Linux) update method.</p>

<p>Install <a href='http://www.java.com/en/'>Java</a>, the <a href='http://www.rxtx.org/'>rxtx serial port library</a>, and the <a href='http://www.sump.org/projects/analyzer/client/'>SUMP client</a>.  Jack Gassett at the <a href='http://www.gadgetfactory.net/gf/'>Gadget Factory</a> has a <a href='http://www.gadgetfactory.net/gf/project/lax/frs/?action=FrsReleaseBrowse&amp;frs_package_id=1'>version compiled from the latest source code</a>. He also has a <a href='http://www.gadgetfactory.net/gf/project/lax/frs/?action=FrsReleaseBrowse&amp;frs_package_id=1'>Windows compile of SUMP</a> for his <a href='http://www.gadgetfactory.net/gf/project/butterfly_main/'>ButterFly Platform</a> that doesn't require you to install Java. SUMP has a <a href='http://sourceforge.net/projects/jlac/'>SourceForge page</a>, but it's not very active.</p>

<p><strong>Using the logic analyzer</strong></p>
<p>The Bus Pirate understands the SUMP initialization commands, no special configuration is required to put the Bus Pirate into logic analyzer mode. It will also return to user terminal mode automatically.</p>
<p><img src='http://wherelabs.files.wordpress.com/2009/11/sump-config.png?w=450&#038;h=281' alt='SUMP-config' height='281' width='450' title='SUMP-config' /></p>
<p>Open SUMP. Press the rocket button. Configure SUMP as shown here.</p>
<ol>
<li>Change the serial port to match the normal Bus Pirate serial port on your system.</li>
<li>Uncheck channel groups 2, 3, and 4.</li>
<li>We can capture a maximum of 4K samples (actually 4096), but the Bus Pirate will send fewer depending on the <em>recording size</em> setting.</li>

<li>Speed settings 10Hz to 1MHz are valid. Higher speeds default to about 1MHz.</li>
<li>Click capture to start. The MODE LED lights to indicate that the analyzer is active.</li>
</ol>
<p><img src='http://wherelabs.files.wordpress.com/2009/11/sumptrigger.png?w=500&#038;h=134' alt='SUMPtrigger' height='134' width='500' title='SUMPtrigger' /></p>
<p>Sampling can also be triggered by a change on one or more pins.</p>
<ol>
<li>Enable the trigger by checking the enable box.</li>
<li>Check the mask bits (bits4-0) to set a trigger on one or more pins.</li>
<li>Click capture. The MODE LED lights to indicate that the analyzer is active. A change on any of the selected pins triggers sampling.</li>
</ol>
<p>Note that sampling is triggered by a change on any of the selected pins. There's currently no direction configuration. Channel triggers are set with mask bits 4-0, ordered according to the channel table.</p>

<p><img src='http://wherelabs.files.wordpress.com/2009/10/rc5toggle-bitii.png?w=450&#038;h=84' alt='RC5toggle-bitii' height='84' width='450' title='RC5toggle-bitii' /></p>
<p>Samples are sent to SUMP and displayed.</p>
<p><strong>Improving the logic analyzer</strong></p>
<p>The logic analyzer could be upgraded with a rolling sample buffer that can show activity prior to the trigger.</p>