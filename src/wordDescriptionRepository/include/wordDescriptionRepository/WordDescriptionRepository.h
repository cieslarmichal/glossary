#pragma once

#include <optional>

#include "WordDescription.h"
#include "WordDescriptionRepositoryApi.h"

namespace glossary::wordDescriptionRepository
{
class WORD_DESCRIPTION_REPOSITORY_API WordDescriptionRepository
{
public:
    virtual ~WordDescriptionRepository() = default;

    virtual void addWordDescription(const WordDescription&) = 0;
    virtual std::optional<WordDescription> getWordDescription(const std::string&) const = 0;
    virtual bool contains(const std::string&) const = 0;
};
}
