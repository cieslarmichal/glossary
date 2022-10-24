#pragma once

#include <string>

namespace glossary::translation
{
struct GoogleTranslateClientConfig
{
    std::string googleTranslateBaseUrl;
    std::string googleTranslateApiKey;
};
}
