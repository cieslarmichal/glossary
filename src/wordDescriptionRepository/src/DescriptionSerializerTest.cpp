#include "DescriptionSerializer.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::wordDescriptionRepository;

namespace
{
const DefinitionWithExample definitionWithExample1{"definition1", boost::none};
const DefinitionWithExample definitionWithExample2{"definition2", std::string{"example2"}};
const DefinitionsWithExamples definitionsWithExamples{definitionWithExample1, definitionWithExample2};
const Sentence sentence1{"sentence1"};
const Sentence sentence2{"sentence2"};
const Sentences sentences{sentence1, sentence2};
const Description description{definitionsWithExamples, sentences};
const auto expectedSerializedDescription{
    R"({"definitionsWithExamples":[{"definition":"definition1"},{"definition":"definition2","example":"example2"}],"sentences":["sentence1","sentence2"]})"};
const auto expectedSerializedDescriptionWithoutDefinitionsAndExamples{
    R"({"sentences":["sentence1","sentence2"]})"};
const auto expectedSerializedDescriptionWithoutSentences{
    R"({"definitionsWithExamples":[{"definition":"definition1"},{"definition":"definition2","example":"example2"}]})"};
const DefinitionsWithExamples emptyDefinitionsWithExamples{};
const Sentences emptySentences{};
const Description descriptionWithoutDefinitionsAndExamples{emptyDefinitionsWithExamples, sentences};
const Description descriptionWithoutSentences{definitionsWithExamples, emptySentences};
const Description emptyDescription{emptyDefinitionsWithExamples, emptySentences};
}

class DescriptionSerializerTest : public Test
{
public:
    nlohmann::json prepareJsonFromText(const std::string& jsonText) const
    {
        return nlohmann::json::parse(jsonText);
    }

    DescriptionSerializer serializer;
};

TEST_F(DescriptionSerializerTest, givenEmptyDescription_shouldReturnEmptyJson)
{
    const auto serializedDescription = serializer.serialize(emptyDescription);

    EXPECT_TRUE(serializedDescription.empty());
}

TEST_F(DescriptionSerializerTest, givenDescription_shouldReturnSerializedDescription)
{
    const auto serializedDescription = serializer.serialize(description);

    EXPECT_EQ(serializedDescription.dump(), expectedSerializedDescription);
}

TEST_F(
    DescriptionSerializerTest,
    givenDescriptionWithoutDefinitionsAndExamplesField_shouldReturnSerializedDescriptionWithoutDefinitionsAndExamples)
{
    const auto serializedDescription = serializer.serialize(descriptionWithoutDefinitionsAndExamples);

    EXPECT_EQ(serializedDescription.dump(), expectedSerializedDescriptionWithoutDefinitionsAndExamples);
}

TEST_F(DescriptionSerializerTest,
       givenDescriptionWithoutSentencesField_shouldReturnSerializedDescriptionWithoutSentences)
{
    const auto serializedDescription = serializer.serialize(descriptionWithoutSentences);

    EXPECT_EQ(serializedDescription.dump(), expectedSerializedDescriptionWithoutSentences);
}

TEST_F(DescriptionSerializerTest, givenEmptyJson_shouldReturnEmptyDescription)
{
    const auto serializedDescription = serializer.serialize(emptyDescription);

    EXPECT_TRUE(serializedDescription.empty());
}

TEST_F(DescriptionSerializerTest, givenSerializedDescription_shouldReturnDescription)
{
    const auto serializedDescription = prepareJsonFromText(expectedSerializedDescription);

    const auto actualDescription = serializer.deserialize(serializedDescription);

    EXPECT_EQ(actualDescription, description);
}

TEST_F(
    DescriptionSerializerTest,
    givenSerializedDescriptionWithoutDefinitionsAndExamplesField_shouldReturnDescriptionWithoutDefinitionsAndExamples)
{
    const auto serializedDescription =
        prepareJsonFromText(expectedSerializedDescriptionWithoutDefinitionsAndExamples);

    const auto actualDescription = serializer.deserialize(serializedDescription);

    EXPECT_EQ(actualDescription, descriptionWithoutDefinitionsAndExamples);
    EXPECT_TRUE(actualDescription.definitionsWithExamples.empty());
}

TEST_F(DescriptionSerializerTest,
       givenSerializedDescriptionWithoutSentencesField_shouldReturnDescriptionWithoutSentences)
{
    const auto serializedDescription = prepareJsonFromText(expectedSerializedDescriptionWithoutSentences);

    const auto actualDescription = serializer.deserialize(serializedDescription);

    EXPECT_EQ(actualDescription, descriptionWithoutSentences);
    EXPECT_TRUE(actualDescription.sentences.empty());
}
