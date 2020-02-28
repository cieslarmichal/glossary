#pragma once

#include <memory>

#include "TranslationsDb.h"
#include "utils/FileAccess.h"

namespace translationsDb
{
class TranslationsDbFactory
{
public:
    virtual ~TranslationsDbFactory() = default;

    virtual std::unique_ptr<TranslationsDb> createTranslationsDb() const = 0;

    static std::unique_ptr<TranslationsDbFactory>
    createTranslationsDbFactory(const std::shared_ptr<const utils::FileAccess>&);
};
}