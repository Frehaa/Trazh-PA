#include "http_requester.h"

#include <stdio.h>
#include <iostream>
#include <type_traits>

HttpRequester::HttpRequester() : HttpRequester("-", true)
{}

HttpRequester::HttpRequester(bool redirect) : HttpRequester("-", true)
{}

HttpRequester::HttpRequester(const char *cookieFile) : HttpRequester(cookieFile, true)
{}

HttpRequester::HttpRequester(const char* cookieFile, bool redirect) : _easyHandle(curl_easy_init()), _headerData(""), _contentData(""), _followRedirect(redirect), _redirectCount(0)
{
	HttpRequester::_curlGlobalInit();

	if (this->_easyHandle) {
		/* Write lots of usefull shit (DEBUGGING) */
		curl_easy_setopt(this->_easyHandle, CURLOPT_VERBOSE, 1L);

		/* Setting default options */

		// Follow redirections (doing this automaticly fucks our header map)
		//this->_result = curl_easy_setopt(this->_easyHandle, CURLOPT_FOLLOWLOCATION, 1L);
		//this->_checkResult();

		// Header Callback data
		curl_easy_setopt(this->_easyHandle, CURLOPT_HEADERDATA, static_cast<void*>(this));

		// Header Callback
		curl_easy_setopt(this->_easyHandle, CURLOPT_HEADERFUNCTION, HttpRequester::_header_callback);

		// Write Callback data
		curl_easy_setopt(this->_easyHandle, CURLOPT_WRITEDATA, static_cast<void*>(this));

		// Write Callback */
		curl_easy_setopt(this->_easyHandle, CURLOPT_WRITEFUNCTION, HttpRequester::_write_callback);

		// Cookies: Write to file
		auto result = curl_easy_setopt(this->_easyHandle, CURLOPT_COOKIEJAR, cookieFile);
		this->_checkResult(result, "CURLOPT_COOKIEJAR");

		// Cookies: read from file?
		// Cookies: set cookie?
	}
	
}

HttpRequester::~HttpRequester()
{
	curl_easy_cleanup(this->_easyHandle);
}

void HttpRequester::_curlGlobalInit()
{
	static bool initialized = false;
	if (!initialized)
	{
		curl_global_init(CURL_GLOBAL_ALL);
		initialized = true;
	}
}

void HttpRequester::_setUrl(const char* url)
{
	auto result = curl_easy_setopt(this->_easyHandle, CURLOPT_URL, url);
	this->_checkResult(result, "setUrl");
}

void HttpRequester::_checkResult(CURLcode result, const char* function)
{
	if (result != CURLE_OK) {
		fprintf(stderr, "Curl error: %s\n",
			curl_easy_strerror(result));
	}
}

size_t HttpRequester::_write_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
	size_t realSize = size*nitems;

	/* Casting back to wrapper class and writing from buffer to _contentData*/
	auto wrapper = static_cast<HttpRequester*>(userdata);
	wrapper->_contentData.append(buffer, realSize);

	return realSize;
}
size_t HttpRequester::_header_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
	size_t realSize = size*nitems;

	/* Casting back to wrapper class and writing from buffer to _headerData */
	auto wrapper = static_cast<HttpRequester*>(userdata);
	wrapper->_headerData.append(buffer, realSize);

	return realSize;
}

void HttpRequester::printCookies()
{
	curl_slist *cookies;

	auto result = curl_easy_getinfo(this->_easyHandle, CURLINFO_COOKIELIST, &cookies);
	this->_checkResult(result, "printCookies");

	curl_slist_free_all(cookies);
}


void HttpRequester::newRequest(const char *url)
{
	this->_setUrl(url);

	this->_contentData.clear();

	/* Perform the request, _result will get the return code */
	auto result = curl_easy_perform(this->_easyHandle);

	/* Check for errors */
	if (result != CURLE_OK) {
		fprintf(stderr, "Curl error: %s\n",
			curl_easy_strerror(result));

		return;
	}
	
	this->_parseHeader();

	this->_checkForRedirect();

}

void HttpRequester::setWriteCallback(void* userdata, size_t(*callback)(char*, size_t, size_t, void*))
{
	// Write Callback data
	curl_easy_setopt(this->_easyHandle, CURLOPT_WRITEDATA, userdata);

	// Write Callback */
	curl_easy_setopt(this->_easyHandle, CURLOPT_WRITEFUNCTION, callback);
}

void HttpRequester::_parseHeader()
{
	if (this->_headerData.length() == 0)
	{
		return;
	}

	//	Split the header data up with "\r\n" as the delimiter 
	std::string::size_type next = this->_headerData.find("\r\n", 0);
	std::string::size_type last = 0;

	// First we seperate the return code
	this->_httpCode = this->_headerData.substr(last, next - last);

	//	Next we iterate over the remaining key value pairs of the header and add them to out _headerMap
	last = next + 2;
	next = this->_headerData.find("\r\n", last);
	for (; next != last; next = this->_headerData.find("\r\n", last))
	{
		std::string line = this->_headerData.substr(last, next - last);

		std::string::size_type delimiterIndex = line.find(":");
		std::string key = line.substr(0, delimiterIndex);
		std::string value = line.substr(delimiterIndex + 2);

		this->_headerMap[key] = value;

		//	Save current position to last while skipping the delimiter \r\n (\r\n only counts as 2 characters so we only add 2)
		last = next + 2;
	}

	//	Free some of the memory since we've moved the data over to _headerMap for easier working
	this->_headerData.clear();
	this->_headerData.shrink_to_fit();
}

void HttpRequester::_checkForRedirect()
{
	// If we didn't get any content data, the redirect flag has been set, we were supplied with and Location value in the header, and we haven't already been redirected once, we redirect and perform this again
	if (this->_contentData.length() == 0 && this->_followRedirect && this->_headerMap.find("Location") != this->_headerMap.end() && this->_redirectCount < 1)
	{
		this->_redirectCount++;
		this->newRequest(this->_headerMap["Location"].c_str());
	}
}

std::string HttpRequester::getContentData()
{
	return this->_contentData;
}