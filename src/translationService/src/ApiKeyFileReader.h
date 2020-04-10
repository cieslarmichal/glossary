#pragma once

#include <string>

#include "boost/optional.hpp"

namespace glossary::translationService
{
class ApiKeyFileReader
{
public:
    virtual ~ApiKeyFileReader() = default;

    virtual boost::optional<std::string> readApiKey() const = 0;
};
}