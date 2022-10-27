#pragma once

#include "gmock/gmock.h"

#include "DictionarySerializer.h"

namespace glossary::dictionary
{
class DictionarySerializerMock : public DictionarySerializer
{
public:
    MOCK_METHOD(std::string, serialize, (const std::vector<Dictionary>&), (const));
    MOCK_METHOD(std::vector<Dictionary>, deserialize, (const std::string&), (const));
};
}
