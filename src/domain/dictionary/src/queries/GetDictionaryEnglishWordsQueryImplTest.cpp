#include "GetDictionaryEnglishWordsQueryImpl.h"

#include "gtest/gtest.h"

#include "../repositories/DictionaryRepositoryMock.h"

#include "exceptions/DictionaryNotFoundError.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string dictionaryName1{"dictionaryName1"};
const std::string dictionaryName2{"dictionaryName2"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", std::nullopt};
const std::vector<DictionaryWord> dictionaryWords1{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const std::vector<DictionaryWord> dictionaryWords2{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const Dictionary dictionary1{dictionaryName1, dictionaryWords1};
const Dictionary dictionary2{dictionaryName2, dictionaryWords2};
const std::vector<Dictionary> dictionaries{dictionary1, dictionary2};
}

class GetDictionaryEnglishWordsQueryImplTest : public Test
{
public:
    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();

    GetDictionaryEnglishWordsQueryImpl query{dictionaryRepository};
};

TEST_F(GetDictionaryEnglishWordsQueryImplTest, shouldReturnDictionaryEnglishWords)
{
    EXPECT_CALL(*dictionaryRepository, getDictionary(dictionaryName1)).WillOnce(Return(dictionary1));

    const auto actualDictionariesEnglishWords = query.getDictionaryEnglishWords(dictionaryName1);

    const std::vector<std::string> expectedEnglishWords{dictionaryWord1.englishWord, dictionaryWord2.englishWord,
                                                        dictionaryWord3.englishWord};

    ASSERT_EQ(actualDictionariesEnglishWords, expectedEnglishWords);
}

TEST_F(GetDictionaryEnglishWordsQueryImplTest, givenDictionaryNotFound_shouldThrow)
{
    EXPECT_CALL(*dictionaryRepository, getDictionary(dictionaryName1)).WillOnce(Return(std::nullopt));

    ASSERT_THROW(query.getDictionaryEnglishWords(dictionaryName1), exceptions::DictionaryNotFoundError);
}
