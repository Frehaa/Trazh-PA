#include "helper_functions.h"

std::string& stringReplace(std::string &str, const std::string &oldText, const std::string &newText)
{
	auto pos = str.find(oldText);

	if (pos != std::string::npos)
	{
		str.replace(pos, oldText.length(), newText);
	}
	
	return str;
}

std::string& stringReplaceAll(std::string &str, const std::string &oldText, const std::string &newText)
{
	std::string newStr(str);

	for (std::string::size_type pos = str.find(oldText), oldPos = 0; pos != std::string::npos; pos = str.find(oldText, oldPos))
	{
		str.replace(pos, oldText.length(), newText);

		oldPos = pos + oldText.length();
	}


	return newStr;
}