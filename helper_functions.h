#pragma once

#include <string>

// Shorthand function for string find + replace
std::string& stringReplace(std::string &str, const std::string &oldText, const std::string &newText);

// Shorthand function for string find + replace over multiple iterations
std::string& stringReplaceAll(std::string &str, const std::string &oldText, const std::string &newText);