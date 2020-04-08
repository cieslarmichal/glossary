#pragma once

#include <memory>

#include "DictionaryService.h"
#include "utils/FileAccess.h"

namespace glossary::dictionaryService
{
class DictionaryServiceFactory
{
public:
    virtual ~DictionaryServiceFactory() = default;

    virtual std::unique_ptr<DictionaryService> createDictionaryService() const = 0;

    static std::unique_ptr<DictionaryServiceFactory>
    createDictionaryServiceFactory(const std::shared_ptr<const utils::FileAccess>&);
};
}