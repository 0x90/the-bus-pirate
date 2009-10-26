#include <QtGui>
#include "MainWin.h"
#include "BinMode.h"
#include "BPSettings.h"
#include "Events.h"
BPSettingsGui::BPSettingsGui(MainWidgetFrame *p) : QWidget(p)
{
	parent=p;
	QStringList baud_list;
	baud_list << "300" << "600" << "1200" << "2400" << "4800" << "9600" <<
		"19200" << "38400" << "57600" << "115200";

	QStringList databits_list;
	databits_list << "5" << "6" << "7" << "8";

	QStringList parity_list;
	parity_list << "NONE" << "ODD" << "EVEN" << "SPACE"; 
	
	QStringList stopbits_list;
	stopbits_list << "1" << "2";

	QStringList flowctrl_list;
	flowctrl_list << "OFF" << "HARDWARE" << "SOFTWARE";

	cfg = parent->cfg;
	bp = parent->bp;

	QLabel *s_port_label = new QLabel("Serial Port: ");
	QLabel *s_baud_label = new QLabel("Port Baud Rate: ");
	QLabel *s_databits_label = new QLabel("Data bits: ");
	QLabel *s_stopbits_label = new QLabel("Stop bits: ");
	QLabel *s_parity_label = new QLabel("Parity: ");
	QLabel *s_flow_label = new QLabel("Flow Control: ");

	QPushButton *open = new QPushButton("Open BusPirate");
	QPushButton *close = new QPushButton("Close BusPirate");
	
	s_port = new QLineEdit(parent->cfg->serial_port_name);

	s_baud = new QComboBox;
	s_baud->setCurrentIndex(cfg->baud_rate);
	s_databits = new QComboBox;
	s_databits->setCurrentIndex(cfg->databits);
	s_stopbits = new QComboBox;
	s_stopbits->setCurrentIndex(cfg->stopbits);
	s_parity = new QComboBox;
	s_parity->setCurrentIndex(cfg->parity);
	s_flow = new QComboBox;
	s_flow->setCurrentIndex(cfg->flowctrl);

	QVBoxLayout *mlayout = new QVBoxLayout;

	s_baud->addItems(baud_list);
	s_databits->addItems(databits_list);
	s_stopbits->addItems(stopbits_list);
	s_parity->addItems(parity_list);
	s_flow->addItems(flowctrl_list);

	s_baud->setCurrentIndex(9);
	s_databits->setCurrentIndex(3);

	connect(open, SIGNAL(clicked()), this, SLOT(openPort()));
	connect(close, SIGNAL(clicked()), this, SLOT(closePort()));

	connect(s_port, SIGNAL(editingFinished()), this, SLOT(setConfigSettings()));
	connect(s_baud, SIGNAL(currentIndexChanged(int)), this, SLOT(setConfigSettings()));
	connect(s_databits, SIGNAL(currentIndexChanged(int)), this, SLOT(setConfigSettings()));
	connect(s_stopbits, SIGNAL(currentIndexChanged(int)), this, SLOT(setConfigSettings()));
	connect(s_parity, SIGNAL(currentIndexChanged(int)), this, SLOT(setConfigSettings()));
	connect(s_flow, SIGNAL(currentIndexChanged(int)), this, SLOT(setConfigSettings()));

	connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(closePort()));

	mlayout->addWidget(s_port_label);
	mlayout->addWidget(s_port);
	mlayout->addWidget(s_baud_label);
	mlayout->addWidget(s_baud);
	mlayout->addWidget(s_databits_label);
	mlayout->addWidget(s_databits);
	mlayout->addWidget(s_stopbits_label);
	mlayout->addWidget(s_stopbits);
	mlayout->addWidget(s_parity_label);
	mlayout->addWidget(s_parity);
	mlayout->addWidget(s_flow_label);
	mlayout->addWidget(s_flow);
	mlayout->addSpacing(50);
	mlayout->addWidget(open);
	mlayout->addWidget(close);

	setLayout(mlayout);
	setupBusPirate();
}

void BPSettingsGui::SaveSettings()
{
	cfg->serial_port_name = s_port->text();
	cfg->baud_rate = s_baud->currentIndex();
	cfg->databits = s_databits->currentIndex();
	cfg->stopbits = s_stopbits->currentIndex();
	cfg->parity = s_parity->currentIndex();
	cfg->flowctrl = s_flow->currentIndex();
	cfg->Save();
}

void BPSettingsGui::setConfigSettings()
{
	qDebug() << "set Port Settings";
	bp->serial->setPortName(cfg->serial_port_name);
	//bp->serial->setBaudRate(cfg->baud_rate);
	bp->serial->setDataBits((DataBitsType)cfg->databits); //DATA_8
	bp->serial->setStopBits((StopBitsType)cfg->stopbits); //STOP_1
	bp->serial->setParity((ParityType)cfg->parity); //PAR_NONE
	bp->serial->setFlowControl((FlowType)cfg->flowctrl); //FLOW_OFF
}

void BPSettingsGui::openPort()
{
	QString qmsg = QString("Bus Pirate Ready");
	bp->port_open();
	QCoreApplication::sendEvent(parent->parent, new BPStatusMsgEvent::BPStatusMsgEvent(qmsg));
}

void BPSettingsGui::closePort()
{
	QString qmsg = QString("Bus Pirate Closed");
	bp->port_close();
	QCoreApplication::sendEvent(parent->parent, new BPStatusMsgEvent::BPStatusMsgEvent(qmsg));
}

void BPSettingsGui::setupBusPirate()
{
	openPort();
	if (!bp->reset_bbio())
		bp->enter_mode_bbio();	
}

BPSettings::BPSettings() : QSettings("./rc_buspirate", QSettings::IniFormat)
{
	Load();
}

void BPSettings::Save()
{
	qDebug() << "Saving Config File";
	setValue("/serial_port/name", serial_port_name);
	setValue("/serial_port/baud_rate", baud_rate);
	setValue("/serial_port/databits", databits);
	setValue("/serial_port/stopbits", stopbits);
	setValue("/serial_port/parity", parity);
	setValue("/serial_port/flowctrl", flowctrl);
}

void BPSettings::Load()
{
	qDebug() << "Loading Config File";
	serial_port_name = value("/serial_port/name", "/dev/bus_pirate").toString();
	baud_rate = value("/serial_port/baud_rate", 9).toInt();
	databits = value("/serial_port/databits", 3).toInt();
	stopbits = value("/serial_port/stopbits", 0).toInt();
	parity = value("/serial_port/parity", 0).toInt();
	flowctrl = value("/serial_port/flowctrl", 1).toInt();
}