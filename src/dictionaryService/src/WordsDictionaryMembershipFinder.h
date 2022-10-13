#pragma once

#include "Dictionary.h"

namespace glossary::dictionaryService
{
class WordsDictionaryMembershipFinder
{
public:
    DictionaryNames findDictionariesContainingEnglishWord(const std::string&, const Dictionaries&) const;
    DictionaryNames
    findDictionariesContainingEnglishWordTranslation(const std::string& englishWordTranslation,
                                                     const Dictionaries&) const;

private:
    bool englishWordExistsInDictionary(const std::string&, const Dictionary&) const;
    bool englishWordTranslationExistsInDictionary(const std::string& englishWordTranslation,
                                                  const Dictionary&) const;
};
}