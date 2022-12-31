#pragma once

#include "dictionary/Dictionary.h"
#include "dictionary/DictionaryWord.h"
#include "FormattedDictionary.h"

namespace glossary::gui::view
{
class DictionaryFormatter
{
public:
    FormattedDictionaries getFormattedDictionaries(const std::vector<dictionary::Dictionary>&) const;
    FormattedDictionary getFormattedDictionary(const dictionary::Dictionary&) const;
    QString getFormattedDictionaryName(const std::string&) const;
    FormattedDictionaryWords getFormattedDictionaryWords(const std::vector<dictionary::DictionaryWord>&) const;
};
}
