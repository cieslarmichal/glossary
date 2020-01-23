#pragma once

#include "SourceLanguage.h"
#include "TargetLanguage.h"
#include "boost/optional.hpp"

namespace translation
{
class Translator
{
public:
    virtual ~Translator() = default;

    virtual boost::optional<std::string>
    translate(const std::string&, SourceLanguage, TargetLanguage) const = 0;
};
}