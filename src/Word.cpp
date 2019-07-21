#include "Word.h"


Word::Word(const std::string & english_word, const std::string & polish_trans, const Word_Description & wd) 
	:english(english_word), polish(polish_trans)
{
	word_descr = std::make_unique<Word_Description>(Word_Description(wd));

}

std::string Word::get_english() const
{
	return english;
}

std::string Word::get_polish() const
{
	return polish;
}

Word_Description Word::get_description() const
{
	return *word_descr;
}


