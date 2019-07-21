#include "Txt_File.h"


Txt_File::Txt_File(const std::string & path) : access_path(path), file(nullptr)
{
}

std::vector<std::string> Txt_File::get_lines()
{
	open();
	std::vector<std::string> lines;
	std::string line;

	while (file->good() && std::getline(*file, line))
	{
		lines.push_back(line);
	}
	if (file->bad())
	{
		throw ("error while reading data");
	}

	close();
	return lines;
}

void Txt_File::write(const std::string & data)
{
	open();
	if (file->good())
	{
		*file << data;
	}
	else
	{
		throw ("error while writing");
	}
	close();
}

bool Txt_File::open()
{
	file = std::make_unique<std::fstream>(std::fstream(access_path.c_str(), std::ios::in| std::ios::app));

	if (!file->is_open())
	{
		throw ("Cant open file: " + access_path);
	}

	if (file->fail())
	{
		throw ("File is failing" + access_path);
	}

	return true;
}

void Txt_File::close()
{
	if (file)
	{
		file->close();
	}
}

Txt_File & Txt_File::operator<<(const std::string & data)
{
	open();

	if (!file)
	{
		throw "nullpointer file";
	}

	if (file->bad())
	{
		throw "bad file";
	}

	*(file) << data;

	close();

	return *this;
}
