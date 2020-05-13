#include "DefaultTranslationRetrieverService.h"

#include <iostream>

namespace glossary::translationService
{
DefaultTranslationRetrieverService::DefaultTranslationRetrieverService(
    std::shared_ptr<translator::Translator> translatorInit,
    std::shared_ptr<translationRepository::TranslationRepository> repo,
    std::unique_ptr<ApiKeyFileReader> apiKeyReaderInit,
    std::unique_ptr<TranslatorConnectionChecker> connectionChecker)
    : translator{std::move(translatorInit)},
      translationRepository{std::move(repo)},
      apiKeyReader{std::move(apiKeyReaderInit)},
      translatorApiKey{apiKeyReader->readApiKey()},
      translatorConnectionChecker{std::move(connectionChecker)}
{
}

boost::optional<translator::TranslatedText>
DefaultTranslationRetrieverService::retrieveTranslation(const translator::SourceText& sourceText,
                                                        translator::SourceLanguage sourceLanguage,
                                                        translator::TargetLanguage targetLanguage)
{
    if (const auto translationFromRepository = getTranslationFromRepository(sourceText))
        return translationFromRepository;

    if (const auto translationFromTranslator =
            getTranslationFromTranslator(sourceText, sourceLanguage, targetLanguage))
    {
        saveTranslationInRepository(sourceText, *translationFromTranslator);
        return translationFromTranslator;
    }

    return boost::none;
}

std::vector<std::string> DefaultTranslationRetrieverService::retrieveSupportedLanguages() const
{
    return supportedLanguagesRetriever.retrieveSupportedLanguages();
}

TranslationApiConnectionStatus DefaultTranslationRetrieverService::connectionToTranslateApiAvailable()
{
    if (translatorApiKey)
    {
        return translatorConnectionChecker->connectionToTranslatorWithApiKeyIsAvailable(*translatorApiKey);
    }
    return TranslationApiConnectionStatus::InvalidApiKey;
}

boost::optional<translator::TranslatedText>
DefaultTranslationRetrieverService::getTranslationFromRepository(const std::string& sourceText) const
{
    if (const auto translation = translationRepository->getTranslation(sourceText))
        return translator::TranslatedText{translation->translatedText};
    return boost::none;
}

boost::optional<translator::TranslatedText> DefaultTranslationRetrieverService::getTranslationFromTranslator(
    const std::string& sourceText, translator::SourceLanguage sourceLanguage,
    translator::TargetLanguage targetLanguage) const
{
    if (translatorApiKey)
        return translator->translate(sourceText, sourceLanguage, targetLanguage, *translatorApiKey);

    std::cerr << "No available translate api key";
    return boost::none;
}

void DefaultTranslationRetrieverService::saveTranslationInRepository(
    const std::string& sourceText, const translator::TranslatedText& translatedText)
{
    const auto newTranslation = translationRepository::Translation{
        translationRepository::SourceText{sourceText}, translationRepository::TranslatedText{translatedText}};
    translationRepository->addTranslation(newTranslation);
}
}
