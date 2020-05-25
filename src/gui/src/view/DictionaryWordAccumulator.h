#pragma once

#include "FormattedDictionaryWord.h"

namespace glossary::gui::view
{
class DictionaryWordAccumulator
{
public:
    QString accumulateDictionaryWord(const FormattedDictionaryWord&) const;
    FormattedDictionaryWord separateDictionaryWord(const QString&) const;
};
}
