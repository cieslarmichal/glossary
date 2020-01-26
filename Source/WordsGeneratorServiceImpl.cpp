#include "WordsGeneratorServiceImpl.h"

#include <iostream>

#include "DictionaryReaderImpl.h"
#include "FileAccessImpl.h"
#include "GlossaryHtmlParser.h"
#include "HtmlWordsCreatorImpl.h"
#include "WordsShufflerImpl.h"
#include "webConnection/HttpRequestHandlerImpl.h"
#include "wordsDb/descriptionsDb/DescriptionsDbImpl.h"
#include "wordsDb/descriptionsDb/DescriptionsPersistentStorage.h"
#include "wordsDb/descriptionsDb/DescriptionsSerializerImpl.h"

WordsGeneratorServiceImpl::WordsGeneratorServiceImpl()
{
    initializeWordsCreatorService();
    initializeDictionary();
}

void WordsGeneratorServiceImpl::initializeWordsCreatorService()
{
    std::shared_ptr<const FileAccess> fileAccess =
        std::make_shared<const FileAccessImpl>();
    std::shared_ptr<const wordsDb::descriptionsDb::DescriptionsSerializer>
        wordsSerializer = std::make_shared<
            const wordsDb::descriptionsDb::DescriptionsSerializerImpl>();
    std::unique_ptr<wordsDb::descriptionsDb::DescriptionsStorage> storage =
        std::make_unique<
            wordsDb::descriptionsDb::DescriptionsPersistentStorage>(
            fileAccess, wordsSerializer);
    wordsDb = std::make_unique<wordsDb::descriptionsDb::DescriptionsDbImpl>(
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

wordsDb::descriptionsDb::WordsDescriptions
WordsGeneratorServiceImpl::generateWords() const
{
    wordsDb::descriptionsDb::WordsDescriptions words;
    int wordsCounter = 0;
    for (const auto& wordWithTranslation : dictionary)
    {
        words.push_back(generateWord(wordWithTranslation));
        std::cout << "Downloading words " << ++wordsCounter << "/"
                  << dictionary.size() << "\n";
    }

    return wordsShuffler->shuffle(words);
}

wordsDb::descriptionsDb::WordDescription
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

boost::optional<wordsDb::descriptionsDb::WordDescription>
WordsGeneratorServiceImpl::getWordFromDatabase(
    const EnglishWord& englishWord) const
{
    if (wordIsInStorage(englishWord))
    {
        return *wordsDb->getWordDescription(englishWord);
    }
    return boost::none;
}

boost::optional<wordsDb::descriptionsDb::WordDescription>
WordsGeneratorServiceImpl::getWordFromHtml(
    const Translation& wordWithTranslation) const
{
    return htmlWordCreator->createWord(wordWithTranslation);
}

void WordsGeneratorServiceImpl::addWordToStorage(
    const wordsDb::descriptionsDb::WordDescription& word) const
{
    wordsDb->addWordDescription(word);
}

bool WordsGeneratorServiceImpl::wordIsInStorage(
    const EnglishWord& englishWord) const
{
    return wordsDb->contains(englishWord);
}
