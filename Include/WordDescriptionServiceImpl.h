#pragma once

#include <memory>

#include "HttpWordDescriptionCreator.h"
#include "WordDescriptionService.h"
#include "wordsDb/wordsDescriptionsDb/WordsDescriptionsDb.h"

class WordDescriptionServiceImpl : public WordDescriptionService
{
public:
    WordDescriptionServiceImpl(
        std::unique_ptr<HttpWordDescriptionCreator>,
        std::shared_ptr<wordsDb::wordsDescriptionsDb::WordsDescriptionsDb>);

    boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>
    getWordDescription(const EnglishWord&) override;

private:
    // TODO:using WordsDescriptionDb =
    // wordsDb::wordsDescriptionsDb::WordsDescriptionsDb;

    boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>
    getWordDescriptionFromDb(const EnglishWord& englishWord) const;
    boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>
    createWordDescriptionFromHttp(const EnglishWord& englishWord) const;
    void saveWordDescriptionInDb(
        const wordsDb::wordsDescriptionsDb::WordDescription&);

    std::unique_ptr<HttpWordDescriptionCreator> wordDescriptionCreator;
    std::shared_ptr<wordsDb::wordsDescriptionsDb::WordsDescriptionsDb>
        wordsDescriptionsDb;
};