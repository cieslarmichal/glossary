#include "TranslationServiceImpl.h"

#include "plog/Log.h"

TranslationServiceImpl::TranslationServiceImpl(std::unique_ptr<translator::Translator> translatorInit,
                                               std::shared_ptr<translationsDb::TranslationsDb> db)
    : translator{std::move(translatorInit)}, translationsDb{std::move(db)}
{
}

boost::optional<translator::TranslatedText>
TranslationServiceImpl::translate(const std::string& sourceText, translator::SourceLanguage sourceLanguage,
                                  translator::TargetLanguage targetLanguage)
{
    LOG_DEBUG << "Translating \"" << sourceText << "\" from " << sourceLanguage << " to " << targetLanguage;

    if (const auto translationFromDb = getTranslationFromDb(sourceText))
    {
        LOG_DEBUG << "Got translation from translations database";
        return translationFromDb;
    }

    if (const auto translationFromTranslator =
            getTranslationFromTranslator(sourceText, sourceLanguage, targetLanguage))
    {
        LOG_DEBUG << "Got translation from translator";
        saveTranslationInDb(sourceText, *translationFromTranslator);
        return translationFromTranslator;
    }

    LOG_DEBUG << "No translation for \"" << sourceText << "\"";
    return boost::none;
}

boost::optional<translator::TranslatedText>
TranslationServiceImpl::getTranslationFromDb(const std::string& sourceText) const
{
    if (const auto translation = translationsDb->getTranslation(sourceText))
    {
        return translator::TranslatedText{translation->translatedText};
    }
    return boost::none;
}

boost::optional<translator::TranslatedText>
TranslationServiceImpl::getTranslationFromTranslator(const std::string& sourceText,
                                                     translator::SourceLanguage sourceLanguage,
                                                     translator::TargetLanguage targetLanguage) const
{
    return translator->translate(sourceText, sourceLanguage, targetLanguage);
}

void TranslationServiceImpl::saveTranslationInDb(const std::string& sourceText,
                                                 const translator::TranslatedText& translatedText)
{
    const auto newTranslation = translationsDb::Translation{translationsDb::SourceText{sourceText},
                                                            translationsDb::TranslatedText{translatedText}};
    translationsDb->addTranslation(newTranslation);
}
