#pragma once

#include <stdexcept>

namespace glossary::translation::exceptions
{
struct GoogleTranslateApiError : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}
