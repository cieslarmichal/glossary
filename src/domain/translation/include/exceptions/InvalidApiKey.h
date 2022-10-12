#pragma once

#include <exception>

namespace glossary::translation::exceptions
{
struct InvalidApiKey : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}
