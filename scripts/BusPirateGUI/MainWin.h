#ifndef __QMAIN_H
#define __QMAIN_H

#include <QtGui>

class SpiGui;
class I2CGui;
class OneWireGui;
class RawTextGui;
class PowerGui;
class BPSettingsGui;
class BinMode;
class BPSettings;
class MainAppWindow : public QMainWindow
{
protected:
	virtual void customEvent(QEvent *ev);
public:
	MainAppWindow();
private:
	void createActions();
	void createMenus();
	QLabel *bpstatus;
};

class MainWidgetFrame : public QWidget
{
Q_OBJECT
public:
	MainWidgetFrame(MainAppWindow *p);
	QTabWidget *tabs;
	BPSettings *cfg;
	BinMode *bp;
	SpiGui *spi;
	I2CGui *i2c;
	OneWireGui *onewire;
	RawTextGui *raw_text;
	PowerGui *power;
	BPSettingsGui *settings;
	MainAppWindow *parent;
};

#endif