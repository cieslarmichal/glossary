#pragma once

#include <memory>

#include "boost/optional.hpp"

#include "DictionaryReader.h"
#include "utils/FileAccess.h"

namespace dictionaryRepository
{
class DefaultDictionaryReader : public DictionaryReader
{
public:
    explicit DefaultDictionaryReader(std::shared_ptr<const utils::FileAccess>);

    Dictionaries readDictionaries() const override;

private:
    Dictionary getDictionary(const std::string&) const;
    boost::optional<DictionaryWord> getDictionaryWord(const std::string&) const;

    std::shared_ptr<const utils::FileAccess> fileAccess;

    static const std::string directory;
    static const std::string filename;
};
}