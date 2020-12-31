#pragma once

#include <memory>

#include "DictionaryService.h"
#include "utils/FileAccess.h"
#include "DictionaryServiceApi.h"

namespace glossary::dictionaryService
{
class DICTIONARY_SERVICE_API DictionaryServiceFactory
{
public:
    virtual ~DictionaryServiceFactory() = default;

    virtual std::unique_ptr<DictionaryService> createDictionaryService() const = 0;

    static std::unique_ptr<DictionaryServiceFactory>
    createDictionaryServiceFactory(const std::shared_ptr<const utils::FileAccess>&);
};
}