#include "TranslationServiceImpl.h"

#include <iostream>

TranslationServiceImpl::TranslationServiceImpl(
    std::unique_ptr<translation::Translator> translatorInit,
    std::shared_ptr<wordsDb::translationsDb::TranslationsDb> db)
    : translator{std::move(translatorInit)}, translationsDb{std::move(db)}
{
}

boost::optional<translation::TranslatedText>
TranslationServiceImpl::translate(const std::string& sourceText,
                                  translation::SourceLanguage sourceLanguage,
                                  translation::TargetLanguage targetLanguage)
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

boost::optional<translation::TranslatedText>
TranslationServiceImpl::getTranslationFromDb(
    const std::string& sourceText) const
{
    if (const auto translation = translationsDb->getTranslation(sourceText))
    {
        return translation::TranslatedText{translation->englishWord};
    }
    return boost::none;
}

boost::optional<translation::TranslatedText>
TranslationServiceImpl::getTranslationFromTranslator(
    const std::string& sourceText, translation::SourceLanguage sourceLanguage,
    translation::TargetLanguage targetLanguage) const
{
    return translator->translate(sourceText, sourceLanguage, targetLanguage);
}

void TranslationServiceImpl::saveTranslationInDb(
    const std::string& sourceText,
    const translation::TranslatedText& translatedText)
{
    const auto newTranslation = wordsDb::translationsDb::Translation{
        PolishWord{sourceText}, EnglishWord{translatedText}};
    translationsDb->addTranslation(newTranslation);
}
