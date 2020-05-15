#include "WordDescriptionFormatter.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary;
using namespace gui::view;

namespace
{
const EnglishWord englishWord{"englishWord"};
const Definition definition1{"definition1", std::string{"example1"}};
const Definition definition2{"definition2", boost::none};
const Definitions definitions{definition1, definition2};
const Sentences sentences{"sentence1", "sentence2"};
const WordDescription wordDescription{englishWord, Description{definitions, sentences}};

const QString formattedEnglishWord{"englishWord"};
const QList<QString> formattedDefinitions{"definition1", "// example1", "definition2", ""};
const QList<QString> formattedSentences{"sentence1", "sentence2"};
const FormattedWordDescription formattedWordDescription{formattedEnglishWord, formattedDefinitions,
                                                        formattedSentences};
}

class WordDescriptionFormatterTest : public Test
{
public:
    WordDescriptionFormatter formatter;
};

TEST_F(WordDescriptionFormatterTest, givenWordDescription_shouldSplitIntoFormattedWordDescription)
{
    const auto actualFormattedWordDescription = formatter.formatWordDescription(wordDescription);

    ASSERT_EQ(actualFormattedWordDescription, formattedWordDescription);
}
