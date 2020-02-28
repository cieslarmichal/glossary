#pragma once

#include <memory>

#include "boost/optional.hpp"

#include "DictionaryReader.h"
#include "utils/FileAccess.h"

class DictionaryReaderImpl : public DictionaryReader
{
public:
    explicit DictionaryReaderImpl(std::shared_ptr<const utils::FileAccess>);

    Dictionary read() const override;

private:
    Dictionary processDictionaryContent(const std::string&) const;
    boost::optional<translationsDb::Translation> getWordWithTranslation(const std::string&) const;

    std::shared_ptr<const utils::FileAccess> fileAccess;

    static const std::string fileDirectory;
    static const std::string fileName;
    static const std::string filePath;
};
