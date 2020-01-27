#pragma once

#include "wordsDb/wordsDescriptionsDb/WordDescription.h"

class WordViewer
{
public:
    virtual ~WordViewer() = default;

    virtual std::string
    viewWord(const wordsDb::wordsDescriptionsDb::WordDescription&) const = 0;
    virtual std::string viewPolishWord(const PolishWord&) const = 0;
};
