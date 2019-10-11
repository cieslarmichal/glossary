#include "WordsSerializerImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const Word word1("computer", "komputer", {});
const Word word2("tea", "herbata", {});
const Words words{word1, word2};
}

class WordsSerializerImplTest : public Test
{
public:
    WordsSerializerImpl serializer;

    WordDescription createWordDescription()
    {
        WordDescription wordDescription;
//        std::vector<std::string> wordSentences{sentence};
//        std::vector<DefinitionWithExample> wordDefinitionsAndExamples{{definition, example}};
//        wordDescription.definitionsWithExamples = wordDefinitionsAndExamples;
//        wordDescription.sentences = wordSentences;
        return wordDescription;
    }
};

TEST_F(WordsSerializerImplTest, givenWordsSerialization_shouldReturnJsonFromWords)
{

    auto serializedWords = serializer.serialize(words);

    std::cout<<serializedWords;
}