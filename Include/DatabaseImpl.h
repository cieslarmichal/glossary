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
    void appendWordExistenceInfo(const WordExistenceInfo &) const override;
    boost::optional<WordDescription> readWordDescription(const std::string &) const override;
    void writeWordDescription(const std::string &, const WordDescription &) const override;

private:
    FileAccess & fileAccess;
    std::vector<std::string> dictionaryWords;
    mutable std::vector<std::string>::size_type currentWordIndex;

    bool nextWordExists() const;

};

