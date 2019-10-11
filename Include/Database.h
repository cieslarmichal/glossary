#pragma once

#include <string>
#include "boost/optional.hpp"
#include "WordAvailability.h"
#include "WordWithTranslation.h"
#include "EnglishWordWithDescription.h"

class Database
{
    //should ask storage for words and save words to file, and get words from file
    //or better, inject already created MemoryStorage with words to databse........
    //first process Words from file to storage and then process user list
    //make service containing word factory database, readers, html connection

    //make MemoryStorage non template like in job
public:
    virtual boost::optional<WordDescription> getWordDescription(const EnglishWord &) const = 0;
    virtual void saveWord(const EnglishWordWithDescription&) const = 0;
};
