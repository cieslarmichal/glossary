#pragma once

#include <memory>

#include "httpClient/HttpClient.h"
#include "WordsApiClient.h"
#include "WordsApiClientConfig.h"

namespace glossary::dictionary
{
class WordsApiClientImpl : public WordsApiClient
{
public:
    WordsApiClientImpl(std::shared_ptr<const common::httpClient::HttpClient>, WordsApiClientConfig);

    std::vector<std::string> getWordDefinitions(const std::string& englishWord) const;
    std::vector<std::string> getWordExamples(const std::string& englishWord) const;
    std::vector<std::string> getWordSynonyms(const std::string& englishWord) const;

private:
    std::map<std::string, std::string> getHeaders() const;
    std::string getWordDefinitionsEndpoint(const std::string& englishWord) const;
    std::string getWordExamplesEndpoint(const std::string& englishWord) const;
    std::string getWordSynonymsEndpoint(const std::string& englishWord) const;

    std::vector<std::string> parseWordDefinitionsResponseBody(const std::string& responseBody) const;
    std::vector<std::string> parseWordExamplesResponseBody(const std::string& responseBody) const;
    std::vector<std::string> parseWordSynonymsResponseBody(const std::string& responseBody) const;

    std::shared_ptr<const common::httpClient::HttpClient> httpClient;
    const WordsApiClientConfig config;
};
}
