#pragma once
#include "Txt_File.h"
#include "Word.h"

namespace Glossary
{
	Txt_File & operator<<(Txt_File &, const Word &);
	Word_Description read_description(const std::vector<std::string> &, const std::string & english_word);
	std::pair<bool,bool> word_in_database(const std::vector<std::string> &, const std::string & english_word);
	void write_to_database(Txt_File & tf, const std::string &, bool has_descr);

}	