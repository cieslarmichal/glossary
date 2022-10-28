#pragma once

#include "gmock/gmock.h"

#include "CreateDictionaryFromCsvFileCommand.h"

namespace glossary::dictionary
{
class CreateDictionaryFromCsvFileCommandMock : public CreateDictionaryFromCsvFileCommand
{
public:
    MOCK_METHOD(void, createDictionaryFromCsvFile,
                (const std::string& dictionaryName, const std::string& dictionaryWordsCsvFilePat), ());
};
}
