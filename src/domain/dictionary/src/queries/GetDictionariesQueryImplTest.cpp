#include "GetDictionariesQueryImpl.h"

#include "gtest/gtest.h"

#include "../repositories/DictionaryRepositoryMock.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string dictionaryName{"dictionaryName"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", std::nullopt};
const std::vector<DictionaryWord> dictionaryWords{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const Dictionary dictionary{dictionaryName, dictionaryWords};
const std::vector<Dictionary> dictionaries{dictionary};
}

class GetDictionariesQueryImplTest : public Test
{
public:
    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();

    GetDictionariesQueryImpl query{dictionaryRepository};
};

TEST_F(GetDictionariesQueryImplTest, shouldReturnDictionaries)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));

    const auto actualDictionaries = query.getDictionaries();

    ASSERT_EQ(actualDictionaries, dictionaries);
}
