#include "DefaultWordDescriptionDownloader.h"

#include <iostream>

#include "exceptions/InvalidApiKey.h"
#include "webConnection/exceptions/ConnectionFailed.h"

namespace glossary::wordDescriptionDownloader
{
namespace
{
const webConnection::ResponseCode okResponse{200};
}

DefaultWordDescriptionDownloader::DefaultWordDescriptionDownloader(
    std::unique_ptr<const ApiResponseFetcher> fetcher,
    std::unique_ptr<const WordDescriptionResponseDeserializer> deserializer)
    : apiResponseFetcher{std::move(fetcher)}, responseDeserializer{std::move(deserializer)}
{
}

wordDescriptionRepository::WordDescription DefaultWordDescriptionDownloader::tryDownloadWordDescription(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    auto definitions = downloadDefinitions(englishWord);
    auto examples = downloadExamples(englishWord);
    auto synonyms = downloadSynonyms(englishWord);
    return wordDescriptionRepository::WordDescription{englishWord, definitions, examples, synonyms};
}

wordDescriptionRepository::Definitions DefaultWordDescriptionDownloader::downloadDefinitions(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    const auto definitionsApiResponse = apiResponseFetcher->tryGetWordDefinitionsResponse(englishWord);
    if (responseCodeIsOk(definitionsApiResponse.code))
    {
        return responseDeserializer->deserializeDefinitions(definitionsApiResponse.content);
    }
    return {};
}

wordDescriptionRepository::Examples DefaultWordDescriptionDownloader::downloadExamples(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    const auto examplesApiResponse = apiResponseFetcher->tryGetWordExamplesResponse(englishWord);
    if (responseCodeIsOk(examplesApiResponse.code))
    {
        return responseDeserializer->deserializeExamples(examplesApiResponse.content);
    }
    return {};
}

wordDescriptionRepository::Synonyms DefaultWordDescriptionDownloader::downloadSynonyms(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{

    const auto synonymsApiResponse = apiResponseFetcher->tryGetWordSynonymsResponse(englishWord);
    if (responseCodeIsOk(synonymsApiResponse.code))
    {
        return responseDeserializer->deserializeSynonyms(synonymsApiResponse.content);
    }
    return {};
}

bool DefaultWordDescriptionDownloader::responseCodeIsOk(const webConnection::ResponseCode responseCode) const
{
    return responseCode == okResponse;
}

}