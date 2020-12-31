#include "WordsApiJsonResponseDeserializer.h"

#include "gtest/gtest.h"
#include <boost/optional/optional_io.hpp>

using namespace glossary;
using namespace wordDescriptionDownloader;
using namespace wordDescriptionRepository;
using namespace ::testing;

namespace
{
const std::string invalidJson{"{."};
const std::string definitionsJson =
    R"({"word":"fetch",
"definitions":[
{"definition":"be sold for a certain price","partOfSpeech":"verb"},
{"definition":"go or come after and bring or take back","partOfSpeech":"verb"},
{"definition":"take away or remove","partOfSpeech":"verb"},
{"definition":"the action of fetching","partOfSpeech":"noun"}
]})";
const std::string examplesJson =
    R"({"word":"fetch",
"examples":[
"The old print fetched a high price at the auction",
"The dog fetched the hat",
"The devil will fetch you!"
]})";
const std::string synonymsJson =
    R"({"word":"fetch",
"synonyms":[
"bring",
"bring in",
"convey",
"get"
]})";
const std::string definitionsJsonWithoutDefinitionsField =
    R"({"word":"fetch",
"":[
{"definition":"be sold for a certain price","partOfSpeech":"verb"},
{"definition":"go or come after and bring or take back","partOfSpeech":"verb"},
{"definition":"take away or remove","partOfSpeech":"verb"},
{"definition":"the action of fetching","partOfSpeech":"noun"}
]})";
const std::string examplesJsonWithoutExamplesField =
    R"({"word":"fetch",
"":[
"The old print fetched a high price at the auction",
"The dog fetched the hat",
"The devil will fetch you!"
]})";
const std::string synonymsJsonWithoutSynonymsField =
    R"({"word":"fetch",
"":[
"bring",
"bring in",
"convey",
"get"
]})";
const Definitions expectedDefinitions{"be sold for a certain price",
                                      "go or come after and bring or take back", "take away or remove",
                                      "the action of fetching"};
const Examples expectedExamples{"The old print fetched a high price at the auction",
                                "The dog fetched the hat", "The devil will fetch you!"};
const Synonyms expectedSynonyms{"bring", "bring in", "convey", "get"};
}

class WordsApiJsonResponseDeserializerTest : public Test
{
public:
    WordsApiJsonResponseDeserializer deserializer;
};

TEST_F(WordsApiJsonResponseDeserializerTest, invalidJson_shouldReturnEmptyDefinitions)
{
    const auto actualDefinitions = deserializer.deserializeDefinitions(invalidJson);

    ASSERT_TRUE(actualDefinitions.empty());
}

TEST_F(WordsApiJsonResponseDeserializerTest, jsonWithoutDefinitionsField_shouldReturnEmptyDefinitions)
{
    const auto actualDefinitions =
        deserializer.deserializeDefinitions(definitionsJsonWithoutDefinitionsField);

    ASSERT_TRUE(actualDefinitions.empty());
}

TEST_F(WordsApiJsonResponseDeserializerTest, jsonWithDefinitionsField_shouldReturnDefinitions)
{
    const auto actualDefinitions = deserializer.deserializeDefinitions(definitionsJson);

    ASSERT_EQ(actualDefinitions, expectedDefinitions);
}

TEST_F(WordsApiJsonResponseDeserializerTest, invalidJson_shouldReturnEmptyExamples)
{
    const auto actualExamples = deserializer.deserializeExamples(invalidJson);

    ASSERT_TRUE(actualExamples.empty());
}

TEST_F(WordsApiJsonResponseDeserializerTest, jsonWithoutExamplesField_shouldReturnEmptyExamples)
{
    const auto actualExamples = deserializer.deserializeExamples(examplesJsonWithoutExamplesField);

    ASSERT_TRUE(actualExamples.empty());
}

TEST_F(WordsApiJsonResponseDeserializerTest, jsonWithExamplesField_shouldReturnExamples)
{
    const auto actualExamples = deserializer.deserializeExamples(examplesJson);

    ASSERT_EQ(actualExamples, expectedExamples);
}

TEST_F(WordsApiJsonResponseDeserializerTest, invalidJson_shouldReturnEmptySynonyms)
{
    const auto actualSynonyms = deserializer.deserializeSynonyms(invalidJson);

    ASSERT_TRUE(actualSynonyms.empty());
}

TEST_F(WordsApiJsonResponseDeserializerTest, jsonWithoutSynonymsField_shouldReturnEmptySynonyms)
{
    const auto actualSynonyms = deserializer.deserializeSynonyms(synonymsJsonWithoutSynonymsField);

    ASSERT_TRUE(actualSynonyms.empty());
}

TEST_F(WordsApiJsonResponseDeserializerTest, jsonWithSynonymsField_shouldReturnSynonyms)
{
    const auto actualSynonyms = deserializer.deserializeSynonyms(synonymsJson);

    ASSERT_EQ(actualSynonyms, expectedSynonyms);
}