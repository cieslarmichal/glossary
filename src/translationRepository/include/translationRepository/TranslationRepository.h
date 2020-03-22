#pragma once

#include <vector>

#include "boost/optional.hpp"

#include "Translation.h"

namespace translationRepository
{
class TranslationRepository
{
public:
    // TODO: add support different languages in storage
    virtual ~TranslationRepository() = default;

    virtual void addTranslation(Translation) = 0;
    virtual boost::optional<Translation> getTranslation(const SourceText&) const = 0;
    virtual std::vector<Translation> getTranslations() const = 0;
};
}
