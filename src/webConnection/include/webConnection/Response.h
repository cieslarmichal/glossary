#pragma once

#include <ostream>

#include "Payload.h"
#include "StatusCode.h"

namespace webConnection
{
struct Response
{
    ResponseCode code;
    ResponseContent content;
};

inline bool operator==(const Response& lhs, const Response& rhs)
{
    return (lhs.code == rhs.code && lhs.content == rhs.content);
}

}
