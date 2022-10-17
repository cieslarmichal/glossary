#pragma once

#include <optional>
#include <vector>

#include "Language.h"

namespace glossary::translation
{
class TranslationService
{
public:
    virtual ~TranslationService() = default;

    virtual std::optional<std::string> translate(const std::string& textToTranslate, Language sourceLanguage,
                                                 Language targetLanguage,
                                                 const std::string& apiKey) const = 0;
    virtual std::vector<Language> getSupportedLanguages() const = 0;
};
}