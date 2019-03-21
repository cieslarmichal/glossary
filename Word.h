#pragma once
#include "Word_Description.h"
#include <memory>

class Word
{
public:
	Word(const std::string & english_word, const std::string & polish_trans, const Word_Description &);
	std::string get_english() const;
	std::string get_polish() const;
	Word_Description get_description() const;
private:
	std::string english;
	std::string polish;
	std::unique_ptr<Word_Description> word_descr;
};
