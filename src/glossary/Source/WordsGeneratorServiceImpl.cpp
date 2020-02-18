#include "WordsGeneratorServiceImpl.h"

#include <iostream>

#include "DescriptionParserImpl.h"
#include "DictionaryReaderImpl.h"
#include "GlossaryHtmlParserImpl.h"
#include "HttpWordDescriptionCreatorImpl.h"
#include "WordsShufflerImpl.h"
#include "utils/FileAccessImpl.h"
#include "webConnection/HttpHandlerFactory.h"
#include "wordsDescriptionsDb/WordsDescriptionsDbFactory.h"

WordsGeneratorServiceImpl::WordsGeneratorServiceImpl()
{
    initializeWordsCreatorService();
    initializeDictionary();
}

void WordsGeneratorServiceImpl::initializeWordsCreatorService()
{
    std::shared_ptr<const utils::FileAccess> fileAccess =
        std::make_shared<const utils::FileAccessImpl>();

    std::unique_ptr<const wordsDescriptionsDb::WordsDescriptionsDbFactory>
        wordsDescriptionsDbFactory =
            wordsDescriptionsDb::WordsDescriptionsDbFactory::
                createWordsDescriptionsDbFactory(fileAccess);
    wordsDescriptionsDb =
        wordsDescriptionsDbFactory->createWordsDescriptionDb();

    std::unique_ptr<const webConnection::HttpHandlerFactory>
        httpHandlerFactory =
            webConnection::HttpHandlerFactory::createHttpHandlerFactory();

    std::unique_ptr<const webConnection::HttpHandler> httpHandler =
        httpHandlerFactory->createHttpHandler();

    std::unique_ptr<const GlossaryHtmlParser> htmlParser =
        std::make_unique<GlossaryHtmlParserImpl>();
    std::unique_ptr<const DescriptionParser> descriptionParser =
        std::make_unique<DescriptionParserImpl>();
    httpWordDescriptionCreator =
        std::make_unique<HttpWordDescriptionCreatorImpl>(
            std::move(httpHandler), std::move(htmlParser),
            std::move(descriptionParser));

    dictionaryReader = std::make_unique<DictionaryReaderImpl>(fileAccess);

    wordsShuffler = std::make_unique<WordsShufflerImpl>();
}

void WordsGeneratorServiceImpl::initializeDictionary()
{
    dictionary = dictionaryReader->read();
}

std::vector<Word> WordsGeneratorServiceImpl::generateWords() const
{
    std::vector<Word> words;
    int wordsCounter = 0;
    for (const auto& wordWithTranslation : dictionary)
    {
        words.push_back(generateWord(wordWithTranslation));
        std::cout << "Downloading words " << ++wordsCounter << "/"
                  << dictionary.size() << "\n";
    }

    return wordsShuffler->shuffle(words);
}

Word WordsGeneratorServiceImpl::generateWord(
    const translationsDb::Translation& wordWithTranslation) const
{
    // TODO: if word have empty description check with html once more
    if (const auto wordFromDatabase =
            getWordDescriptionFromDatabase(wordWithTranslation.translatedText))
    {
        return {wordWithTranslation.sourceText,
                wordWithTranslation.translatedText, *wordFromDatabase};
    }
    else
    {
        if (const auto wordFromHttp =
                getWordDescriptionFromHttp(wordWithTranslation.translatedText))
        {
            addWordToStorage(*wordFromHttp);
            return {wordWithTranslation.sourceText,
                    wordWithTranslation.translatedText, *wordFromHttp};
        }
        else
        {
            return {wordWithTranslation.sourceText,
                    wordWithTranslation.translatedText,
                    {}};
        }
    }
}

boost::optional<wordsDescriptionsDb::WordDescription>
WordsGeneratorServiceImpl::getWordDescriptionFromDatabase(
    const EnglishWord& englishWord) const
{
    if (wordIsInStorage(englishWord))
    {
        return *wordsDescriptionsDb->getWordDescription(englishWord);
    }

    return boost::none;
}

boost::optional<wordsDescriptionsDb::WordDescription>
WordsGeneratorServiceImpl::getWordDescriptionFromHttp(
    const wordsDescriptionsDb::EnglishWord& englishWord) const
{
    return httpWordDescriptionCreator->createWordDescription(
        englishWord);
}

void WordsGeneratorServiceImpl::addWordToStorage(
    const wordsDescriptionsDb::WordDescription& word) const
{
    wordsDescriptionsDb->addWordDescription(word);
}

bool WordsGeneratorServiceImpl::wordIsInStorage(
    const EnglishWord& englishWord) const
{
    return wordsDescriptionsDb->contains(englishWord);
}
