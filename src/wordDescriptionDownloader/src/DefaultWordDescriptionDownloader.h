#pragma once

#include <memory>

#include "ApiResponseFetcher.h"
#include "WordDescriptionDownloader.h"
#include "WordDescriptionResponseDeserializer.h"
#include "webConnection/HttpHandler.h"
#include "wordDescriptionRepository/EnglishWord.h"

namespace glossary::wordDescriptionDownloader
{
class DefaultWordDescriptionDownloader : public WordDescriptionDownloader
{
public:
    DefaultWordDescriptionDownloader(std::unique_ptr<const ApiResponseFetcher>,
                                     std::unique_ptr<const WordDescriptionResponseDeserializer>);

    wordDescriptionRepository::WordDescription
    tryDownloadWordDescription(const wordDescriptionRepository::EnglishWord&,
                               const std::string& wordsApiKey) const override;

private:
    wordDescriptionRepository::Definitions downloadDefinitions(const wordDescriptionRepository::EnglishWord&,
                                                               const std::string& wordsApiKey) const;
    wordDescriptionRepository::Examples downloadExamples(const wordDescriptionRepository::EnglishWord&,
                                                         const std::string& wordsApiKey) const;
    wordDescriptionRepository::Synonyms downloadSynonyms(const wordDescriptionRepository::EnglishWord&,
                                                         const std::string& wordsApiKey) const;
    bool responseCodeIsOk(webConnection::ResponseCode) const;

    std::unique_ptr<const ApiResponseFetcher> apiResponseFetcher;
    std::unique_ptr<const WordDescriptionResponseDeserializer> responseDeserializer;
};
}