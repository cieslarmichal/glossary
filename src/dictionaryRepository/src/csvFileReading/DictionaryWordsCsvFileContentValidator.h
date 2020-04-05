#pragma once

#include "ValidationResult.h"

namespace glossary::dictionaryService::csvFileReading
{
class DictionaryWordsCsvFileContentValidator
{
public:
    ValidationResult validate(const std::string& fileContent) const;

private:
    bool dictionaryWordsContentIsValid(const std::string&) const;
    bool dictionaryWordLineIsValid(const std::string&) const;
};
}