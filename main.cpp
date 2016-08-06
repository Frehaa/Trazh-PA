#include "personalassistant.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PersonalAssistant w;
	w.show();
	return a.exec();
}
