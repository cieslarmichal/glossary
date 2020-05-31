#include "DefaultWordDescriptionDownloader.h"

#include "exceptions/InvalidApiKey.h"

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
    const wordDescriptionRepository::EnglishWord& englishWord, const std::string& wordsApiKey) const
{
    auto definitions = downloadDefinitions(englishWord, wordsApiKey);
    auto examples = downloadExamples(englishWord, wordsApiKey);
    auto synonyms = downloadSynonyms(englishWord, wordsApiKey);
    return wordDescriptionRepository::WordDescription{englishWord, definitions, examples, synonyms};
}

wordDescriptionRepository::Definitions DefaultWordDescriptionDownloader::downloadDefinitions(
    const wordDescriptionRepository::EnglishWord& englishWord, const std::string& wordsApiKey) const
{
    const auto definitionsApiResponse =
        apiResponseFetcher->tryGetWordDefinitionsResponse(englishWord, wordsApiKey);
    if (responseCodeIsOk(definitionsApiResponse.code))
    {
        return responseDeserializer->deserializeDefinitions(definitionsApiResponse.content);
    }
    return {};
}

wordDescriptionRepository::Examples
DefaultWordDescriptionDownloader::downloadExamples(const wordDescriptionRepository::EnglishWord& englishWord,
                                                   const std::string& wordsApiKey) const
{
    const auto examplesApiResponse = apiResponseFetcher->tryGetWordExamplesResponse(englishWord, wordsApiKey);
    if (responseCodeIsOk(examplesApiResponse.code))
    {
        return responseDeserializer->deserializeExamples(examplesApiResponse.content);
    }
    return {};
}

wordDescriptionRepository::Synonyms
DefaultWordDescriptionDownloader::downloadSynonyms(const wordDescriptionRepository::EnglishWord& englishWord,
                                                   const std::string& wordsApiKey) const
{

    const auto synonymsApiResponse = apiResponseFetcher->tryGetWordSynonymsResponse(englishWord, wordsApiKey);
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