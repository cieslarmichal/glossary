#pragma once
#include "Txt_File.h"
#include "Word.h"
#include "Parser.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>


class Database
{
public:
	Database();

	std::pair<bool, bool> word_in_list(const std::string & english_word) const;

	void write_to_list(const std::string &, bool has_descr);

	Word_Description read_description(const std::string & english_word) const;

	void write_to_glossary(const std::string & english_word, const Word_Description & description);

	std::pair<std::string, std::string> read_word() const;

	bool is_next_word() const;

private:
	std::unique_ptr<Txt_File> list, glossary, dictionary;
	std::vector<std::string> dictionary_words;
	static int current_word;
	static const std::vector<std::string> file_names;
	enum class File_Name { list, glossary, dictionary };
};

