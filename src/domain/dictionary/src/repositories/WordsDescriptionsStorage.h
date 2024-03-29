#pragma once

#include <optional>

#include "WordDescription.h"

namespace glossary::dictionary
{
class WordsDescriptionsStorage
{
public:
    virtual ~WordsDescriptionsStorage() = default;

    virtual void addWordDescription(const WordDescription&) = 0;
    virtual std::optional<WordDescription> getWordDescription(const std::string&) const = 0;
    virtual std::vector<WordDescription> getWordsDescriptions() const = 0;
    virtual bool contains(const std::string&) const = 0;
    virtual std::vector<WordDescription>::size_type size() const = 0;
    virtual bool empty() const = 0;
};
}
