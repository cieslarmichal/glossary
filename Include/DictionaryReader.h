#pragma once
#include "WordWithTranslation.h"
#include <vector>
#include "FileAccess.h"

class DictionaryReader
{
public:
    explicit DictionaryReader(FileAccess &);

    std::vector<WordWithTranslation> read() const;

private:
    std::vector<WordWithTranslation> processDictionaryContent(const std::string&) const;
    WordWithTranslation getWordWithTranslation(const std::string&) const;

    FileAccess & fileAccess;
};