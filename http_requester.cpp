#include "http_requester.h"

#include <stdio.h>
#include <iostream>
#include <type_traits>

HttpRequester::HttpRequester() : _easyHandle(curl_easy_init()), _headerData(""), _contentData("")
{
	HttpRequester::_curlGlobalInit();

	if (this->_easyHandle) {
		if (debugging)
		{
			/* Makes curl write lots of usefull stuff */
			curl_easy_setopt(this->_easyHandle, CURLOPT_VERBOSE, 1L);
		}
		

		/* Setting default options */

		// Follow redirections (doing this automaticly fucks our header map)
		//curl_easy_setopt(this->_easyHandle, CURLOPT_FOLLOWLOCATION, 1L);

		//	Setting default protocol for schemeless URLs to https
		curl_easy_setopt(this->_easyHandle, CURLOPT_DEFAULT_PROTOCOL, "https");

		//	Setting limits of allowed protocols to http and https 
		curl_easy_setopt(this->_easyHandle, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);

		// Setting header Callback data to this class 
		curl_easy_setopt(this->_easyHandle, CURLOPT_HEADERDATA, static_cast<void*>(this));

		// Setting the header Callback
		curl_easy_setopt(this->_easyHandle, CURLOPT_HEADERFUNCTION, HttpRequester::_header_callback);

		// Setting the write Callback data to this class 
		curl_easy_setopt(this->_easyHandle, CURLOPT_WRITEDATA, static_cast<void*>(this));

		// Setting the write Callback */
		curl_easy_setopt(this->_easyHandle, CURLOPT_WRITEFUNCTION, HttpRequester::_write_callback);

		// Cookies: Write to file
		//auto result = curl_easy_setopt(this->_easyHandle, CURLOPT_COOKIEJAR, cookieFile);
		//this->_checkResult(result, "CURLOPT_COOKIEJAR");

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
	this->_checkResult(result, __func__);
}

bool HttpRequester::_checkResult(CURLcode result, const char* function)
{
	if (result != CURLE_OK) {
		fprintf(stderr, "Curl error: %s\n%s",
			curl_easy_strerror(result), function);
		return false;
	}
	return true;
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

bool HttpRequester::newRequest(const char *url)
{
	this->_setUrl(url);

	this->clear();

	/* Perform the request, result will get the return code */
	auto result = curl_easy_perform(this->_easyHandle);

	if (!this->_checkResult(result, __func__))
		return false;
	
	this->_parseHeader();

	return true;
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
		return;

	//	Split the header data up with "\r\n" as the delimiter 
	std::string::size_type next = this->_headerData.find("\r\n", 0);
	std::string::size_type last = 0;

	// First we seperate the return code
	this->_httpCode = this->_headerData.substr(last, next - last);

	//	Next we iterate over the remaining key value pairs of the header, split them up by the ":" delimiter, and add them to out _headerMap
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

std::string HttpRequester::getContentData()
{
	return this->_contentData;
}

void HttpRequester::clear()
{
	this->_contentData.clear();
	this->_headerMap.clear();
	this->_httpCode.clear();
}

void HttpRequester::shrink_to_fit()
{
	this->_contentData.shrink_to_fit();
}

std::string HttpRequester::getHttpCode()
{
	return this->_httpCode;
}

std::unordered_map<std::string, std::string> HttpRequester::getHeaderMap()
{
	return this->_headerMap;
}
