#pragma once

#include <memory>

#include "DictionaryService.h"
#include "fileSystem/FileAccess.h"

namespace glossary::dictionary
{
class DictionaryServiceFactory
{
public:
    virtual ~DictionaryServiceFactory() = default;

    virtual std::unique_ptr<DictionaryService> createDictionaryService() const = 0;

    static std::unique_ptr<DictionaryServiceFactory>
    createDictionaryServiceFactory(const std::shared_ptr<const common::fileSystem::FileAccess>&);
};
}