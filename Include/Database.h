#pragma once

#include <string>
#include "boost/optional.hpp"
#include "WordAvailability.h"
#include "WordWithTranslation.h"
#include "EnglishWordWithDescription.h"

class Database
{
    //should ask storage for words and save words to file, and get words from file
    //or better, inject already created Storage with words to databse........
    //first process Words from file to storage and then process user list
    //make service containing word factory database, readers, html connection
public:
    //virtual boost::optional<WordWithTranslation> readNextWord() const = 0;
    //virtual boost::optional<WordAvailability> getWordExistenceInfo(const EnglishWord &) const = 0;
    virtual boost::optional<WordDescription> getWordDescription(const EnglishWord &) const = 0;
    virtual void saveWordExistenceInfo(const WordAvailability &) const = 0;
    virtual void saveWord(const EnglishWordWithDescription&) const = 0;
};
