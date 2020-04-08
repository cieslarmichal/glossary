#include "SupportedLanguagesRetriever.h"

namespace glossary::translationService
{

const std::vector<translator::Language> SupportedLanguagesRetriever::supportedLanguages{
    translator::Language::Polish, translator::Language::English};

std::vector<std::string> SupportedLanguagesRetriever::retrieveSupportedLanguages() const
{
    std::vector<std::string> supportedLanguagesAsString;
    supportedLanguagesAsString.reserve(supportedLanguages.size());

    for (const auto& supportedLanguage : supportedLanguages)
        supportedLanguagesAsString.push_back(toString(supportedLanguage));

    return supportedLanguagesAsString;
}
}