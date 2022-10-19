#pragma once

#include <memory>
#include <optional>

#include "DictionaryWordsCsvFileContentValidator.h"
#include "DictionaryWordsReader.h"
#include "fileSystem/FileAccess.h"

namespace glossary::dictionary::csvFileReading
{
class DictionaryWordsCsvFileReader : public DictionaryWordsReader
{
public:
    explicit DictionaryWordsCsvFileReader(std::shared_ptr<const common::fileSystem::FileAccess>);

    std::optional<std::vector<DictionaryWord>>
    readDictionaryWords(const std::string& absolutePath) const override;

private:
    bool dictionaryWordsContentIsValid(const std::string&) const;
    std::vector<DictionaryWord> getDictionaryWords(const std::string&) const;
    std::optional<DictionaryWord> getDictionaryWord(const std::string&) const;

    DictionaryWordsCsvFileContentValidator validator;
    std::shared_ptr<const common::fileSystem::FileAccess> fileAccess;
};
}