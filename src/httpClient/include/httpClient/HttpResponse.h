#pragma once

#include <ostream>

namespace httpClient
{
struct HttpResponse
{
    int statusCode;
    std::string data;
};

inline bool operator==(const HttpResponse& lhs, const HttpResponse& rhs)
{
    return (lhs.statusCode == rhs.statusCode && lhs.data == rhs.data);
}

}
