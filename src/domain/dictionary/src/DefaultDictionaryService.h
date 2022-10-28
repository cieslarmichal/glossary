#pragma once

#include <memory>

#include "DictionaryService.h"
#include "DictionaryWordsCsvReader.h"
#include "ObserverService.h"
#include "random/RandomNumberGenerator.h"
#include "repositories/DictionaryRepository.h"

namespace glossary::dictionary
{
class DefaultDictionaryService : public DictionaryService
{
public:
    DefaultDictionaryService(std::shared_ptr<DictionaryRepository>, std::unique_ptr<DictionaryWordsCsvReader>,
                             std::unique_ptr<ObserverService>, std::shared_ptr<common::random::RandomNumberGenerator>);

    std::optional<Dictionary> getDictionary(const std::string& dictionaryName) const override;
    std::vector<Dictionary> getDictionaries() const override;
    std::vector<std::string> getDictionaryNames() const override;
    std::optional<std::vector<DictionaryWord>> getDictionaryWords(const std::string& dictionaryName) const override;
    std::optional<std::vector<std::string>> getEnglishWords(const std::string& dictionaryName) const override;
    std::vector<std::string> getEnglishWords() const override;
    std::optional<DictionaryWord> getRandomDictionaryWord() const override;
    std::optional<DictionaryWord> getRandomDictionaryWord(const std::string& dictionaryName) const override;
    void addDictionary(const std::string& dictionaryName) override;
    void addDictionaryFromFile(const std::string& dictionaryName, const std::string& dictionaryWordsPath) override;
    void addWordToDictionary(const DictionaryWord&, const std::string& dictionaryName) override;
    void removeDictionary(const std::string& dictionaryName) override;
    void removeWordFromDictionary(const std::string& englishWord, const std::string& dictionaryName) override;
    void updateWordTranslationFromDictionary(const std::string& englishWord, const std::string& translation,
                                             const std::string& dictionaryName) override;
    void synchronizeDictionaries() override;
    void registerObserver(DictionaryObserver*) override;
    void removeObserver(DictionaryObserver*) override;

private:
    void notifyObservers(const std::vector<std::string>&) override;
    std::optional<DictionaryWord> randomizeDictionaryWord(const std::vector<DictionaryWord>&) const;

    std::shared_ptr<DictionaryRepository> dictionaryRepository;
    std::unique_ptr<DictionaryWordsCsvReader> dictionaryWordsCsvReader;
    std::unique_ptr<ObserverService> observerService;
    std::shared_ptr<common::random::RandomNumberGenerator> randomNumberGenerator;
};
}
