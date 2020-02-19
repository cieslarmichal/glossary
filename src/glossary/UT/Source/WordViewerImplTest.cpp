#include "WordViewerImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordsDescriptionsDb;

namespace
{
const PolishWord polishWord{"zaslony"};
const auto polishWordView{"Polish word: zaslony\n"};
const WordDescription
    wordDescription("computer", {{{"definition", std::string{"example"}},
                                  {"definition2", std::string{"example2"}}},
                                 {"sentence"}});
const auto wordViewWithoutDescription{"English word: computer\n"
                                      "Polish word: komputer\n"};
const auto wordView{"English word: computer\n"
                    "Polish word: komputer\n"
                    "Definition: definition\n"
                    "Example: example\n"
                    "Definition: definition2\n"
                    "Example: example2\n"
                    "Sentence: sentence\n"};
const Word word{{"komputer"}, {"computer"}, wordDescription};
const Word wordWithoutDescription{{"komputer"}, {"computer"}, boost::none};
}

class WordViewerImplTest : public Test
{
public:
    WordViewerImpl wordViewer;
};

TEST_F(WordViewerImplTest, givenEnglishWord_shouldReturnEnglishWordView)
{
    const auto actualEnglishWordView = wordViewer.viewPolishWord(polishWord);

    ASSERT_EQ(actualEnglishWordView, polishWordView);
}

TEST_F(WordViewerImplTest, givenWord_shoulReturnWordView)
{
    const auto actualWordView = wordViewer.viewWord(word);

    ASSERT_EQ(actualWordView, wordView);
}

TEST_F(WordViewerImplTest, givenWordWithoutDescription_shouldReturnWordView)
{
    const auto actualWordView = wordViewer.viewWord(wordWithoutDescription);

    ASSERT_EQ(actualWordView, wordViewWithoutDescription);
}
