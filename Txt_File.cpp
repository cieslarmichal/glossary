#include "Txt_File.h"



Txt_File::Txt_File(const std::string & dir) : directory(dir)
{
	open();
}

Txt_File::~Txt_File()
{
	close();
}

std::vector<std::string> Txt_File::getLines()
{
	try
	{
		open();
	}
	catch (std::string error)
	{
		std::cerr << error << std::endl;
		return std::vector<std::string>();
	}

	std::vector<std::string> lines;
	std::string line = "";

	while (file->good() && std::getline(*file, line))
	{
		lines.push_back(line);
	}

	close();
	return lines;
}

bool Txt_File::open()
{
	file = new std::fstream(directory.c_str(), std::ios::in| std::ios::out);

	if (!file->is_open())
	{
		throw ("Cant open file: " + directory);
	}

	if (file->fail())
	{
		throw ("File is failing" + directory);
	}

	return file->good();
}

void Txt_File::close()
{
	file->close();
	delete file;
}
