#include "WordViewerImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const EnglishWord englishWord{"curtains"};
const auto englishWordView{"English word: curtains\n"};
const Word word("computer", "komputer",
                {{{"definition", std::string{"example"}}, {"definition2", std::string{"example2"}}},
                 {"sentence"}});
const Word wordWithoutDescription{"computer", "komputer", {}};
const auto wordViewWithoutDescription{"English word: computer\n"
                                      "Polish translation: komputer\n"};
const auto wordView{"English word: computer\n"
                    "Polish translation: komputer\n"
                    "Definition: definition\n"
                    "Example: example\n"
                    "Definition: definition2\n"
                    "Example: example2\n"
                    "Sentence: sentence\n"};
}

class WordViewerImplTest : public Test
{
public:
    WordViewerImpl wordViewer;
};

TEST_F(WordViewerImplTest, givenEnglishWord_shouldReturnEnglishWordView)
{
    const auto actualEnglishWordView = wordViewer.viewEnglishWord(englishWord);

    ASSERT_EQ(actualEnglishWordView, englishWordView);
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