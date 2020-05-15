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
    const auto dictionaryNames = glossary->listDictionariesNames();

    QList<QString> listOfDictionaryNames;
    for (const auto& dictionaryName : dictionaryNames)
    {
        listOfDictionaryNames.push_back(QString::fromStdString(dictionaryName));
    }

    return listOfDictionaryNames;
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

void GlossaryAdapter::onTranslationCorectnessTriggered(const QString& polishWord,
                                                       const QString& englishWord) const
{
    auto translationCorectnessVerification = verifyCorrectnessOfTranslation(polishWord, englishWord);
    emit notifyAboutTranslationVerdict(translationCorectnessVerification);
}

}
