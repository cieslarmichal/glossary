#include "WordsDescriptionsSerializerImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordsDescriptionsDb;

namespace
{
const WordDescription wordDescription1{
    "computer",
    {{{"definition", std::string{"example"}},
      {"definition2", std::string{"example2"}}},
     {"sentence"}}};
const WordDescription wordDescription2("tea", {});
const WordDescription wordDescription3("headphones", {});
const WordsDescriptions wordsDescriptions{wordDescription1, wordDescription2,
                                          wordDescription3};
const WordsDescriptions emptyWordsDescriptions{};
const std::string invalidJson{"{."};
const std::string expectedSerializedWordsDescriptions{
    R"({"wordsDescriptions":[{"description":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]},"englishWord":"computer"},{"description":{},"englishWord":"tea"},{"description":{},"englishWord":"headphones"}]})"};
const std::string serializedWordsDescriptionsWithoutEnglishWordField{
    R"({"wordsDescriptions":[{"description":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]}}]})"};
;
const std::string serializedWordsDescriptionsWithoutDescriptionField{
    R"({"wordsDescriptions":[{"":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]}},"englishWord":"computer"]})"};
const std::string serializedWordsDescriptionsWithoutWordsDescriptionsField{
    R"({"xxx":[{"description":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]}}]})"};
const std::string emptySerializedWordsDescriptions{};
}

class WordsDescriptionsSerializerImplTest : public Test
{
public:
    WordsDescriptionsSerializerImpl serializer;
};

TEST_F(WordsDescriptionsSerializerImplTest,
       giveNoWordsDescriptions_shouldReturnEmptyString)
{
    const auto actualSerializedWordsDescriptions =
        serializer.serialize(emptyWordsDescriptions);

    EXPECT_TRUE(actualSerializedWordsDescriptions.empty());
}

TEST_F(WordsDescriptionsSerializerImplTest,
       givenWordsDescriptions_shouldReturnSerializedWordsDescriptions)
{
    const auto actualSerializedWordsDescriptions =
        serializer.serialize(wordsDescriptions);

    EXPECT_EQ(actualSerializedWordsDescriptions,
              expectedSerializedWordsDescriptions);
}

TEST_F(WordsDescriptionsSerializerImplTest,
       givenInvalidJson_shouldReturnNoWordsDescriptions)
{
    const auto actualDescriptions = serializer.deserialize(invalidJson);

    EXPECT_TRUE(actualDescriptions.empty());
}

TEST_F(WordsDescriptionsSerializerImplTest,
       givenJsonWithoutDescriptionsField_shouldReturnNoWordsDescriptions)
{
    const auto actualDescriptions = serializer.deserialize(
        serializedWordsDescriptionsWithoutWordsDescriptionsField);

    EXPECT_TRUE(actualDescriptions.empty());
}

TEST_F(WordsDescriptionsSerializerImplTest,
       giveEmptySerializedWordsDescriptions_shouldReturnEmptyWordsDescriptions)
{
    const auto actualDescriptions =
        serializer.deserialize(emptySerializedWordsDescriptions);

    EXPECT_TRUE(actualDescriptions.empty());
}

TEST_F(WordsDescriptionsSerializerImplTest,
       givenSerializedWordsDescriptions_shouldReturnWordsDescriptions)
{
    const auto actualDescriptions =
        serializer.deserialize(expectedSerializedWordsDescriptions);

    EXPECT_EQ(actualDescriptions, wordsDescriptions);
}

TEST_F(
    WordsDescriptionsSerializerImplTest,
    givenSerializedWordsDescriptionsWithoutEnglishWordField_shouldReturnNoWordsDescriptions)
{
    const auto actualDescriptions = serializer.deserialize(
        serializedWordsDescriptionsWithoutEnglishWordField);

    EXPECT_TRUE(actualDescriptions.empty());
}

TEST_F(
    WordsDescriptionsSerializerImplTest,
    givenSerializedWordsDescriptionsWithoutWordDescriptionField_shouldReturnNoWordsDecriptions)
{
    const auto actualDescriptions = serializer.deserialize(
        serializedWordsDescriptionsWithoutDescriptionField);

    EXPECT_TRUE(actualDescriptions.empty());
}
