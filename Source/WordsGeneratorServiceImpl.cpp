#include <iostream>
#include "WordsGeneratorServiceImpl.h"

#include "DictionaryReaderImpl.h"
#include "WordsDatabase.h"
#include "HtmlWordsCreatorImpl.h"
#include "PersistentStorage.h"
#include "FileAccessImpl.h"
#include "WordsSerializerImpl.h"
#include "HtmlReaderImpl.h"
#include "GlossaryHtmlParser.h"
#include "WordsShufflerImpl.h"

WordsGeneratorServiceImpl::WordsGeneratorServiceImpl()
{
    initializeWordsCreatorService();
    initializeDictionary();
}

void WordsGeneratorServiceImpl::initializeWordsCreatorService()
{
    std::shared_ptr<const FileAccess> fileAccess = std::make_shared<const FileAccessImpl>();
    std::shared_ptr<const WordsSerializer> wordsSerializer = std::make_shared<const WordsSerializerImpl>();
    std::unique_ptr<Storage> storage = std::make_unique<PersistentStorage>(fileAccess, wordsSerializer);
    wordsDb = std::make_unique<WordsDatabase>(std::move(storage));

    std::unique_ptr<const HtmlReader> htmlReader = std::make_unique<HtmlReaderImpl>();
    std::unique_ptr<const HtmlParser> htmlParser = std::make_unique<GlossaryHtmlParser>();
    htmlWordCreator = std::make_unique<HtmlWordsCreatorImpl>(std::move(htmlReader), std::move(htmlParser));

    dictionaryReader = std::make_unique<DictionaryReaderImpl>(fileAccess);

    wordsShuffler = std::make_unique<WordsShufflerImpl>();
}

void WordsGeneratorServiceImpl::initializeDictionary()
{
    dictionary = dictionaryReader->read();
}

Words WordsGeneratorServiceImpl::generateWords() const
{
    Words words;
    int wordsCounter = 0;
    for (const auto& wordWithTranslation: dictionary)
    {
        words.push_back(generateWord(wordWithTranslation));
        std::cout << "Downloading words " << ++wordsCounter << "/" << dictionary.size() << "\n";
    }

    return wordsShuffler->shuffle(words);
}

Word WordsGeneratorServiceImpl::generateWord(const WordWithTranslation& wordWithTranslation) const
{
//TODO: if word have empty description check with html once more
    if (const auto wordFromDatabase = getWordFromDatabase(wordWithTranslation.englishWord))
    {
        return *wordFromDatabase;
    }
    else
    {
        if (const auto wordFromHtml = getWordFromHtml(wordWithTranslation))
        {
            addWordToStorage(*wordFromHtml);
            return *wordFromHtml;
        }
        else
        {
            return Word(wordWithTranslation.englishWord, wordWithTranslation.polishTranslation, {});
        }
    }
}

boost::optional<Word> WordsGeneratorServiceImpl::getWordFromDatabase(const EnglishWord& englishWord) const
{
    if (wordIsInStorage(englishWord))
    {
        return *wordsDb->getWord(englishWord);
    }
    return boost::none;
}

boost::optional<Word> WordsGeneratorServiceImpl::getWordFromHtml(const WordWithTranslation& wordWithTranslation) const
{
    return htmlWordCreator->createWord(wordWithTranslation);
}

void WordsGeneratorServiceImpl::addWordToStorage(const Word& word) const
{
    wordsDb->addWord(word);
}

bool WordsGeneratorServiceImpl::wordIsInStorage(const EnglishWord& englishWord) const
{
    return wordsDb->contains(englishWord);
}

