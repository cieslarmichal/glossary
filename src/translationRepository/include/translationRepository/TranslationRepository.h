#pragma once

#include <vector>

#include "boost/optional.hpp"

#include "Translation.h"

namespace glossary::translationRepository
{
class TranslationRepository
{
public:
    virtual ~TranslationRepository() = default;

    virtual void addTranslation(Translation) = 0;
    virtual boost::optional<Translation> getTranslation(const SourceText&) const = 0;
    virtual bool containsTranslation(const SourceText&) const = 0;
};
}
