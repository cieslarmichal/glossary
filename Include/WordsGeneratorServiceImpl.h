#pragma once

#include <memory>

#include "DictionaryReader.h"
#include "HtmlWordsCreator.h"
#include "WordsGeneratorService.h"
#include "WordsShuffler.h"
#include "wordsDb/descriptionsDb/DescriptionsDb.h"

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

    std::unique_ptr<const wordsDb::descriptionsDb::DescriptionsDb> wordsDb;
    std::unique_ptr<const HtmlWordsCreator> htmlWordCreator;
    std::unique_ptr<const DictionaryReader> dictionaryReader;
    std::unique_ptr<const WordsShuffler> wordsShuffler;

    Dictionary dictionary;
};