#pragma once

#include "DictionaryWordsFileContentValidator.h"

namespace dictionaryRepository
{
class DictionaryWordsCSVFileContentValidator : public DictionaryWordsFileContentValidator
{
public:
    ValidationResult validate(const std::string& fileContent) const override;

private:
    bool dictionaryWordsContentIsValid(const std::string&) const;
    bool dictionaryWordLineIsValid(const std::string&) const;
};
}