#pragma once

#include <stdexcept>

namespace common::fileSystem::exceptions
{
struct DirectoryNotFound : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}