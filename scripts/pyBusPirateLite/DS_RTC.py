#!/usr/bin/env python
# encoding: utf-8
"""
Created by Andrew Schamp on April 24, 2011.
Copyright 2011 Andrew Schamp <schamp@gmail.com>
Based on the DS1631 temperature sensor interface from Ondrej Caletka.

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

import datetime
import sys
from pyBusPirateLite.I2Chigh import *

def initI2C(port="COM3", address = 0x68):
    try:
        # Serial timeout five seconds for debugging mistakes in I2C class
        i2c = I2Chigh(port, 115200, 5) 
    except Exception, e:
        print "Error",e
        sys.exit()

    print "Entering binmode: ",
    if i2c.BBmode():
        print "OK."
    else:
        print "failed."
        sys.exit()

    print "Entering raw I2C mode: ",
    if i2c.enter_I2C():
        print "OK."
    else:
        print "failed."
        sys.exit()
    
    print "Configuring I2C."
    if not i2c.cfg_pins(I2CPins.POWER | I2CPins.PULLUPS):
        print "Failed to set I2C peripherals."
        sys.exit()
    # the DS3231 supports 100KHz mode or 400KHz mode
    if not i2c.set_speed(I2CSpeed._400KHZ):
        print "Failed to set I2C Speed."
        sys.exit()
    i2c.timeout(0.2)
    return i2c

def bcd_to_int(bcd, bits = 8):
    # shift left to erase unwanted high order bits
    bcd = bcd << (8 - bits)
    # shift right to get everything back in the right position
    bcd = bcd >> (8 - bits)
    # mask off high nibble and shift right
    digit10s = ((bcd & 0xF0) >> 4) 
    # mask off low nibble
    digit1s  = bcd & 0x0F
    return (digit10s * 10) + digit1s

def int_to_bcd(int_val, bits = 8):
    int10s = int_val / 10
    int1s  = int_val % 10
    bcd = (int10s << 4) | int1s
    # shift left to erase unwanted high order bits
    bcd = bcd << (8 - bits)
    # shift right to get everything back in the right position
    bcd = bcd >> (8 - bits)
    return bcd

class RTCError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(Self):
        return repr(self.value)

class DS_RTC:
    """ DS realtime clock interface, common for DS1307, DS3231, and DS3232. Uses I2Chigh class for communication with device. """
    SEC_ADDR   = 0x00
    MIN_ADDR   = 0x01
    HOUR_ADDR  = 0x02
    DAY_ADDR   = 0x03
    DATE_ADDR  = 0x04
    MONTH_ADDR = 0x05
    YEAR_ADDR  = 0x06

    HOUR_MODE_12 = "12"
    HOUR_MODE_24 = "24"
    HOUR_AM      = "AM"
    HOUR_PM      = "PM"

    def __init__(self, i2c=None, port="COM3", address=0x68):
        if i2c == None:
            i2c = initI2C(port=port, address=address)
        self.i2c = i2c;
        self.address = address;

    def get_byte(self, addr):
        return self.i2c.get_byte(self.address, addr)

    def set_byte(self, addr, byte):
        self.i2c.set_byte(self.address, addr, byte)

    def get_seconds(self):
        s = self.get_byte(DS3231.SEC_ADDR)
        return bcd_to_int(s, 7)

    def set_seconds(self, sec):
        self.set_byte(DS3231.SEC_ADDR, int_to_bcd(sec, 7))
        new_sec = self.get_seconds()
        if not new_sec == sec:
            raise RTCError("Seconds (%s) not set to requested value (%s)" % (new_sec, sec))
            
    def get_minutes(self):
        m = self.get_byte(DS3231.MIN_ADDR)
        return bcd_to_int(m, 7)

    def set_minutes(self, minutes):
        self.set_byte(DS3231.MIN_ADDR, int_to_bcd(minutes, 7))
        new_min = self.get_minutes()
        if not new_min == minutes:
            raise RTCError("Minutes (%s) not set to requested value (%s)" % (new_min, minutes))

    def get_12_24_hour_mode(self):
        h = self.get_byte(DS3231.HOUR_ADDR)
        if h & 0x40:
            return DS3231.HOUR_MODE_12
        else:
            return DS3231.HOUR_MODE_24

    # kind of a mess, but it ought to work
    # when setting 12/24 hour mode, set the hours (and the AM/PM flag) to the proper value 
    # based on the current value of hours
    def set_12_24_hour_mode(self, mode):
        old_mode = self.get_12_24_hour_mode()
        if old_mode == mode:
            return

        if mode == DS3231.HOUR_MODE_12:
            hours = self.get_hours_24()
            is_pm = (hours / 12) > 0
            hours = hours % 12
            h = 0x40 | (is_pm << 6) 
            h += int_to_bcd(hours, 5)
        else:
            hours = self.get_hours_12()
            am_pm = self.get_am_pm()
            if am_pm == DS3231.HOUR_PM:
                hours += 12
            h = 0x40 + int_to_bcd(hours, 6)

        self.set_byte(DS3231.HOUR_ADDR, h)
        new_mode = self.get_12_24_hour_mode()
        if not new_mode == mode:
            raise RTCError("12/24 Hour Mode (%s) not set to requested value (%s)" % (new_mode, mode))

    def get_am_pm(self):
        if self.get_12_24_hour_mode() == DS3231.HOUR_MODE_24:
            raise RTCError("Attempted to get AM/PM bit while in 24-hour mode.")
        h = self.get_byte(DS3231.HOUR_ADDR)
        if h & 0x20:
            return DS3231.HOUR_PM
        else:
            return DS3231.HOUR_AM

    def set_am_pm(self, am_pm):
        if self.get_12_24_hour_mode() == DS3231.HOUR_MODE_24:
            raise RTCError("Attempted to set AM/PM bit while in 24-hour mode.")
        h = self.get_byte(DS3231.HOUR_ADDR)
        if am_pm == DS3231.HOUR_PM:
            h |= 0x20
        else:
            h ^= 0x20
        self.set_byte(DS3231.HOUR_ADDR, h)
        new_am_pm = self.get_am_pm()
        if not new_am_pm == am_pm:
            raise RTCError("AM/PM mode (%s) not set to requested value (%s)" % (new_am_pm, am_pm))


    def get_hours_12(self):
        if self.get_12_24_hour_mode() == DS3231.HOUR_MODE_24:
            return self.get_hours_24() % 12
        else:
            h = self.get_byte(DS3231.HOUR_ADDR)
            return bcd_to_int(h, 5)

    def set_hours_12(self, hours):
        self.set_12_24_hour_mode(DS3231.HOUR_MODE_12)
        self.set_byte(DS3231.HOUR_ADDR, int_to_bcd(hours, 5))
        if hours > 12:
            self.set_am_pm(DS3231.HOUR_PM)
        new_hours = self.get_hours_12()
        if not new_hours == hours:
            raise RTCError("Hours (%s) not set to requested value (%s)" % (new_hours, hours))

    def get_hours_24(self):
        if self.get_12_24_hour_mode() == DS3231.HOUR_MODE_12:
            if self.get_am_pm == DS3231.HOUR_PM:
                return self.get_hours_12() + 12
            else:
                return self.get_hours_12()
        else:
            h = self.get_byte(DS3231.HOUR_ADDR)
            return bcd_to_int(h, 6)

    def set_hours_24(self, hours):
        self.set_12_24_hour_mode(DS3231.HOUR_MODE_24)
        self.set_byte(DS3231.HOUR_ADDR, int_to_bcd(hours, 6))
        new_hours = self.get_hours_24()
        if not new_hours == hours:
            raise RTCError("Hours (%s) not set to requested value (%s)" % (new_hours, hours))


    def get_hours(self):
        if self.get_12_24_hour_mode() == DS3231.HOUR_MODE_12:
            return self.get_hours_12()
        else:
            return self.get_hours_24()

    def get_time(self):
        return datetime.time(self.get_hours_24(),
                             self.get_minutes(),
                             self.get_seconds())

    def set_time(self, time):
        self.set_hours_24(time.hour)
        self.set_minutes(time.minute)
        self.set_seconds(time.second)


    def get_day_of_week(self):
        d = self.get_byte(DS3231.DAY_ADDR)
        return bcd_to_int(d, 3)

    def set_day_of_week(self, day):
        self.set_byte(DS3231.DAY_ADDR, int_to_bcd(day, 3))
        new_day = self.get_day_of_week()
        if not new_day == day:
            raise RTCError("Day of week (%d) not set to requested value (%d)" % (new_day, day))

    def get_day_of_month(self):
        d = self.get_byte(DS3231.DATE_ADDR)
        return bcd_to_int(d, 6)

    def set_day_of_month(self, day):
        self.set_byte(DS3231.DATE_ADDR, int_to_bcd(day, 6))
        new_day = self.get_day_of_month()
        if not new_day == day:
            raise RTCError("Day of month (%d) not set to requested value (%d)" % (new_day, day))

    def get_month(self):
        m = self.get_byte(DS3231.MONTH_ADDR)
        return bcd_to_int(m, 5)

    def set_month(self, month):
        self.set_byte(DS3231.MONTH_ADDR, int_to_bcd(month, 5))
        new_month = self.get_month()
        if not new_month == month:
            raise RTCError("Month (%d) not set to requested value (%d)" % (new_month, month))

    def get_year(self):
        y = self.get_byte(DS3231.YEAR_ADDR)
        return 2000 + bcd_to_int(y, 8) 

    def set_year(self, year):
        self.set_byte(DS3231.YEAR_ADDR, year % 100)
        new_year = self.get_year()
        if not new_year == year:
            raise RTCError("Year (%d) not set to requested value (%d)" % (new_year, year))

    def get_date(self):
        return datetime.date(self.get_year(),
                             self.get_month(),
                             self.get_day_of_month())

    def set_date(self, date):
        self.set_year(date.year)
        self.set_month(date.month)
        self.set_day_of_month(date.day)

    def get_datetime(self):
        date = self.get_date()
        time = self.get_time()
        return datetime.datetime(date.year,
                                 date.month,
                                 date.day,
                                 time.hour,
                                 time.minute,
                                 time.second)
                                 
    def set_datetime(self, dt):
        self.set_date(datetime.date(dt.year, dt.month, dt.day))
        self.set_time(datetime.time(dt.hour, dt.minute, dt.second))


class DS1307(DS_RTC):
    "The DS1307 has a special clock-halt bit (haven't implemented yet, no way to test)"
    pass

class DS3231(DS_RTC):
    "The DS3231 has several alarms"
    # TODO: implement alarm support
    pass

class DS3232(DS3231):
    "Apart from some SRAM, the DS3232 has the same interface as the DS3231"
    # TODO: implement SRAM support
    pass
