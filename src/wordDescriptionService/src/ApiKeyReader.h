#pragma once

#include <string>

#include <optional>

namespace glossary::wordDescriptionService
{
class ApiKeyReader
{
public:
    virtual ~ApiKeyReader() = default;

    virtual std::optional<std::string> readApiKey() const = 0;
};
}