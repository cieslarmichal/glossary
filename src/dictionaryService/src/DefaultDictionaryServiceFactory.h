#pragma once

#include "DictionaryServiceFactory.h"

namespace glossary::dictionaryService
{
class DefaultDictionaryServiceFactory : public DictionaryServiceFactory
{
public:
    explicit DefaultDictionaryServiceFactory(std::shared_ptr<const common::FileAccess>);

    std::unique_ptr<DictionaryService> createDictionaryService() const override;

private:
    std::shared_ptr<const common::FileAccess> fileAccess;
};
}