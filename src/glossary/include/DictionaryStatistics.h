#pragma once

#include "dictionaryService/DictionaryName.h"

namespace glossary
{
struct DictionaryStatistics
{
    dictionaryService::DictionaryName name;
    unsigned correctAnswers;
    unsigned incorrectAnswers;
};
}