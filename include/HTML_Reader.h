#pragma once
#pragma comment(lib, "libcurl_a.lib")

#include "curl.h"
#include <string>

class HTML_Reader
{
public:
	/**
	* Default constructor is inaccessible.
	*/
	HTML_Reader() = delete;

	/**
	* Reads HTML file and converts content into string
	* @param url_address	string containing full URL address
	* @return string with HTML content
	*/
	static std::string read_html(const std::string & url_address);

private:
	static int writer(char *data, size_t size, size_t nmemb, std::string *writerData);
};


