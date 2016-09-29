#define RUN_RECURSIVE_TESTS true
#if !RUN_RECURSIVE_TESTS

#include "personalassistant.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	PersonalAssistant w;
	w.show();

	return a.exec();
}


#else



#define BOOST_TEST_MODULE Tests
#include <boost\test\included\unit_test.hpp>
#include <fstream>

//____________________________________________________________________________//

struct MyConfig {
	MyConfig() : test_log("tests.log") { boost::unit_test::unit_test_log.set_stream(test_log); }
	~MyConfig() { boost::unit_test::unit_test_log.set_stream(std::cout); }

	std::ofstream test_log;
};

//____________________________________________________________________________//

BOOST_GLOBAL_FIXTURE(MyConfig);

BOOST_AUTO_TEST_CASE(first_test)
{
	int i = 1;
	BOOST_TEST(i);
	BOOST_TEST(i == 2);
}



#endif