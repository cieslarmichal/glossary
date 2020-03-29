#pragma once

#include "DictionaryRepositoryFactory.h"

namespace dictionaryRepository
{
class DefaultDictionaryRepositoryFactory : public DictionaryRepositoryFactory
{
public:
    explicit DefaultDictionaryRepositoryFactory(std::shared_ptr<const utils::FileAccess>);

    std::unique_ptr<DictionaryRepository> createDictionaryRepository() const override;

private:
    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}