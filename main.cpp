#include "global_defines.h"
#if RUN_RECURSIVE_TESTS
	//	Handle all the testing in test_main.cpp
	#include "Tests/test_main.h"
#else

//#include "personalassistant.h"
#include "dialog_window.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	DialogWindow w;
	w.show();

	return a.exec();
}

#endif