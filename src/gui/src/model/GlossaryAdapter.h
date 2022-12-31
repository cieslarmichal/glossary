#pragma once

#include <memory>
#include <QList>
#include <QObject>
#include <QString>

#include "Glossary.h"

namespace glossary::gui::model
{
class GlossaryAdapter : public QObject
{
    Q_OBJECT
public:
    explicit GlossaryAdapter(std::unique_ptr<Glossary>);

    QString getRandomPolishWord() const;
    QString getRandomPolishWord(const QString& dictionaryName) const;
    dictionary::WordDescription getWordDescription(const QString& englishWord) const;
    bool verifyCorrectnessOfTranslation(const QString& polishWord, const QString& englishWord) const;
    QList<QString> getDictionaryNames() const;
    std::vector<dictionary::Dictionary> getDictionaries() const;
    std::vector<dictionary::DictionaryWord> getDictionaryWords(const QString& dictionaryName) const;
    QStringList getAvailableLanguages() const;
    QString getTranslation(const QString& textToTranslate, const QString& sourceLanguage,
                           const QString& targetLanguage) const;
    DictionaryStatistics getDictionaryStatistics(const QString& dictionaryName) const;
    DictionariesStatistics getDictionariesStatistics() const;

signals:
    void notifyAboutRandomPolishWord(const QString& polishWord) const;
    void notifyGuessTabAboutWordDescription(const dictionary::WordDescription&) const;
    void notifyWordDescriptionTabAboutWordDescription(const dictionary::WordDescription&) const;
    void notifyAboutTranslationVerdict(bool translationVerdict) const;
    void notifyAboutDictionaryWordsUpdate(const std::string&, const std::vector<dictionary::DictionaryWord>&) const;
    void notifyAboutDictionariesUpdate(const std::vector<dictionary::Dictionary>&) const;
    void notifyAboutTranslation(const QString& translatedText) const;
    void notifyAboutAvailableLanguages(const QStringList& availableLanguages) const;
    void notifyAboutDictionaryStatistics(const DictionaryStatistics&) const;
    void notifyAboutDictionariesStatistics(const DictionariesStatistics&) const;

public slots:
    void onRandomPolishWordTriggered() const;
    void onRandomPolishWordFromDictionaryTriggered(const QString& dictionaryName) const;
    void onWordDescriptionTriggeredFromGuessTab(const QString& englishWord) const;
    void onWordDescriptionTriggeredFromWordDescriptionTab(const QString& englishWord) const;
    void onTranslationCorrectnessTriggered(const QString& dictionaryName, const QString& polishWord,
                                           const QString& englishWord) const;
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
    void onTextTranslateRequest(const QString& textToTranslate, const QString& sourceLanguage,
                                const QString& targetLanguage) const;
    void onTranslatorAvailableLanguagesRequest() const;
    void onDictionaryStatisticsRequest(const QString& dictionaryName) const;
    void onDictionariesStatisticsRequest() const;
    void onResetStatistics() const;

private:
    std::unique_ptr<glossary::Glossary> glossary;
};
}
