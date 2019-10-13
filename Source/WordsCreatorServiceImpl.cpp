#include <iostream>
#include "WordsCreatorServiceImpl.h"

#include "DictionaryReaderImpl.h"
#include "DictionaryAvailabilityHandlerImpl.h"
#include "WordsDatabase.h"
#include "HtmlWordsCreatorImpl.h"
#include "PersistentStorage.h"
#include "FileAccessImpl.h"
#include "WordsSerializerImpl.h"
#include "HtmlReaderImpl.h"
#include "GlossaryHtmlParser.h"
#include "Exceptions/ConnectionFailed.h"


WordsCreatorServiceImpl::WordsCreatorServiceImpl()
{
    initializeWordsCreatorService();
    initializeDictionary();
}

void WordsCreatorServiceImpl::initializeWordsCreatorService()
{
    std::shared_ptr<const FileAccess> fileAccess = std::make_shared<const FileAccessImpl>();
    std::shared_ptr<const WordsSerializer> wordsSerializer = std::make_shared<const WordsSerializerImpl>();
    std::unique_ptr<Storage> storage = std::make_unique<PersistentStorage>(fileAccess, wordsSerializer);
    wordsDb = std::make_unique<WordsDatabase>(std::move(storage));

    std::unique_ptr<const HtmlReader> htmlReader = std::make_unique<HtmlReaderImpl>();
    std::unique_ptr<const HtmlParser> htmlParser = std::make_unique<GlossaryHtmlParser>();
    htmlWordCreator = std::make_unique<HtmlWordsCreatorImpl>(std::move(htmlReader), std::move(htmlParser));

    dictionaryReader = std::make_unique<DictionaryReaderImpl>(fileAccess);
    availabilityHandler = std::make_unique<DictionaryAvailabilityHandlerImpl>(fileAccess);
}

void WordsCreatorServiceImpl::initializeDictionary()
{
    dictionary = dictionaryReader->read();
    dictionaryAvailability = availabilityHandler->read();
}

Words WordsCreatorServiceImpl::createWords() const
{
    Words words;
    for(const auto& wordWithTranslation: dictionary)
    {
        const auto englishWord = wordWithTranslation.englishWord;
        if (dictionaryAvailability.count(englishWord))
        {
            auto word = wordsDb->getWord(englishWord);
            if(word)
            {
                words.push_back(*word);
            }
            else
            {
                //check with internet
                //delete from list availability
            }
            //check if in database
        }
        else
        {
            try
            {
                auto word = htmlWordCreator->createWord(wordWithTranslation);
                words.push_back(word);
                wordsDb->addWord(word);
                availabilityHandler->add({wordWithTranslation.englishWord, true});
            }
            catch (const exceptions::ConnectionFailed& e)
            {
                std::cerr << e.what();
                words.push_back({wordWithTranslation.englishWord, wordWithTranslation.polishTranslation, {}});
            }
        }
    }
    return words;
}






