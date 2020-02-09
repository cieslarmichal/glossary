#pragma once

#include <memory>

#include "DictionaryReader.h"
#include "HttpWordDescriptionCreator.h"
#include "WordsGeneratorService.h"
#include "WordsShuffler.h"
#include "wordsDb/wordsDescriptionsDb/WordsDescriptionsDb.h"

class WordsGeneratorServiceImpl : public WordsGeneratorService
{
public:
    WordsGeneratorServiceImpl();

    WordDescription
    generateWord(const wordsDb::translationsDb::Translation&) const override;
    WordsDescriptions generateWords() const override;

private:
    void initializeWordsCreatorService();
    void initializeDictionary();
    boost::optional<WordDescription>
    getWordFromDatabase(const EnglishWord&) const;
    boost::optional<WordDescription> getWordFromHtml(const Translation&) const;
    void addWordToStorage(const WordDescription&) const;
    bool wordIsInStorage(const EnglishWord&) const;

    std::unique_ptr<const wordsDb::wordsDescriptionsDb::WordsDescriptionsDb>
        wordsDb;
    std::unique_ptr<const HttpWordDescriptionCreator> htmlWordCreator;
    std::unique_ptr<const DictionaryReader> dictionaryReader;
    std::unique_ptr<const WordsShuffler> wordsShuffler;

    Dictionary dictionary;
};