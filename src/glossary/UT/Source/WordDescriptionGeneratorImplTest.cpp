#include "WordDescriptionGeneratorImpl.h"

#include "WordDescriptionServiceMock.h"
#include "gmock/gmock.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordsDescriptionsDb;

namespace
{
const EnglishWord englishWord{"englishWord"};
const WordDescription wordDescription{englishWord, {}};
}

class WordDescriptionServiceImplTest : public Test
{
public:
    std::unique_ptr<HttpWordDescriptionCreatorMock> wordDescriptionCreatorInit =
        std::make_unique<StrictMock<HttpWordDescriptionCreatorMock>>();
    HttpWordDescriptionCreatorMock* wordDescriptionCreator =
        wordDescriptionCreatorInit.get();
    std::shared_ptr<wordsDescriptionsDb::WordsDescriptionsDbMock>
        wordsDescriptionsDb = std::make_shared<
            StrictMock<wordsDescriptionsDb::WordsDescriptionsDbMock>>();
    WordDescriptionServiceImpl wordDescriptionService{
        std::move(wordDescriptionCreatorInit), wordsDescriptionsDb};
};
