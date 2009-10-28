#include <QtGui>
#include <qextserialport/qextserialport.h>
#include "Events.h"
#include "MainWin.h"
#include "BPSettings.h"
#include "BinMode.h"

BinMode::BinMode(MainWidgetFrame *parent) : QWidget(parent)
{
	this->parent = parent;
	serial = new QextSerialPort(QextSerialPort::Polling);
}

BinMode::~BinMode()
{
	port_close();
}

QByteArray BinMode::dumpBuffer()
{
	QByteArray resp;
	qDebug() << "Dump Buffers";
	do {
		resp = serial->readAll();
		qDebug() << resp.data();
	} while (!resp.isEmpty());
	return resp;
}

/* Port Manipulation */
bool BinMode::port_open()
{
	serial->setPortName(parent->settings->s_port->text());
	serial->setBaudRate((BaudRateType)parent->settings->usable_baud_rate->value(parent->settings->s_baud->currentText(), BAUD115200)); //BAUD115200
	serial->setDataBits((DataBitsType)parent->settings->s_databits->currentIndex());  //DATA_8
	serial->setStopBits((StopBitsType)parent->settings->s_stopbits->currentIndex());  //STOP_1
	serial->setParity((ParityType)parent->settings->s_parity->currentIndex());      //PAR_NONE
	serial->setFlowControl((FlowType)parent->settings->s_flow->currentIndex());      //FLOW_OFF
	serial->setTimeout(100);
	bool ret = serial->open(QIODevice::ReadWrite);
	serial->flush();
	return ret;
}

void BinMode::port_close()
{
	serial->flush();
	serial->close();
	qDebug() << "Serial Port Closed:" << serial->portName() << "is open-" << serial->isOpen();
}

QByteArray BinMode::command(short int command)
{
	char data = (command);
	QByteArray res;
	serial->write(&data, 1);
	res = serial->readAll();
	return res;
}

/* BBIO */
int BinMode::enter_mode_bbio(void)
{
	int ret=0;
	QByteArray res;
	serial->write("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 20);
	res = serial->readAll();
	if (res.contains("BBIO")) ret = 1;
	if (ret) qDebug() << "BBIO Ready!";
	return ret;
}

int BinMode::reset_bbio(void)
{
	QByteArray version_string;
	int ret = 0;

	serial->write("\x00", 1);
	version_string = serial->readAll();
	if (version_string.contains("BBIO")) ret = 1;
	qDebug() << "BBIO - text:" << version_string;
	return ret;
}

QByteArray BinMode::reset_hardware(void)
{
	QByteArray buspirate_info, resp;
	serial->write("\x0F", 1);
	serial->read(1);
	buspirate_info = serial->readAll();
	qDebug() << "reset BP:" << buspirate_info;
	return buspirate_info;
}

QByteArray BinMode::reset_user_terminal(void)
{
	QByteArray resp;
	serial->write("\n\n\n\n\n\n\n\n\n\n#\n", 12);
	resp = serial->readAll();
	qDebug() << "reset user term:" << resp;
	return resp;
}

/* Interface Entry Methods */
int BinMode::enter_mode_spi(void)
{
	QByteArray version_string;
	int ret = 0;
	serial->write("\x01", 1);
	version_string = serial->readAll();
	if (version_string.contains("SPI")) ret = 1;
	qDebug() << "SPI - text: " << version_string;
	return ret;
}

int BinMode::enter_mode_i2c(void)
{
	int ret = 0;
	QByteArray version_string;
	serial->write("\x02", 1);
	version_string = serial->readAll();
	if (version_string.contains("I2C")) ret = 1;
	qDebug() << "I2C text: " << version_string;
	return ret;
}

int BinMode::enter_mode_uart(void)
{
	int ret = 0;
	QByteArray version_string;
	serial->write("\x03", 1);
	version_string = serial->readAll();
	if (version_string.contains("ART")) ret = 1;
	qDebug() << "UART text: " << version_string;
	return ret;
}

int BinMode::enter_mode_onewire(void)
{
	int ret = 0;
	QByteArray version_string;
	serial->write("\x04", 1);
	version_string = serial->readAll();
	if (version_string.contains("1W")) ret = 1;
	qDebug() << "1Wire text: " << version_string;
	return ret;
}

/* BBIO Pin Settings */
int BinMode::raw_set_io(short int pins)
{
	int ret = 0;
	char data = (0x40|pins);
	QByteArray resp;
	serial->write(&data, 1);
	resp = serial->readAll();
	if (resp.contains("\x01")) ret = 1;
	qDebug() << "raw set io:" << data;
	return ret;
}

int BinMode::raw_set_pins(short int pins)
{
	int ret = 0;
	char data = (0x80|pins);
	QByteArray resp;
	serial->write(&data, 1);
	resp = serial->readAll();
	if (resp.contains("\x01")) ret = 1;
	qDebug() << "raw set pins:" << data;
	return ret;
}

/* Self Test Methods */
QByteArray BinMode::test_mode_short(void)
{
	QByteArray resp;
	serial->write("\x10", 1);
	resp = serial->readAll();
	return resp;
}

QByteArray BinMode::test_mode_long(void)
{
	QByteArray resp;
	serial->write("\x11", 1);
	resp = serial->readAll();
	return resp;
}

/* Common Interfaces Methods */
QByteArray BinMode::bbio_mode_version(void)
{
	QByteArray resp;
	serial->write("\x01", 1);
	resp = serial->readAll();
	return resp;
}

char *BinMode::bbio_bulk_trans(char *data, short int size)
{
	int i = 0;
	QByteArray cmd_response;
	QByteArray data_response;
	char cmd_data = (0x10|(size-1));
	serial->write(&cmd_data, 1);
	cmd_response = serial->readAll();
	serial->write(data, size);
	data_response = serial->readAll();
	if (cmd_response.contains("\x01")) return data_response.data();
	qDebug() << "bulk trans:" << data_response.toHex();
	return data_response.data();
}

int BinMode::bbio_speed_set(short int speed)
{
	char data = (0x60|speed);
	QByteArray res;
	int ret = 0;
	serial->write(&data, 1);
	res = serial->readAll();
	if (res.contains("\x01")) ret=1;
	return ret;
}

QByteArray BinMode::bbio_speed_read(void)
{
	QByteArray res;
	serial->write("\x70");
	res = serial->readAll();
	return res;
}

int BinMode::bbio_peripherial_set(short int pins)
{
	char data = (0x40|pins);
	int ret = 0;
	bool Ok;
	QByteArray res;
	serial->write(&data, 1);
	res = serial->readAll();
	if (res.contains("\x01")) ret=1;
	return ret;
}

QByteArray BinMode::bbio_peripherial_read(void)
{
	QByteArray res;
	serial->write("\x50");
	res = serial->readAll();
	return res;
}

/* SPI methods */
int BinMode::spi_cs_low(void)
{
	int ret = 0;
	QByteArray res;
	serial->write("\x02", 1);
	res = serial->readAll();
	if (res.contains("\x01")) ret = 1;
	return ret;
}

int BinMode::spi_cs_high(void)
{
	int ret = 0;
	QByteArray res;
	serial->write("\x03", 1);
	res = serial->readAll();
	if (res.contains("\x01")) ret=1;
	return ret;
}

int BinMode::spi_nibble_high(short int nibble)
{
	int ret = 0;
	QByteArray resp;
	char nib = (0x30|nibble);
	serial->write(&nib, 1);
	resp = serial->readAll();
	if (resp.contains("\x01")) ret = 1;
	return ret;
}

QByteArray BinMode::spi_nibble_low(short int nibble)
{
	QByteArray ret;
	char nib = (0x20|nibble);
	serial->write(&nib, 1);
	ret = serial->readAll();
	return ret;
}

int BinMode::spi_configure_set(short int spi_cfg)
{
	char data = (0x80|spi_cfg);
	int ret = 0;
	QByteArray res;
	serial->write(&data, 1);
	res = serial->readAll();
	if (res.contains("\x01")) ret=1;
	return ret;
}

QByteArray BinMode::spi_configure_read(void)
{
	QByteArray resp;
	serial->write("\x90", 1);
	resp = serial->readAll();
	return resp;
}

/* I2C Methods */
int BinMode::i2c_start(void)
{
	int ret = 0;
	QByteArray res;
	serial->write("\x02", 1);
	res = serial->readAll();
	if (res.contains("\x01")) ret = 1;
	return ret;
}

int BinMode::i2c_stop(void)
{
	int ret = 0;
	QByteArray res;
	serial->write("\x03", 1);
	res = serial->readAll();
	if (res.contains("\x01")) ret = 1;
	return ret;
}

QByteArray BinMode::i2c_byte_read(void)
{
	QByteArray res;
	serial->write("\x04", 1);
	res = serial->readAll();
	return res;
}

int BinMode::i2c_ack_send(void)
{
	int ret = 0;
	QByteArray res;
	serial->write("\x05", 1);
	res = serial->readAll();
	if (res.contains("\x01")) ret = 1;
	return ret;
}

int BinMode::i2c_nack_send(void)
{
	int ret = 0;
	QByteArray res;
	serial->write("\x06", 1);
	res = serial->readAll();
	if (res.contains("\x01")) ret = 1;
	return ret;
}

