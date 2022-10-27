#include "WordsApiClientImpl.h"

#include <utility>

#include "fmt/core.h"
#include "nlohmann/json.hpp"

#include "exceptions/InvalidJsonError.h"
#include "exceptions/WordsApiClientError.h"
#include "exceptions/WordsApiJsonResponseMissingRequiredFieldsError.h"
#include "httpClient/HttpStatusCode.h"

namespace glossary::dictionary
{
namespace
{
nlohmann::json parseJsonText(const std::string& jsonText);
void validateFieldExistence(const nlohmann::json& data, const std::string& fieldName);

const std::string definitionsField{"definitions"};
const std::string definitionField{"definition"};
const std::string examplesField{"examples"};
const std::string synonymsField{"synonyms"};
}

WordsApiClientImpl::WordsApiClientImpl(std::shared_ptr<const common::httpClient::HttpClient> httpClientInit,
                                       WordsApiClientConfig configInit)
    : httpClient{std::move(httpClientInit)}, config{std::move(configInit)}
{
}

std::vector<std::string> WordsApiClientImpl::getWordDefinitions(const std::string& englishWord) const
{
    const auto wordDefinitionsUrl = getWordDefinitionsEndpoint(englishWord);

    const auto headers = getHeaders();

    const auto response = httpClient->get({wordDefinitionsUrl, headers});

    if (response.statusCode != common::httpClient::HttpStatusCode::Ok)
    {
        throw exceptions::WordsApiClientError(response.data);
    }

    return parseWordDefinitionsResponseBody(response.data);
}

std::vector<std::string> WordsApiClientImpl::getWordExamples(const std::string& englishWord) const
{
    const auto wordExamplesUrl = getWordExamplesEndpoint(englishWord);

    const auto headers = getHeaders();

    const auto response = httpClient->get({wordExamplesUrl, headers});

    if (response.statusCode != common::httpClient::HttpStatusCode::Ok)
    {
        throw exceptions::WordsApiClientError(response.data);
    }

    return parseWordExamplesResponseBody(response.data);
}

std::vector<std::string> WordsApiClientImpl::getWordSynonyms(const std::string& englishWord) const
{

    const auto wordSynonymsUrl = getWordSynonymsEndpoint(englishWord);

    const auto headers = getHeaders();

    const auto response = httpClient->get({wordSynonymsUrl, headers});

    if (response.statusCode != common::httpClient::HttpStatusCode::Ok)
    {
        throw exceptions::WordsApiClientError(response.data);
    }

    return parseWordSynonymsResponseBody(response.data);
}

std::map<std::string, std::string> WordsApiClientImpl::getHeaders() const
{
    return {{"x-rapidapi-host", config.wordsApiHost}, {"x-rapidapi-key", config.wordsApiKey}};
}

std::string WordsApiClientImpl::getWordDefinitionsEndpoint(const std::string& englishWord) const
{
    return fmt::format("{}/words/{}/definitions", config.wordsApiBaseUrl, englishWord);
}

std::string WordsApiClientImpl::getWordExamplesEndpoint(const std::string& englishWord) const
{
    return fmt::format("{}/words/{}/examples", config.wordsApiBaseUrl, englishWord);
}

std::string WordsApiClientImpl::getWordSynonymsEndpoint(const std::string& englishWord) const
{
    return fmt::format("{}/words/{}/synonyms", config.wordsApiBaseUrl, englishWord);
}

std::vector<std::string> WordsApiClientImpl::parseWordDefinitionsResponseBody(const std::string& responseBody) const
{
    const auto json = parseJsonText(responseBody);

    validateFieldExistence(json, definitionsField);

    std::vector<std::string> definitions;

    for (const auto& definitionData : json[definitionsField])
    {
        validateFieldExistence(definitionData, definitionField);

        definitions.push_back(definitionData[definitionField].get<std::string>());
    }

    return definitions;
}

std::vector<std::string> WordsApiClientImpl::parseWordExamplesResponseBody(const std::string& responseBody) const
{
    const auto json = parseJsonText(responseBody);

    validateFieldExistence(json, examplesField);

    return json[examplesField].get<std::vector<std::string>>();
}

std::vector<std::string> WordsApiClientImpl::parseWordSynonymsResponseBody(const std::string& responseBody) const
{
    const auto json = parseJsonText(responseBody);

    validateFieldExistence(json, synonymsField);

    return json[synonymsField].get<std::vector<std::string>>();
}

namespace
{
nlohmann::json parseJsonText(const std::string& jsonText)
{
    try
    {
        return nlohmann::json::parse(jsonText);
    }
    catch (const std::exception& e)
    {
        throw exceptions::InvalidJsonError{e.what()};
    }
}

void validateFieldExistence(const nlohmann::json& data, const std::string& fieldName)
{
    if (data.find(fieldName) == data.end())
    {
        throw exceptions::WordsApiJsonResponseMissingRequiredFieldsError{fmt::format("Missing {} field.", fieldName)};
    }
}
}

}
