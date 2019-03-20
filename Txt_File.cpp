#include "Txt_File.h"


Txt_File::Txt_File(const std::string & dir) : directory(dir)
{
	try
	{
		open();
	}
	catch (std::string error)
	{
		std::cerr << error << std::endl;
	}
}

Txt_File::~Txt_File()
{
	try
	{
		close();
	}
	catch (std::string error)
	{
		std::cerr << error << std::endl;
	}
}

std::vector<std::string> Txt_File::get_lines()
{
	std::vector<std::string> lines;
	std::string line = "";

	while (file->good() && std::getline(*file, line))
	{
		lines.push_back(line);
	}

	return lines;
}

std::fstream * Txt_File::get_file()
{
	return file;
}

bool Txt_File::open()
{
	file = new std::fstream(directory.c_str(), std::ios::in| std::ios::app);

	if (!file->is_open())
	{
		throw ("Cant open file: " + directory);
	}

	if (file->bad())
	{
		throw ("File is failing" + directory);
	}

	return file->good();
}

void Txt_File::close()
{
	if (file->bad())
	{
		throw ("bad file in closure " + directory);

	}
	if (file)
	{
		file->close();
		delete file;
	}
}
