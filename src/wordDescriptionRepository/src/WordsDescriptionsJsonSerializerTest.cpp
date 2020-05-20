#include "WordsDescriptionsJsonSerializer.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::wordDescriptionRepository;

namespace
{
const DefinitionWithExample definitionWithExample1{"definition1", {"example11", "example12"}};
const DefinitionWithExample definitionWithExample2{"definition2", {"example21", "example22"}};
const DefinitionsWithExamples definitionsWithExamples1{definitionWithExample1, definitionWithExample2};
const DefinitionsWithExamples definitionsWithExamples2{definitionWithExample2};
const Sentence sentence1{"sentence1"};
const Sentence sentence2{"sentence2"};
const Sentences sentences1{sentence1, sentence2};
const Sentences sentences2{sentence1};
const WordDescription wordDescription1{"computer", definitionsWithExamples1, sentences1};
const WordDescription wordDescription2{"tea", {}, sentences2};
const WordDescription wordDescription1WithDefinitionErrors{"computer", definitionsWithExamples2, sentences1};
const WordsDescriptions wordsDescriptions1{wordDescription1, wordDescription2};
const WordsDescriptions wordsDescriptions2{wordDescription2};
const WordsDescriptions wordsDescriptions3{wordDescription1WithDefinitionErrors, wordDescription2};
const WordsDescriptions emptyWordsDescriptions{};
const std::string invalidJson{"{."};
const std::string expectedSerializedWordsDescriptions{
    R"({"wordsDescriptions":[{"definitionsWithExamples":[{"definition":"definition1","examples":["example11","example12"]},{"definition":"definition2","examples":["example21","example22"]}],"englishWord":"computer","sentences":["sentence1","sentence2"]},{"definitionsWithExamples":[],"englishWord":"tea","sentences":["sentence1"]}]})"};
const std::string serializedWordsDescriptionsWithoutEnglishWordField{
    R"({"wordsDescriptions":[{"definitionsWithExamples":[{"definition":"definition1","examples":["example11","example12"]},{"definition":"definition2","examples":["example21","example22"]}],"error":"computer","sentences":["sentence1","sentence2"]},{"definitionsWithExamples":[],"englishWord":"tea","sentences":["sentence1"]}]})"};
const std::string serializedWordsDescriptionsWithoutDefinitionsWithExamplesField{
    R"({"wordsDescriptions":[{"error":[{"definition":"definition1","examples":["example11","example12"]},{"definition":"definition2","examples":["example21","example22"]}],"englishWord":"computer","sentences":["sentence1","sentence2"]},{"definitionsWithExamples":[],"englishWord":"tea","sentences":["sentence1"]}]})"};
const std::string serializedWordsDescriptionsWithoutSentencesField{
    R"({"wordsDescriptions":[{"definitionsWithExamples":[{"definition":"definition1","examples":["example11","example12"]},{"definition":"definition2","examples":["example21","example22"]}],"englishWord":"computer","error":["sentence1","sentence2"]},{"definitionsWithExamples":[],"englishWord":"tea","sentences":["sentence1"]}]})"};
const std::string serializedWordsDescriptionsWithoutWordsDescriptionsField{
    R"({"error":[{"definitionsWithExamples":[{"definition":"definition1","examples":["example11","example12"]},{"definition":"definition2","examples":["example21","example22"]}],"englishWord":"computer","sentences":["sentence1","sentence2"]},{"definitionsWithExamples":[],"englishWord":"tea","sentences":["sentence1"]}]})"};
const std::string serializedWordsDescriptionsWithoutDefinitionField{
    R"({"wordsDescriptions":[{"definitionsWithExamples":[{"error":"definition1","examples":["example11","example12"]},{"definition":"definition2","examples":["example21","example22"]}],"englishWord":"computer","sentences":["sentence1","sentence2"]},{"definitionsWithExamples":[],"englishWord":"tea","sentences":["sentence1"]}]})"};
const std::string serializedWordsDescriptionsWithoutExamplesField{
    R"({"wordsDescriptions":[{"definitionsWithExamples":[{"definition":"definition1","error":["example11","example12"]},{"definition":"definition2","examples":["example21","example22"]}],"englishWord":"computer","sentences":["sentence1","sentence2"]},{"definitionsWithExamples":[],"englishWord":"tea","sentences":["sentence1"]}]})"};
const std::string emptySerializedWordsDescriptions{};
}

class WordsDescriptionsJsonSerializerTest : public Test
{
public:
    WordsDescriptionsJsonSerializer serializer;
};

TEST_F(WordsDescriptionsJsonSerializerTest, givenNoWordsDescriptions_shouldReturnEmptyString)
{
    const auto actualSerializedWordsDescriptions = serializer.serialize(emptyWordsDescriptions);

    EXPECT_TRUE(actualSerializedWordsDescriptions.empty());
}

TEST_F(WordsDescriptionsJsonSerializerTest, givenWordsDescriptions_shouldReturnSerializedWordsDescriptions)
{
    const auto actualSerializedWordsDescriptions = serializer.serialize(wordsDescriptions1);

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
       givenEmptySerializedWordsDescriptions_shouldReturnEmptyWordsDescriptions)
{
    const auto actualDescriptions = serializer.deserialize(emptySerializedWordsDescriptions);

    EXPECT_TRUE(actualDescriptions.empty());
}

TEST_F(WordsDescriptionsJsonSerializerTest, givenSerializedWordsDescriptions_shouldReturnWordsDescriptions)
{
    const auto actualDescriptions = serializer.deserialize(expectedSerializedWordsDescriptions);

    EXPECT_EQ(actualDescriptions, wordsDescriptions1);
}

TEST_F(
    WordsDescriptionsJsonSerializerTest,
    givenSerializedWordsDescriptionsFirstWithAndSecondWithoutEnglishWordField_shouldReturnFirstWordDescription)
{
    const auto actualDescriptions =
        serializer.deserialize(serializedWordsDescriptionsWithoutEnglishWordField);

    EXPECT_EQ(actualDescriptions, wordsDescriptions2);
}

TEST_F(
    WordsDescriptionsJsonSerializerTest,
    givenSerializedWordsDescriptionsFirstWithAndSecondWithoutDefinitionsWithExamplesField_shouldReturnFirstWordDecription)
{
    const auto actualDescriptions =
        serializer.deserialize(serializedWordsDescriptionsWithoutDefinitionsWithExamplesField);

    EXPECT_EQ(actualDescriptions, wordsDescriptions2);
}

TEST_F(
    WordsDescriptionsJsonSerializerTest,
    givenSerializedWordsDescriptionsFirstWithAndSecondWithoutSentencesField_shouldReturnFirstWordDecription)
{
    const auto actualDescriptions = serializer.deserialize(serializedWordsDescriptionsWithoutSentencesField);

    EXPECT_EQ(actualDescriptions, wordsDescriptions2);
}

TEST_F(
    WordsDescriptionsJsonSerializerTest,
    givenSerializedWordsDescriptionsSomeWithoutDefinitionField_shouldDeserializeThoseWhichHaveDefinitionField)
{
    const auto actualDescriptions = serializer.deserialize(serializedWordsDescriptionsWithoutDefinitionField);

    EXPECT_EQ(actualDescriptions, wordsDescriptions3);
}

TEST_F(WordsDescriptionsJsonSerializerTest,
       givenSerializedWordsDescriptionsSomeWithoutExampleField_shouldThoseWhichHaveExamplesField)
{
    const auto actualDescriptions = serializer.deserialize(serializedWordsDescriptionsWithoutExamplesField);

    EXPECT_EQ(actualDescriptions, wordsDescriptions3);
}
