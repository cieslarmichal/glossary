#pragma once

#include "boost/optional.hpp"

#include "translator/Language.h"
#include "translator/SourceText.h"
#include "translator/TranslatedText.h"

class TranslationRetrieverService
{
public:
    virtual ~TranslationRetrieverService() = default;

    virtual boost::optional<translator::TranslatedText> retrieveTranslation(const translator::SourceText&,
                                                                            translator::SourceLanguage,
                                                                            translator::TargetLanguage) = 0;
};