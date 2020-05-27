#include "GlossaryAdapter.h"

#include "GlossaryFactory.h"

// TODO: add GuiFactory class
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

void GlossaryAdapter::onWordDescriptionTriggered(const QString& englishName) const
{
    auto wordDescription = getWordDescription(englishName);
    emit notifyAboutWordDescription(wordDescription);
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

}
