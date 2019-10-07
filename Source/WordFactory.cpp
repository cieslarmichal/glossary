#include "WordFactory.h"

#include <iostream>
#include "Exceptions/ConnectionFailed.h"
#include "HtmlReaderImpl.h"
#include "GlossaryHtmlParser.h"

WordFactory::WordFactory(std::shared_ptr<Database> db) : database{std::move(db)}
{
    htmlReader = std::make_unique<HtmlReaderImpl>(HtmlReaderImpl{});
    htmlParser = std::make_unique<GlossaryHtmlParser>(GlossaryHtmlParser{});
}

std::unique_ptr<Word> WordFactory::createWord(const WordWithTranslation &wordWithTranslation)
{
    WordDescription wordDescription;

    auto wordExistenceInfo = database->getWordExistenceInfo(wordWithTranslation.englishWord);

    if (wordExistenceInfo && wordExistenceInfo->descriptionExists)
    {
        auto tryWordDescription = database->getWordDescription(wordWithTranslation.englishWord);
        if (tryWordDescription)
        {
            wordDescription = *tryWordDescription;
            std::cout << "1";
            return std::make_unique<Word>(wordWithTranslation.englishWord, wordWithTranslation.polishTranslation,
                                          wordDescription);
        }
        else
        {
            std::cerr << "Cant read description";
        }
    }
    else if (not wordExistenceInfo)
    {
        std::string htmlContent;
        try
        {
            const auto urlAddress = "https://www.merriam-webster.com/dictionary/";
            htmlContent = htmlReader->read(urlAddress + wordWithTranslation.englishWord);
        }
        catch (const exceptions::ConnectionFailed &err)
        {
            std::cerr << err.what();
            database->saveWordExistenceInfo({wordWithTranslation.englishWord, false});
            return {};
        }

        auto parsedHtmlContent = htmlParser->parse(htmlContent);
        wordDescription = wordDescriptionParser.parse(parsedHtmlContent);
        database->writeWordWithDescription(EnglishWordWithDescription{wordWithTranslation.englishWord, wordDescription});
        database->saveWordExistenceInfo({wordWithTranslation.englishWord, true});
        std::cout << "2";
        return std::make_unique<Word>(wordWithTranslation.englishWord, wordWithTranslation.polishTranslation,
                                      wordDescription);
    }
    return {};
}