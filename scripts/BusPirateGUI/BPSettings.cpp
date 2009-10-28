#include <QtGui>
#include <qextserialport/qextserialport.h>
#include "MainWin.h"
#include "BPSettings.h"
#include "Events.h"
#include "BinMode.h"

BPSettingsGui::BPSettingsGui(MainWidgetFrame *parent) : QWidget(parent)
{
	this->parent=parent;

	CreateBaudMap();
	QStringList baud_list;
	baud_list << "300" << "600" << "1200" << "2400" << "4800" << "9600" 
		<< "19200" << "38400" << "57600" << "115200";

	QStringList databits_list;
	databits_list << "5" << "6" << "7" << "8";

	QStringList parity_list;
	parity_list << "NONE" << "ODD" << "EVEN" << "SPACE"; 
	
	QStringList stopbits_list;
	stopbits_list << "1" << "2";

	QStringList flowctrl_list;
	flowctrl_list << "OFF" << "HARDWARE" << "SOFTWARE";


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
	s_baud->addItems(baud_list);
	s_baud->setCurrentIndex(s_baud->findText(usable_baud_rate->key(parent->cfg->baud_rate)));

	s_databits = new QComboBox;
	s_databits->addItems(databits_list);
	s_databits->setCurrentIndex(parent->cfg->databits);

	s_stopbits = new QComboBox;
	s_stopbits->addItems(stopbits_list);
	s_stopbits->setCurrentIndex(parent->cfg->stopbits);

	s_parity = new QComboBox;
	s_parity->addItems(parity_list);
	s_parity->setCurrentIndex(parent->cfg->parity);

	s_flow = new QComboBox;
	s_flow->addItems(flowctrl_list);
	s_flow->setCurrentIndex(parent->cfg->flowctrl);

	QVBoxLayout *mlayout = new QVBoxLayout;

	connect(open, SIGNAL(clicked()), this, SLOT(openPort()));
	connect(close, SIGNAL(clicked()), this, SLOT(closePort()));

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
	//setupBusPirate();
}

BPSettingsGui::~BPSettingsGui()
{
	SaveSettings();
}

void BPSettingsGui::SaveSettings()
{
	qDebug() << "Save Port Settings";
	parent->cfg->serial_port_name = s_port->text();
	parent->cfg->baud_rate = usable_baud_rate->value(s_baud->currentText(), BAUD115200);
	parent->cfg->databits = s_databits->currentIndex();
	parent->cfg->stopbits = s_stopbits->currentIndex();
	parent->cfg->parity = s_parity->currentIndex();
	parent->cfg->flowctrl = s_flow->currentIndex();
	parent->cfg->Save();
}

void BPSettingsGui::setConfigSettings()
{
	qDebug() << "set Port Settings";
	parent->bp->serial->setPortName(s_port->text());
	parent->bp->serial->setBaudRate((BaudRateType)usable_baud_rate->value(s_baud->currentText(), BAUD115200)); //BAUD115200
	parent->bp->serial->setDataBits((DataBitsType)s_databits->currentIndex());  //DATA_8
	parent->bp->serial->setStopBits((StopBitsType)s_stopbits->currentIndex());  //STOP_1
	parent->bp->serial->setParity((ParityType)s_parity->currentIndex());      //PAR_NONE
	parent->bp->serial->setFlowControl((FlowType)s_flow->currentIndex());      //FLOW_OFF
}

void BPSettingsGui::openPort()
{
	QString qmsg = QString("Bus Pirate Ready");
	if (parent->bp->port_open())
		QCoreApplication::sendEvent(parent->parent, new BPPortStatusMsgEvent::BPPortStatusMsgEvent(qmsg));
}

void BPSettingsGui::closePort()
{
	QString qmsg = QString("Bus Pirate Closed");
	parent->bp->port_close();
	QCoreApplication::sendEvent(parent->parent, new BPPortStatusMsgEvent::BPPortStatusMsgEvent(qmsg));
}

void BPSettingsGui::setupBusPirate()
{
	openPort();
	if (!parent->bp->reset_bbio())
		parent->bp->enter_mode_bbio();	
}

void BPSettingsGui::CreateBaudMap(void)
{
	/*
    BAUD300,
    BAUD600,
    BAUD1200,
    BAUD2400,
    BAUD4800,
    BAUD9600,
    BAUD19200,
    BAUD38400,
    BAUD57600,
    BAUD115200,
    */
	usable_baud_rate = new QMap<QString, int>();
	usable_baud_rate->insert("300", BAUD300);
	usable_baud_rate->insert("600", BAUD600);
	usable_baud_rate->insert("1200", BAUD1200);
	usable_baud_rate->insert("2400", BAUD2400);
	usable_baud_rate->insert("4800", BAUD4800);
	usable_baud_rate->insert("9600", BAUD9600);
	usable_baud_rate->insert("19200", BAUD19200);
	usable_baud_rate->insert("38400", BAUD38400);
	usable_baud_rate->insert("57600", BAUD57600);
	usable_baud_rate->insert("115200", BAUD115200);
}

BPSettings::BPSettings() : QSettings("./rc_buspirate", QSettings::IniFormat)
{
	Load();
}

BPSettings::~BPSettings()
{
	Save();
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
	serial_port_name = value("/serial_port/name", QString("/dev/bus_pirate")).toString();
	baud_rate = value("/serial_port/baud_rate", BAUD115200).toInt();
	databits = value("/serial_port/databits", DATA_8).toInt();
	stopbits = value("/serial_port/stopbits", STOP_1).toInt();
	parity = value("/serial_port/parity", PAR_NONE).toInt();
	flowctrl = value("/serial_port/flowctrl", FLOW_HARDWARE).toInt();
	//qDebug() << serial_port_name;
}

