#include "DefaultDictionaryReader.h"

#include "gtest/gtest.h"
#include "utils/FileAccessMock.h"
#include "utils/exceptions/FileNotFound.h"

using namespace ::testing;
using namespace utils;
using namespace dictionaryRepository;

namespace
{
const std::string baseDictionaryName{"base"};
const std::string dictionaryFilePath{"database/dictionaries/input.txt"};
const std::string content{"car samochod\n"
                          "air powietrze\n"};
const std::string contentWithTwoWordsAndOneIncomplete{"car samochod\n"
                                                     "     air\n"};
const DictionaryName dictionaryName1{"dictionaryName1"};
const DictionaryName dictionaryName2{"dictionaryName2"};
const DictionaryWord dictionaryWord1{"car", std::string{"samochod"}};
const DictionaryWord dictionaryWord2{"air", std::string{"powietrze"}};
const DictionaryWord dictionaryWord3{"air", boost::none};
const Dictionary emptyDictionary1{dictionaryName1, {}};
const Dictionary dictionaryWithTwoWordAndOneIncomplete{dictionaryName1,{dictionaryWord1, dictionaryWord3}};
const Dictionary completeDictionary{dictionaryName1, DictionaryWords{dictionaryWord1, dictionaryWord2}};
const std::string emptyContent{};
}

class DefaultDictionaryReaderTest : public Test
{
public:
    bool dictionariesContainDictionary(const Dictionaries& dictionariesToLook, const Dictionary& dictionaryToFind)
    {
        return std::find(dictionariesToLook.begin(), dictionariesToLook.end(), dictionaryToFind) != dictionariesToLook.end();
    }

    std::shared_ptr<FileAccessMock> fileAccess = std::make_shared<StrictMock<FileAccessMock>>();
    DefaultDictionaryReader reader{fileAccess};
};

TEST_F(DefaultDictionaryReaderTest, givenEmptyDictionaryContent_shouldReturnEmptyDictionary)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath)).WillOnce(Return(emptyContent));

    const auto actualDictionaries = reader.readDictionaries();

    EXPECT_TRUE(dictionariesContainDictionary(actualDictionaries, emptyDictionary1));
}

TEST_F(DefaultDictionaryReaderTest,
       givenyDictionaryContentWithTwoWordsAndOneOfThemIsIncomplete_shouldReturnDictWithOneWord)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath))
        .WillOnce(Return(contentWithTwoWordsAndOneIncomplete));

    const auto actualDictionaries = reader.readDictionaries();

    EXPECT_TRUE(dictionariesContainDictionary(actualDictionaries, dictionaryWithTwoWordAndOneIncomplete));
}

TEST_F(DefaultDictionaryReaderTest, givenDictionaryContent_shouldReadDictionary)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath)).WillOnce(Return(content));

    const auto actualDictionaries = reader.readDictionaries();

    EXPECT_TRUE(dictionariesContainDictionary(actualDictionaries, completeDictionary));
}

TEST_F(DefaultDictionaryReaderTest, givenInvalidFile_shouldReturnEmptyDictionary)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryFilePath))
        .WillOnce(Throw(utils::exceptions::FileNotFound{""}));

    const auto actualDictionaries = reader.readDictionaries();

    EXPECT_TRUE(actualDictionaries.empty());
}
