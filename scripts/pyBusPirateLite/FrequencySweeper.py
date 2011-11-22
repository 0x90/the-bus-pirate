#!/usr/bin/env python
# encoding: utf-8

"""
Created by beth.null on 2011-11-21.
Copyright 2009 beth.null <beth.null@gmail.com>

This file is part of pyBusPirate.

pyBusPirate is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pyBusPirate is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with pyBusPirate.  If not, see <http://www.gnu.org/licenses/>.
"""


#
#	Frequency Sweeper
#
#	This script sweeps a range of frequencies, from a top frequency to a bottom one,
#	using the PWM output of the BusPirate (AUX pin)
#
#	The sweep could be modified via a few parameters, execute ./Sweeper --help to see them
#
#	It's based on the set_pwm_frequency from the pyBusPirate.BitBang library
#
#


import sys,time

from optparse import OptionParser
from pyBusPirateLite.BitBang import *

def main():
    # First of all parse the command line
    
    parser = OptionParser()
    
    parser.add_option("-d", "--device", dest="device", help="serial interface where bus pirate is in.[/dev/bus_pirate].", default="/dev/tty.usbserial-PirateV3")
    parser.add_option("-t", "--top_frequency", dest="top", help="highest frequency (Hz).", type="int", default=10000)
    parser.add_option("-b", "--bottom_frequency", dest="bottom", help="lowest frequency (Hz).", type="int", default=50)
    parser.add_option("-s", "--step", dest="step", help="step increment or decrement.", type="int", default = 100)
    parser.add_option("-x","--step_delay", dest="step_delay", help="time that a frequency is set.", type="float", default=0.05)
    parser.add_option("-m", "--mode", dest="mode", help="tb: top to bottom, bt: bottom to top.", default="tb")
    parser.add_option("-r", "--repeat", dest="repeat", help="times to repeat.", type="int", default=1)
    parser.add_option("-l", "--lift", dest="lift", help="if repeat is greater than one, lift indicate that the following sweep will occur from the last limit.", type="int", default=0)
    
    (options,args) = parser.parse_args()
    
    
    print "### Bus Pirate Frequency Sweeper ###"
    print
    print "\tDevice:\t\t", options.device
    print "\tTop Frequency:\t", options.top, "Khz."
    print "\tBottom Freq:\t", options.bottom, "Khz."
    print "\tStepping:\t", options.step
    print "\tStepping delay:", options.step_delay
    print "\tMode:\t\t", options.mode
    print "\tRepeat:\t\t", options.repeat
    print "\tLift mode:\t", options.lift
    print
    print "####################################"
    
    if options.top < options.bottom:
    	dummy = options.top;
    	options.top = options.bottom;
    	options.bottom = dummy;
    	
    
    bp = BBIO(p=options.device)
    bp.BBmode()
    
    steps = (options.top - options.bottom) / options.step
    steps += 1
    
    if options.mode == "tb":
    	options.step *= -1
    
    if options.mode == "tb":
    	frequency = options.top
    else:
    	frequency = options.bottom
    	
    for I in range(0, options.repeat):
    	if options.lift == 0:
    		print "No lift"
    		if options.mode == "tb":
    			frequency = options.top
    		else:
    			frequency = options.bottom
    	else:
    		print "Lift"
    		if I != 0:
    			options.step *= -1
		
	for J in range(0, steps):
		print "Sweep: ", I,  " Frequency: ", frequency
		bp.set_pwm_frequency(frequency)
		time.sleep(options.step_delay);
		
		if J != steps - 1:	
			frequency += options.step;
			
		
    
    bp.resetBP()
    
    
    
    
if __name__ == '__main__':
    
    main()
    	
