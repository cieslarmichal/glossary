#pragma once

#include "TranslationsDbFactory.h"

namespace translationsDb
{
class DefaultTranslationsDbFactory : public TranslationsDbFactory
{
public:
    explicit DefaultTranslationsDbFactory(std::shared_ptr<const utils::FileAccess>);

    std::unique_ptr<TranslationsDb> createTranslationsDb() const override;

private:
    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}
