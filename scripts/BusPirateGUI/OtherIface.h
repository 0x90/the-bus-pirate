#ifndef __OTHER_IFACE_H
#define __OTHER_IFACE_H

#include <QtGui>

class BinMode;
class MainWidgetFrame;

class RawTextGui : public QWidget
{
Q_OBJECT
protected:
	virtual void customEvent(QEvent *ev);
public:
	RawTextGui(MainWidgetFrame *p);
	void postMsgEvent(const char* msg);
	QTextEdit *msglog;
private slots:
	void ExecuteFile(void);
private:
	QLineEdit *raw_file;
	MainWidgetFrame *parent;
	BinMode *bp;
};

class PowerGui : public QWidget
{
Q_OBJECT
public:
	PowerGui(MainWidgetFrame *p);
	MainWidgetFrame *parent;
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
	BinMode *bp;
};

#endif