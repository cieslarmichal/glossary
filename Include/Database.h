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
    virtual void appendWordExistenceInfo(const WordExistenceInfo &) const = 0;
    virtual boost::optional<WordDescription> readWordDescription(const std::string &) const = 0;
    virtual void writeWordDescription(const std::string &, const WordDescription &) const = 0;
};