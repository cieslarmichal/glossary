#pragma once

#include <map>
#include <optional>
#include <string>

#include "StlOperators.h"

namespace common::httpClient
{
struct GetPayload
{
    std::string url;
    std::optional<std::map<std::string, std::string>> headers = std::nullopt;
    std::optional<std::map<std::string, std::string>> queries = std::nullopt;
};

inline bool operator==(const GetPayload& lhs, const GetPayload& rhs)
{
    return (lhs.url == rhs.url && lhs.headers == rhs.headers && lhs.queries == rhs.queries);
}

inline std::ostream& operator<<(std::ostream& os, const GetPayload& getPayload)
{
    return os << "{url:" << getPayload.url << ",headers:" << getPayload.headers
              << ",queries:" << getPayload.queries << "}";
}
}
