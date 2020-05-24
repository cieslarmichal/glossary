#pragma once

#include <stdexcept>

namespace glossary::wordDescriptionDownloader::exceptions
{
struct InvalidApiKey : std::runtime_error
{
    using std::runtime_error::runtime_error;
};
}
