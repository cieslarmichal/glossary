#pragma once

#include "Translations.h"
#include "boost/optional.hpp"

namespace translationsDb
{
class TranslationsDb
{
public:
    // TODO: add support different languages in storage
    virtual ~TranslationsDb() = default;

    virtual void addTranslation(Translation) = 0;
    virtual boost::optional<Translation>
    getTranslation(const PolishWord&) const = 0;
    virtual Translations getTranslations() const = 0;
};
}
