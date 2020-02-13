#pragma once

#include <stdexcept>

namespace exceptions
{
// TODO: move into specific folders where needed
struct ConnectionFailed : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}
