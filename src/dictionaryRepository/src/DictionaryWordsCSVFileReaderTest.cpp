#include "gtest/gtest.h"

#include "utils/FileAccessMock.h"

#include "DictionaryWordsCSVFileReader.h"
#include "utils/exceptions/FileNotFound.h"

using namespace ::testing;
using namespace dictionaryRepository;

namespace
{
const std::string absoluteDictionaryWordsPath{"absoultePathToDictionaryWords.txt"};
const std::string content{"car samochod\n"
                          "air powietrze\n"};
const std::string contentWithTwoWordsAndOneIncomplete{"car samochod\n"
                                                      "     air\n"};
const DictionaryName dictionaryName1{"dictionaryName1"};
const DictionaryName dictionaryName2{"dictionaryName2"};
const DictionaryWord dictionaryWord1{"car", std::string{"samochod"}};
const DictionaryWord dictionaryWord2{"air", std::string{"powietrze"}};
const DictionaryWord dictionaryWord3{"air", boost::none};
const DictionaryWords twoDictionaryWordsWithOneIncomplete{dictionaryWord1, dictionaryWord3};
const DictionaryWords dictionaryWords{dictionaryWord1, dictionaryWord2};
const std::string emptyContent{};
}

class DictionaryWordsTextFileReaderTest : public Test
{
public:
    // TODO: change all NiceMock to StrictMock :)
    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    DictionaryWordsCSVFileReader reader{fileAccess};
};

TEST_F(DictionaryWordsTextFileReaderTest, givenEmptyDictionaryWordsContent_shouldReturnEmptyDictionaryWords)
{
    EXPECT_CALL(*fileAccess, exists(absoluteDictionaryWordsPath)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath)).WillOnce(Return(emptyContent));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    EXPECT_TRUE(actualDictionaryWords.empty());
}

TEST_F(DictionaryWordsTextFileReaderTest,
       givenyContentWithTwoWordsAndOneOfThemIsIncomplete_shouldReturnDictionaryWordsWithOneWord)
{
    EXPECT_CALL(*fileAccess, exists(absoluteDictionaryWordsPath)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath))
        .WillOnce(Return(contentWithTwoWordsAndOneIncomplete));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    EXPECT_EQ(actualDictionaryWords, twoDictionaryWordsWithOneIncomplete);
}

TEST_F(DictionaryWordsTextFileReaderTest, givenDictionaryWordsContent_shouldReadDictionaryWords)
{
    EXPECT_CALL(*fileAccess, exists(absoluteDictionaryWordsPath)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath)).WillOnce(Return(content));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    EXPECT_EQ(actualDictionaryWords, dictionaryWords);
}

TEST_F(DictionaryWordsTextFileReaderTest, givenInvalidFile_shouldReturnEmptyDictionaryWords)
{
    EXPECT_CALL(*fileAccess, exists(absoluteDictionaryWordsPath)).WillOnce(Return(false));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    EXPECT_TRUE(actualDictionaryWords.empty());
}
