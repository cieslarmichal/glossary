#pragma once
#include "Word_Description.h"
#include "Parser.h"
#include "HTML_Reader.h"

class Word
{
public:
	Word(const std::string & english_word, const std::string & polish_trans);
private:
	std::string english;
	std::string polish;
	Word_Description word_descr;
};

