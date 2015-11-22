<h1>Bus Pirate: Self-test in binary mode</h1>

<p><img src='http://wherelabs.files.wordpress.com/2009/10/perl-st.png?w=442&#038;h=198' alt='perl-st' height='198' width='442' title='perl-st' /></p>
<p>Since v2 the Bus Pirate firmware has included a <a href='http://dangerousprototypes.com/2009/07/28/bus-pirate-self-test-guide/'>self-test</a> that verifies the function of  pins and peripherals. The latest <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/firmware/v2-nightly'>v2.6-nightly build</a> adds a self-test to the <a href='http://dangerousprototypes.com/2009/10/09/bus-pirate-raw-bitbang-mode/'>binary bitbang mode</a>. This is a useful way for applications to test the Bus Pirate, and for manufacturing quality control.</p>
<p>Self-test details after the break. Don't forget that we're <a href='http://dangerousprototypes.com/2009/10/14/free-probe-cables-for-your-binmode-scripts/'>giving Bus Pirate probe cables</a> to script authors.</p>

<p><span></span></p>
<p><strong>Self-test commands</strong></p>
<ul>
<li>00010000 - Short self-test</li>
<li>00010001 - Long test (requires jumpers between +5 and Vpu, +3.3 and ADC)</li>
</ul>
<p>Self-tests are access from the <a href='http://dangerousprototypes.com/2009/10/09/bus-pirate-raw-bitbang-mode/'>binary bitbang mode</a>. There are actually two self-tests available. The full test is the same as self-test in the user terminal, it requires jumpers between two sets of pins in order to test some features. The short test eliminates the six checks that require jumpers.</p>

<p>After the test is complete, the Bus Pirate responds with the number of errors. It also echoes any input plus the number of errors. The MODE LED blinks if the test was successful, or remains solid if there were errors. Exit the self-test by sending 0xff, the Bus Pirate will respond 0x01 and return to binary bitbang mode.</p>
<p>There's a simple <a href='http://code.google.com/p/the-bus-pirate/source/browse/trunk/scripts/selftest.pl'>Perl self-test example</a> in our <a href='http://code.google.com/p/the-bus-pirate/source/browse/#svn/trunk/scripts'>scripts folder</a>.  Specify the Bus Pirate serial port with -p, and choose a full test (-tf) or a short test (-ts). Run the script without options for a help page.</p>