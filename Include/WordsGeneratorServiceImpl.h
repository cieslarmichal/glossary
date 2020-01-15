#pragma once

#include <memory>

#include "DictionaryReader.h"
#include "HtmlWordsCreator.h"
#include "WordsGeneratorService.h"
#include "WordsShuffler.h"
#include "wordsDb/descriptionsDb/Database.h"

class WordsGeneratorServiceImpl : public WordsGeneratorService
{
public:
    WordsGeneratorServiceImpl();

    Word generateWord(const WordWithTranslation&) const override;
    Words generateWords() const override;

private:
    void initializeWordsCreatorService();
    void initializeDictionary();
    boost::optional<Word> getWordFromDatabase(const EnglishWord&) const;
    boost::optional<Word> getWordFromHtml(const WordWithTranslation&) const;
    void addWordToStorage(const Word&) const;
    bool wordIsInStorage(const EnglishWord&) const;

    std::unique_ptr<const Database> wordsDb;
    std::unique_ptr<const HtmlWordsCreator> htmlWordCreator;
    std::unique_ptr<const DictionaryReader> dictionaryReader;
    std::unique_ptr<const WordsShuffler> wordsShuffler;

    Dictionary dictionary;
};