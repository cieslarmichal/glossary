#include "WordDescriptionConcurrentUpdater.h"

#include "gtest/gtest.h"

#include "dictionary/queries/GetWordDescriptionQueryMock.h"

using namespace ::testing;
using namespace glossary;
using namespace dictionary;

namespace
{
const std::string englishWord1{"englishWord1"};
const std::string englishWord2{"englishWord2"};
const std::string englishWord3{"englishWord3"};
const std::vector<std::string> englishWords{englishWord1, englishWord2, englishWord3};
const dictionary::WordDescription wordDescription1{englishWord1, {}, {}, {}};
}

class WordDescriptionConcurrentUpdaterTest : public Test
{
public:
    std::shared_ptr<GetWordDescriptionQueryMock> getWordDescriptionQuery =
        std::make_shared<StrictMock<GetWordDescriptionQueryMock>>();
    WordDescriptionConcurrentUpdater updater{getWordDescriptionQuery};
};

TEST_F(WordDescriptionConcurrentUpdaterTest, givenEnglishWords_shouldGetWordDescriptions)
{
    EXPECT_CALL(*getWordDescriptionQuery, getWordDescription(englishWord1)).WillOnce(Return(wordDescription1));
    EXPECT_CALL(*getWordDescriptionQuery, getWordDescription(englishWord2)).WillOnce(Return(wordDescription1));
    EXPECT_CALL(*getWordDescriptionQuery, getWordDescription(englishWord3)).WillOnce(Return(wordDescription1));

    updater.update(englishWords);
}
