#pragma once
#include "Word_Description.h"
#include <memory>

class Word
{
public:
	/**
	* Class parametrized constructor
	* @param english		string containing english word
	* @param polish			string containing translation of eng word
	* @param description	object containing description of word
	*/
	Word(const std::string & english, const std::string & polish, const Word_Description & description);

	/**
	* Returns english word
	* @return string containing english word
	*/
	std::string get_english() const;

	/**
	* Returns polish translation
	* @return string containing polish translation
	*/
	std::string get_polish() const;

	/**
	* Returns object cantaining description of word
	* @return description of word
	*/
	Word_Description get_description() const;

private:
	std::string english;

	std::string polish;

	std::unique_ptr<Word_Description> word_descr;
};


