#pragma once

#include "boost/optional.hpp"

#include "Language.h"
#include "SourceText.h"
#include "TranslatedText.h"
#include "TranslatorApi.h"

namespace glossary::translator
{
class Translator
{
public:
    virtual ~Translator() = default;

    virtual TRANSLATOR_API boost::optional<TranslatedText> translate(const SourceText&, SourceLanguage, TargetLanguage,
                                                      const std::string& apiKey) const = 0;
};
}