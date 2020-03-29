#include "WordsDescriptionsJsonSerializer.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordDescriptionRepository;

namespace
{
const DefinitionWithExample definitionWithExample1{"definition1", std::string{"example1"}};
const DefinitionWithExample definitionWithExample2{"definition2", std::string{"example2"}};
const DefinitionsWithExamples definitionsWithExamples{definitionWithExample1, definitionWithExample2};
const WordDescription wordDescription1{EnglishWord{"computer"},
                                       Description{definitionsWithExamples, Sentences{"sentence"}}};
const WordDescription wordDescription2("tea", {});
const WordDescription wordDescription3("headphones", {});
const WordsDescriptions wordsDescriptions{wordDescription1, wordDescription2, wordDescription3};
const WordsDescriptions emptyWordsDescriptions{};
const std::string invalidJson{"{."};
const std::string expectedSerializedWordsDescriptions{
    R"({"wordsDescriptions":[{"description":{"definitionsWithExamples":[{"definition":"definition1","example":"example1"},{"definition":"definition2","example":"example2"}],"sentences":["sentence"]},"englishWord":"computer"},{"description":{},"englishWord":"tea"},{"description":{},"englishWord":"headphones"}]})"};
const std::string serializedWordsDescriptionsWithoutEnglishWordField{
    R"({"wordsDescriptions":[{"description":{"definitionsWithExamples":[{"definition":"definition1","example":"example1"},{"definition":"definition2","example":"example2"}],"sentences":["sentence"]}}]})"};
;
const std::string serializedWordsDescriptionsWithoutDescriptionField{
    R"({"wordsDescriptions":[{"":{"definitionsWithExamples":[{"definition":"definition1","example":"example1"},{"definition":"definition2","example":"example2"}],"sentences":["sentence"]}},"englishWord":"computer"]})"};
const std::string serializedWordsDescriptionsWithoutWordsDescriptionsField{
    R"({"xxx":[{"description":{"definitionsWithExamples":[{"definition":"definition1","example":"example1"},{"definition":"definition2","example":"example2"}],"sentences":["sentence"]}}]})"};
const std::string emptySerializedWordsDescriptions{};
}

class WordsDescriptionsJsonSerializerTest : public Test
{
public:
    WordsDescriptionsJsonSerializer serializer;
};

TEST_F(WordsDescriptionsJsonSerializerTest, giveNoWordsDescriptions_shouldReturnEmptyString)
{
    const auto actualSerializedWordsDescriptions = serializer.serialize(emptyWordsDescriptions);

    EXPECT_TRUE(actualSerializedWordsDescriptions.empty());
}

TEST_F(WordsDescriptionsJsonSerializerTest, givenWordsDescriptions_shouldReturnSerializedWordsDescriptions)
{
    const auto actualSerializedWordsDescriptions = serializer.serialize(wordsDescriptions);

    EXPECT_EQ(actualSerializedWordsDescriptions, expectedSerializedWordsDescriptions);
}

TEST_F(WordsDescriptionsJsonSerializerTest, givenInvalidJson_shouldReturnNoWordsDescriptions)
{
    const auto actualDescriptions = serializer.deserialize(invalidJson);

    EXPECT_TRUE(actualDescriptions.empty());
}

TEST_F(WordsDescriptionsJsonSerializerTest,
       givenJsonWithoutWordsDescriptionsField_shouldReturnNoWordsDescriptions)
{
    const auto actualDescriptions =
        serializer.deserialize(serializedWordsDescriptionsWithoutWordsDescriptionsField);

    EXPECT_TRUE(actualDescriptions.empty());
}

TEST_F(WordsDescriptionsJsonSerializerTest,
       giveEmptySerializedWordsDescriptions_shouldReturnEmptyWordsDescriptions)
{
    const auto actualDescriptions = serializer.deserialize(emptySerializedWordsDescriptions);

    EXPECT_TRUE(actualDescriptions.empty());
}

TEST_F(WordsDescriptionsJsonSerializerTest, givenSerializedWordsDescriptions_shouldReturnWordsDescriptions)
{
    const auto actualDescriptions = serializer.deserialize(expectedSerializedWordsDescriptions);

    EXPECT_EQ(actualDescriptions, wordsDescriptions);
}

TEST_F(WordsDescriptionsJsonSerializerTest,
       givenSerializedWordsDescriptionsWithoutEnglishWordField_shouldReturnNoWordsDescriptions)
{
    const auto actualDescriptions =
        serializer.deserialize(serializedWordsDescriptionsWithoutEnglishWordField);

    EXPECT_TRUE(actualDescriptions.empty());
}

TEST_F(WordsDescriptionsJsonSerializerTest,
       givenSerializedWordsDescriptionsWithoutWordDescriptionField_shouldReturnNoWordsDecriptions)
{
    const auto actualDescriptions =
        serializer.deserialize(serializedWordsDescriptionsWithoutDescriptionField);

    EXPECT_TRUE(actualDescriptions.empty());
}
