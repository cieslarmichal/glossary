#pragma once

#include <optional>
#include <string>

#include "utils/StlOperators.h"

namespace httpClient
{
struct GetPayload
{
    std::string url;
    std::optional<std::vector<std::string>> headers = std::nullopt;
};

inline bool operator==(const GetPayload& lhs, const GetPayload& rhs)
{
    return (lhs.url == rhs.url && lhs.headers == rhs.headers);
}

inline std::ostream& operator<<(std::ostream& os, const GetPayload& getPayload)
{
    return os << "{url:" << getPayload.url << ",headers:" << getPayload.headers << "}";
}
}
