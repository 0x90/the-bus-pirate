#!/usr/bin/env python
# encoding: utf-8
"""
Created by Matt Callow
Copyright 2011 Matt Callow
Based on the i2c testscript from Peter Huewe

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
import sys, time
from pyBusPirateLite.I2C import *

# Adjust to suit your actual altitude
ALTITUDE=90 # metres
# Specify how much error you will allow in the ADC results from the device
# This is used to filter spurious readings from the ADC
ALLOWED_ERROR=0.01 # i.e. 1%
# Set this to your bus pirate devide
DEVICE='/dev/buspirate'

def get_avg(values):
	"""Calculate the average value from a list of values.

	The input values (in the form of a list) are sorted, then the median
	value found. Each value is compared to the median and, if it falls
	outside an allowable margin, it is ignored. The arithmetic mean is
	taken of the remaining values.

	"""
	sum=0
	values.sort()
	median = values[len(values)/2]
	new_values = []
	for x in values:
		if (abs(x-median) > median*ALLOWED_ERROR):
			print "Value %s too far from median - ignoring" % x
		else:
			new_values.append(x)
	for x in new_values:
		sum += x
	avg = sum/len(new_values)
	return avg

if __name__ == '__main__':
	i2c = None
	# Allow for old and new bus pirate libraries
	try:
		i2c = I2C()
		i2c.connect(DEVICE, 115200, 0.01)
	except TypeError, x:
		i2c = I2C(DEVICE, 115200)

	print "Entering binmode: ",
	sys.stdout.flush()
	if i2c.BBmode(): print "OK."
	else: raise Exception("failed.")

	print "Entering raw I2C mode: ",
	if i2c.enter_I2C(): print "OK."
	else: raise Exception("failed.")
		
	print "Configuring I2C:",
	if not i2c.cfg_pins(I2CPins.POWER | I2CPins.PULLUPS ):
		raise Exception("Failed to set I2C peripherals.")
	if not i2c.set_speed(I2CSpeed._50KHZ):
		raise Exception("Failed to set I2C Speed.")
	i2c.timeout(0.2)
	print "OK."
	
	print "Reading EEPROM: "
	i2c.send_start_bit()
	i2c.bulk_trans(2,[0xa0, 00])
	# I2C write then read command
	# Write 0xa1, then read 0x31 bytes back
	i2c.port.write('\x08\x00\x01\x00\x30\xa1')
	i2c.timeout(0.1)
	eeprom =  i2c.response(0x31, True)
	if ord(eeprom[0]) != 1:
		raise Exception('Failed to read EEPROM')
	eeprom = eeprom[1:]
	c1 = 256 * ord(eeprom[16]) + ord(eeprom[17])
	c2 = 256 * ord(eeprom[18]) + ord(eeprom[19])
	c3 = 256 * ord(eeprom[20]) + ord(eeprom[21])
	c4 = 256 * ord(eeprom[22]) + ord(eeprom[23])
	c5 = 256 * ord(eeprom[24]) + ord(eeprom[25])
	c6 = 256 * ord(eeprom[26]) + ord(eeprom[27])
	c7 = 256 * ord(eeprom[28]) + ord(eeprom[29])
	a = ord(eeprom[30])
	b = ord(eeprom[31])
	c = ord(eeprom[32])
	d = ord(eeprom[33])
	print "OK."
	print c1, c2, c3, c4, c5, c6, c7
	print a,b,c,d
	
	print "Entering BitBang mode: ",
	if i2c.BBmode(): print "OK."
	else: raise Exception("Failed to enter BB mode.")

	print "Starting 32khz oscillator: ",
	if i2c.setup_PWM(0, 243, 487): print "OK."
	else: raise Exception("Failed to start PWM.")

	print "Entering raw I2C mode: ",
	if i2c.enter_I2C(): print "OK."
	else: raise Exception("Failed to enter I2C mode.")

	print "Configuring I2C:",
	if not i2c.cfg_pins(I2CPins.POWER | I2CPins.PULLUPS ):
		raise Exception("Failed to set I2C peripherals.")
	if not i2c.set_speed(I2CSpeed._50KHZ):
		raise Exception("Failed to set I2C Speed.")
	i2c.timeout(0.2)
	print "OK."
	# read pressure
	d1=0
	tmp=[]
	for i in range(0,5):
		i2c.send_start_bit()
		i2c.bulk_trans(3,[0xee, 0xff, 0xf0])
		i2c.send_stop_bit()
		time.sleep(0.1)
		i2c.send_start_bit()
		i2c.bulk_trans(2,[0xee, 0xfd])
		i2c.send_start_bit()
		i2c.bulk_trans(1,[0xef])
		d1h = ord(i2c.read_byte())
		i2c.send_ack()
		d1l = ord(i2c.read_byte())
		i2c.send_nack()
		i2c.send_stop_bit()
		tmp.append(d1h * 256 + d1l)
	d1 = get_avg(tmp)
	print 'd1=',d1

	# read temperature
	d2=0
	tmp=[]
	for i in range(0,5):
		i2c.send_start_bit()
		i2c.bulk_trans(3,[0xee, 0xff, 0xe8])
		i2c.send_stop_bit()
		time.sleep(0.1)
		i2c.send_start_bit()
		i2c.bulk_trans(2,[0xee, 0xfd])
		i2c.send_start_bit()
		i2c.bulk_trans(1,[0xef])
		d2h = ord(i2c.read_byte())
		i2c.send_ack()
		d2l = ord(i2c.read_byte())
		i2c.send_nack()
		i2c.send_stop_bit()
		tmp.append(d2h * 256 + d2l)
	d2 = get_avg(tmp)
	print 'd2=',d2

	print "Entering BitBang mode: ",
	if i2c.BBmode(): print "OK."
	else: raise Exception("Failed to enter BB mode.")

	print "Stopping 32khz oscillator: ",
	if i2c.clear_PWM(): print "OK."
	else: raise Exception("Failed to stop PWM.")

	# Calculate dUT
	m1 = d2 - c5
	m2 = (m1*m1)/16384
	m4 = pow(2, c)
	if d2 < c5:
		m3 = m2 * b
	else:
		m3 = m2 * a
	m4 = m3/m4
	dUT = m1 - m4
	print "dUT=", dUT
	# Calculate OFF
	m1 = c4 - 1024
	m2 = pow(2,14)
	m3 = dUT * m1
	m4 = m3/m2
	m4 = c2+m4
	OFF=m4*4
	print "OFF=",OFF
	# Calculate SENS
	m1 = c3 * dUT
	m2 = pow(2,10)
	m3 = m1/m2
	SENS=c1+m3
	print "SENS=",SENS
	# Calculate X
	m1 = pow(2,14)
	m2 = d1 - 7168
	m3 = m2 * SENS
	m4 = m3/m1
	X = m4 - OFF
	print "X=",X
	# Calculate pressure
	m1 = X*100
	m2 = pow(2,5)
	m3 = m1/m2
	m4 = c7 * 10
	P = m3 + m4
	# Calculate temperature
	T=250+dUT*c6/pow(2,16)-dUT/pow(2,d)

	P = float(P/100.0)
	P0 = round(P/pow((1.0-ALTITUDE/44330.0), 5.255),1)
	T = float(T/10.0)
	print "Temperature =", T, "C"
	print "Pressure =", P, "hpa"
	print "Pressure, adjusted for MSL =", P0, "hpa"
	# Some simple sanity checks
	if T < -30 or T > 80:
		print "Temperature outside valid range"
	if P < 100 or P > 1100:
		print "Pressure outside valid range"

	print "Reset Bus Pirate to user terminal: ",
	if i2c.resetBP(): print "OK."
	else: raise Exception("failed.")

# vim:noexpandtab:
