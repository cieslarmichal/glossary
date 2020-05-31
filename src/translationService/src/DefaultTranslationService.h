#pragma once

#include <memory>

#include "ApiKeyFileReader.h"
#include "ApiKeyLocationUpdater.h"
#include "SupportedLanguagesRetriever.h"
#include "TranslationService.h"
#include "TranslatorConnectionChecker.h"
#include "translationRepository/TranslationRepository.h"
#include "translator/Translator.h"

namespace glossary::translationService
{
class DefaultTranslationService : public TranslationService
{
public:
    DefaultTranslationService(std::shared_ptr<translator::Translator>,
                              std::shared_ptr<translationRepository::TranslationRepository>,
                              std::unique_ptr<ApiKeyFileReader>, std::unique_ptr<TranslatorConnectionChecker>,
                              std::unique_ptr<ApiKeyLocationUpdater>);

    boost::optional<translator::TranslatedText> retrieveTranslation(const translator::SourceText&,
                                                                    translator::SourceLanguage,
                                                                    translator::TargetLanguage) override;
    std::vector<std::string> retrieveSupportedLanguages() const override;
    TranslationApiStatus connectionToTranslateApiAvailable() const override;
    void updateApiKeyLocation(const std::string& apiKeyLocation) override;

private:
    boost::optional<translator::TranslatedText> getTranslationFromRepository(const std::string&) const;
    boost::optional<translator::TranslatedText>
    getTranslationFromTranslator(const std::string&, translator::SourceLanguage,
                                 translator::TargetLanguage) const;
    void saveTranslationInRepository(const std::string&, const translator::TranslatedText&);

    std::shared_ptr<translator::Translator> translator;
    std::shared_ptr<translationRepository::TranslationRepository> translationRepository;
    SupportedLanguagesRetriever supportedLanguagesRetriever;
    std::unique_ptr<ApiKeyFileReader> apiKeyReader;
    std::unique_ptr<TranslatorConnectionChecker> translatorConnectionChecker;
    std::unique_ptr<ApiKeyLocationUpdater> apiKeyLocationUpdater;
    boost::optional<std::string> translatorApiKey;
};
}