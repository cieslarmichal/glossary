#pragma once

#include <string>

namespace glossary::dictionary
{
struct DictionaryConfig
{
    std::string wordsApiBaseUrl;
    std::string wordsApiHost;
    std::string wordsApiKey;
};
}
