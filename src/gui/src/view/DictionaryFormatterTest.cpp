#include "DictionaryFormatter.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary;
using namespace gui::view;

namespace
{
const DictionaryName dictionaryName1{"dictionaryName1"};
const DictionaryName dictionaryName2{"dictionaryName2"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", boost::none};
const DictionaryWords dictionaryWords{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const Dictionary dictionary1{dictionaryName1, dictionaryWords};
const Dictionary dictionary2{dictionaryName2, {}};
const Dictionaries dictionaries{dictionary1, dictionary2};

const FormattedDictionaryWord formattedDictionaryWord1{"englishWord1", "translation1"};
const FormattedDictionaryWord formattedDictionaryWord2{"englishWord2", "translation2"};
const FormattedDictionaryWord formattedDictionaryWord3{"englishWord3", ""};
const FormattedDictionaryWords formattedDictionaryWords{formattedDictionaryWord1, formattedDictionaryWord2, formattedDictionaryWord3};
const FormattedDictionaryWords emptyFormattedDictionaryWords{};
const FormattedDictionary formattedDictionary1{"dictionaryName1", formattedDictionaryWords};
const FormattedDictionary formattedDictionary2{"dictionaryName2", emptyFormattedDictionaryWords};
const QList<FormattedDictionary> expectedFormattedDictionaries{formattedDictionary1, formattedDictionary2};
}

class DictionaryFormatterTest : public Test
{
public:
    DictionaryFormatter formatter;
};

TEST_F(DictionaryFormatterTest, givenDictionaries_shouldReturnFormattedDictionaries)
{
    const auto actualFormattedDictionaries = formatter.getFormattedDictionaries(dictionaries);

    ASSERT_EQ(actualFormattedDictionaries, expectedFormattedDictionaries);
}
