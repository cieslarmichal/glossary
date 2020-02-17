#pragma once

#include "boost/optional.hpp"
#include "translator/Language.h"
#include "translator/TranslatedText.h"

class TranslationService
{
public:
    virtual ~TranslationService() = default;

    virtual boost::optional<translator::TranslatedText>
    translate(const std::string&, translator::SourceLanguage,
              translator::TargetLanguage) = 0;
};