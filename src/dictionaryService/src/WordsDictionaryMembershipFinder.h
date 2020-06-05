#pragma once

#include "Dictionary.h"

namespace glossary::dictionaryService
{
class WordsDictionaryMembershipFinder
{
public:
    DictionaryNames findDictionariesContainingEnglishWord(const EnglishWord&, const Dictionaries&) const;
    DictionaryNames
    findDictionariesContainingEnglishWordTranslation(const std::string& englishWordTranslation,
                                                     const Dictionaries&) const;

private:
    bool englishWordExistsInDictionary(const EnglishWord&, const Dictionary&) const;
    bool englishWordTranslationExistsInDictionary(const std::string& englishWordTranslation,
                                                  const Dictionary&) const;
};
}