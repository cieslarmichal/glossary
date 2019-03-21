#include "Database.h"

int Database::current_word{ 0 };

const std::vector<std::string> Database::file_names
{
	"database/list.txt",
	"database/glossary.txt",
	"database/dictionary.txt"
};

Database::Database()
{
	list = std::make_unique<Txt_File>(Txt_File(file_names.at((int)Database::File_Name::list)));
	glossary = std::make_unique<Txt_File>(Txt_File(file_names.at((int)Database::File_Name::glossary)));
	dictionary = std::make_unique<Txt_File>(Txt_File(file_names.at((int)Database::File_Name::dictionary)));

	dictionary_words = dictionary->get_lines();
}


std::pair<bool, bool> Database::word_in_list(const std::string & english_word) const
{
	bool is_in_database = false;
	bool has_description = false;

	std::string word;

	for (auto line : list->get_lines())
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

	return std::make_pair(is_in_database, has_description);
}

void Database::write_to_list(const std::string & word, bool has_descr)
{
	*list << word << " " << std::to_string(has_descr) << "\n";
}

std::pair<std::string, std::string> Database::read_word() const
{
	if (current_word >= dictionary_words.size())
	{
		throw "no more words in dictionary file";
	}

	std::stringstream line(dictionary_words.at(current_word));
	std::string english, polish;

	line >> english >> polish;

	current_word++;

	return std::make_pair(english, polish);
}

bool Database::is_next_word() const
{
	return (current_word < dictionary->get_lines().size());
}

Word_Description Database::read_description(const std::string & english_word) const
{
	Word_Description description;
	std::string def, eg, sentc;
	std::string line;

	bool allow_read = false;
	bool eg_next = false;

	std::vector<std::string> lines(glossary->get_lines());

	for (int index = 0; index < lines.size(); ++index)
	{
		line = lines.at(index);

		if ((line.size() >= 1) && (line.at(0) == '$') && allow_read)
		{
			break;
		}

		if ((line.size() > english_word.size()) && line == ("$" + english_word))
		{
			allow_read = true;
			continue;
		}

		if (allow_read && (line.size() >= 1) && (line.at(0) == ':'))
		{
			def = line;
			eg_next = true;
		}

		if (allow_read && (line.size() >= 3) && (line.substr(0, 3) == "~eg"))
		{
			eg = Parser::cut_off_string(line, 0, 2);
			description.definitions_examples.push_back(std::make_pair(def, eg));
		}

		if (allow_read && (line.size() >= 3) && (line.substr(0, 3) == "~st"))
		{
			sentc = Parser::cut_off_string(line, 0, 2);
			description.sentences.push_back(sentc);
		}
	}

	return description;
}

void Database::write_to_glossary(const std::string & english_word, const Word_Description & description)
{

	*glossary << "$" << english_word << "\n";

	for (auto def_eg :description.definitions_examples)
	{
		*glossary << def_eg.first << "\n";
		*glossary << "~eg" << def_eg.second << "\n";
	}

	for (auto sentc : description.sentences)
	{
		*glossary << "~st" << sentc << "\n";
	}

	*glossary << "\n";
}

