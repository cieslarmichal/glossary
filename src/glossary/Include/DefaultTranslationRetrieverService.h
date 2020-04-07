#pragma once

#include <memory>

#include "TranslationRetrieverService.h"
#include "translationRepository/TranslationRepository.h"
#include "translator/Translator.h"

namespace glossary
{
class DefaultTranslationRetrieverService : public TranslationRetrieverService
{
public:
    DefaultTranslationRetrieverService(std::shared_ptr<translator::Translator>,
                                       std::shared_ptr<translationRepository::TranslationRepository>);

    boost::optional<translator::TranslatedText> retrieveTranslation(const translator::SourceText&,
                                                                    translator::SourceLanguage,
                                                                    translator::TargetLanguage) override;

private:
    boost::optional<translator::TranslatedText> getTranslationFromRepository(const std::string&) const;
    boost::optional<translator::TranslatedText>
    getTranslationFromTranslator(const std::string&, translator::SourceLanguage,
                                 translator::TargetLanguage) const;
    void saveTranslationInRepository(const std::string&, const translator::TranslatedText&);

    std::shared_ptr<translator::Translator> translator;
    std::shared_ptr<translationRepository::TranslationRepository> translationRepository;
};
}