#pragma once

#include <stdexcept>

namespace glossary::dictionary::exceptions
{
struct WordsApiClientError : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}
