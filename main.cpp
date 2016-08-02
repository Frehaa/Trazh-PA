#include "http_requester.h"
#include "Dependencies\TinyXML-2\tinyxml2.h"

#include <iostream>
#include <fstream>


int main(void)
{

	HttpRequester httpRequester;
	httpRequester.newRequest("https://www.reddit.com/r/anime/new.xml");

	std::string content = httpRequester.getContentData();

	tinyxml2::XMLDocument doc;
	doc.Parse(content.c_str());

	std::string text = doc.FirstChildElement("entry")->GetText();

	int t = 5;
	std::cin >> t;


	return 0;
}