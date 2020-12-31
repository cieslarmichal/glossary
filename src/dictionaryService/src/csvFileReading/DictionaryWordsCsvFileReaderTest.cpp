#include "DictionaryWordsCsvFileReader.h"

#include "gtest/gtest.h"

#include "utils/FileAccessMock.h"

#include "utils/exceptions/FileNotFound.h"
#include <boost/optional/optional_io.hpp>

using namespace ::testing;
using namespace glossary::dictionaryService;
using namespace csvFileReading;

namespace
{
const std::string absoluteDictionaryWordsPath{"absoultePathToDictionaryWords.txt"};
const std::string content{"car,samochod\n"
                          "air,powietrze\n"};
const std::string contentWithWhiteSpaces{"\n\n    car   ,   samochod\n\n"
                                         "   air,powietrze    \n"};
const std::string contentWithTwoWordsAndOneIncomplete{"car,samochod\n"
                                                      "air,\n"};
const std::string contentWithIncorrectFormat{"car,samochod\n"
                                             ",powietrze\n"};
const DictionaryName dictionaryName1{"dictionaryName1"};
const DictionaryName dictionaryName2{"dictionaryName2"};
const DictionaryWord dictionaryWord1{"car", std::string{"samochod"}};
const DictionaryWord dictionaryWord2{"air", std::string{"powietrze"}};
const DictionaryWord dictionaryWord3{"air", boost::none};
const DictionaryWords twoDictionaryWordsWithOneIncomplete{dictionaryWord1, dictionaryWord3};
const DictionaryWords dictionaryWords{dictionaryWord1, dictionaryWord2};
const std::string emptyContent{};
}

class DictionaryWordsCsvFileReaderTest : public Test
{
public:
    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    DictionaryWordsCsvFileReader reader{fileAccess};
};

TEST_F(DictionaryWordsCsvFileReaderTest, givenNonExistingFilePath_shouldReturnNone)
{
    EXPECT_CALL(*fileAccess, exists(absoluteDictionaryWordsPath)).WillOnce(Return(false));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    EXPECT_EQ(actualDictionaryWords, boost::none);
}

TEST_F(DictionaryWordsCsvFileReaderTest, givenIncorrectFileContentFormat_shouldReturnNone)
{
    EXPECT_CALL(*fileAccess, exists(absoluteDictionaryWordsPath)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath))
        .WillOnce(Return(contentWithIncorrectFormat));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    EXPECT_EQ(actualDictionaryWords, boost::none);
}

TEST_F(DictionaryWordsCsvFileReaderTest, givenEmptyDictionaryWordsContent_shouldReturnEmptyDictionaryWords)
{
    EXPECT_CALL(*fileAccess, exists(absoluteDictionaryWordsPath)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath)).WillOnce(Return(emptyContent));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    EXPECT_TRUE(actualDictionaryWords->empty());
}

TEST_F(
    DictionaryWordsCsvFileReaderTest,
    givenContentWithEnglishWordWithoutTranslation_shouldReturnDictionaryWordsWithEnglishWordAndNoneTranslation)
{
    EXPECT_CALL(*fileAccess, exists(absoluteDictionaryWordsPath)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath))
        .WillOnce(Return(contentWithTwoWordsAndOneIncomplete));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    EXPECT_EQ(*actualDictionaryWords, twoDictionaryWordsWithOneIncomplete);
}

TEST_F(DictionaryWordsCsvFileReaderTest, givenDictionaryWordsContent_shouldReadDictionaryWords)
{
    EXPECT_CALL(*fileAccess, exists(absoluteDictionaryWordsPath)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath)).WillOnce(Return(content));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    EXPECT_EQ(*actualDictionaryWords, dictionaryWords);
}

TEST_F(DictionaryWordsCsvFileReaderTest, givenDictionaryWordsContentWithWhiteSpaces_shouldReadDictionaryWords)
{
    EXPECT_CALL(*fileAccess, exists(absoluteDictionaryWordsPath)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath))
        .WillOnce(Return(contentWithWhiteSpaces));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    EXPECT_EQ(*actualDictionaryWords, dictionaryWords);
}
