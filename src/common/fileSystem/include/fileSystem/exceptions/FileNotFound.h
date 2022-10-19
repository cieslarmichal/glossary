#pragma once

#include <stdexcept>

namespace common::fileSystem::exceptions
{
struct FileNotFound : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}