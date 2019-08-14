#pragma once
#include <string>
#include "WordInfo.h"
#include "WordDescription.h"
#include "WordTranslation.h"

class Database
{
public:
    WordInfo getWordInformation(const std::string &) const;
    void appendWordInformation(const WordInfo &) const;

    WordDescription readWordDescription(const std::string &) const;
    void writeWordDescription(const WordDescription &) const;

    WordTranslation readWord(const WordTranslation &) const;
    bool isNextWord() const;
};