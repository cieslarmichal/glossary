#pragma once

#include "Dictionaries.h"
#include "FormattedDictionary.h"

namespace glossary::gui::view
{
class DictionaryFormatter
{
public:
    // TODO: change name from FormattedDictionary to smth like QDictionary
    FormattedDictionaries getFormattedDictionaries(const Dictionaries&) const;
    FormattedDictionary getFormattedDictionary(const Dictionary&) const;
    QString getFormattedDictionaryName(const std::string&) const;
    FormattedDictionaryWords getFormattedDictionaryWords(const std::vector<DictionaryWord>&) const;
};
}
