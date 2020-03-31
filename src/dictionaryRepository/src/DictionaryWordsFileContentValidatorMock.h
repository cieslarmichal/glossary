#pragma once

#include "gmock/gmock.h"

#include "DictionaryWordsFileContentValidator.h"

namespace dictionaryRepository
{
class DictionaryWordsFileContentValidatorMock : public DictionaryWordsFileContentValidator
{
public:
    MOCK_CONST_METHOD1(validate, ValidationResult(const std::string& fileContent));
};
}