#pragma once

#include <memory>

#include "boost/optional.hpp"

#include "DictionaryWordsReader.h"
#include "utils/FileAccess.h"

namespace dictionaryRepository
{
class DictionaryWordsCSVFileReader : public DictionaryWordsReader
{
public:
    explicit DictionaryWordsCSVFileReader(std::shared_ptr<const utils::FileAccess>);

    DictionaryWords readDictionaryWords(const std::string& absolutePath) const override;

private:
    bool dictionaryWordsContentIsValid(const std::string&) const;
    bool dictionaryWordLineIsValid(const std::string&) const;
    DictionaryWords getDictionaryWords(const std::string&) const;
    boost::optional<DictionaryWord> getDictionaryWord(const std::string&) const;

    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}