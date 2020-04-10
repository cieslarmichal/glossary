#pragma once

#include <memory>

#include "ApiKeyFileReader.h"
#include "SupportedLanguagesRetriever.h"
#include "TranslationRetrieverService.h"
#include "TranslatorConnectionChecker.h"
#include "translationRepository/TranslationRepository.h"
#include "translator/Translator.h"

namespace glossary::translationService
{
class DefaultTranslationRetrieverService : public TranslationRetrieverService
{
public:
    DefaultTranslationRetrieverService(std::shared_ptr<translator::Translator>,
                                       std::shared_ptr<translationRepository::TranslationRepository>,
                                       std::unique_ptr<ApiKeyFileReader>,
                                       std::unique_ptr<TranslatorConnectionChecker>);

    boost::optional<translator::TranslatedText> retrieveTranslation(const translator::SourceText&,
                                                                    translator::SourceLanguage,
                                                                    translator::TargetLanguage) override;
    std::vector<std::string> retrieveSupportedLanguages() const override;
    bool connectionToTranslateApiAvailable() override;

private:
    void setTranslatorApiKeyFromConfigFile();
    boost::optional<translator::TranslatedText> getTranslationFromRepository(const std::string&) const;
    boost::optional<translator::TranslatedText>
    getTranslationFromTranslator(const std::string&, translator::SourceLanguage,
                                 translator::TargetLanguage) const;
    void saveTranslationInRepository(const std::string&, const translator::TranslatedText&);

    std::shared_ptr<translator::Translator> translator;
    std::shared_ptr<translationRepository::TranslationRepository> translationRepository;
    SupportedLanguagesRetriever supportedLanguagesRetriever;
    std::unique_ptr<ApiKeyFileReader> apiKeyReader;
    const boost::optional<std::string> translatorApiKey;
    std::unique_ptr<TranslatorConnectionChecker> translatorConnectionChecker;
};
}