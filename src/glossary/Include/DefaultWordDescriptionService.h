#pragma once

#include <memory>

#include "WordDescriptionService.h"
#include "wordDescriptionDownloader/WordDescriptionDownloader.h"
#include "wordsDescriptionsDb/WordsDescriptionsDb.h"

class DefaultWordDescriptionService : public WordDescriptionService
{
public:
    DefaultWordDescriptionService(std::unique_ptr<wordDescriptionDownloader::WordDescriptionDownloader>,
                                  std::shared_ptr<wordsDescriptionsDb::WordsDescriptionsDb>);

    boost::optional<wordsDescriptionsDb::WordDescription>
    getWordDescription(const wordsDescriptionsDb::EnglishWord&) override;

private:
    boost::optional<wordsDescriptionsDb::WordDescription>
    getWordDescriptionFromDb(const wordsDescriptionsDb::EnglishWord& englishWord) const;
    boost::optional<wordsDescriptionsDb::WordDescription>
    createWordDescriptionFromHttp(const wordsDescriptionsDb::EnglishWord& englishWord) const;
    void saveWordDescriptionInDb(const wordsDescriptionsDb::WordDescription&);

    std::unique_ptr<wordDescriptionDownloader::WordDescriptionDownloader> wordDescriptionDownloader;
    std::shared_ptr<wordsDescriptionsDb::WordsDescriptionsDb> wordsDescriptionsDb;
};