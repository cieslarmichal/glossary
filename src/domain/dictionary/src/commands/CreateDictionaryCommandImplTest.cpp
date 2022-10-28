#include "CreateDictionaryCommandImpl.h"

#include "gtest/gtest.h"

#include "../repositories/DictionaryRepositoryMock.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string dictionaryName{"dictionaryName"};
}

class CreateDictionaryCommandImplTest : public Test
{
public:
    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();

    CreateDictionaryCommandImpl command{dictionaryRepository};
};

TEST_F(CreateDictionaryCommandImplTest, shouldCreateDictionary)
{
    EXPECT_CALL(*dictionaryRepository, addDictionary(dictionaryName));

    command.addDictionary(dictionaryName);
}
