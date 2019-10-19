#include "DictionaryReaderImpl.h"
#include "FileAccessMock.h"
#include "Exceptions/FileNotFound.h"
#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const std::string dictionaryFilePath{"../database/dictionary.txt"};
const std::string content{"car samochod\n"
                          "air powietrze\n"};
const std::string contentWithTwoWordsAndOneIncorrect{"car samochod\n"
                                                     "     powietrze\n"};
const Dictionary expectedDictionaryWithOneWord{{"car", "samochod"}};
const std::string emptyContent{};
const Dictionary expectedDictionary{{"car", "samochod"},
                                    {"air", "powietrze"}};
}


class DictionaryReaderImplTest : public Test
{
public:
    std::shared_ptr<FileAccessMock> fileAccess = std::make_shared<StrictMock<FileAccessMock>>();
    DictionaryReaderImpl reader{fileAccess};
};

TEST_F(DictionaryReaderImplTest, givenEmptyDictionaryContent_shouldReturnEmptyDictionary)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath)).WillOnce(Return(emptyContent));

    const auto dictionary = reader.read();

    EXPECT_TRUE(dictionary.empty());
}


TEST_F(DictionaryReaderImplTest, givenyDictionaryContentWithTwoWordsAndOneOfThemIsIncorrect_shouldReturnDictWithOneWord)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath)).WillOnce(Return(contentWithTwoWordsAndOneIncorrect));

    const auto dictionary = reader.read();

    EXPECT_EQ(dictionary, expectedDictionaryWithOneWord);
}

TEST_F(DictionaryReaderImplTest, givenDictionaryContent_shouldReadDictionary)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath)).WillOnce(Return(content));

    const auto actualDictionary = reader.read();

    EXPECT_EQ(actualDictionary, expectedDictionary);
}

TEST_F(DictionaryReaderImplTest, givenInvalidFile_shouldReturnEmptyDictionary)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath)).WillOnce(Throw(exceptions::FileNotFound{""}));

    const auto dictionary = reader.read();

    EXPECT_TRUE(dictionary.empty());
}
