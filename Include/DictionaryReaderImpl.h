#pragma once

#include "DictionaryReader.h"
#include "FileAccess.h"
#include <memory>

class DictionaryReaderImpl : public DictionaryReader
{
public:
    explicit DictionaryReaderImpl(std::shared_ptr<const FileAccess>);

    Dictionary read() const override;

private:
    Dictionary processDictionaryContent(const std::string&) const;
    WordWithTranslation getWordWithTranslation(const std::string&) const;

    std::shared_ptr<const FileAccess> fileAccess;

    static const std::string dictionaryFilePath;
};
