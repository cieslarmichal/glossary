#pragma once

#include <string>
#include "boost/optional.hpp"
#include "WordExistenceInfo.h"
#include "WordWithTranslation.h"
#include "EnglishWordWithDescription.h"

class Database
{
    //should ask storage for words and save words to file, and get words from file
    //or better, inject already created Storage with words to databse........
    //first process Words from file to storage and then process user list
public:
    virtual boost::optional<WordWithTranslation> readNextWord() const = 0;
    virtual boost::optional<WordExistenceInfo> getWordExistenceInfo(const EnglishWord &) const = 0;
    virtual boost::optional<WordDescription> getWordDescription(const EnglishWord &) const = 0;
    virtual void writeWordExistenceInfo(const WordExistenceInfo &) const = 0;
    virtual void writeWordWithDescription(const EnglishWordWithDescription&) const = 0;
};
