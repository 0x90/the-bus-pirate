#include <QtGui>
#include "miscellanous.h"
#include "BinMode.h"
#include "BPSettings.h"
#include "MainWin.h"
#include "Interface.h"

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
	parent->parent->statusBar()->showMessage("Getting SPI Chip Id...");
	qWarning() << "JEDEC Chip ID";
	int ret = 0, i = 0;
	char *data_byte = "\x9F\x00\x00\x00";
	char *chip_id;
	
	ret = bp->enter_mode_spi();
	if (ret)
	{
		qWarning() << "SPI OK.";
	} else {
		qCritical() << "SPI Failed.";
		goto e;
	}
	
	ret = bp->bbio_peripherial_set(0x0B);
	if (ret)
	{
		qWarning() << "Peripherial Config Ok.";
	} else {
		qCritical() << "Peripherial Config Failed.";
		goto e;
	}
	
	ret = bp->bbio_speed_set(0x06);
	if (ret)
	{
		qWarning() << "SPI Speed Config Ok.";
	} else {
		qCritical() << "SPI Speed Config Failed.";
		goto e;
	}
	
	ret = bp->spi_configure_set(0x08);
	if (ret)
	{
		qWarning() << "SPI Config Ok.";
	} else {
		qCritical() << "SPI Config Failed.";
		goto e;
	}
	
	ret = bp->spi_cs_low();
	if (ret)
	{
		qWarning() << "CS Low: Ok.";
	} else {
		qCritical() << "CS Low: Failed.";
	}
	
	chip_id = bp->bbio_bulk_trans(data_byte, sizeof(data_byte));
	if (chip_id != NULL)
	{
		qWarning() << "ChipID:";
		for (i = 0; i < sizeof(chip_id); ++i)  qWarning() << QString("0x%1 ").arg((int)chip_id[i], 0, 16);
	} else {
		qCritical() << "ChipID: Failed!";
	}
	
	ret = bp->spi_cs_high();
	if (ret)
	{
		qWarning() << "CS High: Ok.";
	} else {
		qCritical() << "CS High: Failed.";
	}
	
	ret = bp->reset_bbio();
	if (ret)
	{
		qWarning() << "Reset to BBIO mode: Ok.";
	} else {
		qCritical() << "Reset to BBIO mode: Failed.";
	}
e:
	parent->parent->statusBar()->showMessage("Bus Pirate Ready.");
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
	int i = 0;
	char rw;
	for (i=0; i<0x100; i++)
	{
		bp->i2c_start();
		bp->serial->write((char*)&i, 1);
		bp->i2c_byte_read();
		msglog->append(QString("%1 (%2 ").arg(i, 0, 16).arg(i>>1, 0, 16));
		if ((i & 0x01)==0) 
		{
			rw = 'W';
		} else {
			bp->i2c_byte_read();
			bp->i2c_ack_send();
			rw = 'R';
		}
		msglog->insertPlainText(QString("%1)\n").arg(rw));
		bp->i2c_stop();
	}
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

