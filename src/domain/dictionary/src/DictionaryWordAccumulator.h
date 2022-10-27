#pragma once

#include <optional>

#include "Dictionary.h"

namespace glossary::dictionary
{
class DictionaryWordAccumulator
{
public:
    std::vector<DictionaryWord> accumulateDictionaryWords(const Dictionary&) const;
    std::vector<DictionaryWord> accumulateDictionaryWords(const std::vector<Dictionary>&) const;
    std::vector<std::string> accumulateEnglishWords(const Dictionary&) const;
    std::vector<std::string> accumulateEnglishWords(const std::vector<Dictionary>&) const;
};
}
