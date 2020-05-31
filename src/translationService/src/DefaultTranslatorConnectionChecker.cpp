#include "DefaultTranslatorConnectionChecker.h"

#include "translator/exceptions/InvalidApiKey.h"
#include "webConnection/exceptions/ConnectionFailed.h"

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

TranslationApiStatus
DefaultTranslatorConnectionChecker::connectionToTranslatorWithApiKeyIsAvailable(const std::string& apiKey) const
{
    try
    {
        translator->translate(examplePolishWord, sourceLanguage, targetLanguage, apiKey);
        return TranslationApiStatus::Available;
    }
    catch (const translator::exceptions::InvalidApiKey&)
    {
        return TranslationApiStatus::InvalidApiKey;
    }
    catch (const webConnection::exceptions::ConnectionFailed&)
    {
        return TranslationApiStatus::Unavailable;
    }
}

}