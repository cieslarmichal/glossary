#pragma once

#include "DictionaryReader.h"
#include "FileAccess.h"
#include "boost/optional.hpp"
#include <memory>

class DictionaryReaderImpl : public DictionaryReader
{
public:
    explicit DictionaryReaderImpl(std::shared_ptr<const FileAccess>);

    Dictionary read() const override;

private:
    Dictionary processDictionaryContent(const std::string&) const;
    boost::optional<WordWithTranslation> getWordWithTranslation(const std::string&) const;

    std::shared_ptr<const FileAccess> fileAccess;

    static const std::string fileDirectory;
    static const std::string fileName;
    static const std::string filePath;
};
