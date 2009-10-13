v2
I. Upgrade only
II. New installs
III. History

***Depending on your PIC microcontroller, you can increase the bootloader speed up to 115200bps by clicking on the default 9600bps setting and choosing another speed from the drop-down menu. Not all PICs work at 115200bps, but most will work much faster than 9600bps.***

I. Upgrade only
If your Bus Pirate already has a bootloader programmed, follow these steps to load the new firmware.
1. Place a jumper between the PGC and PGD pins of the programming header. This will trigger the bootloader mode.
2. Connect the Bus Pirate to a USB port (or, if applicable, power and serial cable).
3. Start the MS Windows P24QP.exe programmer utility included in this archive. You may need to modify the COM port (portindex=) in P24qp.ini to match your system.
4. Click the connect to device icon. The program should detect and connect to the PIC.
5. Click the folder icon and open the firmware update file (vxx-Firmware-v2.hex).
6. Click the erase device icon to erase the chip. DO NOT SKIP THIS STEP.
7. Click the write device icon to program the new firmware. 
8. Ignore any verify errors between 0x400 and 0xBFF, this is where the bootloader lives.
9. Click the green arrow icon (normal execution mode) to exit the bootloader and start the program.
10. Remove the jumper from the PGC and PGD pins, or move it over one position to connect the inner PGx pin to GND.
11. ***IMPORTANT*** Now restart the Bus Pirate by disconnecting and reconnecting the USB cable (or power cable). Some features won't work until after a complete hardware reset.

II. New installs
If you're starting with a blank chip, follow these steps to load the firmware. 
1. Connect the Bus Pirate to a USB port (or, if applicable, power and serial cable).
2. Program the PIC with the bootloader HEX file through the 5pin ICSP header (vxx-PIC Bootloader-V2.hex).
3. Disconnect the programing cable. DO NOT SKIP THIS STEP.
4. Start the MS Windows P24QP.exe programmer utility included in this archive. You may need to modify the COM port (portindex=) in P24qp.ini to match your system.
5. Click the connect to device icon. The program should detect and connect to the PIC.
6. Click the folder icon and open the firmware update file (vxx-Firmware-v2.hex).
7. Click the erase device icon to erase the chip. DO NOT SKIP THIS STEP.
8. Click the write device icon to program the new firmware. 
9. Ignore any verify errors between 0x400 and 0xBFF, this is where the bootloader lives.
10. Click the green arrow icon (normal execution mode) to exit the bootloader and start the program.
11. ***IMPORTANT*** Now restart the Bus Pirate by disconnecting and reconnecting the USB cable (or power cable). Some features won't work until after a complete hardware reset.

***You DO NOT need to use a jumper between PGC and PGD on a new install, a fresh bootloader on a blank chip waits forever to connect to the programmer utility. 

III. History
See the project tracker on our google SVN page for a complete list of updates
v2.5
*Raw spi fixes: CS command didn't return 1,CS bit of peripheral set command was inverted.
*Smartcard macro in raw2wire uses configured LSB setting (doesn't force LSB bit order).

v2.4
*Bug with some hardware and terminals: require 0x00 20 times to enter BBIO mode to prevent 'dead terminal' syndrome.

v2.3 preview
*Major bug fix to all speed settings, esp. UART
*Raw bigbang mode
*Raw SPI mode

v2.2
*Firmware v2.2 IS compatible with bootloader v0f and v0g, and v2. Upgrade to bootloader V2 if possible.
*V3 hardware compiles in all languages.
*Small fix to smartcard macros.
*Transparent UART bridge macro.
*Updated Spanish translation.

v2.1
*Firmware v2 IS compatible with bootloader v0f and v0g, and v2. Upgrade to bootloader V2 if possible.
*Press 'i' to get your PIC revision and config bits.
*Hardware I2C added, major I2C bug fixes.
*Bulk writes (0xff:12) for most libraries.
*Press '=' for HEX/DEC/BIN conversion.
*New public domain software I2C library, bugs fixed.
*All software libraries now use cental bitbang routines with speed settings.
*JTAG XSFV programmer removed to make room. We'll replace it with a 'real' SFV programmer in the future.
*JTAG chain probe now detects multiple devices, fixed numbering error, refreshed interface.
*Smartcard marco updated. RESET signal now controlled by Bus Pirate CS pin. LSB reads forced for ease of use and ISO compliance, added warning.
*Spanish, Italian translations.
*Firmware for Bus Pirate v3 first release.
*Better translation use, cleaner terminal text.
*General spelling and menu fixes.
*Small bug fixes here and there.

v2
*Firmware v2 IS compatible with bootloader v0f and v0g, but upgrade to bootloader V2 if possible.
*V2 adds LCD library which uses an PCF8574 to interface HD44780 LCDs.
*V2 adds # software reset command
*V2 adds ~ self test for v2go.
*Overall code structure is much cleaner, many bugs removed, minor feature enhancements, this version is a major internal upgrade from v0g.
*V2 bootloader uses mode LED to indicate bootloader entry

v0h
*Firmware v0h-RC2 was renamed v2 to sync with Bus Pirate hardware versioning and reflect improved code structure and function.


v0g
*Firmware v0g IS compatible with bootloader v0f, but upgrade the bootloader if possible.
*Bootloader and vectors straightened out.
*Enhanced bootloader jumper check.

v0f 
*The first version that uses the PIC24 bootloader. 
*Use/upgrade to v0g bootloader if possible.