#include "WordDescriptionServiceImpl.h"
#include "plog/Log.h"

WordDescriptionServiceImpl::WordDescriptionServiceImpl(
    std::unique_ptr<HttpWordDescriptionCreator> creator,
    std::shared_ptr<wordsDescriptionsDb::WordsDescriptionsDb> db)
    : wordDescriptionCreator{std::move(creator)}, wordsDescriptionsDb{std::move(db)}
{
}

boost::optional<wordsDescriptionsDb::WordDescription>
WordDescriptionServiceImpl::getWordDescription(const wordsDescriptionsDb::EnglishWord& englishWord)
{
    LOG_DEBUG << "Getting word description for: "<<englishWord;

    if (const auto wordDescriptionFromDb = getWordDescriptionFromDb(englishWord))
    {
        LOG_DEBUG << "Got word description from word descriptions database";
        return wordDescriptionFromDb;
    }

    if (const auto createdWordDescription = createWordDescriptionFromHttp(englishWord))
    {
        LOG_DEBUG << "Got word description from http";
        saveWordDescriptionInDb(*createdWordDescription);
        return createdWordDescription;
    }

    LOG_DEBUG << "No word description for "<< englishWord;
    return boost::none;
}

boost::optional<wordsDescriptionsDb::WordDescription> WordDescriptionServiceImpl::getWordDescriptionFromDb(
    const wordsDescriptionsDb::EnglishWord& englishWord) const
{
    return wordsDescriptionsDb->getWordDescription(englishWord);
}

boost::optional<wordsDescriptionsDb::WordDescription>
WordDescriptionServiceImpl::createWordDescriptionFromHttp(
    const wordsDescriptionsDb::EnglishWord& englishWord) const
{
    return wordDescriptionCreator->createWordDescription(englishWord);
}

void WordDescriptionServiceImpl::saveWordDescriptionInDb(
    const wordsDescriptionsDb::WordDescription& wordDescription)
{
    wordsDescriptionsDb->addWordDescription(wordDescription);
}