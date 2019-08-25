#pragma once

#include <string>
#include "boost/optional.hpp"
#include "WordExistenceInfo.h"
#include "WordDescription.h"
#include "WordWithTranslation.h"

class Database
{
public:
    virtual boost::optional<WordWithTranslation> readNextWord() const = 0;
    virtual boost::optional<WordExistenceInfo> getWordExistenceInfo(const std::string &) const = 0;
    virtual boost::optional<WordDescription> getWordDescription(const std::string &) const = 0;
    virtual void writeWordExistenceInfo(const WordExistenceInfo &) const = 0;
    virtual void writeWordDescription(const WordDescription &) const = 0;
};
