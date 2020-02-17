#pragma once

#include <memory>

#include "DictionaryReader.h"
#include "HttpWordDescriptionCreator.h"
#include "WordsGeneratorService.h"
#include "WordsShuffler.h"
#include "wordsDescriptionsDb/WordDescription.h"
#include "wordsDescriptionsDb/WordsDescriptionsDb.h"

class WordsGeneratorServiceImpl : public WordsGeneratorService
{
public:
    WordsGeneratorServiceImpl();

    Word generateWord(const translationsDb::Translation&) const override;
    std::vector<Word> generateWords() const override;

private:
    void initializeWordsCreatorService();
    void initializeDictionary();
    boost::optional<wordsDescriptionsDb::WordDescription>
    getWordDescriptionFromDatabase(const EnglishWord&) const;
    boost::optional<wordsDescriptionsDb::WordDescription>
    getWordDescriptionFromHttp(const translationsDb::Translation&) const;
    void addWordToStorage(const wordsDescriptionsDb::WordDescription&) const;
    bool wordIsInStorage(const EnglishWord&) const;

    std::shared_ptr<const wordsDescriptionsDb::WordsDescriptionsDb>
        wordsDescriptionsDb;
    std::unique_ptr<const HttpWordDescriptionCreator>
        httpWordDescriptionCreator;
    std::unique_ptr<const DictionaryReader> dictionaryReader;
    std::unique_ptr<const WordsShuffler> wordsShuffler;

    Dictionary dictionary;
};