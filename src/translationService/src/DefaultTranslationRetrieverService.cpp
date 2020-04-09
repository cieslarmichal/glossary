#include "DefaultTranslationRetrieverService.h"

namespace glossary::translationService
{
DefaultTranslationRetrieverService::DefaultTranslationRetrieverService(
    std::shared_ptr<translator::Translator> translatorInit,
    std::shared_ptr<translationRepository::TranslationRepository> repo)
    : translator{std::move(translatorInit)}, translationRepository{std::move(repo)}
{
}

boost::optional<translator::TranslatedText>
DefaultTranslationRetrieverService::retrieveTranslation(const translator::SourceText& sourceText,
                                                        translator::SourceLanguage sourceLanguage,
                                                        translator::TargetLanguage targetLanguage)
{
    if (const auto translationFromRepo = getTranslationFromRepository(sourceText))
        return translationFromRepo;

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
    return translator->translate(sourceText, sourceLanguage, targetLanguage);
}

void DefaultTranslationRetrieverService::saveTranslationInRepository(
    const std::string& sourceText, const translator::TranslatedText& translatedText)
{
    const auto newTranslation = translationRepository::Translation{
        translationRepository::SourceText{sourceText}, translationRepository::TranslatedText{translatedText}};
    translationRepository->addTranslation(newTranslation);
}

}
