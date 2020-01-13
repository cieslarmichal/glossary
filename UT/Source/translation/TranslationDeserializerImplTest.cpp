#include "translation/TranslationDeserializerImpl.h"
#include "gtest/gtest.h"

using namespace ::testing;
using namespace translation;

namespace
{
const auto jsonContentWithText = R"({"code":200,"lang":"pl-en","text":["beer"]})";
const auto expectedText = "beer";
const auto jsonContentWithoutText = R"({"code":403,"lang":"pl-en"})";
const auto emptyJson = "";
}

class TranslationDeserializerImplTest : public Test
{
public:
    TranslationDeserializerImpl deserializer;
};

TEST_F(TranslationDeserializerImplTest, givenEmpyJson_shouldReturnEmptyText)
{
    const auto result = deserializer.deserialize(emptyJson);

    ASSERT_TRUE(result.empty());
}

TEST_F(TranslationDeserializerImplTest, givenJsonWithoutTextField_shouldReturnEmptyText)
{
    const auto result = deserializer.deserialize(jsonContentWithoutText);

    ASSERT_TRUE(result.empty());
}

TEST_F(TranslationDeserializerImplTest, givenJsonWithTextField_shouldReturnText)
{
    const auto result = deserializer.deserialize(jsonContentWithText);

    ASSERT_EQ(result, expectedText);
}


