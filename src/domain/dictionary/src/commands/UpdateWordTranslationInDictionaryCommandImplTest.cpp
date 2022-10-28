#include "UpdateWordTranslationInDictionaryCommandImpl.h"

#include "gtest/gtest.h"

#include "../repositories/DictionaryRepositoryMock.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string dictionaryName{"dictionaryName"};
const std::string englishWord{"englishWord"};
const std::string translation{"translation"};
}

class UpdateWordTranslationInDictionaryCommandImplTest : public Test
{
public:
    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();

    UpdateWordTranslationInDictionaryCommandImpl command{dictionaryRepository};
};

TEST_F(UpdateWordTranslationInDictionaryCommandImplTest, updateWordTranslationInDictionary)
{
    EXPECT_CALL(*dictionaryRepository, changeWordTranslationFromDictionary(englishWord, translation, dictionaryName));

    command.updateWordTranslation(dictionaryName, englishWord, translation);
}
