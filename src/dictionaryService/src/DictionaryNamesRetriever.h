#pragma once

#include "DictionaryName.h"

namespace glossary::dictionaryService
{
class DictionaryNamesRetriever
{
public:
    virtual ~DictionaryNamesRetriever() = default;

    virtual DictionaryNames retrieveDictionaryNames() const = 0;
};
}