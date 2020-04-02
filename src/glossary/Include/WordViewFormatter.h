#pragma once

#include "Word.h"

namespace glossary
{
class WordViewFormatter
{
public:
    virtual ~WordViewFormatter() = default;

    virtual std::string formatWordView(const Word&) const = 0;
    virtual std::string formatPolishWordView(const PolishWord&) const = 0;
};
}