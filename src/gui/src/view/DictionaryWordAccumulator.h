#pragma once

#include <optional>

#include "FormattedDictionaryWord.h"

namespace glossary::gui::view
{
class DictionaryWordAccumulator
{
public:
    QString accumulateDictionaryWord(const FormattedDictionaryWord&) const;
    std::optional<FormattedDictionaryWord> separateDictionaryWord(const QString&) const;
};
}
