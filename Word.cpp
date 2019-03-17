#include "Word.h"


Word::Word(const std::string & english_word, const std::string & polish_trans) :english(english_word), polish(polish_trans),
	word_descr(Parser::parser_v0((HTML_Reader::read_html("https://www.merriam-webster.com/dictionary/" + english_word))))
{
	
}
