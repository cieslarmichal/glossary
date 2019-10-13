#pragma once

#include "Database.h"
#include "Storage.h"
#include <memory>


class WordsDatabase : public Database
{
public:
    explicit WordsDatabase(std::unique_ptr<Storage>);

    void addWord(const Word &) const override;
    boost::optional<Word> getWord(const EnglishWord &) const override;
    bool contains(const EnglishWord&) const override;

private:
    std::unique_ptr<Storage> storage;
};
