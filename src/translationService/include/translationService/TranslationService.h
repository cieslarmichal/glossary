#pragma once

#include <vector>

#include "boost/optional.hpp"

#include "TranslationApiStatus.h"
#include "translator/Language.h"
#include "translator/SourceText.h"
#include "translator/TranslatedText.h"

namespace glossary::translationService
{
class TranslationService
{
public:
    virtual ~TranslationService() = default;

    virtual boost::optional<translator::TranslatedText> retrieveTranslation(const translator::SourceText&,
                                                                            translator::SourceLanguage,
                                                                            translator::TargetLanguage) = 0;
    virtual std::vector<std::string> retrieveSupportedLanguages() const = 0;
    virtual TranslationApiStatus connectionToTranslateApiAvailable() const = 0;
    virtual void updateApiKeyLocation(const std::string& apiKeyLocation) = 0;
};
}