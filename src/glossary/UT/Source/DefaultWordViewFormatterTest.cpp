#include "DefaultWordViewFormatter.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordDescriptionRepository;

namespace
{
const PolishWord polishWord{"zaslony"};
const auto polishWordView{"Polish word: zaslony\n"};
const WordDescription wordDescription("computer", {{{"definition", std::string{"example"}},
                                                    {"definition2", std::string{"example2"}}},
                                                   {"sentence"}});
const auto wordViewWithoutDescription{"English word: computer\n"
                                      "Polish translation: komputer\n"};
const auto wordView{"English word: computer\n"
                    "Polish translation: komputer\n"
                    "Definition: definition\n"
                    "Example: example\n"
                    "Definition: definition2\n"
                    "Example: example2\n"
                    "Sentence: sentence\n"};
const Word word{{"computer"}, std::string{"komputer"}, wordDescription};
const Word wordWithoutWordDescription{{"computer"}, std::string{"komputer"}, boost::none};
}

class DefaultWordViewFormatterTest : public Test
{
public:
    DefaultWordViewFormatter wordViewFormatter;
};

TEST_F(DefaultWordViewFormatterTest, givenEnglishWord_shouldReturnEnglishWordView)
{
    const auto actualEnglishWordView = wordViewFormatter.formatPolishWordView(polishWord);

    ASSERT_EQ(actualEnglishWordView, polishWordView);
}

TEST_F(DefaultWordViewFormatterTest, givenWord_shoulReturnWordView)
{
    const auto actualWordView = wordViewFormatter.formatWordView(word);

    ASSERT_EQ(actualWordView, wordView);
}

TEST_F(DefaultWordViewFormatterTest, givenWordWithoutDescription_shouldReturnWordView)
{
    const auto actualWordView = wordViewFormatter.formatWordView(wordWithoutWordDescription);

    ASSERT_EQ(actualWordView, wordViewWithoutDescription);
}
