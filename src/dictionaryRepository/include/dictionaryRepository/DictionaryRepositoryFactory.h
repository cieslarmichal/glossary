#pragma once

#include <memory>

#include "DictionaryRepository.h"
#include "utils/FileAccess.h"

namespace dictionaryRepository
{
class DictionaryRepositoryFactory
{
public:
    virtual ~DictionaryRepositoryFactory() = default;

    virtual std::unique_ptr<DictionaryRepository> createDictionaryRepository() const = 0;

    static std::unique_ptr<DictionaryRepositoryFactory>
    createDictionaryRepositoryFactory(const std::shared_ptr<const utils::FileAccess>&);
};
}