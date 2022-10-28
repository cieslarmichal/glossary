#pragma once

#include <string>

namespace glossary::dictionary
{
class CreateDictionaryFromCsvFileCommand
{
public:
    virtual ~CreateDictionaryFromCsvFileCommand() = default;

    virtual void createDictionaryFromCsvFile(const std::string& dictionaryName,
                                             const std::string& dictionaryWordsCsvFilePath) = 0;
};
}
