#pragma once
#include "Word.h"
#include <vector>
#include "FileAccess.h"
#include "Database.h"
#include "WordDescriptionParser.h"
#include "Storage.h"

class DatabaseImpl :  public Database
{
public:
    explicit DatabaseImpl(FileAccess &, Storage<EnglishWord, Word>&);

    boost::optional<WordDescription> getWordDescription(const EnglishWord &) const override;
    void writeWordWithDescription(const EnglishWordWithDescription &) const override;

private:

    FileAccess & fileAccess;
    Storage<EnglishWord, Word> & storage; //unique pointer
    WordDescriptionParser wordDescriptionParser;
};

