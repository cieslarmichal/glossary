#include "wordsDb/descriptionsDb/WordDescriptionSerializer.h"

#include "gtest/gtest.h"
#include "wordsDb/descriptionsDb/DefinitionsWithExamples.h"
#include "wordsDb/descriptionsDb/Sentences.h"

using namespace ::testing;

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
const Description wordDescription{definitionsWithExamples, sentences};
const auto expectedSerializedWordDescription{
    R"({"definitionsWithExamples":["definition1","definition2:example"],"sentences":["sentence1","sentence2"]})"};
const auto expectedSerializedWordDescriptionWithoutDefinitionsAndExamples{
    R"({"sentences":["sentence1","sentence2"]})"};
const auto expectedSerializedWordDescriptionWithoutSentences{
    R"({"definitionsWithExamples":["definition1","definition2:example"]})"};
constexpr auto definitionsWithExamplesField = "definitionsWithExamples";
constexpr auto sentencesField = "sentences";
const DefinitionsWithExamples emptyDefinitionsWithExamples{};
const Sentences emptySentences{};
const Description wordDescriptionWithoutDefinitionsAndExamples{
    emptyDefinitionsWithExamples, sentences};
const Description wordDescriptionWithoutSentences{definitionsWithExamples,
                                                      emptySentences};
const Description emptyWordDescription{emptyDefinitionsWithExamples,
                                           emptySentences};
}

class WordDescriptionSerializerTest : public Test
{
public:
    nlohmann::json prepareWordDescriptionJson()
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

    nlohmann::json prepareWordDescriptionWithoutDefinitionsAndExamplesJson()
    {
        nlohmann::json val;
        val[sentencesField].push_back(sentence1);
        val[sentencesField].push_back(sentence2);
        return val;
    }

    nlohmann::json prepareWordDescriptionWithoutSentencesJson()
    {
        nlohmann::json val;
        val[definitionsWithExamplesField].push_back(
            definitionWithExample1.toString());
        val[definitionsWithExamplesField].push_back(
            definitionWithExample2.toString());
        return val;
    }

    WordDescriptionSerializer serializer;
};

TEST_F(WordDescriptionSerializerTest,
       givenEmptyWordDescription_shouldReturnEmptyJson)
{
    const auto serializedWordDescription =
        serializer.serialize(emptyWordDescription);

    EXPECT_TRUE(serializedWordDescription.empty());
}

TEST_F(WordDescriptionSerializerTest,
       givenWordDescription_shouldReturnSerializedWordDescription)
{
    const auto serializedWordDescription =
        serializer.serialize(wordDescription);

    EXPECT_EQ(serializedWordDescription.dump(),
              expectedSerializedWordDescription);
}

TEST_F(
    WordDescriptionSerializerTest,
    givenWordDescriptionWithoutDefinitionsAndExamplesField_shouldReturnSerializedWordDescriptionWithoutDefinitionsAndExamples)
{
    const auto serializedWordDescription =
        serializer.serialize(wordDescriptionWithoutDefinitionsAndExamples);

    EXPECT_EQ(serializedWordDescription.dump(),
              expectedSerializedWordDescriptionWithoutDefinitionsAndExamples);
}

TEST_F(
    WordDescriptionSerializerTest,
    givenWordDescriptionWithoutSentencesField_shouldReturnSerializedWordDescriptionWithoutSentences)
{
    const auto serializedWordDescription =
        serializer.serialize(wordDescriptionWithoutSentences);

    EXPECT_EQ(serializedWordDescription.dump(),
              expectedSerializedWordDescriptionWithoutSentences);
}

TEST_F(WordDescriptionSerializerTest,
       givenEmptyJson_shouldReturnEmptyWordDescription)
{
    const auto serializedWordDescription =
        serializer.serialize(emptyWordDescription);

    EXPECT_TRUE(serializedWordDescription.empty());
}

TEST_F(WordDescriptionSerializerTest,
       givenSerializedWordDescription_shouldReturnWordDescription)
{
    const auto actualWordDescription =
        serializer.deserialize(prepareWordDescriptionJson());

    EXPECT_EQ(actualWordDescription, wordDescription);
}

TEST_F(
    WordDescriptionSerializerTest,
    givenSerializedWordDescriptionWithoutDefinitionsAndExamplesField_shouldReturnWordDescriptionWithoutDefinitionsAndExamples)
{
    const auto actualWordDescription = serializer.deserialize(
        prepareWordDescriptionWithoutDefinitionsAndExamplesJson());

    EXPECT_EQ(actualWordDescription,
              wordDescriptionWithoutDefinitionsAndExamples);
    EXPECT_TRUE(actualWordDescription.definitionsWithExamples.empty());
}

TEST_F(
    WordDescriptionSerializerTest,
    givenSerializedWordDescriptionWithoutSentencesField_shouldReturnWordDescriptionWithoutSentences)
{
    const auto actualWordDescription =
        serializer.deserialize(prepareWordDescriptionWithoutSentencesJson());

    EXPECT_EQ(actualWordDescription, wordDescriptionWithoutSentences);
    EXPECT_TRUE(actualWordDescription.sentences.empty());
}
