#pragma once

#include <memory>

#include "TranslationService.h"
#include "translation/Translator.h"
#include "translationsDb/TranslationsDb.h"

class TranslationServiceImpl : public TranslationService
{
public:
    TranslationServiceImpl(
        std::unique_ptr<translation::Translator>,
        std::shared_ptr<translationsDb::TranslationsDb>);

    boost::optional<translation::TranslatedText>
    translate(const std::string&, translation::SourceLanguage,
              translation::TargetLanguage) override;

private:
    boost::optional<translation::TranslatedText>
    getTranslationFromDb(const std::string&) const;
    boost::optional<translation::TranslatedText>
    getTranslationFromTranslator(const std::string&,
                                 translation::SourceLanguage,
                                 translation::TargetLanguage) const;
    void saveTranslationInDb(const std::string&,
                             const translation::TranslatedText&);

    std::unique_ptr<translation::Translator> translator;
    std::shared_ptr<translationsDb::TranslationsDb> translationsDb;
};