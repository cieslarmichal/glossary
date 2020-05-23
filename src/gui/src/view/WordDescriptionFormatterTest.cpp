#include "WordDescriptionFormatter.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary;
using namespace gui::view;

namespace
{
const EnglishWord englishWord{"englishWord"};
const Definitions definitions{"definition1", "definition2"};
const Examples examples{"example1", "example2"};
const Synonyms synonyms{"synonym420"};
const WordDescription wordDescription{englishWord, definitions, examples, synonyms};

const QString formattedEnglishWord{"englishWord"};
const QList<QString> formattedDefinitions{"definition1", "definition2"};
const QList<QString> formattedExamples{"example1", "example2"};
const QList<QString> formattedSynonyms{"synonym420"};
const FormattedWordDescription formattedWordDescription{formattedEnglishWord, formattedDefinitions,
                                                        formattedExamples, formattedSynonyms};
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
