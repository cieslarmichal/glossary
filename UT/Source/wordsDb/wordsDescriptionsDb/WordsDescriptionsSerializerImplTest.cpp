#include "wordsDb/wordsDescriptionsDb/WordsDescriptionsSerializerImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordsDb::wordsDescriptionsDb;

namespace
{
const WordDescription
    wordDescription1("computer", "komputer",
                     {{{"definition", std::string{"example"}},
                       {"definition2", std::string{"example2"}}},
                      {"sentence"}});
const WordDescription wordDescription2("tea", "herbata", {});
const WordDescription wordDescription3("headphones", "sluchawki", {});
const WordsDescriptions wordsDescriptions{wordDescription1, wordDescription2,
                                          wordDescription3};
const WordsDescriptions emptyWordsDescriptions{};
const std::string invalidJson{"{."};
const std::string expectedSerializedWordsDescriptions{
    R"({"wordsDescriptions":[{"description":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]},"englishWord":"computer","polishWord":"komputer"},{"description":{},"englishWord":"tea","polishWord":"herbata"},{"description":{},"englishWord":"headphones","polishWord":"sluchawki"}]})"};
const std::string serializedWordsDescriptionsWithoutEnglishWordField{
    R"({"wordsDescriptions":[{"polishWord":"komputer","description":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]}}]})"};
const std::string serializedWordsDescriptionsWithoutPolishWordField{
    R"({"wordsDescriptions":[{"polishWord":"komputer","description":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]}}]})"};
const std::string serializedWordsDescriptionsWithoutDescriptionField{
    R"({"wordsDescriptions":[{"polishWord":"komputer","xxx":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]}}]})"};
const std::string serializedWordsDescriptionsWithoutWordsDescriptionsField{
    R"({"xxx":[{"polishWord":"komputer","":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]}}]})"};
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
    givenSerializedWordsDescriptionsWithoutPolishWordField_shouldReturnNoWordsDescriptions)
{
    const auto actualDescriptions = serializer.deserialize(
        serializedWordsDescriptionsWithoutPolishWordField);

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
