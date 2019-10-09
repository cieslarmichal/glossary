#pragma once
#include "DictionaryReader.h"
#include "FileAccess.h"

class DictionaryReaderImpl : public DictionaryReader
{
public:
    explicit DictionaryReaderImpl(FileAccess &);

    Dictionary read() const override;

private:
    Dictionary processDictionaryContent(const std::string&) const;
    WordWithTranslation getWordWithTranslation(const std::string&) const;

    FileAccess & fileAccess;
};
