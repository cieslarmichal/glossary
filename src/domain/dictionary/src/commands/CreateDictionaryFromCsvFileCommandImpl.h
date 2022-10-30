#pragma once

#include <memory>

#include "../readers/DictionaryWordsCsvReader.h"
#include "../repositories/DictionaryRepository.h"
#include "commands/CreateDictionaryFromCsvFileCommand.h"

namespace glossary::dictionary
{
// TODO: notify dictionary observers about loaded english words
class CreateDictionaryFromCsvFileCommandImpl : public CreateDictionaryFromCsvFileCommand
{
public:
    CreateDictionaryFromCsvFileCommandImpl(std::shared_ptr<DictionaryRepository>,
                                           std::unique_ptr<DictionaryWordsCsvReader>);

    void createDictionaryFromCsvFile(const std::string& dictionaryName,
                                     const std::string& dictionaryWordsCsvFilePath) override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
    std::unique_ptr<DictionaryWordsCsvReader> dictionaryWordsCsvReader;
};
}
