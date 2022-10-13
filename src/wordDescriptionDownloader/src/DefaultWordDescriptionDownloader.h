#pragma once

#include <memory>

#include "ApiResponseFetcher.h"
#include "WordDescriptionDownloader.h"
#include "WordDescriptionResponseDeserializer.h"
#include "httpClient/HttpClient.h"
#include "wordDescriptionRepository/std::string.h"

namespace glossary::wordDescriptionDownloader
{
class DefaultWordDescriptionDownloader : public WordDescriptionDownloader
{
public:
    DefaultWordDescriptionDownloader(std::unique_ptr<const ApiResponseFetcher>,
                                     std::unique_ptr<const WordDescriptionResponseDeserializer>);

    wordDescriptionRepository::WordDescription
    tryDownloadWordDescription(const wordDescriptionRepository::std::string&,
                               const std::string& wordsApiKey) const override;

private:
    wordDescriptionRepository::Definitions downloadDefinitions(const wordDescriptionRepository::std::string&,
                                                               const std::string& wordsApiKey) const;
    wordDescriptionRepository::Examples downloadExamples(const wordDescriptionRepository::std::string&,
                                                         const std::string& wordsApiKey) const;
    wordDescriptionRepository::Synonyms downloadSynonyms(const wordDescriptionRepository::std::string&,
                                                         const std::string& wordsApiKey) const;
    bool responseCodeIsOk(int) const;

    std::unique_ptr<const ApiResponseFetcher> apiResponseFetcher;
    std::unique_ptr<const WordDescriptionResponseDeserializer> responseDeserializer;
};
}