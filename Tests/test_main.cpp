#include "global_defines.h"
#if RUN_RECURSIVE_TESTS

#include "Tests/test_main.h"

#include "Tests/test_initialization.h"
#include "test_http_requester.h"

#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test;
BOOST_GLOBAL_FIXTURE(TestConfigs);

test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	test_suite* httpRequesterTests = BOOST_TEST_SUITE("HttpRequester");
	httpRequesterTests->add(BOOST_TEST_CASE(&TestHttpRequester::testInitialization));
	httpRequesterTests->add(BOOST_TEST_CASE(&TestHttpRequester::testValidRequest));
	httpRequesterTests->add(BOOST_TEST_CASE(&TestHttpRequester::testInvalidRequest));
	//httpRequesterTests->add(BOOST_TEST_CASE(&TestHttpRequester::testRequest));


	framework::master_test_suite().add(httpRequesterTests);

	return 0;
}

#endif