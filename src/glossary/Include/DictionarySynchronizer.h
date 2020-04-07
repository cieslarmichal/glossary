#pragma once

#include "dictionaryService/DictionaryName.h"

namespace glossary
{
class DictionarySynchronizer
{
public:
    virtual ~DictionarySynchronizer() = default;

    virtual void synchronizeDictionary(const dictionaryService::DictionaryName&) = 0;
    virtual void synchronizeDictionaries() = 0;
};

}