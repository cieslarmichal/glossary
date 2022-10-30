#pragma once

#include <optional>

#include "WordDescription.h"

namespace glossary::dictionary
{
class WordDescriptionRepository
{
public:
    virtual ~WordDescriptionRepository() = default;

    virtual void addWordDescription(const WordDescription&) = 0;
    virtual std::optional<WordDescription> getWordDescription(const std::string&) const = 0;
    virtual bool contains(const std::string&) const = 0;
};
}
