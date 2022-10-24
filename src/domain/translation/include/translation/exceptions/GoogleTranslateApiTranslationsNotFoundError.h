#pragma once

#include <stdexcept>

namespace glossary::translation::exceptions
{
struct GoogleTranslateApiTranslationsNotFoundError : std::runtime_error
{
    GoogleTranslateApiTranslationsNotFoundError()
        : std::runtime_error("GoogleTranslateApiTranslationsNotFoundError")
    {
    }
};

}
