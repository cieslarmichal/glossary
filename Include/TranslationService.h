#pragma once

#include "boost/optional.hpp"
#include "translation/SourceLanguage.h"
#include "translation/TargetLanguage.h"
#include "translation/TranslatedText.h"

class TranslationService
{
public:
    virtual ~TranslationService() = default;

    virtual boost::optional<translation::TranslatedText>
    translate(const std::string&, translation::SourceLanguage,
              translation::TargetLanguage) const = 0;
};