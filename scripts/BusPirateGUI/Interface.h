#ifndef __IFACE_H
#define __IFACE_H

#include <QtGui>

class BinMode;
class MainWidgetFrame;

class SpiGui : public QWidget
{
Q_OBJECT
public:
	SpiGui(MainWidgetFrame *p);
	MainWidgetFrame *parent;
	QTextEdit *msglog;
private slots:
	void read_spi();
	void write_spi();
	void spi_chip_id();
private:
	QLineEdit *spi_file;
	BinMode *bp;
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
	MainWidgetFrame *parent;
	QTextEdit *msglog;
private slots:
	void search_i2c(void);
private:
	QLineEdit *device_addr;
	QLineEdit *spi_file;
	BinMode *bp;
protected:
	virtual void customEvent(QEvent *ev);
public:
	void postMsgEvent(const char* msg);
};

class OneWireGui : public QWidget
{
public:
	OneWireGui(MainWidgetFrame *p);
	MainWidgetFrame *parent;
	QLineEdit *device_addr;
	QLineEdit *spi_file;
	QTextEdit *msglog;
protected:
	virtual void customEvent(QEvent *ev);
public:
	void postMsgEvent(const char* msg);
};

#endif