#pragma once

#include "Dictionary.h"

namespace glossary::dictionary
{
class WordsDictionaryMembershipFinder
{
public:
    std::vector<std::string> findDictionariesContainingEnglishWord(const std::string&,
                                                                   const Dictionaries&) const;
    std::vector<std::string>
    findDictionariesContainingEnglishWordTranslation(const std::string& englishWordTranslation,
                                                     const Dictionaries&) const;

private:
    bool englishWordExistsInDictionary(const std::string&, const Dictionary&) const;
    bool englishWordTranslationExistsInDictionary(const std::string& englishWordTranslation,
                                                  const Dictionary&) const;
};
}