#pragma once
#include <vector>
#include <iostream>
#include <sstream>

class Parser
{
public:
	Parser() = delete;
	static std::vector<std::string> parser_v0(const std::string &&);
	static void cut_off_string(std::string & line, size_t start_position, size_t end_position);
private:
	static std::string clean_line(const std::string &);
};

