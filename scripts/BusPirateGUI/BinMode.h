#ifndef __BINMODE_H
#define __BINMODE_H

#include <qextserialport/qextserialport.h>

#define     WREN         0x06 // A:0 U:0 D:0
#define     WRDI         0x04 // A:0 U:0 D:0
#define     RDID         0x9F // A:0 U:0 D:3
#define     RDSR         0x05 // A:0 U:0 D:inf
#define     READ         0x03 // A:3 U:0 D:inf
#define     FAST_READ    0x0B // A:3 U:1 D:inf
#define     PW           0x0A // A:3 U:0 D:256
#define     PP           0x02 // A:3 U:0 D:256
#define     PE           0xDB // A:3 U:0 D:0
#define     SE           0xD8 // A:3 U:0 D:0
#define     DP           0xB9 // A:0 U:0 D:0
#define     RDP          0xAB // A:0 U:0 D:0

class BinMode : public QObject
{
public:
	/* Construct */
	BinMode(QObject *parent, QString s);
	~BinMode();
public slots:
	/* Port Manipulation */
	bool       port_open(void);
	void       port_close(void);
public:
	/* Command Method */
	QByteArray command(short int command);
	
	/* Dump Buffers */
	QByteArray dumpBuffer();

	/* BBIO */
	int        enter_mode_bbio(void);
	int        reset_bbio(void);
	QByteArray reset_hardware(void);
	QByteArray reset_user_terminal(void);

	/* Interface Entry Methods */ 
	int        enter_mode_spi(void);
	int        enter_mode_i2c(void);
	int        enter_mode_uart(void);
	int        enter_mode_onewire(void);

	/* BBIO pin settings */
	int        raw_set_io(short int pins);
	int        raw_set_pins(short int pins);

	/* Self Test Methods */
	QByteArray test_mode_short(void);
	QByteArray test_mode_long(void);

	/* Common Interface Methods */
	QByteArray bbio_mode_version(void);        
	char*      bbio_bulk_trans(char* data, short int size);
	int        bbio_speed_set(short int speed);
	QByteArray bbio_speed_read(void);
	int        bbio_peripherial_set(short int pins);
	QByteArray bbio_peripherial_read(void);

	/* SPI */
	int        spi_cs_low(void);
	int        spi_cs_high(void);
	int        spi_nibble_high(short int nibble);
	QByteArray spi_nibble_low(short int nibble);
	int        spi_configure_set(short int spi_cfg);
	QByteArray spi_configure_read(void);

	/* I2C */
	int        i2c_start(void);
	int        i2c_stop(void);
	QByteArray i2c_byte_read(void);
	int        i2c_ack_send(void);
	int        i2c_nack_send(void);

	/* Serial Port Access */
	QextSerialPort *serial;
};

#endif

