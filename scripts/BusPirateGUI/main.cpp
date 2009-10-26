#include <QtGui>

#include "MainWin.h"

int main(int argc, char *argv[])
{
	MainAppWindow *win;
	QApplication app(argc, argv);

	app.setApplicationName("QBusPirate");
	app.setOrganizationName("Sean Nelson");

	win = new MainAppWindow;
	win->show();
	return app.exec();
}
