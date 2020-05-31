#include "GlossaryAdapter.h"

#include "GlossaryFactory.h"

namespace glossary::gui::model
{

GlossaryAdapter::GlossaryAdapter(QObject* parent)
    : QObject(parent), glossary{glossary::GlossaryFactory::createGlossaryFactory()->createGlossary()}
{
}

QString GlossaryAdapter::getRandomPolishWord() const
{
    if (const auto polishWord = glossary->getRandomPolishWord())
    {
        return QString::fromStdString(*polishWord);
    }
    return {"error"};
}

QString GlossaryAdapter::getRandomPolishWord(const QString& dictionaryName) const
{
    if (const auto polishWord = glossary->getRandomPolishWord(dictionaryName.toStdString()))
    {
        return QString::fromStdString(*polishWord);
    }
    return {"error"};
}

WordDescription GlossaryAdapter::getWordDescription(const QString& englishWord) const
{
    return glossary->getEnglishWordDescription(englishWord.toStdString());
}

bool GlossaryAdapter::verifyCorrectnessOfTranslation(const QString& polishWord,
                                                     const QString& englishWord) const
{
    return glossary->verifyPolishWordTranslation(polishWord.toStdString(), englishWord.toStdString());
}

QList<QString> GlossaryAdapter::getDictionaryNames() const
{
    const auto dictionaryNames = glossary->getDictionariesNames();

    QList<QString> listOfDictionaryNames;
    for (const auto& dictionaryName : dictionaryNames)
    {
        listOfDictionaryNames.push_back(QString::fromStdString(dictionaryName));
    }

    return listOfDictionaryNames;
}

Dictionaries GlossaryAdapter::getDictionaries() const
{
    return glossary->getDictionaries();
}

DictionaryWords GlossaryAdapter::getDictionaryWords(const QString& dictionaryName) const
{
    return glossary->getDictionaryWords(dictionaryName.toStdString());
}

QStringList GlossaryAdapter::getAvailableLanguages() const
{
    const auto availableTranslatorLanguages = glossary->getSupportedTranslatorLanguages();

    QList<QString> availableLanguages;
    for (const auto& availableLanguage : availableTranslatorLanguages)
    {
        availableLanguages.push_back(QString::fromStdString(availableLanguage));
    }

    return availableLanguages;
}

QString GlossaryAdapter::getTranslation(const QString& textToTranslate, const QString& sourceLanguage,
                                        const QString& targetLanguage) const
{
    if (auto translation = glossary->translate(textToTranslate.toStdString(), sourceLanguage.toStdString(),
                                               targetLanguage.toStdString()))
    {
        return QString::fromStdString(*translation);
    }
    return {};
}

DictionaryStatistics GlossaryAdapter::getDictionaryStatistics(const QString& dictionaryName) const
{
    if (auto dictionaryStatistics = glossary->getDictionaryStatistics(dictionaryName.toStdString()))
    {
        return *dictionaryStatistics;
    }
    return DictionaryStatistics{dictionaryName.toStdString(), 0, 0};
}

DictionariesStatistics GlossaryAdapter::getDictionariesStatistics() const
{
    return glossary->getDictionariesStatistics();
}

void GlossaryAdapter::onRandomPolishWordTriggered() const
{
    auto randomPolishWord = getRandomPolishWord();
    emit notifyAboutRandomPolishWord(randomPolishWord);
}

void GlossaryAdapter::onRandomPolishWordFromDictionaryTriggered(const QString& dictionaryName) const
{
    auto randomPolishWord = getRandomPolishWord(dictionaryName);
    emit notifyAboutRandomPolishWord(randomPolishWord);
}

void GlossaryAdapter::onWordDescriptionTriggeredFromGuessTab(const QString& englishWord) const
{
    auto wordDescription = getWordDescription(englishWord);
    emit notifyGuessTabAboutWordDescription(wordDescription);
}

void GlossaryAdapter::onWordDescriptionTriggeredFromWordDescriptionTab(const QString& englishWord) const
{
    auto wordDescription = getWordDescription(englishWord);
    emit notifyWordDescriptionTabAboutWordDescription(wordDescription);
}

void GlossaryAdapter::onTranslationCorrectnessTriggered(const QString& polishWord,
                                                        const QString& englishWord) const
{
    auto translationCorrectnessVerification = verifyCorrectnessOfTranslation(polishWord, englishWord);
    emit notifyAboutTranslationVerdict(translationCorrectnessVerification);
}

void GlossaryAdapter::onDictionaryAdded(const QString& dictionaryName) const
{
    glossary->addDictionary(dictionaryName.toStdString());
    auto currentDictionaries = getDictionaries();
    emit notifyAboutDictionariesUpdate(currentDictionaries);
}

void GlossaryAdapter::onDictionaryAddedFromFile(const QString& dictionaryName,
                                                const QString& pathToDictionaryWords) const
{
    glossary->addDictionaryFromFile(dictionaryName.toStdString(), pathToDictionaryWords.toStdString());
    auto currentDictionaries = getDictionaries();
    emit notifyAboutDictionariesUpdate(currentDictionaries);
}

void GlossaryAdapter::onDictionaryRemoved(const QString& dictionaryName) const
{
    glossary->removeDictionary(dictionaryName.toStdString());
    auto currentDictionaries = getDictionaries();
    emit notifyAboutDictionariesUpdate(currentDictionaries);
}

void GlossaryAdapter::onDictionaryTranslationsUpdateRequest(const QString& dictionaryName) const
{
    glossary->updateDictionaryTranslationsAutomatically(dictionaryName.toStdString());
    auto currentDictionaryWords = getDictionaryWords(dictionaryName);
    emit notifyAboutDictionaryWordsUpdate(dictionaryName.toStdString(), currentDictionaryWords);
}

void GlossaryAdapter::onWordWithTranslationAdded(const QString& dictionaryName, const QString& englishWord,
                                                 const QString& translation) const
{
    glossary->addEnglishWordToDictionary(englishWord.toStdString(), translation.toStdString(),
                                         dictionaryName.toStdString());
    auto currentDictionaryWords = getDictionaryWords(dictionaryName);
    emit notifyAboutDictionaryWordsUpdate(dictionaryName.toStdString(), currentDictionaryWords);
}

void GlossaryAdapter::onWordWithoutTranslationAdded(const QString& dictionaryName,
                                                    const QString& englishWord) const
{
    glossary->addEnglishWordToDictionary(englishWord.toStdString(), dictionaryName.toStdString());
    auto currentDictionaryWords = getDictionaryWords(dictionaryName);
    emit notifyAboutDictionaryWordsUpdate(dictionaryName.toStdString(), currentDictionaryWords);
}

void GlossaryAdapter::onWordRemoved(const QString& dictionaryName, const QString& englishWord) const
{
    glossary->removeEnglishWordFromDictionary(englishWord.toStdString(), dictionaryName.toStdString());
    auto currentDictionaryWords = getDictionaryWords(dictionaryName);
    emit notifyAboutDictionaryWordsUpdate(dictionaryName.toStdString(), currentDictionaryWords);
}

void GlossaryAdapter::onWordTranslationUpdateRequest(const QString& dictionaryName,
                                                     const QString& englishWord) const
{
    glossary->updateDictionaryWordTranslationAutomatically(dictionaryName.toStdString(),
                                                           englishWord.toStdString());
    auto currentDictionaryWords = getDictionaryWords(dictionaryName);
    emit notifyAboutDictionaryWordsUpdate(dictionaryName.toStdString(), currentDictionaryWords);
}

void GlossaryAdapter::onWordTranslationChanged(const QString& dictionaryName, const QString& englishWord,
                                               const QString& translation) const
{
    glossary->updateDictionaryWordTranslationManually(dictionaryName.toStdString(), englishWord.toStdString(),
                                                      translation.toStdString());
    auto currentDictionaryWords = getDictionaryWords(dictionaryName);
    emit notifyAboutDictionaryWordsUpdate(dictionaryName.toStdString(), currentDictionaryWords);
}

void GlossaryAdapter::onTextTranslateRequest(const QString& textToTranslate, const QString& sourceLanguage,
                                             const QString& targetLanguage) const
{
    auto translation = getTranslation(textToTranslate, sourceLanguage, targetLanguage);
    emit notifyAboutTranslation(translation);
}

void GlossaryAdapter::onTranslatorAvailableLanguagesRequest() const
{
    auto availableLanguages = getAvailableLanguages();
    emit notifyAboutAvailableLanguages(availableLanguages);
}

void GlossaryAdapter::onDictionaryStatisticsRequest(const QString& dictionaryName) const
{
    auto dictionaryStatistics = getDictionaryStatistics(dictionaryName);
    emit notifyAboutDictionaryStatistics(dictionaryStatistics);
}

void GlossaryAdapter::onDictionariesStatisticsRequest() const
{
    auto dictionariesStatistics = getDictionariesStatistics();
    emit notifyAboutDictionariesStatistics(dictionariesStatistics);
}

}
