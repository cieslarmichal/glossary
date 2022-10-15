#pragma once

#include "dictionaryService/Dictionary.h"

namespace glossary
{
using DictionaryWord = dictionary::DictionaryWord;
using std::vector<DictionaryWord> = dictionary::std::vector<DictionaryWord>;
using std::string = std::string;
using std::vector<std::string> = dictionary::std::vector<std::string>;
using Dictionary = dictionary::Dictionary;
using Dictionaries = dictionary::Dictionaries;
}