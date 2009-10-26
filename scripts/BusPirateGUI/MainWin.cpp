#include <QtGui>

#include "Interface.h"
#include "OtherIface.h"
#include "BPSettings.h"
#include "BinMode.h"
#include "MainWin.h"
#include "Events.h"
MainAppWindow::MainAppWindow()
{
	/* QSplashScreen */
	createActions();
	createMenus();
	setStatusBar(new QStatusBar);
	statusBar()->showMessage("Bus Pirate Closed");
	MainWidgetFrame *frame = new MainWidgetFrame(this);
	setCentralWidget(frame);
}

void MainAppWindow::customEvent(QEvent *ev)
{
	if (static_cast<BPEventType>(ev->type()) == BPStatusMsgEvent)
	{
		statusBar()->showMessage(dynamic_cast<BPStatusMsgEvent::BPStatusMsgEvent* >(ev)->msg);
	}
}

void MainAppWindow::createActions(){}
void MainAppWindow::createMenus(){}

MainWidgetFrame::MainWidgetFrame(MainAppWindow *p) : QWidget(p)
{
	parent=p;
	tabs = new QTabWidget(p);
	cfg = new BPSettings;
	bp = new BinMode(this, cfg->serial_port_name);
	settings = new BPSettingsGui(this);
	spi = new SpiGui(this);
	i2c = new I2CGui(this);
	onewire = new OneWireGui(this);
	raw_text = new RawTextGui(this);
	power = new PowerGui(this);
	
	tabs->addTab(spi, "SPI");
	tabs->addTab(i2c, "I2C");
	tabs->addTab(onewire, "1Wire");
	tabs->addTab(raw_text, "Raw Text");
	tabs->addTab(power, "Bus Pirate");
	tabs->addTab(settings, "Settings");

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tabs);
	setLayout(mainLayout);
	setWindowTitle("QBusPirate");
}

