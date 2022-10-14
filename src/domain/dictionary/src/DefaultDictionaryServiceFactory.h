#pragma once

#include "DictionaryServiceFactory.h"

namespace glossary::dictionary
{
class DefaultDictionaryServiceFactory : public DictionaryServiceFactory
{
public:
    explicit DefaultDictionaryServiceFactory(std::shared_ptr<const common::fileSystem::FileAccess>);

    std::unique_ptr<DictionaryService> createDictionaryService() const override;

private:
    std::shared_ptr<const common::fileSystem::FileAccess> fileAccess;
};
}