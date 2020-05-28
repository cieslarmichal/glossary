#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <memory>

#include "Glossary.h"

namespace glossary::gui::model
{
class GlossaryAdapter : public QObject
{
    Q_OBJECT
public:
    explicit GlossaryAdapter(QObject* parent = nullptr);

    QString getRandomPolishWord() const;
    QString getRandomPolishWord(const QString& dictionaryName) const;
    WordDescription getWordDescription(const QString& englishWord) const;
    bool verifyCorrectnessOfTranslation(const QString& polishWord, const QString& englishWord) const;
    QList<QString> getDictionaryNames() const;
    Dictionaries getDictionaries() const;
    DictionaryWords getDictionaryWords(const QString& dictionaryName) const;

signals:
    void notifyAboutRandomPolishWord(const QString&) const;
    void notifyGuessTabAboutWordDescription(const WordDescription&) const;
    void notifyWordDescriptionTabAboutWordDescription(const WordDescription&) const;
    void notifyAboutTranslationVerdict(bool) const;
    void notifyAboutDictionaryWordsUpdate(const DictionaryName&, const DictionaryWords&) const;
    void notifyAboutDictionariesUpdate(const Dictionaries&) const;

public slots:
    void onRandomPolishWordTriggered() const;
    void onRandomPolishWordFromDictionaryTriggered(const QString& dictionaryName) const;
    void onWordDescriptionTriggeredFromGuessTab(const QString& englishWord) const;
    void onWordDescriptionTriggeredFromWordDescriptionTab(const QString& englishWord) const;
    void onTranslationCorrectnessTriggered(const QString& polishWord, const QString& englishWord) const;
    void onDictionaryAdded(const QString& dictionaryName) const;
    void onDictionaryAddedFromFile(const QString& dictionaryName, const QString& pathToDictionaryWords) const;
    void onDictionaryRemoved(const QString& dictionaryName) const;
    void onDictionaryTranslationsUpdateRequest(const QString& dictionaryName) const;
    void onWordWithTranslationAdded(const QString& dictionaryName, const QString& englishWord,
                                    const QString& translation) const;
    void onWordWithoutTranslationAdded(const QString& dictionaryName, const QString& englishWord) const;
    void onWordRemoved(const QString& dictionaryName, const QString& englishWord) const;
    void onWordTranslationUpdateRequest(const QString& dictionaryName, const QString& englishWord) const;
    void onWordTranslationChanged(const QString& dictionaryName, const QString& englishWord,
                                  const QString& translation) const;

private:
    std::unique_ptr<glossary::Glossary> glossary;
};
}
