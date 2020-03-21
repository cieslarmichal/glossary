#pragma once

#include "boost/optional.hpp"

#include "Language.h"
#include "TranslatedText.h"
#include "SourceText.h"

namespace translator
{
class Translator
{
public:
    virtual ~Translator() = default;

    virtual boost::optional<TranslatedText> translate(const SourceText&, SourceLanguage,
                                                      TargetLanguage) const = 0;
};
}