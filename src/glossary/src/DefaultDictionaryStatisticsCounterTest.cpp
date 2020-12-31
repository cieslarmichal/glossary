#include "DefaultDictionaryStatisticsCounter.h"

#include "gtest/gtest.h"
#include <boost/optional/optional_io.hpp>

using namespace ::testing;
using namespace glossary;
using namespace dictionaryService;
using namespace statisticsRepository;

namespace
{
const EnglishWord englishWord1{"englishWord1"};
const EnglishWord englishWord2{"englishWord2"};
const EnglishWord englishWord3{"englishWord3"};
const EnglishWord englishWord4{"englishWord4"};
const EnglishWord englishWord5{"englishWord5"};
const EnglishWord englishWord6{"englishWord6"};
const WordStatistics wordStats1{englishWord1, 7, 5};
const WordStatistics wordStats2{englishWord2, 8, 2};
const WordStatistics wordStats3{englishWord3, 1, 4};
const WordStatistics wordStats4{englishWord4, 4, 1};
const WordStatistics wordStats5{englishWord5, 5, 0};
const WordStatistics wordStats6{englishWord6, 6, 3};
const Statistics statistics1{wordStats1, wordStats2, wordStats3};
const Statistics statistics2{wordStats1, wordStats2, wordStats3, wordStats4, wordStats5, wordStats6};

const DictionaryWord dictionaryWord1{englishWord1, std::string{"translation1"}};
const DictionaryWord dictionaryWord2{englishWord2, std::string{"translation2"}};
const DictionaryWord dictionaryWord3{englishWord3, std::string{"translation3"}};
const DictionaryWord dictionaryWord4{englishWord4, std::string{"translation4"}};
const DictionaryWord dictionaryWord5{englishWord5, std::string{"translation5"}};
const DictionaryWord dictionaryWord6{englishWord6, boost::none};
const DictionaryWords dictionaryWords1{dictionaryWord4, dictionaryWord5, dictionaryWord6};
const DictionaryWords dictionaryWords2{dictionaryWord2, dictionaryWord3, dictionaryWord4, dictionaryWord5};
const DictionaryWords dictionaryWords3{dictionaryWord4, dictionaryWord5};
const DictionaryName dictionaryName1{"dictionaryName1"};
const DictionaryName dictionaryName2{"dictionaryName2"};
const DictionaryName dictionaryName3{"dictionaryName3"};
const DictionaryName dictionaryName4{"dictionaryName4"};
const Dictionary dictionary1{dictionaryName1, dictionaryWords1};
const Dictionary dictionary2{dictionaryName2, dictionaryWords2};
const Dictionary dictionary3{dictionaryName3, dictionaryWords3};
const Dictionary dictionary4{dictionaryName4, {}};
const Dictionaries dictionaries{dictionary1, dictionary2, dictionary3, dictionary4};
const DictionaryStatistics emptyDictionaryStatistics{dictionaryName1, 0, 0};
const DictionaryStatistics dictionaryStatistics1{dictionaryName1, 15, 4};
const DictionaryStatistics dictionaryStatistics2{dictionaryName2, 18, 7};
const DictionaryStatistics dictionaryStatistics3{dictionaryName3, 9, 1};
const DictionaryStatistics dictionaryStatistics4{dictionaryName4, 0, 0};
const DictionariesStatistics dictionariesStatistics{dictionaryStatistics1, dictionaryStatistics2,
                                                    dictionaryStatistics3, dictionaryStatistics4};
}

class DefaultDictionaryStatisticsCounterTest : public Test
{
public:
    DefaultDictionaryStatisticsCounter statisticsCounter;
};

TEST_F(DefaultDictionaryStatisticsCounterTest,
       givenWordsFromDictionaryNonExistingInStatistics_shouldReturnZeroAnswers)
{
    const auto actualDictionaryStatistics =
        statisticsCounter.countDictionaryStatistics(dictionary1, statistics1);

    ASSERT_EQ(actualDictionaryStatistics, emptyDictionaryStatistics);
}

TEST_F(
    DefaultDictionaryStatisticsCounterTest,
    givenWordsFromDictionaryExistingInStatistics_shouldCountAnswersForWordsFromStatisticsThatOccursInDictionary)
{
    const auto actualDictionaryStatistics =
        statisticsCounter.countDictionaryStatistics(dictionary2, statistics2);

    ASSERT_EQ(actualDictionaryStatistics, dictionaryStatistics2);
}

TEST_F(DefaultDictionaryStatisticsCounterTest,
       givenWordsFromDictionaries_shouldCountAnswersForWordsFromStatisticsThatOccursInDictionary)
{
    const auto actualDictionariesStatistics =
        statisticsCounter.countDictionariesStatistics(dictionaries, statistics2);

    ASSERT_EQ(actualDictionariesStatistics, dictionariesStatistics);
}