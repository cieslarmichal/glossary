#pragma once

#include "Translation.h"
#include "boost/optional.hpp"
#include <vector>

namespace translationsDb
{
class TranslationsDb
{
public:
    // TODO: add support different languages in storage
    virtual ~TranslationsDb() = default;

    virtual void addTranslation(Translation) = 0;
    virtual boost::optional<Translation>
    getTranslation(const SourceText&) const = 0;
    virtual std::vector<Translation> getTranslations() const = 0;
};
}
