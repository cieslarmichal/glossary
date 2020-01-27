#include "wordsDb/wordsDescriptionsDb/DescriptionSerializer.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordsDb::wordsDescriptionsDb;

namespace
{
const DefinitionWithExample definitionWithExample1{"definition1", boost::none};
const DefinitionWithExample definitionWithExample2{"definition2",
                                                   std::string{"example"}};
const DefinitionsWithExamples definitionsWithExamples{definitionWithExample1,
                                                      definitionWithExample2};
const Sentence sentence1{"sentence1"};
const Sentence sentence2{"sentence2"};
const Sentences sentences{sentence1, sentence2};
const Description description{definitionsWithExamples, sentences};
const auto expectedSerializedDescription{
    R"({"definitionsWithExamples":["definition1","definition2:example"],"sentences":["sentence1","sentence2"]})"};
const auto expectedSerializedDescriptionWithoutDefinitionsAndExamples{
    R"({"sentences":["sentence1","sentence2"]})"};
const auto expectedSerializedDescriptionWithoutSentences{
    R"({"definitionsWithExamples":["definition1","definition2:example"]})"};
constexpr auto definitionsWithExamplesField = "definitionsWithExamples";
constexpr auto sentencesField = "sentences";
const DefinitionsWithExamples emptyDefinitionsWithExamples{};
const Sentences emptySentences{};
const Description descriptionWithoutDefinitionsAndExamples{
    emptyDefinitionsWithExamples, sentences};
const Description descriptionWithoutSentences{definitionsWithExamples,
                                              emptySentences};
const Description emptyDescription{emptyDefinitionsWithExamples,
                                   emptySentences};
const std::string invalidJson{"{."};
}

class DescriptionSerializerTest : public Test
{
public:
    nlohmann::json prepareDescriptionJson()
    {
        nlohmann::json val;
        val[definitionsWithExamplesField].push_back(
            definitionWithExample1.toString());
        val[definitionsWithExamplesField].push_back(
            definitionWithExample2.toString());
        val[sentencesField].push_back(sentence1);
        val[sentencesField].push_back(sentence2);
        return val;
    }

    nlohmann::json prepareDescriptionWithoutDefinitionsAndExamplesJson()
    {
        nlohmann::json val;
        val[sentencesField].push_back(sentence1);
        val[sentencesField].push_back(sentence2);
        return val;
    }

    nlohmann::json prepareDescriptionWithoutSentencesJson()
    {
        nlohmann::json val;
        val[definitionsWithExamplesField].push_back(
            definitionWithExample1.toString());
        val[definitionsWithExamplesField].push_back(
            definitionWithExample2.toString());
        return val;
    }

    DescriptionSerializer serializer;
};

TEST_F(DescriptionSerializerTest, givenEmptyDescription_shouldReturnEmptyJson)
{
    const auto serializedDescription = serializer.serialize(emptyDescription);

    EXPECT_TRUE(serializedDescription.empty());
}

TEST_F(DescriptionSerializerTest,
       givenDescription_shouldReturnSerializedDescription)
{
    const auto serializedDescription = serializer.serialize(description);

    EXPECT_EQ(serializedDescription.dump(), expectedSerializedDescription);
}

TEST_F(
    DescriptionSerializerTest,
    givenDescriptionWithoutDefinitionsAndExamplesField_shouldReturnSerializedDescriptionWithoutDefinitionsAndExamples)
{
    const auto serializedDescription =
        serializer.serialize(descriptionWithoutDefinitionsAndExamples);

    EXPECT_EQ(serializedDescription.dump(),
              expectedSerializedDescriptionWithoutDefinitionsAndExamples);
}

TEST_F(
    DescriptionSerializerTest,
    givenDescriptionWithoutSentencesField_shouldReturnSerializedDescriptionWithoutSentences)
{
    const auto serializedDescription =
        serializer.serialize(descriptionWithoutSentences);

    EXPECT_EQ(serializedDescription.dump(),
              expectedSerializedDescriptionWithoutSentences);
}

TEST_F(DescriptionSerializerTest, givenEmptyJson_shouldReturnEmptyDescription)
{
    const auto serializedDescription = serializer.serialize(emptyDescription);

    EXPECT_TRUE(serializedDescription.empty());
}

TEST_F(DescriptionSerializerTest, givenInvalidJson_shouldReturnNoDescription)
{
    const auto actualDescription = serializer.deserialize(invalidJson);

    EXPECT_TRUE(actualDescription.empty());
}

TEST_F(DescriptionSerializerTest,
       givenSerializedDescription_shouldReturnDescription)
{
    const auto actualDescription =
        serializer.deserialize(prepareDescriptionJson());

    EXPECT_EQ(actualDescription, description);
}

TEST_F(
    DescriptionSerializerTest,
    givenSerializedDescriptionWithoutDefinitionsAndExamplesField_shouldReturnDescriptionWithoutDefinitionsAndExamples)
{
    const auto actualDescription = serializer.deserialize(
        prepareDescriptionWithoutDefinitionsAndExamplesJson());

    EXPECT_EQ(actualDescription, descriptionWithoutDefinitionsAndExamples);
    EXPECT_TRUE(actualDescription.definitionsWithExamples.empty());
}

TEST_F(
    DescriptionSerializerTest,
    givenSerializedDescriptionWithoutSentencesField_shouldReturnDescriptionWithoutSentences)
{
    const auto actualDescription =
        serializer.deserialize(prepareDescriptionWithoutSentencesJson());

    EXPECT_EQ(actualDescription, descriptionWithoutSentences);
    EXPECT_TRUE(actualDescription.sentences.empty());
}
