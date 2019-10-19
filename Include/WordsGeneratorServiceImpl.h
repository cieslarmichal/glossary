#pragma once

#include <memory>

#include "Database.h"
#include "DictionaryReader.h"
#include "HtmlWordsCreator.h"
#include "WordsGeneratorService.h"
#include "WordsShuffler.h"

class WordsGeneratorServiceImpl : public WordsGeneratorService
{
public:
    WordsGeneratorServiceImpl();

    Words generateWords() const override;

private:
    void initializeWordsCreatorService();
    void initializeDictionary();
    Word generateWord(const WordWithTranslation&) const;
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