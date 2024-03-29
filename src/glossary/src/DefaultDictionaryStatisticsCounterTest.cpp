#include "DefaultDictionaryStatisticsCounter.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary;
using namespace dictionary;
using namespace statistics;

namespace
{
const std::string englishWord1{"englishWord1"};
const std::string englishWord2{"englishWord2"};
const std::string englishWord3{"englishWord3"};
const std::string englishWord4{"englishWord4"};
const std::string englishWord5{"englishWord5"};
const std::string englishWord6{"englishWord6"};
const WordStatistics wordStats1{englishWord1, 7, 5};
const WordStatistics wordStats2{englishWord2, 8, 2};
const WordStatistics wordStats3{englishWord3, 1, 4};
const WordStatistics wordStats4{englishWord4, 4, 1};
const WordStatistics wordStats5{englishWord5, 5, 0};
const WordStatistics wordStats6{englishWord6, 6, 3};
const std::vector<WordStatistics> statistics1{wordStats1, wordStats2, wordStats3};
const std::vector<WordStatistics> statistics2{wordStats1, wordStats2, wordStats3, wordStats4, wordStats5, wordStats6};

const DictionaryWord dictionaryWord1{englishWord1, std::string{"translation1"}};
const DictionaryWord dictionaryWord2{englishWord2, std::string{"translation2"}};
const DictionaryWord dictionaryWord3{englishWord3, std::string{"translation3"}};
const DictionaryWord dictionaryWord4{englishWord4, std::string{"translation4"}};
const DictionaryWord dictionaryWord5{englishWord5, std::string{"translation5"}};
const DictionaryWord dictionaryWord6{englishWord6, std::nullopt};
const std::vector<DictionaryWord> dictionaryWords1{dictionaryWord4, dictionaryWord5, dictionaryWord6};
const std::vector<DictionaryWord> dictionaryWords2{dictionaryWord2, dictionaryWord3, dictionaryWord4, dictionaryWord5};
const std::vector<DictionaryWord> dictionaryWords3{dictionaryWord4, dictionaryWord5};
const std::string dictionaryName1{"dictionaryName1"};
const std::string dictionaryName2{"dictionaryName2"};
const std::string dictionaryName3{"dictionaryName3"};
const std::string dictionaryName4{"dictionaryName4"};
const Dictionary dictionary1{dictionaryName1, dictionaryWords1};
const Dictionary dictionary2{dictionaryName2, dictionaryWords2};
const Dictionary dictionary3{dictionaryName3, dictionaryWords3};
const Dictionary dictionary4{dictionaryName4, {}};
const std::vector<Dictionary> dictionaries{dictionary1, dictionary2, dictionary3, dictionary4};
const DictionaryStatistics emptyDictionaryStatistics{dictionaryName1, 0, 0};
const DictionaryStatistics dictionaryStatistics1{dictionaryName1, 15, 4};
const DictionaryStatistics dictionaryStatistics2{dictionaryName2, 18, 7};
const DictionaryStatistics dictionaryStatistics3{dictionaryName3, 9, 1};
const DictionaryStatistics dictionaryStatistics4{dictionaryName4, 0, 0};
const DictionariesStatistics dictionariesStatistics{dictionaryStatistics1, dictionaryStatistics2, dictionaryStatistics3,
                                                    dictionaryStatistics4};
}

class DefaultDictionaryStatisticsCounterTest : public Test
{
public:
    DefaultDictionaryStatisticsCounter statisticsCounter;
};

TEST_F(DefaultDictionaryStatisticsCounterTest, givenWordsFromDictionaryNonExistingInStatistics_shouldReturnZeroAnswers)
{
    const auto actualDictionaryStatistics = statisticsCounter.countDictionaryStatistics(dictionary1, statistics1);

    ASSERT_EQ(actualDictionaryStatistics, emptyDictionaryStatistics);
}

TEST_F(DefaultDictionaryStatisticsCounterTest,
       givenWordsFromDictionaryExistingInStatistics_shouldCountAnswersForWordsFromStatisticsThatOccursInDictionary)
{
    const auto actualDictionaryStatistics = statisticsCounter.countDictionaryStatistics(dictionary2, statistics2);

    ASSERT_EQ(actualDictionaryStatistics, dictionaryStatistics2);
}

TEST_F(DefaultDictionaryStatisticsCounterTest,
       givenWordsFromDictionaries_shouldCountAnswersForWordsFromStatisticsThatOccursInDictionary)
{
    const auto actualDictionariesStatistics = statisticsCounter.countDictionariesStatistics(dictionaries, statistics2);

    ASSERT_EQ(actualDictionariesStatistics, dictionariesStatistics);
}
