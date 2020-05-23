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

boost::optional<wordDescriptionRepository::WordDescription>
DefaultWordDescriptionDownloader::downloadWordDescription(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    const auto definitions = downloadDefinitions(englishWord);
    if (not definitions)
    {
        return boost::none;
    }
    const auto examples = downloadExamples(englishWord);
    if (not examples)
    {
        return boost::none;
    }
    const auto synonyms = downloadSynonyms(englishWord);
    if (not synonyms)
    {
        return boost::none;
    }
    return wordDescriptionRepository::WordDescription{englishWord, *definitions, *examples, *synonyms};
}

boost::optional<wordDescriptionRepository::Definitions> DefaultWordDescriptionDownloader::downloadDefinitions(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    try
    {
        const auto definitionsApiResponse = apiResponseFetcher->tryGetWordDefinitionsResponse(englishWord);
        if (responseCodeIsOk(definitionsApiResponse.code))
        {
            return responseDeserializer->deserializeDefinitions(definitionsApiResponse.content);
        }
    }
    catch (const webConnection::exceptions::ConnectionFailed& e)
    {
        std::cerr << "Get content from http failed: " << e.what();
    }
    catch (const exceptions::InvalidApiKey& e)
    {
        std::cerr << "Invalid api key: " << e.what();
    }
    return boost::none;
}

boost::optional<wordDescriptionRepository::Examples> DefaultWordDescriptionDownloader::downloadExamples(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    try
    {
        const auto examplesApiResponse = apiResponseFetcher->tryGetWordExamplesResponse(englishWord);
        if (responseCodeIsOk(examplesApiResponse.code))
        {
            return responseDeserializer->deserializeExamples(examplesApiResponse.content);
        }
    }
    catch (const webConnection::exceptions::ConnectionFailed& e)
    {
        std::cerr << "Get content from http failed: " << e.what();
    }
    catch (const exceptions::InvalidApiKey& e)
    {
        std::cerr << "Invalid api key: " << e.what();
    }
    return boost::none;
}

boost::optional<wordDescriptionRepository::Synonyms> DefaultWordDescriptionDownloader::downloadSynonyms(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    try
    {
        const auto synonymsApiResponse = apiResponseFetcher->tryGetWordSynonymsResponse(englishWord);
        if (responseCodeIsOk(synonymsApiResponse.code))
        {
            return responseDeserializer->deserializeSynonyms(synonymsApiResponse.content);
        }
    }
    catch (const webConnection::exceptions::ConnectionFailed& e)
    {
        std::cerr << "Get content from http failed: " << e.what();
    }
    catch (const exceptions::InvalidApiKey& e)
    {
        std::cerr << "Invalid api key: " << e.what();
    }
    return boost::none;
}

bool DefaultWordDescriptionDownloader::responseCodeIsOk(const webConnection::ResponseCode responseCode) const
{
    return responseCode == okResponse;
}

}