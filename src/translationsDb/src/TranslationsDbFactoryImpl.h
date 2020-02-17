#pragma once

#include "TranslationsDbFactory.h"

namespace translationsDb
{
class TranslationsDbFactoryImpl : public TranslationsDbFactory
{
public:
    explicit TranslationsDbFactoryImpl(std::shared_ptr<const utils::FileAccess>);

    std::unique_ptr<TranslationsDb>
    createTranslationsDb() const override;

private:
    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}
