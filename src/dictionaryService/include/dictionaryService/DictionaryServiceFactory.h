#pragma once

#include <memory>

#include "../../../common/fileSystem/include/FileAccess.h"
#include "DictionaryService.h"
#include "DictionaryServiceApi.h"

namespace glossary::dictionaryService
{
class DICTIONARY_SERVICE_API DictionaryServiceFactory
{
public:
    virtual ~DictionaryServiceFactory() = default;

    virtual std::unique_ptr<DictionaryService> createDictionaryService() const = 0;

    static std::unique_ptr<DictionaryServiceFactory>
    createDictionaryServiceFactory(const std::shared_ptr<const common::FileAccess>&);
};
}