#include "TranslationJsonDeserializer.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace translator;

namespace
{
const auto contentWithSingleWord = R"({"code":200,"lang":"pl-en","text":["beer"]})";
const auto contentWithMultipleWords =
    R"({"code":200,"lang":"pl-en","text":["the castle is a building surrounded by walls"]})";
const auto expectedTextWithSingleWord = "beer";
const auto expectedTextWithMultipleWords = "the castle is a building surrounded by walls";
const auto contentWithoutTextField = R"({"code":403,"lang":"pl-en"})";
const auto invalidJson{"{:"};
const auto emptyJson = "";
}

class TranslationJsonDeserializerTest : public Test
{
public:
    TranslationJsonDeserializer deserializer;
};

TEST_F(TranslationJsonDeserializerTest, givenEmpyJson_shouldReturnEmptyText)
{
    const auto actualText = deserializer.deserialize(emptyJson);

    ASSERT_TRUE(actualText.empty());
}

TEST_F(TranslationJsonDeserializerTest, givenInvalidJson_shouldReturnEmptyText)
{
    const auto actualText = deserializer.deserialize(invalidJson);

    ASSERT_TRUE(actualText.empty());
}

TEST_F(TranslationJsonDeserializerTest, givenJsonWithoutTextField_shouldReturnEmptyText)
{
    const auto actualText = deserializer.deserialize(contentWithoutTextField);

    ASSERT_TRUE(actualText.empty());
}

TEST_F(TranslationJsonDeserializerTest, givenJsonWithSingleWord_shouldReturnThisWord)
{
    const auto actualText = deserializer.deserialize(contentWithSingleWord);

    ASSERT_EQ(actualText, expectedTextWithSingleWord);
}

TEST_F(TranslationJsonDeserializerTest, givenJsonWithMultipleWords_shouldReturnThisWords)
{
    const auto actualText = deserializer.deserialize(contentWithMultipleWords);

    ASSERT_EQ(actualText, expectedTextWithMultipleWords);
}
