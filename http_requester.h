#pragma once

#include <curl\curl.h>

#include <string>
#include <unordered_map>
//	This is a simple wrapper class for the libcurl library 
//	The purpose of this class is to give a simple interface to get the content or header from a web url
//	The class allows one to create a request to get the content of a web page with an url with the newRequest(url) function
//	And to either set your own streaming callback to specify how to handle the data, or to simply get the content data as a std::string
class HttpRequester
{
public:
	HttpRequester();
	HttpRequester(bool redirect);
	HttpRequester(const char* cookieFile);
	HttpRequester(const char* cookieFile, bool redirect);
	HttpRequester(const HttpRequester& rhs) = delete;
	~HttpRequester();

	//	Debug function to print cookies
	void printCookies();
	//	Gets the content of a web page given a valid url
	void newRequest(const char* url);
	//	Allows you to create your own callback for curl to stream body data to (header data is kept in this class)
	//	The callback has to have the parameters char* for the actual data, size_t to indicate the stream size, 
	//	another size_t which multiplied with the first gives the stream size, and a void* for a userdata object to write to (You would have to manually cast it to void and back)
	void setWriteCallback(void *userdata, size_t(*callback)(char*, size_t, size_t, void*));
	//	Gets the body from the url page if no other callback has been set
	std::string getContentData();

private:
	bool debugging = false;

	std::string _headerData;
	std::string _contentData;
	std::string _httpCode;
	std::unordered_map<std::string, std::string> _headerMap;
	bool _followRedirect;
	size_t _redirectCount;
	CURL* _easyHandle;

	//	The callback used for the CURLOPT_WRITEFUNCTION setting to stream data to
	static size_t _write_callback(char *buffer, size_t size, size_t nitems, void *userdata);
	//	The callback used for the CURLOPT_HEADERFUNCTION setting to stream data to
	static size_t _header_callback(char *buffer, size_t size, size_t nitems, void *userdata);
	static void _curlGlobalInit();

	//	Function for checking the CURLcode to check if it is OK
	void _checkResult(CURLcode result, const char* function);
	void _checkForRedirect();
	//	Shorthand for setting a new curl url and checking if it is valid
	void _setUrl(const char* url);
	void _parseHeader();
	//void _resizeToContentLength(bool resetFlag = false);
	//void _resetRequest();
};