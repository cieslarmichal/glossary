#pragma once

#include <map>
#include <ostream>

namespace common::httpClient
{
enum HttpStatusCode
{
    Ok = 200,
    BadRequest = 400,
    Unauthorized = 401,
};

inline std::ostream& operator<<(std::ostream& os, const HttpStatusCode& httpStatusCode)
{
    std::map<HttpStatusCode, std::string> statusCodeToStringMapping{
        {HttpStatusCode::Ok, "Ok"},
        {HttpStatusCode::BadRequest, "BadRequest"},
        {HttpStatusCode::Unauthorized, "Unauthorized"}};

    return os << "HttpStatusCode::" << statusCodeToStringMapping.at(httpStatusCode);
}
}
