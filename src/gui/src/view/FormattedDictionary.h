#pragma once

#include "FormattedDictionaryWord.h"

namespace glossary::gui::view
{
struct FormattedDictionary
{
    QString dictionaryName;
    FormattedDictionaryWords dictionaryWords;
};

using FormattedDictionaries = QList<FormattedDictionary>;

inline bool operator==(const FormattedDictionary& lhs, const FormattedDictionary& rhs)
{
    return lhs.dictionaryName == rhs.dictionaryName && lhs.dictionaryWords == rhs.dictionaryWords;
}
}
