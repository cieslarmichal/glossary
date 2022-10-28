#include "WordsDescriptionsJsonSerializer.h"

#include "gtest/gtest.h"

#include "exceptions/InvalidJsonError.h"
#include "exceptions/WordDescriptionJsonMissingRequiredFieldsError.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::vector<std::string> definitions{"definition1", "definition2"};
const std::vector<std::string> examples{"example1", "example2"};
const std::vector<std::string> synonyms{"synonym1", "synonym2"};
const WordDescription wordDescription1{"computer", definitions, examples, synonyms};
const WordDescription wordDescription2{"tea", {}, {}, {}};
const WordsDescriptions wordsDescriptions1{wordDescription1, wordDescription2};
const WordsDescriptions emptyWordsDescriptions{};
const std::string invalidJson{"{."};
const std::string expectedSerializedWordsDescriptions =
    R"([{"definitions":["definition1","definition2"],"englishWord":"computer","examples":["example1","example2"],"synonyms":["synonym1","synonym2"]},{"definitions":[],"englishWord":"tea","examples":[],"synonyms":[]}])";
const std::string serializedWordsDescriptionsWithoutEnglishWordField =
    R"([{"definitions":["definition1","definition2"],"error":"computer","examples":["example1","example2"],"synonyms":["synonym1","synonym2"]},{"definitions":[],"englishWord":"tea","examples":[],"synonyms":[]}])";
const std::string serializedWordsDescriptionsWithoutDefinitionsField =
    R"([{"error":["definition1","definition2"],"englishWord":"computer","examples":["example1","example2"],"synonyms":["synonym1","synonym2"]},{"definitions":[],"englishWord":"tea","examples":[],"synonyms":[]}])";
const std::string serializedWordsDescriptionsWithoutExamplesField =
    R"([{"definitions":["definition1","definition2"],"englishWord":"computer","error":["example1","example2"],"synonyms":["synonym1","synonym2"]},{"definitions":[],"englishWord":"tea","examples":[],"synonyms":[]}])";
const std::string serializedWordsDescriptionsWithoutSynonymsField =
    R"([{"definitions":["definition1","definition2"],"englishWord":"computer","examples":["example1","example2"],"error":["synonym1","synonym2"]},{"definitions":[],"englishWord":"tea","examples":[],"synonyms":[]}])";
const std::string emptySerializedWordsDescriptions{"[]"};
}

class WordsDescriptionsJsonSerializerTest : public Test
{
public:
    WordsDescriptionsJsonSerializer serializer;
};

TEST_F(WordsDescriptionsJsonSerializerTest, givenNoWordsDescriptions_shouldReturnEmptyJson)
{
    const auto actualSerializedWordsDescriptions = serializer.serialize(emptyWordsDescriptions);

    EXPECT_EQ(actualSerializedWordsDescriptions, "{}");
}

TEST_F(WordsDescriptionsJsonSerializerTest, givenWordsDescriptions_shouldReturnSerializedWordsDescriptions)
{
    const auto actualSerializedWordsDescriptions = serializer.serialize(wordsDescriptions1);

    EXPECT_EQ(actualSerializedWordsDescriptions, expectedSerializedWordsDescriptions);
}

TEST_F(WordsDescriptionsJsonSerializerTest, givenInvalidJson_shouldThrow)
{
    ASSERT_THROW(serializer.deserialize(invalidJson), exceptions::InvalidJsonError);
}

TEST_F(WordsDescriptionsJsonSerializerTest, givenEmptySerializedWordsDescriptions_shouldReturnEmptyWordsDescriptions)
{
    const auto actualWordsDescriptions = serializer.deserialize(emptySerializedWordsDescriptions);

    EXPECT_TRUE(actualWordsDescriptions.empty());
}

TEST_F(WordsDescriptionsJsonSerializerTest, givenSerializedWordsDescriptions_shouldReturnWordsDescriptions)
{
    const auto actualWordsDescriptions = serializer.deserialize(expectedSerializedWordsDescriptions);

    EXPECT_EQ(actualWordsDescriptions, wordsDescriptions1);
}

TEST_F(WordsDescriptionsJsonSerializerTest, givenSerializedWordsDescriptionsWithoutEnglishWordField_shouldThrow)
{
    ASSERT_THROW(serializer.deserialize(serializedWordsDescriptionsWithoutEnglishWordField),
                 exceptions::WordDescriptionJsonMissingRequiredFieldsError);
}

TEST_F(WordsDescriptionsJsonSerializerTest, givenSerializedWordsDescriptionsWithoutDefinitionsField_shouldThrow)
{
    ASSERT_THROW(serializer.deserialize(serializedWordsDescriptionsWithoutDefinitionsField),
                 exceptions::WordDescriptionJsonMissingRequiredFieldsError);
}

TEST_F(WordsDescriptionsJsonSerializerTest, givenSerializedWordsDescriptionsWithoutExamplesField_shouldThrow)
{
    ASSERT_THROW(serializer.deserialize(serializedWordsDescriptionsWithoutExamplesField),
                 exceptions::WordDescriptionJsonMissingRequiredFieldsError);
}

TEST_F(WordsDescriptionsJsonSerializerTest, givenSerializedWordsDescriptionsWithoutSynonymsField_shouldThrow)
{
    ASSERT_THROW(serializer.deserialize(serializedWordsDescriptionsWithoutSynonymsField),
                 exceptions::WordDescriptionJsonMissingRequiredFieldsError);
}
