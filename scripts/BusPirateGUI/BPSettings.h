#ifndef __BPSETTINGS_H
#define __BPSETTINGS_H

#include <QtGui>

class BinMode;
class MainWidgetFrame;

class BPSettings : public QSettings
{
Q_OBJECT
public:
	BPSettings();
	~BPSettings();
	QSettings *m_cfg;
	QString serial_port_name;
	int baud_rate;
	int databits;
	int stopbits;
	int parity;
	int flowctrl;
public slots:
	void Save();
	void Load();
};

class BPSettingsGui : public QWidget
{
Q_OBJECT
public:
	BPSettingsGui(MainWidgetFrame *parent);
	~BPSettingsGui();
	void CreateBaudMap(void);
	QLineEdit *s_port;
	QComboBox *s_baud;
	QComboBox *s_databits;
	QComboBox *s_stopbits;
	QComboBox *s_parity;
	QComboBox *s_flow;
	QMap<QString, int> *usable_baud_rate;
	MainWidgetFrame *parent;
	void setConfigSettings();
	void setupBusPirate();
public slots:
	void SaveSettings();
	void openPort();
	void closePort();
};

#endif

