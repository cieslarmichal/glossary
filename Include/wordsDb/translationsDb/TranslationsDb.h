#pragma once

#include "Translations.h"
#include "boost/optional.hpp"

namespace wordsDb::translationsDb
{
class TranslationsDb
{
public:
    virtual ~TranslationsDb() = default;

    virtual void addTranslation(Translation) = 0;
    virtual boost::optional<Translation>
    getTranslation(const PolishWord&) const = 0;
    virtual Translations getTranslations() const = 0;
};
}
