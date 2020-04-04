#include "DefaultWordViewFormatter.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary;
using namespace wordDescriptionRepository;

namespace
{
const std::string polishWord{"zaslony"};
const auto wordView{"Word: zaslony\n"};
const WordDescription wordDescription("computer", {{{"definition", std::string{"example"}},
                                                    {"definition2", std::string{"example2"}}},
                                                   {"sentence"}});
const auto wordDescriptionView{"English word: computer\n"
                               "Description:\n"
                               "Definition: definition\n"
                               "Example: example\n"
                               "Definition: definition2\n"
                               "Example: example2\n"
                               "Sentence: sentence\n"};
}

class DefaultWordViewFormatterTest : public Test
{
public:
    DefaultWordViewFormatter wordViewFormatter;
};

TEST_F(DefaultWordViewFormatterTest, givenSingleWord_shouldReturnSingleWordView)
{
    const auto actualWordView = wordViewFormatter.formatSingleWordView(polishWord);

    ASSERT_EQ(actualWordView, wordView);
}

TEST_F(DefaultWordViewFormatterTest, givenWordDescription_shoulReturnWordDescriptionView)
{
    const auto actualWordDescriptionView = wordViewFormatter.formatWordDescriptionView(wordDescription);

    ASSERT_EQ(actualWordDescriptionView, wordDescriptionView);
}
