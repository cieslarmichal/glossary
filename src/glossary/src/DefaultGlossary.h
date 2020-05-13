#pragma once

#include <memory>

#include "AnswerValidator.h"
#include "DictionaryTranslationUpdater.h"
#include "ExternalServicesAvailabilityChecker.h"
#include "Glossary.h"
#include "dictionaryService/DictionaryService.h"
#include "statisticsRepository/StatisticsRepository.h"
#include "translationService/TranslationRetrieverService.h"
#include "wordDescriptionService/WordDescriptionRetrieverService.h"

namespace glossary
{
class DefaultGlossary : public Glossary
{
public:
    DefaultGlossary(std::shared_ptr<dictionaryService::DictionaryService>,
                    std::shared_ptr<translationService::TranslationRetrieverService>,
                    std::shared_ptr<statisticsRepository::StatisticsRepository>,
                    std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService>,
                    std::shared_ptr<DictionaryTranslationUpdater>,
                    std::vector<std::shared_ptr<dictionaryService::DictionaryObserver>>,
                    std::unique_ptr<ExternalServicesAvailabilityChecker>, std::unique_ptr<AnswerValidator>);

    ExternalServicesAvailabilityStatus checkConnectionToExternalServices() const override;
    boost::optional<std::string> getRandomPolishWord() const override;
    boost::optional<std::string> getRandomPolishWord(const std::string& dictionaryName) const override;
    bool verifyPolishWordTranslation(const std::string& polishWord,
                                     const std::string& englishWord) const override;
    std::vector<std::string> listDictionariesNames() override;
    std::vector<std::string> listDictionaryWordsFromDictionary(const std::string& dictionaryName) override;
    void addDictionary(const std::string& dictionaryName) const override;
    void removeDictionary(const std::string& dictionaryName) const override;
    void addEnglishWordToDictionary(const std::string& englishWord,
                                    const std::string& dictionaryName) const override;
    void removeEnglishWordFromDictionary(const std::string& englishWord,
                                         const std::string& dictionaryName) const override;
    void addDictionaryFromFile(const std::string& dictionaryName,
                               const std::string& pathToFileWithDictionaryWords) const override;
    void updateDictionaryWordTranslationManually(const std::string& dictionaryName,
                                                 const std::string& englishWord,
                                                 const std::string& newTranslation) const override;
    void updateDictionaryWordTranslationAutomatically(const std::string& dictionaryName,
                                                      const std::string& englishWord) const override;
    void updateDictionaryTranslationsAutomatically(const std::string& dictionaryName) const override;
    std::string getEnglishWordDescription(const std::string& englishWord) const override;
    boost::optional<std::string> translate(const std::string& textToTranslate,
                                           const std::string& sourceLanguage,
                                           const std::string& targetLanguage) const override;
    std::vector<std::string> getSupportedTranslatorLanguages() const override;
    std::vector<std::string> showStatistics() const override;
    void resetStatistics() const override;

private:
    void initialize();

    std::shared_ptr<dictionaryService::DictionaryService> dictionaryService;
    std::shared_ptr<translationService::TranslationRetrieverService> translationRetrieverService;
    std::shared_ptr<statisticsRepository::StatisticsRepository> statisticsRepository;
    std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService> wordDescriptionRetrieverService;
    std::shared_ptr<DictionaryTranslationUpdater> dictionaryTranslationUpdater;
    std::vector<std::shared_ptr<dictionaryService::DictionaryObserver>> dictionaryObservers;

    std::unique_ptr<ExternalServicesAvailabilityChecker> externalServicesConnectionChecker;
    std::unique_ptr<AnswerValidator> answerValidator;
};
}