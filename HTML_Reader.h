#pragma once
#pragma comment(lib, "libcurl_a.lib")
#include "include/curl.h"
#include "Parser.h"
#include <string>
#include <sstream>
#include <iostream>

class HTML_Reader
{
public:
	HTML_Reader() = delete;
	static std::vector<std::string> read_html(const std::string & english_word);
private:
	static int writer(char *data, size_t size, size_t nmemb, std::string *writerData);
	static const std::string prefix_url;
};

