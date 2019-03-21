#include "Txt_File.h"


Txt_File::Txt_File(const std::string & dir) : directory(dir), file(nullptr)
{

}

std::vector<std::string> Txt_File::get_lines()
{
	open();
	std::vector<std::string> lines;
	std::string line = "";

	while (*file && file->good() && std::getline(*file, line))
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

void Txt_File::write(const std::string & inp)
{
	open();
	if (file->good())
	{
		*file << inp;
	}
	else
	{
		throw ("error while writing");
	}
	close();
}

bool Txt_File::open()
{
	file = std::make_unique<std::fstream>(std::fstream(directory.c_str(), std::ios::in| std::ios::app));

	if (!file->is_open())
	{
		throw ("Cant open file: " + directory);
	}

	if (file->fail())
	{
		throw ("File is failing" + directory);
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

Txt_File & operator<<(Txt_File & tf, const std::string & inp)
{
	tf.open();


	if (!tf.file)
	{
		throw "nullpointer file";
	}

	if (tf.file->bad())
	{
		throw "bad file";
	}

	*(tf.file) << inp;

	tf.close();

	return tf;
}
