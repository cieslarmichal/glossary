#pragma once

#include "wordsDb/descriptionsDb/WordDescription.h"

class WordViewer
{
public:
    virtual ~WordViewer() = default;

    virtual std::string viewWord(const WordDescription&) const = 0;
    virtual std::string viewPolishWord(const PolishWord&) const = 0;
};
