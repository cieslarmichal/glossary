#pragma once

#include <memory>

#include "AnswerValidator.h"
#include "ConnectionChecker.h"
#include "DictionaryStatisticsCounter.h"
#include "DictionaryTranslationUpdater.h"
#include "Glossary.h"
#include "dictionaryService/DictionaryService.h"
#include "statisticsRepository/StatisticsRepository.h"
#include "translationService/TranslationService.h"
#include "wordDescriptionService/WordDescriptionService.h"

namespace glossary
{
class DefaultGlossary : public Glossary
{
public:
    DefaultGlossary(std::shared_ptr<dictionaryService::DictionaryService>,
                    std::shared_ptr<translationService::TranslationService>,
                    std::shared_ptr<statisticsRepository::StatisticsRepository>,
                    std::shared_ptr<wordDescriptionService::WordDescriptionService>,
                    std::shared_ptr<DictionaryTranslationUpdater>,
                    std::vector<std::shared_ptr<dictionaryService::DictionaryObserver>>,
                    std::unique_ptr<DictionaryStatisticsCounter>, std::unique_ptr<ConnectionChecker>,
                    std::unique_ptr<AnswerValidator>);

    ExternalServicesStatus checkConnectionToExternalServices() const override;
    void updateTranslateApiKeyLocation(const std::string& apiKeyLocation) const override;
    void updateWordsApiKeyLocation(const std::string& apiKeyLocation) const override;

    boost::optional<std::string> getRandomPolishWord() const override;
    boost::optional<std::string> getRandomPolishWord(const DictionaryName&) const override;
    bool verifyPolishWordTranslation(const std::string& polishWord,
                                     const std::string& englishWord) const override;
    Dictionaries getDictionaries() const override;
    DictionaryNames getDictionariesNames() const override;
    DictionaryWords getDictionaryWords(const DictionaryName&) const override;
    void addDictionary(const DictionaryName&) const override;
    void removeDictionary(const DictionaryName&) const override;
    void addEnglishWordToDictionary(const EnglishWord&, const DictionaryName&) const override;
    void addEnglishWordToDictionary(const EnglishWord&, const std::string& translation,
                                    const DictionaryName&) const override;
    void removeEnglishWordFromDictionary(const EnglishWord&, const DictionaryName&) const override;
    void addDictionaryFromFile(const DictionaryName&,
                               const std::string& pathToFileWithDictionaryWords) const override;
    void updateDictionaryWordTranslationManually(const DictionaryName&, const EnglishWord&,
                                                 const std::string& newTranslation) const override;
    void updateDictionaryWordTranslationAutomatically(const DictionaryName&,
                                                      const EnglishWord&) const override;
    void updateDictionaryTranslationsAutomatically(const DictionaryName&) const override;
    WordDescription getEnglishWordDescription(const EnglishWord&) const override;
    boost::optional<std::string> translate(const std::string& textToTranslate,
                                           const std::string& sourceLanguage,
                                           const std::string& targetLanguage) const override;
    std::vector<std::string> getSupportedTranslatorLanguages() const override;
    boost::optional<DictionaryStatistics> getDictionaryStatistics(const DictionaryName&) const override;
    DictionariesStatistics getDictionariesStatistics() const override;
    void resetStatistics() const override;

private:
    void initialize();

    std::shared_ptr<dictionaryService::DictionaryService> dictionaryService;
    std::shared_ptr<translationService::TranslationService> translationRetrieverService;
    std::shared_ptr<statisticsRepository::StatisticsRepository> statisticsRepository;
    std::shared_ptr<wordDescriptionService::WordDescriptionService> wordDescriptionRetrieverService;
    std::shared_ptr<DictionaryTranslationUpdater> dictionaryTranslationUpdater;
    std::vector<std::shared_ptr<dictionaryService::DictionaryObserver>> dictionaryObservers;
    std::unique_ptr<DictionaryStatisticsCounter> dictionaryStatisticsCounter;

    std::unique_ptr<ConnectionChecker> externalServicesConnectionChecker;
    std::unique_ptr<AnswerValidator> answerValidator;
};
}