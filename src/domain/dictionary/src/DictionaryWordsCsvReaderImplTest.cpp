#include "DictionaryWordsCsvReaderImpl.h"

#include "gtest/gtest.h"

#include "fileSystem/FileAccessMock.h"

#include "exceptions/InvalidDictionaryWordsCsvFile.h"

using namespace ::testing;
using namespace glossary::dictionary;

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
const std::string contentWithoutSeparator{"car samochod\n"};
const std::string dictionaryName1{"dictionaryName1"};
const std::string dictionaryName2{"dictionaryName2"};
const DictionaryWord dictionaryWord1{"car", std::string{"samochod"}};
const DictionaryWord dictionaryWord2{"air", std::string{"powietrze"}};
const DictionaryWord dictionaryWord3{"air", std::nullopt};
const std::vector<DictionaryWord> dictionaryWords{dictionaryWord1, dictionaryWord2};
const std::string emptyContent{};
}

class DictionaryWordsCsvFileReaderImplTest : public Test
{
public:
    std::shared_ptr<common::fileSystem::FileAccessMock> fileAccess =
        std::make_shared<StrictMock<common::fileSystem::FileAccessMock>>();
    DictionaryWordsCsvReaderImpl reader{fileAccess};
};

TEST_F(DictionaryWordsCsvFileReaderImplTest, givenIncorrectFileContentFormat1_shouldReturnThrowError)
{
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath)).WillOnce(Return(contentWithIncorrectFormat));

    ASSERT_THROW(reader.readDictionaryWords(absoluteDictionaryWordsPath), exceptions::InvalidDictionaryWordsCsvFile);
}

TEST_F(DictionaryWordsCsvFileReaderImplTest, givenIncorrectFileContentFormat2_shouldReturnThrowError)
{
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath)).WillOnce(Return(contentWithoutSeparator));

    ASSERT_THROW(reader.readDictionaryWords(absoluteDictionaryWordsPath), exceptions::InvalidDictionaryWordsCsvFile);
}

TEST_F(DictionaryWordsCsvFileReaderImplTest, givenEmptyDictionaryWordsContent_shouldReturnEmptyDictionaryWords)
{
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath)).WillOnce(Return(emptyContent));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    EXPECT_TRUE(actualDictionaryWords.empty());
}

TEST_F(DictionaryWordsCsvFileReaderImplTest,
       givenContentWithEnglishWordWithoutTranslation_shouldReturnDictionaryWordsWithEnglishWordAndNoneTranslation)
{
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath))
        .WillOnce(Return(contentWithTwoWordsAndOneIncomplete));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    const std::vector<DictionaryWord> expectedDictionaryWords{dictionaryWord1, dictionaryWord3};

    EXPECT_EQ(actualDictionaryWords, expectedDictionaryWords);
}

TEST_F(DictionaryWordsCsvFileReaderImplTest, givenDictionaryWordsContent_shouldReadDictionaryWords)
{
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath)).WillOnce(Return(content));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    EXPECT_EQ(actualDictionaryWords, dictionaryWords);
}

TEST_F(DictionaryWordsCsvFileReaderImplTest, givenDictionaryWordsContentWithWhiteSpaces_shouldReadDictionaryWords)
{
    EXPECT_CALL(*fileAccess, readContent(absoluteDictionaryWordsPath)).WillOnce(Return(contentWithWhiteSpaces));

    const auto actualDictionaryWords = reader.readDictionaryWords(absoluteDictionaryWordsPath);

    EXPECT_EQ(actualDictionaryWords, dictionaryWords);
}
