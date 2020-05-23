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

    boost::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescription(const wordDescriptionRepository::EnglishWord&) const override;

private:
    boost::optional<wordDescriptionRepository::Definitions>
    downloadDefinitions(const wordDescriptionRepository::EnglishWord&) const;
    boost::optional<wordDescriptionRepository::Examples>
    downloadExamples(const wordDescriptionRepository::EnglishWord&) const;
    boost::optional<wordDescriptionRepository::Synonyms>
    downloadSynonyms(const wordDescriptionRepository::EnglishWord&) const;
    bool responseCodeIsOk(const webConnection::ResponseCode) const;

    std::unique_ptr<const ApiResponseFetcher> apiResponseFetcher;
    std::unique_ptr<const WordDescriptionResponseDeserializer> responseDeserializer;
};
}