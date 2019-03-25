#pragma once
#include "Database.h"
#include "HTML_Parser.h"

class Word_Factory
{
public:
	/**
	* Default constructor is inaccessible.
	*/
	Word_Factory() = delete;

	/**
	* Generates instances of Word by database
	* or internet connection 
	* @return vector of made Words 
	*/
	static std::vector<Word> generate_words();

private:
	// respectively english, polish word
	static Word make_word(const std::pair<std::string, std::string> &);

	static std::unique_ptr<Database> database;
};


