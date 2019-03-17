#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class Txt_File
{
public:
	Txt_File(const std::string & dir);
	~Txt_File();
	std::vector<std::string> getLines();
private:
	std::fstream * file;
	std::string directory;
	bool open();
	void close();
};

