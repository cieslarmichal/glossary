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
    explicit GlossaryAdapter(std::unique_ptr<Glossary>);

    QString getRandomPolishWord() const;
    QString getRandomPolishWord(const QString& dictionaryName) const;
    WordDescription getWordDescription(const QString& englishWord) const;
    bool verifyCorrectnessOfTranslation(const QString& polishWord, const QString& englishWord) const;
    QList<QString> getDictionaryNames() const;
    Dictionaries getDictionaries() const;
    std::vector<DictionaryWord> getDictionaryWords(const QString& dictionaryName) const;
    QStringList getAvailableLanguages() const;
    QString getTranslation(const QString& textToTranslate, const QString& sourceLanguage,
                           const QString& targetLanguage) const;
    DictionaryStatistics getDictionaryStatistics(const QString& dictionaryName) const;
    DictionariesStatistics getDictionariesStatistics() const;
    ExternalServicesStatus getStatusOfConnectionToExternalServices() const;

signals:
    void notifyAboutRandomPolishWord(const QString& polishWord) const;
    void notifyGuessTabAboutWordDescription(const WordDescription&) const;
    void notifyWordDescriptionTabAboutWordDescription(const WordDescription&) const;
    void notifyAboutTranslationVerdict(bool translationVerdict) const;
    void notifyAboutDictionaryWordsUpdate(const std::string&, const std::vector<DictionaryWord>&) const;
    void notifyAboutDictionariesUpdate(const Dictionaries&) const;
    void notifyAboutTranslation(const QString& translatedText) const;
    void notifyAboutAvailableLanguages(const QStringList& availableLanguages) const;
    void notifyAboutDictionaryStatistics(const DictionaryStatistics&) const;
    void notifyAboutDictionariesStatistics(const DictionariesStatistics&) const;
    void notifyAboutExternalServicesStatus(const ExternalServicesStatus&) const;

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
    void onUpdateTranslateApiKeyLocationRequest(const QString& translateApiKeyLocation) const;
    void onUpdateWordsApiKeyLocationRequest(const QString& wordsApiKeyLocation) const;
    void onResetStatistics() const;

private:
    std::unique_ptr<glossary::Glossary> glossary;
};
}
