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
	framework::master_test_suite().p_name.value = "Master test suite";

	/* Tests for HttpRequester*/
	test_suite* httpRequesterTests = BOOST_TEST_SUITE("HttpRequester");

	//	Independant tests
	httpRequesterTests->add(BOOST_TEST_CASE(&TestHttpRequester::testInitialization));
	httpRequesterTests->add(BOOST_TEST_CASE(&TestHttpRequester::testInvalidRequest));
	httpRequesterTests->add(BOOST_TEST_CASE(&TestHttpRequester::testRedirectRequest));

	//	Dependent tests
	test_unit* testValidRequest = BOOST_TEST_CASE(&TestHttpRequester::testValidRequest);
	test_unit* testClear =	 BOOST_TEST_CASE(&TestHttpRequester::testClear);
	test_unit* testClearOnRepeatedRequests = BOOST_TEST_CASE(&TestHttpRequester::testClearOnRepeatedRequests);
	httpRequesterTests->add(testValidRequest);

	testClear->depends_on(testValidRequest);
	httpRequesterTests->add(testClear);

	testClearOnRepeatedRequests->depends_on(testClear);
	httpRequesterTests->add(testClearOnRepeatedRequests);


	/* Tests for ******* */

	/* Add test suites to the master suite */
	framework::master_test_suite().add(httpRequesterTests);

	return 0;
}

#endif