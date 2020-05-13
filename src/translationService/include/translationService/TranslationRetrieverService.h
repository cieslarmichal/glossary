#pragma once

#include <vector>

#include "boost/optional.hpp"

#include "TranslationApiConnectionStatus.h"
#include "translator/Language.h"
#include "translator/SourceText.h"
#include "translator/TranslatedText.h"

namespace glossary::translationService
{
class TranslationRetrieverService
{
public:
    virtual ~TranslationRetrieverService() = default;

    virtual boost::optional<translator::TranslatedText> retrieveTranslation(const translator::SourceText&,
                                                                            translator::SourceLanguage,
                                                                            translator::TargetLanguage) = 0;
    virtual std::vector<std::string> retrieveSupportedLanguages() const = 0;
    virtual TranslationApiConnectionStatus connectionToTranslateApiAvailable() = 0;
};
}