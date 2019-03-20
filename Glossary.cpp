#include "Glossary.h"

Txt_File & Glossary::operator<<(Txt_File & tf, const Word & word)
{
	*(tf.get_file()) << "$" << word.get_english() << std::endl;

	for (auto def_eg : word.get_description().definitions_examples)
	{
		*(tf.get_file()) << def_eg.first << std::endl;
		*(tf.get_file()) << "~eg" << def_eg.second << std::endl;
	}

	for (auto sentc : word.get_description().sentences)
	{
		*(tf.get_file()) << "~st" << sentc << std::endl;
	}

	*(tf.get_file()) << std::endl;
	return tf;
}

//not ready yet
Word_Description Glossary::read_description(const std::vector<std::string> & lines, const std::string & english_word)
{
	Word_Description wd;
	std::string def, eg, sentc;
	std::string line;

	bool allow_read = false;
	bool eg_next = false;

	for (int index = 0; index < lines.size(); ++index)
	{
		line = lines.at(index);
		//std::cout << index<<": "<<line <<allow_read<< std::endl;

		if ((line.size() >= 1) && (line.at(0) == '$') && allow_read)
		{
			break;
		}

		if ((line.size() > english_word.size()) && line == ("$" + english_word))
		{

			std::cout << "$$$$$$$$$" << line << std::endl;

			allow_read = true;
			continue;
		}

		if (allow_read && (line.size() >= 1) && (line.at(0) == ':'))
		{
			std::cout << "DEF" << line << std::endl;

			def = line;
			eg_next = true;
			continue;

		}

		if (allow_read && (line.size() >= 3) && (line.substr(0, 3) == "~eg"))
		{
			std::cout << "EG" << line << std::endl;

			eg = Parser::cut_off_string(line, 0, 2);
			wd.definitions_examples.push_back(std::make_pair(def, eg));
			continue;

		}

		if (allow_read && (line.size() >= 3) && (line.substr(0, 3) == "~st"))
		{
			sentc = Parser::cut_off_string(line, 0, 2);
			wd.sentences.push_back(sentc);
			continue;

		}



	}

	return wd;
}

std::pair<bool, bool> Glossary::word_in_database(const std::vector<std::string>& database, const std::string & english_word)
{
	bool is_in_database = false;
	bool has_description = false;

	std::string word;

	for (auto line : database)
	{
		std::stringstream ss(line);
		ss >> word;
		if (word == english_word)
		{
			is_in_database = true;
			ss >> has_description;
			break;
		}
	}
}

void Glossary::write_to_database(Txt_File & tf, const std::string & word, bool has_descr)
{
	*(tf.get_file()) << word << " " << has_descr << std::endl;
}
