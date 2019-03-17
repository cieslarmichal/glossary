#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

class Parser
{
public:
	Parser() = delete;
	static std::vector<std::string> parser_v0(const std::string &);
	static std::string cut_off_string(const std::string & line, size_t start_position, size_t end_position);
private:
	static std::string clean_line(const std::string &);
	static std::string remove_spaces(const std::string &);
};

