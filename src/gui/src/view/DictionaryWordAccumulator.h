#pragma once

#include "boost/optional.hpp"

#include "FormattedDictionaryWord.h"

namespace glossary::gui::view
{
class DictionaryWordAccumulator
{
public:
    QString accumulateDictionaryWord(const FormattedDictionaryWord&) const;
    boost::optional<FormattedDictionaryWord> separateDictionaryWord(const QString&) const;
};
}
