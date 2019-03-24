#pragma once
#include "Txt_File.h"
#include "String_Additives.h"
#include "Word.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>


class Database
{
public:
	/**
	* Class default constructor
	* Makes unique pointers point to the corresponding txt file
	*/
	Database();

	/**
	* Checks if given word occurs in database's list and if has a description
	* @param	string containing english word
	* @return	pair of bool, respectively if occurs, if has a description
	*/
	std::pair<bool, bool> word_in_list(const std::string &) const;

	/**
	* Writes word and if has a description to database's list
	* @param word			string containing english word
	* @param description	if word has adescription
	*/
	void write_to_list(const std::string & word, bool description);

	/**
	* Reads description of given word from database's glossary
	* @param string containing english word
	* @return description provided by Word_Description instance
	*/
	Word_Description read_description(const std::string &) const;

	/**
	* Writes a word and its description to database's glossary
	* @param word			string containing english word
	* @param description	description of word by Word_Description instance
	*/
	void write_to_glossary(const std::string & word, const Word_Description & description);

	/**
	* Reads next word from database's dictionary
	* @return pair of strings containing respectively:
	* english word and polish translation
	*/
	std::pair<std::string, std::string> read_word() const;

	/**
	* Checks if there is an available word in database's dictionary
	* also immadiately checks if a word is empty, if so checks another one
	* @return if there is another word that can be read
	*/
	bool is_next_word() const;

private:
	std::unique_ptr<Txt_File> list, glossary, dictionary;

	static const std::vector<std::string> file_names;

	enum class File_Name { list, glossary, dictionary };

private:
	std::vector<std::string> dictionary_words;

	bool is_line_word(const std::string &) const;

	static int current_word;
};

