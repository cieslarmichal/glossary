#pragma once
#include "Word.h"
#include <vector>
#include "FileAccess.h"
#include "Database.h"

class DatabaseImpl :  public Database
{
public:
    explicit DatabaseImpl(FileAccess &);

    boost::optional<WordWithTranslation> readNextWord() const override;
    boost::optional<WordExistenceInfo> getWordExistenceInfo(const std::string &) const override;
    boost::optional<WordDescription> getWordDescription(const std::string &) const override;
    void writeWordExistenceInfo(const WordExistenceInfo &) const override;
    void writeWordDescription(const WordDescription &) const override;

private:
    bool nextWordExists() const;

    FileAccess & fileAccess;
    std::vector<std::string> dictionaryWords;
    mutable std::vector<std::string>::size_type currentWordIndex;
};

