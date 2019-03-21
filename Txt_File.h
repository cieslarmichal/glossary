#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class Txt_File
{
public:
	Txt_File(const std::string & dir);
	std::vector<std::string> get_lines();
	void write(const std::string &);
	friend Txt_File & operator<<(Txt_File &, const std::string &);
private:
	std::unique_ptr<std::fstream> file;
	std::string directory;
	bool open();
	void close();
};

