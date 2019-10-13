#include "DictionaryReaderImpl.h"
#include "FileAccessMock.h"

#include "gtest/gtest.h"
using namespace ::testing;

namespace
{
    const std::string dictionaryFilePath{"../database/dictionary.txt"};
    const std::string content{"car samochod\n"
                       "air powietrze\n"};
    const std::string emptyContent{};
    Dictionary expectedDictionary{{"car", "samochod"}, {"air", "powietrze"}};
    Dictionary emptyDictionary{};
}


class DictionaryReaderImplTest : public Test
{
public:
    std::shared_ptr<FileAccessMock> fileAccess = std::make_shared<StrictMock<FileAccessMock>>();
    DictionaryReaderImpl reader{fileAccess};
};

TEST_F(DictionaryReaderImplTest,  givenEmptyDictionaryContent_shouldReturnEmptyDictionary)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath)).WillOnce(Return(emptyContent));

    auto dictionary = reader.read();

    EXPECT_EQ(dictionary, emptyDictionary);
}

TEST_F(DictionaryReaderImplTest,  givenDictionaryContent_shouldReadDictionary)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath)).WillOnce(Return(content));

    auto actualDictionary = reader.read();

    EXPECT_EQ(actualDictionary, expectedDictionary);
}
