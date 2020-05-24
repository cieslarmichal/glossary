#pragma once

#include <memory>

#include "DictionaryNamesRetriever.h"
#include "DictionaryService.h"
#include "DictionaryWordsRetriever.h"
#include "ObserverService.h"
#include "RandomDictionaryWordRetriever.h"
#include "csvFileReading/DictionaryWordsReader.h"
#include "repository/DictionaryRepository.h"

namespace glossary::dictionaryService
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

    Dictionaries getDictionaries() const override;
    DictionaryNames getDictionaryNames() const override;
    boost::optional<DictionaryWords> getDictionaryWords(const DictionaryName&) const override;
    boost::optional<EnglishWords> getEnglishWords(const DictionaryName&) const override;
    EnglishWords getEnglishWords() const override;
    boost::optional<DictionaryWord> getRandomDictionaryWord() const override;
    boost::optional<DictionaryWord> getRandomDictionaryWord(const DictionaryName&) const override;
    void addDictionary(const DictionaryName&) override;
    void addDictionaryFromFile(const DictionaryName&, const std::string& dictionaryWordsPath) override;
    void addWordToDictionary(const DictionaryWord&, const DictionaryName&) override;
    void removeDictionary(const DictionaryName&) override;
    void removeWordFromDictionary(const EnglishWord& word, const DictionaryName&) override;
    void updateWordTranslationFromDictionary(const EnglishWord&, const std::string&,
                                             const DictionaryName&) override;
    void synchronizeDictionaries() override;
    void registerObserver(DictionaryObserver*) override;
    void removeObserver(DictionaryObserver*) override;

private:
    void notifyObservers(const EnglishWords&) override;

    std::shared_ptr<repository::DictionaryRepository> dictionaryRepository;
    std::unique_ptr<DictionaryNamesRetriever> dictionaryNamesRetriever;
    std::unique_ptr<DictionaryWordsRetriever> dictionaryWordsRetriever;
    std::unique_ptr<RandomDictionaryWordRetriever> randomDictionaryWordRetriever;
    std::unique_ptr<csvFileReading::DictionaryWordsReader> dictionaryWordsReader;
    std::unique_ptr<ObserverService> observerService;
};
}
