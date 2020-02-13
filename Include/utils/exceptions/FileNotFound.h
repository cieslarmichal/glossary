#pragma once

#include <stdexcept>

namespace utils::exceptions
{
struct FileNotFound : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}