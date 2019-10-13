#pragma once

#include "WordsGeneratorService.h"

#include "DictionaryReader.h"
#include "Database.h"
#include "HtmlWordsCreator.h"

#include <memory>

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
    Dictionary dictionary;
};