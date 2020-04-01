#pragma once

#include <memory>

#include "boost/optional.hpp"

#include "DictionaryWordsCsvFileContentValidator.h"
#include "DictionaryWordsReader.h"
#include "utils/FileAccess.h"

namespace dictionaryRepository
{
class DictionaryWordsCsvFileReader : public DictionaryWordsReader
{
public:
    explicit DictionaryWordsCsvFileReader(std::shared_ptr<const utils::FileAccess>);

    boost::optional<DictionaryWords> readDictionaryWords(const std::string& absolutePath) const override;

private:
    bool dictionaryWordsContentIsValid(const std::string&) const;
    DictionaryWords getDictionaryWords(const std::string&) const;
    boost::optional<DictionaryWord> getDictionaryWord(const std::string&) const;

    DictionaryWordsCsvFileContentValidator validator;
    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}