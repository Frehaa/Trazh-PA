#pragma once

#include "http_requester.h"

#include <boost/test/included/unit_test.hpp>

/*	Test class for HttpRequester
 *	The class is used to organise our different tests  
 *	Since this header will only be included once, and because if it has any .cpp file associated with it boost fucks up (?)
 *		We define all our tests in the header after we have declared them
*/
class TestHttpRequester 
{
public:
	static void testInitialization();
	static void testValidRequest();
	static void testInvalidRequest();
	static void testClear();
	static void testClearOnRepeatedRequests();
	static void testRedirectRequest();
private:
	static void testEmpty(HttpRequester &requester);
	
};


//	Testing for initialization errors
void TestHttpRequester::testInitialization()
{
	HttpRequester requester;
	testEmpty(requester);
}

void TestHttpRequester::testValidRequest()
{
	HttpRequester requester;
	requester.newRequest("http://www.example.com/");
	//	Test there isn't any content
	BOOST_TEST(requester.getContentData().length() != 0);
	//	Test there isn't any http code 
	BOOST_TEST(requester.getHttpCode().length() != 0);
	//	Test there isn't any header data 
	BOOST_TEST(requester.getHeaderMap().empty() != true);

}

void TestHttpRequester::testInvalidRequest()
{
	HttpRequester requester;
	//	Test invalid url
	BOOST_TEST(requester.newRequest("Obviously invalid url") == false);
	testEmpty(requester);
	//	Test valid url on non existing siet
	BOOST_TEST(requester.newRequest("http://test.test/") == false);
	testEmpty(requester);


}

void TestHttpRequester::testEmpty(HttpRequester& requester)
{
	//	Test there isn't any content
	BOOST_TEST(requester.getContentData().length() == 0);
	//	Test there isn't any http code 
	BOOST_TEST(requester.getHttpCode().length() == 0);
	//	Test there isn't any header data 
	BOOST_TEST(requester.getHeaderMap().empty() == true);
}

void TestHttpRequester::testClear()
{
	HttpRequester requester;
	requester.newRequest("http://www.example.com/");
	requester.clear();
	testEmpty(requester);
}

void TestHttpRequester::testClearOnRepeatedRequests()
{
	HttpRequester requester;
	//	Start with a valid request we know works
	requester.newRequest("http://www.example.com/");
	//	Follow up with a request we know should leave requester empty
	requester.newRequest("Obviously invalid url");
	testEmpty(requester);


}
//	Test redirects
void TestHttpRequester::testRedirectRequest()
{
	HttpRequester requester;
	//	www.fb.com redirects to https://www.facebook.com
	requester.newRequest("www.fb.com");
	//	Test there isn't any content
	BOOST_TEST(requester.getContentData().length() == 0);
	//	Test there is an http code 
	BOOST_TEST(requester.getHttpCode().length() != 0);
	//	Test there is header data 
	BOOST_TEST(requester.getHeaderMap().empty() == false);

}