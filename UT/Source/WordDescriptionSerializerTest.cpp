#include "WordDescriptionSerializer.h"

#include "gtest/gtest.h"
#include "DefinitionsWithExamples.h"
#include "Sentences.h"

using namespace ::testing;

namespace
{
const DefinitionWithExample definitionWithExample1{"definition1", boost::none};
const DefinitionWithExample definitionWithExample2{"definition2", std::string{"example"}};
const DefinitionsWithExamples definitionsWithExamples{definitionWithExample1, definitionWithExample2};
const Sentence sentence1{"sentence1"};
const Sentence sentence2{"sentence2"};
const Sentences sentences{sentence1, sentence2};
const WordDescription wordDescription{definitionsWithExamples, sentences};
const auto expectedSerializedWordDescription{
        R"({"definitionsWithExamples":["definition1","definition2:example"],"sentences":["sentence1","sentence2"]})"};
constexpr auto definitionsWithExamplesField = "definitionsWithExamples";
constexpr auto sentencesField = "sentences";
}

class WordDescriptionSerializerTest : public Test
{
public:
    nlohmann::json prepareWordDescriptionJson()
    {
        nlohmann::json val;
        val[definitionsWithExamplesField].push_back(definitionWithExample1.toString());
        val[definitionsWithExamplesField].push_back(definitionWithExample2.toString());
        val[sentencesField].push_back(sentence1);
        val[sentencesField].push_back(sentence2);
        return val;
    }

    WordDescriptionSerializer serializer;
};

TEST_F(WordDescriptionSerializerTest, givenWordDescription_shouldReturnSerializedWordDescription)
{
    const auto serializedWordDescription = serializer.serialize(wordDescription);

    EXPECT_EQ(serializedWordDescription.dump(), expectedSerializedWordDescription);
}

TEST_F(WordDescriptionSerializerTest, givenSerializedWordDescription_shouldReturnWordDescription)
{
    const auto actualWordDescription = serializer.deserialize(prepareWordDescriptionJson());

    EXPECT_EQ(actualWordDescription, wordDescription);
}
