#include "wordsDb/descriptionsDb/DescriptionsSerializerImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordsDb::descriptionsDb;

namespace
{
const WordDescription word1("computer", "komputer",
                 {{{"definition", std::string{"example"}},
                   {"definition2", std::string{"example2"}}},
                  {"sentence"}});
const WordDescription word2("tea", "herbata", {});
const WordDescription word3("headphones", "sluchawki", {});
const Words words{word1, word2, word3};
const Words emptyWords{};
const std::string expectedSerializedWords{
    R"({"words":[{"englishWord":"computer","polishWord":"komputer","wordDescription":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]}},{"englishWord":"tea","polishWord":"herbata","wordDescription":{}},{"englishWord":"headphones","polishWord":"sluchawki","wordDescription":{}}]})"};
const std::string serializedWordsWithoutEnglishWordField{
    R"({"words":[{"polishWord":"komputer","wordDescription":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]}}]})"};
const std::string serializedWordsWithoutPolishWordField{
    R"({"words":[{"polishWord":"komputer","wordDescription":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]}}]})"};
const std::string serializedWordsWithoutWordDescriptionField{
    R"({"words":[{"polishWord":"komputer","":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]}}]})"};
const std::string emptySerializedWords{};
}

class DescriptionsSerializerImplTest : public Test
{
public:
    DescriptionsSerializerImpl serializer;
};

TEST_F(DescriptionsSerializerImplTest, giveNonWords_shouldReturnEmptyString)
{
    const auto actualSerializedWords = serializer.serialize(emptyWords);

    EXPECT_TRUE(actualSerializedWords.empty());
}

TEST_F(DescriptionsSerializerImplTest, givenWords_shouldReturnSerializedWords)
{
    const auto actualSerializedWords = serializer.serialize(words);

    EXPECT_EQ(actualSerializedWords, expectedSerializedWords);
}

TEST_F(DescriptionsSerializerImplTest,
       giveEmptySerializedWords_shouldReturnEmptyWords)
{
    const auto actualWords = serializer.deserialize(emptySerializedWords);

    EXPECT_TRUE(actualWords.empty());
}

TEST_F(DescriptionsSerializerImplTest, givenSerializedWords_shouldReturnWords)
{
    const auto actualWords = serializer.deserialize(expectedSerializedWords);

    EXPECT_EQ(actualWords, words);
}

TEST_F(DescriptionsSerializerImplTest,
       givenSerializedWordsWithoutEnglishWordField_shouldReturnNoWords)
{
    const auto actualWords =
        serializer.deserialize(serializedWordsWithoutEnglishWordField);

    EXPECT_TRUE(actualWords.empty());
}

TEST_F(DescriptionsSerializerImplTest,
       givenSerializedWordsWithoutPolishWordField_shouldReturnNoWords)
{
    const auto actualWords =
        serializer.deserialize(serializedWordsWithoutPolishWordField);

    EXPECT_TRUE(actualWords.empty());
}

TEST_F(DescriptionsSerializerImplTest,
       givenSerializedWordsWithoutWordDescriptionField_shouldReturnNoWords)
{
    const auto actualWords =
        serializer.deserialize(serializedWordsWithoutWordDescriptionField);

    EXPECT_TRUE(actualWords.empty());
}
