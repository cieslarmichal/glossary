#include "WordsGeneratorServiceImpl.h"

#include <iostream>

#include "DictionaryReaderImpl.h"
#include "FileAccessImpl.h"
#include "GlossaryHtmlParser.h"
#include "HtmlWordsCreatorImpl.h"
#include "WordsShufflerImpl.h"
#include "webConnection/HttpRequestHandlerImpl.h"
#include "wordsDb/wordsDescriptionsDb/WordsDescriptionsDbImpl.h"
#include "wordsDb/wordsDescriptionsDb/WordsDescriptionsPersistentStorage.h"
#include "wordsDb/wordsDescriptionsDb/WordsDescriptionsSerializerImpl.h"

WordsGeneratorServiceImpl::WordsGeneratorServiceImpl()
{
    initializeWordsCreatorService();
    initializeDictionary();
}

void WordsGeneratorServiceImpl::initializeWordsCreatorService()
{
    std::shared_ptr<const FileAccess> fileAccess =
        std::make_shared<const FileAccessImpl>();
    std::shared_ptr<
        const wordsDb::wordsDescriptionsDb::WordsDescriptionsSerializer>
        wordsSerializer =
            std::make_shared<const wordsDb::wordsDescriptionsDb::
                                 WordsDescriptionsSerializerImpl>();
    std::unique_ptr<wordsDb::wordsDescriptionsDb::WordsDescriptionsStorage>
        storage = std::make_unique<
            wordsDb::wordsDescriptionsDb::WordsDescriptionsPersistentStorage>(
            fileAccess, wordsSerializer);
    wordsDb =
        std::make_unique<wordsDb::wordsDescriptionsDb::WordsDescriptionsDbImpl>(
            std::move(storage));

    std::unique_ptr<const webConnection::HttpRequestHandler> httpHandler =
        std::make_unique<webConnection::HttpRequestHandlerImpl>();
    std::unique_ptr<const HtmlParser> htmlParser =
        std::make_unique<GlossaryHtmlParser>();
    htmlWordCreator = std::make_unique<HtmlWordsCreatorImpl>(
        std::move(httpHandler), std::move(htmlParser));

    dictionaryReader = std::make_unique<DictionaryReaderImpl>(fileAccess);

    wordsShuffler = std::make_unique<WordsShufflerImpl>();
}

void WordsGeneratorServiceImpl::initializeDictionary()
{
    dictionary = dictionaryReader->read();
}

wordsDb::wordsDescriptionsDb::WordsDescriptions
WordsGeneratorServiceImpl::generateWords() const
{
    wordsDb::wordsDescriptionsDb::WordsDescriptions words;
    int wordsCounter = 0;
    for (const auto& wordWithTranslation : dictionary)
    {
        words.push_back(generateWord(wordWithTranslation));
        std::cout << "Downloading words " << ++wordsCounter << "/"
                  << dictionary.size() << "\n";
    }

    return wordsShuffler->shuffle(words);
}

wordsDb::wordsDescriptionsDb::WordDescription
WordsGeneratorServiceImpl::generateWord(
    const Translation& wordWithTranslation) const
{
    // TODO: if word have empty description check with html once more
    if (const auto wordFromDatabase =
            getWordFromDatabase(wordWithTranslation.englishWord))
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
            return WordDescription(wordWithTranslation.englishWord,
                                   wordWithTranslation.polishWord, {});
        }
    }
}

boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>
WordsGeneratorServiceImpl::getWordFromDatabase(
    const EnglishWord& englishWord) const
{
    if (wordIsInStorage(englishWord))
    {
        return *wordsDb->getWordDescription(englishWord);
    }
    return boost::none;
}

boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>
WordsGeneratorServiceImpl::getWordFromHtml(
    const Translation& wordWithTranslation) const
{
    return htmlWordCreator->createWord(wordWithTranslation);
}

void WordsGeneratorServiceImpl::addWordToStorage(
    const wordsDb::wordsDescriptionsDb::WordDescription& word) const
{
    wordsDb->addWordDescription(word);
}

bool WordsGeneratorServiceImpl::wordIsInStorage(
    const EnglishWord& englishWord) const
{
    return wordsDb->contains(englishWord);
}
