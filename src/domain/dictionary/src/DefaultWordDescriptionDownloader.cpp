#include "DefaultWordDescriptionDownloader.h"

#include "../include/exceptions/InvalidApiKey.h"

namespace glossary::dictionary
{
namespace
{
const int okResponse{200};
}

DefaultWordDescriptionDownloader::DefaultWordDescriptionDownloader(
    std::unique_ptr<const ApiResponseFetcher> fetcher,
    std::unique_ptr<const WordDescriptionResponseDeserializer> deserializer)
    : apiResponseFetcher{std::move(fetcher)}, responseDeserializer{std::move(deserializer)}
{
}

dictionary::WordDescription
DefaultWordDescriptionDownloader::tryDownloadWordDescription(const std::string& englishWord,
                                                             const std::string& wordsApiKey) const
{
    auto definitions = downloadDefinitions(englishWord, wordsApiKey);

    auto examples = downloadExamples(englishWord, wordsApiKey);

    auto synonyms = downloadSynonyms(englishWord, wordsApiKey);

    return dictionary::WordDescription{englishWord, definitions, examples, synonyms};
}

std::vector<std::string>
DefaultWordDescriptionDownloader::downloadDefinitions(const std::string& englishWord,
                                                      const std::string& wordsApiKey) const
{
    const auto definitionsApiResponse =
        apiResponseFetcher->tryGetWordDefinitionsResponse(englishWord, wordsApiKey);

    if (responseCodeIsOk(definitionsApiResponse.statusCode))
    {
        return responseDeserializer->deserializeDefinitions(definitionsApiResponse.data);
    }
    return {};
}

std::vector<std::string>
DefaultWordDescriptionDownloader::downloadExamples(const std::string& englishWord,
                                                   const std::string& wordsApiKey) const
{
    const auto examplesApiResponse = apiResponseFetcher->tryGetWordExamplesResponse(englishWord, wordsApiKey);

    if (responseCodeIsOk(examplesApiResponse.statusCode))
    {
        return responseDeserializer->deserializeExamples(examplesApiResponse.data);
    }
    return {};
}

std::vector<std::string>
DefaultWordDescriptionDownloader::downloadSynonyms(const std::string& englishWord,
                                                   const std::string& wordsApiKey) const
{

    const auto synonymsApiResponse = apiResponseFetcher->tryGetWordSynonymsResponse(englishWord, wordsApiKey);

    if (responseCodeIsOk(synonymsApiResponse.statusCode))
    {
        return responseDeserializer->deserializeSynonyms(synonymsApiResponse.data);
    }
    return {};
}

bool DefaultWordDescriptionDownloader::responseCodeIsOk(const int responseCode) const
{
    return responseCode == okResponse;
}

}