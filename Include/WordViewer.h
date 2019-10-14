#pragma once

#include "Word.h"

class WordViewer
{
public:
    virtual ~WordViewer() = default;

    virtual std::string viewWord(const Word&) const = 0;
    virtual std::string viewEnglishWord(const EnglishWord&) const = 0;

};
