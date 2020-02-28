#include "TranslationServiceImpl.h"

#include <iostream>

TranslationServiceImpl::TranslationServiceImpl(
    std::unique_ptr<translator::Translator> translatorInit,
    std::shared_ptr<translationsDb::TranslationsDb> db)
    : translator{std::move(translatorInit)}, translationsDb{std::move(db)}
{
}

boost::optional<translator::TranslatedText>
TranslationServiceImpl::translate(const std::string& sourceText,
                                  translator::SourceLanguage sourceLanguage,
                                  translator::TargetLanguage targetLanguage)
{
    if (const auto translationFromDb = getTranslationFromDb(sourceText))
    {
        return translationFromDb;
    }

    if (const auto translationFromTranslator = getTranslationFromTranslator(
            sourceText, sourceLanguage, targetLanguage))
    {
        saveTranslationInDb(sourceText, *translationFromTranslator);
        return translationFromTranslator;
    }
    return boost::none;
}

boost::optional<translator::TranslatedText>
TranslationServiceImpl::getTranslationFromDb(
    const std::string& sourceText) const
{
    if (const auto translation = translationsDb->getTranslation(sourceText))
    {
        return translator::TranslatedText{translation->translatedText};
    }
    return boost::none;
}

boost::optional<translator::TranslatedText>
TranslationServiceImpl::getTranslationFromTranslator(
    const std::string& sourceText, translator::SourceLanguage sourceLanguage,
    translator::TargetLanguage targetLanguage) const
{
    return translator->translate(sourceText, sourceLanguage, targetLanguage);
}

void TranslationServiceImpl::saveTranslationInDb(
    const std::string& sourceText,
    const translator::TranslatedText& translatedText)
{
    const auto newTranslation = translationsDb::Translation{
        translationsDb::SourceText{sourceText},
        translationsDb::TranslatedText{translatedText}};
    translationsDb->addTranslation(newTranslation);
}