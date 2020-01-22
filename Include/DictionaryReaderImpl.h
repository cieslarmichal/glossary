#pragma once

#include <memory>

#include "DictionaryReader.h"
#include "FileAccess.h"
#include "boost/optional.hpp"

class DictionaryReaderImpl : public DictionaryReader
{
public:
    explicit DictionaryReaderImpl(std::shared_ptr<const FileAccess>);

    Dictionary read() const override;

private:
    Dictionary processDictionaryContent(const std::string&) const;
    boost::optional<Translation>
    getWordWithTranslation(const std::string&) const;

    std::shared_ptr<const FileAccess> fileAccess;

    static const std::string fileDirectory;
    static const std::string fileName;
    static const std::string filePath;
};
