#pragma once

#include <memory>

#include "boost/optional.hpp"

#include "DictionaryWordsReader.h"
#include "utils/FileAccess.h"

namespace dictionaryRepository
{
class DictionaryWordsTextFileReader : public DictionaryWordsReader
{
public:
    explicit DictionaryWordsTextFileReader(std::shared_ptr<const utils::FileAccess>);

    DictionaryWords readDictionaryWords(const std::string& absolutePath) const override;

private:
    DictionaryWords getDictionaryWords(const std::string&) const;
    boost::optional<DictionaryWord> getDictionaryWord(const std::string&) const;

    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}