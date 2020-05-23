#pragma once

#include <string>

#include "boost/optional.hpp"

namespace glossary::wordDescriptionDownloader
{
class ApiKeyReader
{
public:
    virtual ~ApiKeyReader() = default;

    virtual boost::optional<std::string> readApiKey() const = 0;
};
}