#pragma once

#include <memory>

#include "boost/optional.hpp"

#include "DictionaryReader.h"
#include "utils/FileAccess.h"

class DefaultDictionaryReader : public DictionaryReader
{
public:
    explicit DefaultDictionaryReader(std::shared_ptr<const utils::FileAccess>);

    Dictionaries readDictionaries() const override;

private:
    Dictionary processDictionaryContent(const std::string&) const;
    boost::optional<translationsDb::Translation> getWordWithTranslation(const std::string&) const;

    std::shared_ptr<const utils::FileAccess> fileAccess;

    static const std::string fileDirectory;
    static const std::string fileName;
    static const std::string filePath;
};
