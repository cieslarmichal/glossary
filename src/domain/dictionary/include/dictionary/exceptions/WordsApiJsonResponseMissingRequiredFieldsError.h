#pragma once

#include <stdexcept>

namespace glossary::dictionary::exceptions
{
struct WordsApiJsonResponseMissingRequiredFieldsError : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}
