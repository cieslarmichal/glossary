#pragma once

#include <memory>

#include "DictionaryWordsCsvReader.h"
#include "fileSystem/FileAccess.h"

namespace glossary::dictionary
{
class DictionaryWordsCsvReaderImpl : public DictionaryWordsCsvReader
{
public:
    explicit DictionaryWordsCsvReaderImpl(std::shared_ptr<const common::fileSystem::FileAccess>);

    std::vector<DictionaryWord> readDictionaryWords(const std::string& absolutePath) const override;

private:
    bool dictionaryWordsCsvIsValid(const std::string& csvDictionaryWords) const;
    bool dictionaryWordCsvLineIsValid(const std::string& csvDictionaryWordLine) const;

    std::shared_ptr<const common::fileSystem::FileAccess> fileAccess;
};
}
