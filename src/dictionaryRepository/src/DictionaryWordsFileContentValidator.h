#pragma once

#include "ValidationResult.h"
#include <string>

namespace dictionaryRepository
{
class DictionaryWordsFileContentValidator
{
public:
    virtual ~DictionaryWordsFileContentValidator() = default;

    virtual ValidationResult validate(const std::string& fileContent) const = 0;
};
}