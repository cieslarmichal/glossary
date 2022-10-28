#include "GetDictionaryQueryImpl.h"

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
}

class GetDictionaryQueryImplTest : public Test
{
public:
    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();

    GetDictionaryQueryImpl query{dictionaryRepository};
};

TEST_F(GetDictionaryQueryImplTest, shouldReturnDictionary)
{
    EXPECT_CALL(*dictionaryRepository, getDictionary(dictionaryName)).WillOnce(Return(dictionary));

    const auto actualDictionary = query.getDictionary(dictionaryName);

    ASSERT_EQ(actualDictionary, dictionary);
}
