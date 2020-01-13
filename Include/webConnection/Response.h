#pragma once

#include "ResponseCode.h"
#include "ResponseContent.h"
#include <ostream>

namespace webConnection
{
struct Response
{
    ResponseCode code;
    ResponseContent content;
};

inline bool operator==(const Response& lhs,
                       const Response& rhs)
{
    return (lhs.code == rhs.code &&
            lhs.content == rhs.content);
}

inline std::ostream& operator<<(std::ostream& os,
                                const Response& response)
{
    os << response.code << " "
       << response.content;
    return os;
}

}
