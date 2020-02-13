#pragma once

#include <memory>

#include "HttpWordDescriptionCreator.h"
#include "WordDescriptionService.h"
#include "wordsDescriptionsDb/WordsDescriptionsDb.h"

class WordDescriptionServiceImpl : public WordDescriptionService
{
public:
    WordDescriptionServiceImpl(
        std::unique_ptr<HttpWordDescriptionCreator>,
        std::shared_ptr<wordsDescriptionsDb::WordsDescriptionsDb>);

    boost::optional<wordsDescriptionsDb::WordDescription>
    getWordDescription(const EnglishWord&) override;

private:
    boost::optional<wordsDescriptionsDb::WordDescription>
    getWordDescriptionFromDb(const EnglishWord& englishWord) const;
    boost::optional<wordsDescriptionsDb::WordDescription>
    createWordDescriptionFromHttp(const EnglishWord& englishWord) const;
    void saveWordDescriptionInDb(const wordsDescriptionsDb::WordDescription&);

    std::unique_ptr<HttpWordDescriptionCreator> wordDescriptionCreator;
    std::shared_ptr<wordsDescriptionsDb::WordsDescriptionsDb>
        wordsDescriptionsDb;
};