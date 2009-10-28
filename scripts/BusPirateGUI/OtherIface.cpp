#include <QtGui>
#include "miscellanous.h"
#include "BinMode.h"
#include "BPSettings.h"
#include "MainWin.h"
#include "OtherIface.h"

#include "Events.h"

/* Interface: Raw Ascii Text */
RawTextGui::RawTextGui(MainWidgetFrame *parent) : QWidget(parent)
{
	this->parent = parent;
	bp = parent->bp;

	QVBoxLayout *vlayout = new QVBoxLayout;
	QLabel *file_label = new QLabel("File: ");
	raw_file = new QLineEdit("test_hex_ascii.txt");
	QPushButton *button = new QPushButton("Run");
	QLabel *log_label = new QLabel("Log: ");
	msglog = new QTextEdit;
	
	connect(button, SIGNAL(clicked()), this, SLOT(ExecuteFile()));

	vlayout->addWidget(file_label);
	vlayout->addWidget(raw_file);
	vlayout->addWidget(button);
	vlayout->addSpacing(50);
	vlayout->addWidget(log_label);
	vlayout->addWidget(msglog);
	
	setLayout(vlayout);
}

void RawTextGui::customEvent(QEvent *ev)
{
	if (static_cast<BPEventType>(ev->type()) == AsciiHexLogMsgEvent)
	{
		msglog->append(dynamic_cast<AsciiHexLogMsgEvent::AsciiHexLogMsgEvent* >(ev)->msg);
	}
}

void RawTextGui::postMsgEvent(const char* msg)
{
	QString qmsg = QString(msg);
	QCoreApplication::sendEvent(this, new AsciiHexLogMsgEvent::AsciiHexLogMsgEvent(qmsg));
}

void RawTextGui::ExecuteFile()
{
	bool ok;
	uint i=0;
	QByteArray ascii_hex_val;
	QByteArray response;
	QByteArray byte;
	QList<QByteArray> byte_list;
	QString qmsg_start ="Exec: ASCII Script...";
	QString qmsg_success = "Exec: ASCII Script...Success!";
	QString str = "%1 | raw bytes text: %2 tx: %3 rx: %4";
	QString qmsg;
	uint d;

	QFile file(raw_file->text());

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QCoreApplication::sendEvent(parent->parent, new BPStatusMsgEvent::BPStatusMsgEvent(qmsg_start));

	ascii_hex_val = file.readAll().trimmed();
	byte_list = ascii_hex_val.replace('\n', ' ').split(' ');

	while(!byte_list.isEmpty())
	{
		byte = byte_list.takeFirst();
		d = byte.trimmed().toUShort(&ok, 0);
		response = bp->command(d);
		qmsg = str.arg(i++, 3, 10, QChar('0')).arg(byte.data())
			.arg(d, 3, 10, QChar('0')).arg(response.toHex().data());
		QCoreApplication::sendEvent(this, new AsciiHexLogMsgEvent::AsciiHexLogMsgEvent(qmsg));
	}
	QCoreApplication::sendEvent(parent->parent, new BPStatusMsgEvent::BPStatusMsgEvent(qmsg_success));
}

PowerGui::PowerGui(MainWidgetFrame *parent) : QWidget(parent)
{
	this->parent = parent;
	bp = parent->bp;
	QVBoxLayout *vlayout = new QVBoxLayout;

	QPushButton *bbio_mode = new QPushButton("Reset BBIO Mode");
	QPushButton *hard_reset = new QPushButton("Hardware Reset - Bus Pirate");
	QPushButton *userterm_reset = new QPushButton("User Terminal Reset");
	QPushButton *enter_bbio = new QPushButton("Enter BBIO Mode");

	QPushButton *hiz_mode =  new QPushButton("Enable Hi-Z Power");
	QPushButton *normal_mode = new QPushButton("Enable Normal (3.3v) Power");
	QPushButton *open_collector = new QPushButton("Enable Open Collector (5v) Power");

	QPushButton *short_test = new QPushButton("Short Self-Test");
	QPushButton *long_test = new QPushButton("Long Self-Test");
	QPushButton *fetch_buffer = new QPushButton("Fetch Buffer Contents");
	
	connect(hiz_mode, SIGNAL(clicked()), this, SLOT(hiz_power_enable()));

	connect(bbio_mode, SIGNAL(clicked()), this, SLOT(resetBBIO()));
	connect(hard_reset, SIGNAL(clicked()), this, SLOT(hardReset()));
	connect(userterm_reset, SIGNAL(clicked()), this, SLOT(userTermReset()));
	connect(enter_bbio, SIGNAL(clicked()), this, SLOT(enterMode()));
	connect(fetch_buffer, SIGNAL(clicked()), this, SLOT(getBuffer()));

	vlayout->addWidget(bbio_mode);
	vlayout->addWidget(hard_reset);
	vlayout->addWidget(userterm_reset);
	vlayout->addWidget(enter_bbio);
	vlayout->addSpacing(50);
	vlayout->addWidget(hiz_mode);
	vlayout->addWidget(normal_mode);
	vlayout->addWidget(open_collector);
	vlayout->addSpacing(50);
	vlayout->addWidget(short_test);
	vlayout->addWidget(long_test);
	vlayout->addWidget(fetch_buffer);
	setLayout(vlayout);
}

void PowerGui::hiz_power_enable()
{
	qDebug() << "enable HiZ Power Mode";
	if (bp->reset_bbio())
	{
		/* we are in bbio mode */
	} else {
		/* we are in the user terminal */
		bp->reset_user_terminal();
		/* setup power in high-z mode here */
	}
}

void PowerGui::open_collector_power()
{
	qDebug() << "enable collector power";
}

void PowerGui::normal_power_enable()
{
	qDebug() << "enable normal power";
}

void PowerGui::hardReset()
{
	qDebug() << "Hard Reset";
	bp->reset_bbio();
	bp->reset_hardware();
}

void PowerGui::enterMode()
{
	qDebug() << "Enter Bit Banging Mode";
	bp->enter_mode_bbio();
}

void PowerGui::userTermReset()
{
	qDebug() << "User Terminal Reset";
	bp->reset_user_terminal();
}

void PowerGui::resetBBIO()
{
	qDebug() << "Reset BBIO Mode";
	bp->reset_bbio();
}

void PowerGui::setupBusPirate()
{
	qDebug() << "Setup Bus Pirate";
	bp->port_open();
	bp->reset_bbio();
	bp->reset_hardware();
	bp->reset_user_terminal();
	bp->enter_mode_bbio();	
}

void PowerGui::getBuffer()
{
	bp->dumpBuffer();
}