#include "DefaultTranslatorConnectionChecker.h"

namespace glossary::translationService
{

namespace
{
const std::string examplePolishWord{"okno"};
const auto sourceLanguage = translator::Language::Polish;
const auto targetLanguage = translator::Language::English;
}

DefaultTranslatorConnectionChecker::DefaultTranslatorConnectionChecker(
    std::shared_ptr<translator::Translator> translatorInit)
    : translator{std::move(translatorInit)}
{
}

bool DefaultTranslatorConnectionChecker::connectionToTranslatorWithApiKeyIsAvailable(
    const std::string& apiKey)
{
    if (translator->translate(examplePolishWord, sourceLanguage, targetLanguage, apiKey))
        return true;
    return false;
}

}