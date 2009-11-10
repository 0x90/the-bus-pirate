#ifndef __IFACE_H
#define __IFACE_H

#include <QtGui>

enum bbio_pins
{
	BB_POWER = 0x08,
	BB_PULLUPS = 0x04,
	BB_AUX = 0x02,
	BB_CS = 0x01
};

enum bbio_io_pins
{
	BBIO_MOSI = 0x01,
	BBIO_CLK = 0x02,
	BBIO_MISO = 0x04,
	BBIO_CS = 0x08,
	BBIO_AUX = 0x10,
	BBIO_PULLUP = 0x20,
	BBIO_POWER = 0x40
};

enum spi_cfg
{
	SPI_OUT_TYPE = 0x08,
	SPI_IDLE = 0x04,
	SPI_CLK_EDGE = 0x02,
	SPI_SAMPLE = 0x01
};

class MainWidgetFrame;
class SpiGui : public QWidget
{
Q_OBJECT
public:
	SpiGui(MainWidgetFrame *p);
private slots:
	void read_spi();
	void write_spi();
	void spi_chip_id();
private:
	MainWidgetFrame *parent;
	QLineEdit *file;
	QTextEdit *msglog;
protected:
	virtual void customEvent(QEvent *ev);
public:
	void postMsgEvent(const char* msg);
};

class I2CGui : public QWidget
{
Q_OBJECT
public:
	I2CGui(MainWidgetFrame *p);
private:
	MainWidgetFrame *parent;
	QLineEdit *device_addr_read;
	QLineEdit *device_addr_write;
	QLineEdit *file;
	QLineEdit *file_size;
	QLineEdit *start_addr;
	QTextEdit *msglog;
private slots:
	void search_i2c(void);
	void write_i2c(void);
	void read_i2c(void);
protected:
	virtual void customEvent(QEvent *ev);
public:
	void postMsgEvent(const char* msg);
};

class OneWireGui : public QWidget
{
public:
	OneWireGui(MainWidgetFrame *p);
private:
	MainWidgetFrame *parent;
	QLineEdit *device_addr;
	QLineEdit *file;
	QTextEdit *msglog;
protected:
	virtual void customEvent(QEvent *ev);
public:
	void postMsgEvent(const char* msg);
};

class RawWireGui : public QWidget
{
public:
	RawWireGui(MainWidgetFrame *p);
private:
	MainWidgetFrame *parent;
	QLineEdit *device_addr;
	QLineEdit *file;
	QTextEdit *msglog;
protected:
	virtual void customEvent(QEvent *ev);
public:
	void postMsgEvent(const char* msg);
};

class JtagGui : public QWidget
{
Q_OBJECT
public:
	JtagGui(MainWidgetFrame *p);
private:
	MainWidgetFrame *parent;
	QLineEdit *device_addr;
	QLineEdit *file;
	QTextEdit *msglog;
protected:
	virtual void customEvent(QEvent *ev);
public:
	void postMsgEvent(const char* msg);
};

class RawTextGui : public QWidget
{
Q_OBJECT
protected:
	virtual void customEvent(QEvent *ev);
public:
	RawTextGui(MainWidgetFrame *p);
	void postMsgEvent(const char* msg);
private slots:
	void ExecuteFile(void);
private:
	QTextEdit *msglog;
	QLineEdit *raw_file;
	MainWidgetFrame *parent;
};

class PowerGui : public QWidget
{
Q_OBJECT
public:
	PowerGui(MainWidgetFrame *p);
private slots:
	void hiz_power_enable();
	void open_collector_power();
	void normal_power_enable();
	void hardReset();
	void userTermReset();
	void enterMode();
	void resetBBIO();
	void setupBusPirate();
	void getBuffer();
private:
	MainWidgetFrame *parent;
};

#endif

