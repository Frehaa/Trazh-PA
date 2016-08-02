#pragma once

#include <curl\curl.h>

#include <string>
#include <unordered_map>

class HttpRequester
{
public:
	HttpRequester();
	HttpRequester(bool redirect);
	HttpRequester(const char* cookieFile);
	HttpRequester(const char* cookieFile, bool redirect);
	HttpRequester(const HttpRequester& rhs) = delete;
	~HttpRequester();

	void printCookies();
	void newRequest(const char* url);
	std::string getContentData();

private:
	std::string _headerData;
	std::string _contentData;
	std::string _httpCode;
	std::unordered_map<std::string, std::string> _headerMap;
	bool _followRedirect;
	size_t _redirectCount;
	CURL* _easyHandle;

	static size_t _write_callback(char *buffer, size_t size, size_t nitems, void *userdata);
	static size_t _header_callback(char *buffer, size_t size, size_t nitems, void *userdata);
	static void _curlGlobalInit();

	void _checkResult(CURLcode result, const char* function);
	void _checkForRedirect();
	void _setUrl(const char* url);
	void _parseHeader();
	//void _resizeToContentLength(bool resetFlag = false);
	//void _resetRequest();
};