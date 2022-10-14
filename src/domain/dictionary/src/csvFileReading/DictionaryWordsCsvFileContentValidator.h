#pragma once

#include "ValidationResult.h"

namespace glossary::dictionary::csvFileReading
{
class DictionaryWordsCsvFileContentValidator
{
public:
    ValidationResult validate(const std::string& fileContent) const;

private:
    bool dictionaryWordsContentIsValid(const std::string& dictionaryWordsContent) const;
    bool dictionaryWordLineIsValid(const std::string& dictionaryWordLine) const;
};
}