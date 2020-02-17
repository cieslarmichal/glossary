#pragma once

#include "Language.h"
#include "TranslatedText.h"
#include "boost/optional.hpp"

namespace translator
{
class Translator
{
public:
    virtual ~Translator() = default;

    virtual boost::optional<TranslatedText>
    translate(const std::string&, SourceLanguage, TargetLanguage) const = 0;
};
}