#pragma once

#include <memory>

#include "ApiResponseFetcher.h"
#include "WordDescriptionDownloader.h"
#include "WordDescriptionResponseDeserializer.h"
#include "httpClient/HttpClient.h"

namespace glossary::dictionary
{
class DefaultWordDescriptionDownloader : public WordDescriptionDownloader
{
public:
    DefaultWordDescriptionDownloader(std::unique_ptr<const ApiResponseFetcher>,
                                     std::unique_ptr<const WordDescriptionResponseDeserializer>);

    dictionary::WordDescription tryDownloadWordDescription(const std::string&,
                                                           const std::string& wordsApiKey) const override;

private:
    std::vector<std::string> downloadDefinitions(const std::string&, const std::string& wordsApiKey) const;
    std::vector<std::string> downloadExamples(const std::string&, const std::string& wordsApiKey) const;
    std::vector<std::string> downloadSynonyms(const std::string&, const std::string& wordsApiKey) const;
    bool responseCodeIsOk(int) const;

    std::unique_ptr<const ApiResponseFetcher> apiResponseFetcher;
    std::unique_ptr<const WordDescriptionResponseDeserializer> responseDeserializer;
};
}