#pragma once

#include "WordViewFormatter.h"

namespace glossary
{
class DefaultWordViewFormatter : public WordViewFormatter
{
public:
    std::string formatWordView(const Word&) const override;
    std::string formatPolishWordView(const PolishWord&) const override;

private:
    std::string getDescription(const wordDescriptionRepository::Description&) const;

    static size_t amountOfDefinitionsToView;
    static size_t amountOfSentencesToView;
};
}