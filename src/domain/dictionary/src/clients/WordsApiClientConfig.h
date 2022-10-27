#pragma once

#include <string>

namespace glossary::dictionary
{
struct WordsApiClientConfig
{
    std::string wordsApiBaseUrl;
    std::string wordsApiHost;
    std::string wordsApiKey;
};
}
