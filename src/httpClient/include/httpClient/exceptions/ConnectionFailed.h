#pragma once

#include <stdexcept>

namespace httpClient::exceptions
{
struct ConnectionFailed : std::runtime_error
{
    using std::runtime_error::runtime_error;
};
}
