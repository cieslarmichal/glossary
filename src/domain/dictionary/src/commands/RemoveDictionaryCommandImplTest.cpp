#include "RemoveDictionaryCommandImpl.h"

#include "gtest/gtest.h"

#include "../repositories/DictionaryRepositoryMock.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string dictionaryName{"dictionaryName"};
}

class RemoveDictionaryCommandImplTest : public Test
{
public:
    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();

    RemoveDictionaryCommandImpl command{dictionaryRepository};
};

TEST_F(RemoveDictionaryCommandImplTest, shouldRemoveDictionary)
{
    EXPECT_CALL(*dictionaryRepository, removeDictionary(dictionaryName));

    command.removeDictionary(dictionaryName);
}
