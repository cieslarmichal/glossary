#pragma once

#include "gmock/gmock.h"

#include "ApiKeyFileReader.h"

namespace glossary::translationService
{
class ApiKeyFileReaderMock : public ApiKeyFileReader
{
public:
    MOCK_CONST_METHOD0(readApiKey, boost::optional<std::string>());
};
}