#include "AddWordToDictionaryCommandImpl.h"

#include "gtest/gtest.h"

#include "../repositories/DictionaryRepositoryMock.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string dictionaryName{"dictionaryName"};
const DictionaryWord dictionaryWord{"englishWord1", std::string{"translation1"}};
}

class AddWordToDictionaryCommandImplTest : public Test
{
public:
    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();

    AddWordToDictionaryCommandImpl command{dictionaryRepository};
};

TEST_F(AddWordToDictionaryCommandImplTest, shouldCreateDictionary)
{
    EXPECT_CALL(*dictionaryRepository, addWordToDictionary(dictionaryWord, dictionaryName));

    command.addWordToDictionary(dictionaryName, dictionaryWord);
}
