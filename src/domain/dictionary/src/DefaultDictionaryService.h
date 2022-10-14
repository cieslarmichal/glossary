#pragma once

#include <memory>

#include "DictionaryNamesRetriever.h"
#include "DictionaryService.h"
#include "DictionaryWordsRetriever.h"
#include "ObserverService.h"
#include "RandomDictionaryWordRetriever.h"
#include "csvFileReading/DictionaryWordsReader.h"
#include "repository/DictionaryRepository.h"

namespace glossary::dictionary
{
class DefaultDictionaryService : public DictionaryService
{
public:
    DefaultDictionaryService(std::shared_ptr<repository::DictionaryRepository>,
                             std::unique_ptr<DictionaryNamesRetriever>,
                             std::unique_ptr<DictionaryWordsRetriever>,
                             std::unique_ptr<RandomDictionaryWordRetriever>,
                             std::unique_ptr<csvFileReading::DictionaryWordsReader>,
                             std::unique_ptr<ObserverService>);

    std::optional<Dictionary> getDictionary(const std::string&) const override;
    Dictionaries getDictionaries() const override;
    std::vector<std::string> getDictionaryNames() const override;
    std::vector<std::string>
    getDictionaryNamesContainingEnglishWord(const std::string& englishWord) const override;
    std::vector<std::string> getDictionaryNamesContainingEnglishWordTranslation(
        const std::string& englishWordTranslation) const override;
    std::optional<std::vector<DictionaryWord>> getDictionaryWords(const std::string&) const override;
    std::optional<std::vector<std::string>> getEnglishWords(const std::string&) const override;
    std::vector<std::string> getEnglishWords() const override;
    std::optional<DictionaryWord> getRandomDictionaryWord() const override;
    std::optional<DictionaryWord> getRandomDictionaryWord(const std::string&) const override;
    void addDictionary(const std::string&) override;
    void addDictionaryFromFile(const std::string&, const std::string& dictionaryWordsPath) override;
    void addWordToDictionary(const DictionaryWord&, const std::string&) override;
    void removeDictionary(const std::string&) override;
    void removeWordFromDictionary(const std::string& word, const std::string&) override;
    void updateWordTranslationFromDictionary(const std::string&, const std::string&,
                                             const std::string&) override;
    void synchronizeDictionaries() override;
    void registerObserver(DictionaryObserver*) override;
    void removeObserver(DictionaryObserver*) override;

private:
    void notifyObservers(const std::vector<std::string>&) override;

    std::shared_ptr<repository::DictionaryRepository> dictionaryRepository;
    std::unique_ptr<DictionaryNamesRetriever> dictionaryNamesRetriever;
    std::unique_ptr<DictionaryWordsRetriever> dictionaryWordsRetriever;
    std::unique_ptr<RandomDictionaryWordRetriever> randomDictionaryWordRetriever;
    std::unique_ptr<csvFileReading::DictionaryWordsReader> dictionaryWordsReader;
    std::unique_ptr<ObserverService> observerService;
};
}
