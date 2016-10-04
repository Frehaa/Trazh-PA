#pragma once

#include <boost/test/included/unit_test.hpp>
#include <fstream>

/*	Config struct for global fixture
 *	Changes the standard output to a logfile instead of std::cout
*/
struct TestConfigs {
	
	TestConfigs() : test_log("Tests/tests.log") 
	{
		boost::unit_test::unit_test_log.set_stream(test_log); 
	}
	~TestConfigs() 
	{ 
		boost::unit_test::unit_test_log.set_stream(std::cout); 
	}

	std::ofstream test_log;
};
