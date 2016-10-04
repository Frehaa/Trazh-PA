#include "Tests/test_main.h"

//#include "Tests/test_initialization.h"
#include "test_http_requester.h"

#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test;
//BOOST_GLOBAL_FIXTURE(TestConfigs);

test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	test_suite* httpRequesterTests = BOOST_TEST_SUITE("httpRequester");
	//httpRequesterTests->add(BOOST_TEST_CASE(&TestHttpRequester::testValidUrl));



	framework::master_test_suite().add(httpRequesterTests);

	return 0;
}