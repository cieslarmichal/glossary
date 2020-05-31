#include "DefaultTranslationService.h"

#include <iostream>

namespace glossary::translationService
{
DefaultTranslationService::DefaultTranslationService(
    std::shared_ptr<translator::Translator> translatorInit,
    std::shared_ptr<translationRepository::TranslationRepository> repo,
    std::unique_ptr<ApiKeyFileReader> apiKeyReaderInit,
    std::unique_ptr<TranslatorConnectionChecker> connectionChecker,
    std::unique_ptr<ApiKeyLocationUpdater> keyLocationUpdater)
    : translator{std::move(translatorInit)},
      translationRepository{std::move(repo)},
      apiKeyReader{std::move(apiKeyReaderInit)},
      translatorConnectionChecker{std::move(connectionChecker)},
      apiKeyLocationUpdater{std::move(keyLocationUpdater)},
      translatorApiKey{apiKeyReader->readApiKey()}
{
}

boost::optional<translator::TranslatedText>
DefaultTranslationService::retrieveTranslation(const translator::SourceText& sourceText,
                                               translator::SourceLanguage sourceLanguage,
                                               translator::TargetLanguage targetLanguage)
{
    if (auto translationFromRepository = getTranslationFromRepository(sourceText))
    {
        return translationFromRepository;
    }

    if (auto translationFromTranslator =
            getTranslationFromTranslator(sourceText, sourceLanguage, targetLanguage))
    {
        saveTranslationInRepository(sourceText, *translationFromTranslator);
        return translationFromTranslator;
    }

    return boost::none;
}

std::vector<std::string> DefaultTranslationService::retrieveSupportedLanguages() const
{
    return supportedLanguagesRetriever.retrieveSupportedLanguages();
}

TranslationApiStatus DefaultTranslationService::connectionToTranslateApiAvailable() const
{
    if (translatorApiKey)
    {
        return translatorConnectionChecker->connectionToTranslatorWithApiKeyIsAvailable(*translatorApiKey);
    }
    return TranslationApiStatus::InvalidApiKey;
}

boost::optional<translator::TranslatedText>
DefaultTranslationService::getTranslationFromRepository(const std::string& sourceText) const
{
    if (const auto translation = translationRepository->getTranslation(sourceText))
    {
        return translator::TranslatedText{translation->translatedText};
    }
    return boost::none;
}

boost::optional<translator::TranslatedText>
DefaultTranslationService::getTranslationFromTranslator(const std::string& sourceText,
                                                        translator::SourceLanguage sourceLanguage,
                                                        translator::TargetLanguage targetLanguage) const
{
    if (translatorApiKey)
    {
        return translator->translate(sourceText, sourceLanguage, targetLanguage, *translatorApiKey);
    }

    std::cerr << "No available translate api key";
    return boost::none;
}

void DefaultTranslationService::saveTranslationInRepository(const std::string& sourceText,
                                                            const translator::TranslatedText& translatedText)
{
    auto newTranslation = translationRepository::Translation{
        translationRepository::SourceText{sourceText}, translationRepository::TranslatedText{translatedText}};
    translationRepository->addTranslation(newTranslation);
}

void DefaultTranslationService::updateApiKeyLocation(const std::string& apiKeyLocation)
{
    apiKeyLocationUpdater->updateApiKeyLocation(apiKeyLocation);
    translatorApiKey = apiKeyReader->readApiKey();
}

}
