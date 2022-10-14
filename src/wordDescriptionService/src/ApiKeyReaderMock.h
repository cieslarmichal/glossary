#pragma once

#include "gmock/gmock.h"

#include "ApiKeyReader.h"

namespace glossary::wordDescriptionService
{
class ApiKeyReaderMock : public ApiKeyReader
{
public:
    MOCK_CONST_METHOD0(readApiKey, std::optional<std::string>());
};
}