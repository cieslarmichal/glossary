#pragma once
#include "Txt_File.h"
#include "Word.h"

namespace Glossary
{
	Txt_File & operator<<(Txt_File &, const Word &);
	Word_Description read_description(const std::vector<std::string> &, const std::string & english_word);


}	