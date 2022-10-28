#pragma once

#include "gmock/gmock.h"

#include "WordsDescriptionsSerializer.h"

namespace glossary::dictionary
{

class WordsDescriptionsSerializerMock : public WordsDescriptionsSerializer
{
public:
    MOCK_METHOD(std::string, serialize, (const std::vector<WordDescription>&), (const));
    MOCK_METHOD(std::vector<WordDescription>, deserialize, (const std::string&), (const));
};
}
