#include "WordsSerializerImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const Word word1("computer", "komputer",
                 {{{"definition", std::string{"example"}}, {"definition2", std::string{"example2"}}},
                  {"sentence"}});
const Word word2("tea", "herbata", {});
const Word word3("headphones", "sluchawki", {});
const Words words{word1, word2, word3};
const std::string expectedSerializedWords{
        R"({"words":[{"englishWord":"computer","polishWord":"komputer","wordDescription":{"definitionsWithExamples":["definition:example","definition2:example2"],"sentences":["sentence"]}},{"englishWord":"tea","polishWord":"herbata","wordDescription":{}},{"englishWord":"headphones","polishWord":"sluchawki","wordDescription":{}}]})"
};
}

class WordsSerializerImplTest : public Test
{
public:
    WordsSerializerImpl serializer;
};

TEST_F(WordsSerializerImplTest, givenWords_shouldReturnSerializedWords)
{
    auto actualSerializedWords = serializer.serialize(words);

    EXPECT_EQ(actualSerializedWords, expectedSerializedWords);
}

TEST_F(WordsSerializerImplTest, givenSerializedWords_shouldReturnWords)
{
    auto actualWords = serializer.deserialize(expectedSerializedWords);

    EXPECT_EQ(actualWords, words);
}
