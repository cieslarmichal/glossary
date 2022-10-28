#include "RemoveWordFromDictionaryCommandImpl.h"

#include "gtest/gtest.h"

#include "../repositories/DictionaryRepositoryMock.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string dictionaryName{"dictionaryName"};
const std::string englishWord{"englishWord1"};
}

class RemoveWordFromDictionaryCommandImplTest : public Test
{
public:
    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();

    RemoveWordFromDictionaryCommandImpl command{dictionaryRepository};
};

TEST_F(RemoveWordFromDictionaryCommandImplTest, shouldRemoveWordFromDictionary)
{
    EXPECT_CALL(*dictionaryRepository, removeWordFromDictionary(englishWord, dictionaryName));

    command.removeWordFromDictionary(dictionaryName, englishWord);
}
