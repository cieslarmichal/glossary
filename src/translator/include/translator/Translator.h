#pragma once

#include "boost/optional.hpp"

#include "Language.h"
#include "SourceText.h"
#include "TranslatedText.h"

namespace glossary::translator
{
class Translator
{
public:
    virtual ~Translator() = default;

    virtual boost::optional<TranslatedText> translate(const SourceText&, SourceLanguage,
                                                      TargetLanguage) const = 0;
};
}