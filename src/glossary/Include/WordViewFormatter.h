#pragma once

#include "wordDescriptionRepository/WordDescription.h"

namespace glossary
{
class WordViewFormatter
{
public:
    virtual ~WordViewFormatter() = default;

    virtual std::string formatSingleWordView(const std::string&) const = 0;
    virtual std::string
    formatWordDescriptionView(const wordDescriptionRepository::WordDescription&) const = 0;
};
}