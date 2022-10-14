#include "WordsApiKeyFileReader.h"

#include "gtest/gtest.h"

#include "../../common/fileSystem/include/FileAccessMock.h"

#include "../../common/fileSystem/include/GetProjectPath.h"

using namespace ::testing;
using namespace glossary::wordDescriptionService;

namespace
{
const std::string filePathWithPathToFileWithApiKey{common::fileSystem::getProjectPath("glossary") +
                                                   "config/wordsApiKeyLocation.txt"};
const std::string invalidFilePathWithApiKey{"home/invalidApiKeyFilePath.txt"};
const std::string validFilePathWithApiKey{"home/validApiKeyFilePath.txt"};
const std::string exampleApiKey{"apiKey"};
}

class WordsApiKeyFileReaderTest : public Test
{
public:
    std::shared_ptr<common::fileSystem::FileAccessMock> fileAccess =
        std::make_shared<StrictMock<common::fileSystem::FileAccessMock>>();
    WordsApiKeyFileReader apiKeyFileReader{fileAccess};
};

TEST_F(WordsApiKeyFileReaderTest, configFileWithPathToFileWithApiKeyNotExists_shouldReturnNone)
{
    EXPECT_CALL(*fileAccess, exists(filePathWithPathToFileWithApiKey)).WillOnce(Return(false));

    const auto actualApiKey = apiKeyFileReader.readApiKey();

    ASSERT_EQ(actualApiKey, std::nullopt);
}

TEST_F(WordsApiKeyFileReaderTest,
       configFileWithPathToFileWithApiKeyExists_filePathWithApiKeyNotExists_shouldReturnNone)
{
    EXPECT_CALL(*fileAccess, exists(filePathWithPathToFileWithApiKey)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, readContent(filePathWithPathToFileWithApiKey))
        .WillOnce(Return(invalidFilePathWithApiKey));
    EXPECT_CALL(*fileAccess, exists(invalidFilePathWithApiKey)).WillOnce(Return(false));

    const auto actualApiKey = apiKeyFileReader.readApiKey();

    ASSERT_EQ(actualApiKey, std::nullopt);
}

TEST_F(WordsApiKeyFileReaderTest,
       configFileWithPathToFileWithApiKeyExists_filePathWithApiKeyExists_shouldReturnApiKey)
{
    EXPECT_CALL(*fileAccess, exists(filePathWithPathToFileWithApiKey)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, readContent(filePathWithPathToFileWithApiKey))
        .WillOnce(Return(validFilePathWithApiKey));
    EXPECT_CALL(*fileAccess, exists(validFilePathWithApiKey)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, readContent(validFilePathWithApiKey)).WillOnce(Return(exampleApiKey));

    const auto actualApiKey = apiKeyFileReader.readApiKey();

    ASSERT_EQ(*actualApiKey, exampleApiKey);
}