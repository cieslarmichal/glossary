#pragma once

#include "boost/optional.hpp"

#include "Language.h"
#include "TranslatedText.h"

namespace translator
{
class Translator
{
public:
    virtual ~Translator() = default;

    virtual boost::optional<TranslatedText> translate(const std::string&, SourceLanguage,
                                                      TargetLanguage) const = 0;
};
}