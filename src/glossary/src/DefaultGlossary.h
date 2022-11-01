#pragma once

#include <memory>

#include "DictionaryStatisticsCounter.h"
#include "DictionaryTranslationUpdater.h"
#include "Glossary.h"

namespace glossary
{
class DefaultGlossary : public Glossary
{
public:
    DefaultGlossary(std::shared_ptr<dictionary::DictionaryService>,
                    std::shared_ptr<translationService::TranslationService>,
                    std::shared_ptr<statistics::StatisticsRepository>,
                    std::shared_ptr<wordDescriptionService::WordDescriptionService>,
                    std::shared_ptr<DictionaryTranslationUpdater>,
                    std::vector<std::shared_ptr<dictionary::DictionaryObserver>>,
                    std::unique_ptr<DictionaryStatisticsCounter>);

    std::optional<std::string> getRandomPolishWord() const override;
    std::optional<std::string> getRandomPolishWord(const std::string&) const override;
    bool verifyPolishWordTranslation(const std::string& polishWord, const std::string& englishWord) const override;
    Dictionaries getDictionaries() const override;
    std::vector<std::string> getDictionariesNames() const override;
    std::vector<DictionaryWord> getDictionaryWords(const std::string&) const override;
    void addDictionary(const std::string&) const override;
    void removeDictionary(const std::string&) const override;
    void addEnglishWordToDictionary(const std::string&, const std::string&) const override;
    void addEnglishWordToDictionary(const std::string&, const std::string& translation,
                                    const std::string&) const override;
    void removeEnglishWordFromDictionary(const std::string&, const std::string&) const override;
    void addDictionaryFromFile(const std::string&, const std::string& pathToFileWithDictionaryWords) const override;
    void updateDictionaryWordTranslationManually(const std::string&, const std::string&,
                                                 const std::string& newTranslation) const override;
    void updateDictionaryWordTranslationAutomatically(const std::string&, const std::string&) const override;
    void updateDictionaryTranslationsAutomatically(const std::string&) const override;
    WordDescription getEnglishWordDescription(const std::string&) const override;
    std::optional<std::string> translate(const std::string& textToTranslate, const std::string& sourceLanguage,
                                         const std::string& targetLanguage) const override;
    std::vector<std::string> getSupportedTranslatorLanguages() const override;
    std::optional<DictionaryStatistics> getDictionaryStatistics(const std::string&) const override;
    DictionariesStatistics getDictionariesStatistics() const override;
    void resetStatistics() const override;

private:
    void initialize();

    std::shared_ptr<dictionary::DictionaryService> dictionaryService;
    std::shared_ptr<translationService::TranslationService> translationRetrieverService;
    std::shared_ptr<statistics::StatisticsRepository> statisticsRepository;
    std::shared_ptr<wordDescriptionService::WordDescriptionService> wordDescriptionRetrieverService;
    std::unique_ptr<DictionaryStatisticsCounter> dictionaryStatisticsCounter;
};
}
