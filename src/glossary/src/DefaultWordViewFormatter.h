#pragma once

#include "WordViewFormatter.h"

namespace glossary
{
class DefaultWordViewFormatter : public WordViewFormatter
{
public:
    std::string formatSingleWordView(const std::string&) const override;
    std::string formatWordDescriptionView(const wordDescriptionRepository::WordDescription&) const override;

private:
    std::string getDescription(const wordDescriptionRepository::Description&) const;

    static size_t amountOfDefinitionsToView;
    static size_t amountOfSentencesToView;
};
}