#pragma once
#include "HTML_Reader.h"
#include "String_Additives.h"
#include <vector>
#include <iostream>
#include <sstream>

class HTML_Parser
{
public:
	/**
	* Default constructor is inaccessible.
	*/
	HTML_Parser() = delete;

	/**
	* Filters "https://www.merriam-webster.com/dictionary/some_word" html file
	* and adds glossary's labels: ":" definition, "~eg" example, "~st" sentence
	* @param english_word	string containing english_word
	* @return filtered, separated lines, containing glossary's labels
	*/
	static std::vector<std::string> filter_lines(const std::string & english_word);

private:
	static std::string remove_html_tags(const std::string &);

	static const std::string prefix_url;
};


