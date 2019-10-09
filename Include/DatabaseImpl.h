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
    explicit DatabaseImpl(FileAccess &, Storage&);

    boost::optional<WordDescription> getWordDescription(const EnglishWord &) const override;
    void saveWord(const EnglishWordWithDescription &) const override;

private:
    FileAccess & fileAccess;
    Storage & storage; //unique pointer
    WordDescriptionParser wordDescriptionParser;
};
