#include "WordsDescriptionsJsonSerializer.h"

#include "gtest/gtest.h"
#include <boost/optional/optional_io.hpp>

using namespace ::testing;
using namespace glossary::wordDescriptionRepository;

namespace
{
const Definitions definitions{"definition1", "definition2"};
const Examples examples{"example1", "example2"};
const Synonyms synonyms{"synonym1", "synonym2"};
const WordDescription wordDescription1{"computer", definitions, examples, synonyms};
const WordDescription wordDescription2{"tea", {}, {}, {}};
const WordsDescriptions wordsDescriptions1{wordDescription1, wordDescription2};
const WordsDescriptions wordsDescriptions2{wordDescription2};
const WordsDescriptions emptyWordsDescriptions{};
const std::string invalidJson{"{."};
const std::string expectedSerializedWordsDescriptions =
    R"({"wordsDescriptions":[{"definitions":["definition1","definition2"],"englishWord":"computer","examples":["example1","example2"],"synonyms":["synonym1","synonym2"]},{"definitions":[],"englishWord":"tea","examples":[],"synonyms":[]}]})";
const std::string serializedWordsDescriptionsWithoutWordsDescriptionsField =
    R"({"error":[{"definitions":["definition1","definition2"],"englishWord":"computer","examples":["example1","example2"],"synonyms":["synonym1","synonym2"]},{"definitions":[],"englishWord":"tea","examples":[],"synonyms":[]}]})";
const std::string serializedWordsDescriptionsWithoutEnglishWordField =
    R"({"wordsDescriptions":[{"definitions":["definition1","definition2"],"error":"computer","examples":["example1","example2"],"synonyms":["synonym1","synonym2"]},{"definitions":[],"englishWord":"tea","examples":[],"synonyms":[]}]})";
const std::string serializedWordsDescriptionsWithoutDefinitionsField =
    R"({"wordsDescriptions":[{"error":["definition1","definition2"],"englishWord":"computer","examples":["example1","example2"],"synonyms":["synonym1","synonym2"]},{"definitions":[],"englishWord":"tea","examples":[],"synonyms":[]}]})";
const std::string serializedWordsDescriptionsWithoutExamplesField =
    R"({"wordsDescriptions":[{"definitions":["definition1","definition2"],"englishWord":"computer","error":["example1","example2"],"synonyms":["synonym1","synonym2"]},{"definitions":[],"englishWord":"tea","examples":[],"synonyms":[]}]})";
const std::string serializedWordsDescriptionsWithoutSynonymsField =
    R"({"wordsDescriptions":[{"definitions":["definition1","definition2"],"englishWord":"computer","examples":["example1","example2"],"error":["synonym1","synonym2"]},{"definitions":[],"englishWord":"tea","examples":[],"synonyms":[]}]})";
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
    givenSerializedWordsDescriptionsFirstWithAndSecondWithoutDefinitionsField_shouldReturnFirstWordDecription)
{
    const auto actualDescriptions =
        serializer.deserialize(serializedWordsDescriptionsWithoutDefinitionsField);

    EXPECT_EQ(actualDescriptions, wordsDescriptions2);
}

TEST_F(WordsDescriptionsJsonSerializerTest,
       givenSerializedWordsDescriptionsFirstWithAndSecondWithoutExamplesField_shouldReturnFirstWordDecription)
{
    const auto actualDescriptions = serializer.deserialize(serializedWordsDescriptionsWithoutExamplesField);

    EXPECT_EQ(actualDescriptions, wordsDescriptions2);
}

TEST_F(WordsDescriptionsJsonSerializerTest,
       givenSerializedWordsDescriptionsFirstWithAndSecondWithoutSynonymsField_shouldReturnFirstWordDecription)
{
    const auto actualDescriptions = serializer.deserialize(serializedWordsDescriptionsWithoutSynonymsField);

    EXPECT_EQ(actualDescriptions, wordsDescriptions2);
}