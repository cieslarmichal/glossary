#pragma once

#include <optional>

#include "WordDescription.h"

namespace glossary::wordDescriptionRepository
{
class WordsDescriptionsStorage
{
public:
    virtual ~WordsDescriptionsStorage() = default;

    virtual void addWordDescription(const WordDescription&) = 0;
    virtual std::optional<WordDescription> getWordDescription(const std::string&) const = 0;
    virtual WordsDescriptions getWordsDescriptions() const = 0;
    virtual bool contains(const std::string&) const = 0;
    virtual WordsDescriptions::size_type size() const = 0;
    virtual bool empty() const = 0;
};
}
