#pragma once

#include "EnglishWord.h"

namespace glossary::dictionaryService
{
class DictionaryObserver
{
public:
    virtual ~DictionaryObserver() = default;

    virtual void update(const EnglishWords&) = 0;
};
}