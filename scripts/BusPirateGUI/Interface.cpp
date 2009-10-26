#include <QtGui>
#include "miscellanous.h"
#include "BinMode.h"
#include "BPSettings.h"
#include "MainWin.h"
#include "Interface.h"
#include "Events.h"
/* Interface: SPI */
SpiGui::SpiGui(MainWidgetFrame *p) : QWidget(p)
{
	parent=p;
	bp = p->settings->bp;

	QLabel *file_label = new QLabel("File: ");
	QLabel *log_label = new QLabel("Log: ");

	QPushButton *read_btn = new QPushButton("Read SPI");
	QPushButton *write_btn = new QPushButton("Write SPI");
	QPushButton *chip_id_btn = new QPushButton("SPI Chip ID");

	spi_file = new QLineEdit;
	msglog = new QTextEdit;
	msglog->setReadOnly(true);

	QVBoxLayout *vlayout = new QVBoxLayout;
	QHBoxLayout *hlayout = new QHBoxLayout;

	connect(read_btn, SIGNAL(clicked()), this, SLOT(read_spi()));
	connect(write_btn, SIGNAL(clicked()), this, SLOT(write_spi()));
	connect(chip_id_btn, SIGNAL(clicked()), this, SLOT(spi_chip_id()));

	vlayout->addWidget(file_label);
	vlayout->addWidget(spi_file);

	hlayout->addWidget(read_btn);
	hlayout->addWidget(write_btn);
	hlayout->addWidget(chip_id_btn);
	
	vlayout->addLayout(hlayout);
	vlayout->addSpacing(50);
	vlayout->addWidget(log_label);
	vlayout->addWidget(msglog);

	setLayout(vlayout);
}

void SpiGui::read_spi(void)
{}

void SpiGui::write_spi(void)
{}

void SpiGui::spi_chip_id(void)
{
	QString qmsg_start = QString("Getting SPI Chip Id...");
	QString qmsg_fail = QString("Getting SPI Chip Id...Failed");
	QString qmsg_success = QString("Getting SPI Chip Id...Success!");

	QCoreApplication::sendEvent(parent->parent, new BPStatusMsgEvent::BPStatusMsgEvent(qmsg_start));
	postMsgEvent("JEDEC Chip ID");
	int ret = 0, i = 0;
	char *data_byte = "\x9F\x00\x00\x00";
	char *chip_id;
	
	ret = bp->enter_mode_spi();
	if (ret)
	{
		postMsgEvent("SPI OK.");
	} else {
		postMsgEvent("SPI Failed.");
		goto err;
	}
	
	ret = bp->bbio_peripherial_set(0x0B);
	if (ret)
	{
		postMsgEvent("Peripherial Config Ok.");
	} else {
		postMsgEvent("Peripherial Config Failed.");
		goto err;
	}
	
	ret = bp->bbio_speed_set(0x06);
	if (ret)
	{
		postMsgEvent("SPI Speed Config Ok.");
	} else {
		postMsgEvent("SPI Speed Config Failed.");
		goto err;
	}
	
	ret = bp->spi_configure_set(0x08);
	if (ret)
	{
		postMsgEvent("SPI Config Ok.");
	} else {
		postMsgEvent("SPI Config Failed.");
		goto err;
	}
	
	ret = bp->spi_cs_low();
	if (ret)
	{
		postMsgEvent("CS Low: Ok.");
	} else {
		postMsgEvent("CS Low: Failed.");
	}
	
	chip_id = bp->bbio_bulk_trans(data_byte, sizeof(data_byte));
	if (chip_id != NULL)
	{
		postMsgEvent("ChipID:");
		for (i = 0; i < sizeof(chip_id); ++i)  postMsgEvent(QString("0x%1 ").arg((int)chip_id[i], 0, 16).toAscii());
	} else {
		postMsgEvent("ChipID: Failed!");
	}
	
	ret = bp->spi_cs_high();
	if (ret)
	{
		postMsgEvent("CS High: Ok.");
	} else {
		postMsgEvent("CS High: Failed.");
	}
	
	ret = bp->reset_bbio();
	if (ret)
	{
		postMsgEvent("Reset to BBIO mode: Ok.");
	} else {
		postMsgEvent("Reset to BBIO mode: Failed.");
	}
	QCoreApplication::sendEvent(parent->parent, new BPStatusMsgEvent::BPStatusMsgEvent(qmsg_success));
	return;	
err:
	QCoreApplication::sendEvent(parent->parent, new BPStatusMsgEvent::BPStatusMsgEvent(qmsg_fail));
	return;
}

void SpiGui::customEvent(QEvent *ev)
{
	if (static_cast<BPEventType>(ev->type()) == SpiLogMsgEvent)
	{
		msglog->append(dynamic_cast<SpiLogMsgEvent::SpiLogMsgEvent* >(ev)->msg);
	}
}

void SpiGui::postMsgEvent(const char* msg)
{
	QString qmsg = QString(msg);
	QCoreApplication::sendEvent(this, new SpiLogMsgEvent::SpiLogMsgEvent(qmsg));
}

/* Interface: I2C */
I2CGui::I2CGui(MainWidgetFrame *p) : QWidget(p)
{
	parent = p;
	bp = p->settings->bp;

	QLabel *file_label = new QLabel("File: ");
	QLabel *device_label = new QLabel("Device: ");
	QLabel *log_label = new QLabel("Log: ");

	QPushButton *scan = new QPushButton("Scan I2C");
	QPushButton *read_btn = new QPushButton("Read I2C");
	QPushButton *write_btn = new QPushButton("Write I2C");
	
	device_addr = new QLineEdit;
	spi_file = new QLineEdit;
	msglog = new QTextEdit;
	msglog->setReadOnly(true);
	
	QVBoxLayout *vlayout = new QVBoxLayout;
	QHBoxLayout *hlayout = new QHBoxLayout;
	
	hlayout->addWidget(scan);
	hlayout->addWidget(read_btn);
	hlayout->addWidget(write_btn);
	
	vlayout->addWidget(file_label);
	vlayout->addWidget(spi_file);
	vlayout->addWidget(device_label);
	vlayout->addWidget(device_addr);
	vlayout->addLayout(hlayout);
	vlayout->addSpacing(50);
	vlayout->addWidget(log_label);
	vlayout->addWidget(msglog);
	
	setLayout(vlayout);
}

void I2CGui::search_i2c()
{
	QString dev_addr;
	QString qmsg_start ="Getting I2C Devices...";
	QString qmsg_success = "Getting I2C Devices...Success!";
	int i = 0, dev=0, addr=0;
	char rw;
	QCoreApplication::sendEvent(parent->parent, new BPStatusMsgEvent::BPStatusMsgEvent(qmsg_start));
	for (i=0; i<0x100; i++)
	{
		dev = i;
		addr = i>>1;

		bp->i2c_start();
		bp->serial->write((char*)&dev, 1);
		bp->i2c_byte_read();
		if ((addr & 0x01)==0) 
		{
			rw = 'W';
		} else {
			bp->i2c_byte_read();
			bp->i2c_ack_send();
			rw = 'R';
		}
		bp->i2c_stop();

		dev_addr = QString("%1 (%2 %3)").arg(dev, 0, 16).arg(addr, 0, 16).arg(rw);
		postMsgEvent(dev_addr.toAscii());
	}
	QCoreApplication::sendEvent(parent->parent, new BPStatusMsgEvent::BPStatusMsgEvent(qmsg_success));
}

void I2CGui::customEvent(QEvent *ev)
{
	if (static_cast<BPEventType>(ev->type()) == I2CLogMsgEvent)
	{
		msglog->append(dynamic_cast<I2CLogMsgEvent::I2CLogMsgEvent* >(ev)->msg);
	}
}

void I2CGui::postMsgEvent(const char* msg)
{
	QString qmsg = QString(msg);
	QCoreApplication::sendEvent(this, new I2CLogMsgEvent::I2CLogMsgEvent(qmsg));
}

OneWireGui::OneWireGui(MainWidgetFrame *p) : QWidget(p)
{
	QLabel *file_label = new QLabel("File: ");
	QLabel *device_label = new QLabel("Device: ");
	QLabel *log_label = new QLabel("Log: ");

	QPushButton *scan = new QPushButton("Scan 1Wire");
	QPushButton *read_btn = new QPushButton("Read 1Wire");
	QPushButton *write_btn = new QPushButton("Write 1Wire");
	
	device_addr = new QLineEdit;
	spi_file = new QLineEdit;
	msglog = new QTextEdit;
	msglog->setReadOnly(true);
	
	QVBoxLayout *vlayout = new QVBoxLayout;
	QHBoxLayout *hlayout = new QHBoxLayout;
	
	hlayout->addWidget(scan);
	hlayout->addWidget(read_btn);
	hlayout->addWidget(write_btn);
	
	vlayout->addWidget(file_label);
	vlayout->addWidget(spi_file);
	vlayout->addWidget(device_label);
	vlayout->addWidget(device_addr);
	vlayout->addLayout(hlayout);
	vlayout->addSpacing(50);
	vlayout->addWidget(log_label);
	vlayout->addWidget(msglog);
	
	setLayout(vlayout);
}

void OneWireGui::customEvent(QEvent *ev)
{
	if (static_cast<BPEventType>(ev->type()) == OneWireLogMsgEvent)
	{
		msglog->append(dynamic_cast<OneWireLogMsgEvent::OneWireLogMsgEvent* >(ev)->msg);
	}
}

void OneWireGui::postMsgEvent(const char* msg)
{
	QString qmsg = QString(msg);
	QCoreApplication::sendEvent(this, new OneWireLogMsgEvent::OneWireLogMsgEvent(qmsg));
}
