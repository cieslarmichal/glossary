#pragma once

#include <memory>

#include "DictionaryWordsReader.h"
#include "fileSystem/FileAccess.h"

namespace glossary::dictionary
{
class DictionaryWordsCsvReader : public DictionaryWordsReader
{
public:
    explicit DictionaryWordsCsvReader(std::shared_ptr<const common::fileSystem::FileAccess>);

    std::vector<DictionaryWord> readDictionaryWords(const std::string& absolutePath) const override;

private:
    bool dictionaryWordsCsvIsValid(const std::string& csvDictionaryWords) const;
    bool dictionaryWordCsvLineIsValid(const std::string& csvDictionaryWordLine) const;

    std::shared_ptr<const common::fileSystem::FileAccess> fileAccess;
};
}
