#pragma once

#include <memory>

#include "queries/GetSupportedLanguagesQuery.h"
#include "queries/GetTranslationQuery.h"

namespace glossary::translation
{
class DictionaryFactory
{
public:
    virtual ~DictionaryFactory() = default;

    virtual std::unique_ptr<GetTranslationQuery> createGetTranslationQuery() const = 0;
    virtual std::unique_ptr<GetSupportedLanguagesQuery> createGetSupportedLanguagesQuery() const = 0;

    static std::unique_ptr<DictionaryFactory> createTranslationFactory();
};
}
