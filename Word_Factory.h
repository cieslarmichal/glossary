#pragma once
#include "Database.h"
#include "HTML_Parser.h"

class Word_Factory
{
public:
	/**
	* Class default constructor
	* Takes ownership of instance of Database class
	*/
	Word_Factory();

	/**
	* Generates instances of Word by database
	* or internet connection 
	* @return vector of made Words 
	*/
	std::vector<Word> generate_words();

private:
	// respectively english, polish word
	Word make_word(const std::pair<std::string, std::string> &);

	std::unique_ptr<Database> database;
};


