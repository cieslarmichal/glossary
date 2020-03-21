#include "WordDescriptionServiceImpl.h"

WordDescriptionServiceImpl::WordDescriptionServiceImpl(
    std::unique_ptr<wordDescriptionDownloader::WordDescriptionDownloader> downloader,
    std::shared_ptr<wordsDescriptionsDb::WordsDescriptionsDb> db)
    : wordDescriptionDownloader{std::move(downloader)}, wordsDescriptionsDb{std::move(db)}
{
}

boost::optional<wordsDescriptionsDb::WordDescription>
WordDescriptionServiceImpl::getWordDescription(const wordsDescriptionsDb::EnglishWord& englishWord)
{
    if (const auto wordDescriptionFromDb = getWordDescriptionFromDb(englishWord))
    {
        return wordDescriptionFromDb;
    }

    if (const auto createdWordDescription = createWordDescriptionFromHttp(englishWord))
    {
        saveWordDescriptionInDb(*createdWordDescription);
        return createdWordDescription;
    }
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
    return wordDescriptionDownloader->downloadWordDescription(englishWord);
}

void WordDescriptionServiceImpl::saveWordDescriptionInDb(
    const wordsDescriptionsDb::WordDescription& wordDescription)
{
    wordsDescriptionsDb->addWordDescription(wordDescription);
}