#pragma once
#include "Word.h"
#include <vector>
#include "FileAccess.h"
#include "Database.h"
#include "WordDescriptionParser.h"

class DatabaseImpl :  public Database
{
public:
    explicit DatabaseImpl(FileAccess &);

    boost::optional<WordWithTranslation> readNextWord() const override;
    boost::optional<WordExistenceInfo> getWordExistenceInfo(const EnglishWord &) const override;
    boost::optional<WordDescription> getWordDescription(const EnglishWord &) const override;
    void writeWordExistenceInfo(const WordExistenceInfo &) const override;
    void writeWordWithDescription(const EnglishWordWithDescription &) const override;

private:
    bool nextWordExists() const;

    FileAccess & fileAccess;
    std::vector<std::string> dictionaryWords;
    mutable size_t currentWordIndex; //storage
    WordDescriptionParser wordDescriptionParser;
};

