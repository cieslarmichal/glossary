#pragma once

#include <memory>

#include "TranslationService.h"
#include "translationsDb/TranslationsDb.h"
#include "translator/Translator.h"

class DefaultTranslationService : public TranslationService
{
public:
    DefaultTranslationService(std::unique_ptr<translator::Translator>,
                              std::shared_ptr<translationsDb::TranslationsDb>);

    boost::optional<translator::TranslatedText> translate(const std::string&, translator::SourceLanguage,
                                                          translator::TargetLanguage) override;

private:
    boost::optional<translator::TranslatedText> getTranslationFromDb(const std::string&) const;
    boost::optional<translator::TranslatedText>
    getTranslationFromTranslator(const std::string&, translator::SourceLanguage,
                                 translator::TargetLanguage) const;
    void saveTranslationInDb(const std::string&, const translator::TranslatedText&);

    std::unique_ptr<translator::Translator> translator;
    std::shared_ptr<translationsDb::TranslationsDb> translationsDb;
};