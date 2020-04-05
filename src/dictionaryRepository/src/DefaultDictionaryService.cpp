#include "DefaultDictionaryService.h"

namespace glossary::dictionaryService
{

DefaultDictionaryService::DefaultDictionaryService(
    std::shared_ptr<repository::DictionaryRepository> dictionaryRepositoryInit,
    std::unique_ptr<DictionaryNamesRetriever> namesRetriever,
    std::unique_ptr<DictionaryWordsRetriever> wordsRetriever,
    std::unique_ptr<RandomDictionaryWordRetriever> randomWordRetriever)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)},
      dictionaryNamesRetriever{std::move(namesRetriever)},
      dictionaryWordsRetriever{std::move(wordsRetriever)},
      randomDictionaryWordRetriever{std::move(randomWordRetriever)}
{
}

DictionaryNames DefaultDictionaryService::getDictionaryNames() const
{
    return dictionaryNamesRetriever->retrieveDictionaryNames();
}

DictionaryWords DefaultDictionaryService::getDictionaryWords(const DictionaryName& dictionaryName) const
{
    return dictionaryWordsRetriever->retrieveDictionaryWords(dictionaryName);
}

boost::optional<DictionaryWord> DefaultDictionaryService::getRandomDictionaryWord() const
{
    return randomDictionaryWordRetriever->getRandomDictionaryWord();
}

boost::optional<DictionaryWord>
DefaultDictionaryService::getRandomDictionaryWord(const DictionaryName& dictionaryName) const
{
    return randomDictionaryWordRetriever->getRandomDictionaryWord(dictionaryName);
}

void DefaultDictionaryService::addDictionary(const DictionaryName& dictionaryName)
{
    dictionaryRepository->addDictionary(dictionaryName);
}

void DefaultDictionaryService::addDictionaryFromFile(const DictionaryName& dictionaryName,
                                                     const std::string& filePathToDictionaryWords)
{
    dictionaryRepository->addDictionaryFromFile(dictionaryName, filePathToDictionaryWords);
}

void DefaultDictionaryService::addWordToDictionary(const DictionaryWord& dictionaryWord,
                                                   const DictionaryName& dictionaryName)
{
    dictionaryRepository->addWordToDictionary(dictionaryWord, dictionaryName);
}

void DefaultDictionaryService::removeDictionary(const DictionaryName& dictionaryName)
{
    dictionaryRepository->removeDictionary(dictionaryName);
}

void DefaultDictionaryService::removeWordFromDictionary(const std::string& word,
                                                        const DictionaryName& dictionaryName)
{
    dictionaryRepository->removeWordFromDictionary(word, dictionaryName);
}

}