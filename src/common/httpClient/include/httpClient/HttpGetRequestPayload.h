#pragma once

#include <map>
#include <optional>
#include <string>

#include "collection/StlOperators.h"

namespace common::httpClient
{
struct HttpGetRequestPayload
{
    std::string url;
    std::optional<std::map<std::string, std::string>> headers = std::nullopt;
    std::optional<std::map<std::string, std::string>> queries = std::nullopt;
};

inline bool operator==(const HttpGetRequestPayload& lhs, const HttpGetRequestPayload& rhs)
{
    return (lhs.url == rhs.url && lhs.headers == rhs.headers && lhs.queries == rhs.queries);
}

inline std::ostream& operator<<(std::ostream& os, const HttpGetRequestPayload& getPayload)
{
    return os << "{url:" << getPayload.url << ",headers:" << getPayload.headers
              << ",queries:" << getPayload.queries << "}";
}
}
