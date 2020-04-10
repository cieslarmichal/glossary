#include "TranslateApiKeyFileReader.h"

#include "gtest/gtest.h"

#include "utils/FileAccessMock.h"

#include "utils/GetProjectPath.h"

using namespace ::testing;
using namespace glossary::translationService;

namespace
{
const std::string filePathWithPathToFileWithApiKey{utils::getProjectPath("glossary") +
                                                   "config/translatorApiKeyLocation.txt"};
const std::string invalidFilePathWithApiKey{"home/invalidApiKeyFilePath.txt"};
const std::string validFilePathWithApiKey{"home/validApiKeyFilePath.txt"};
const std::string exampleApiKey{"apiKey"};
}

class TranslateApiKeyFileReaderTest : public Test
{
public:
    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    TranslateApiKeyFileReader apiKeyFileReader{fileAccess};
};

TEST_F(TranslateApiKeyFileReaderTest, configFileWithPathToFileWithApiKeyNotExists_shouldReturnNone)
{
    EXPECT_CALL(*fileAccess, exists(filePathWithPathToFileWithApiKey)).WillOnce(Return(false));

    const auto actualApiKey = apiKeyFileReader.readApiKey();

    ASSERT_EQ(actualApiKey, boost::none);
}

TEST_F(TranslateApiKeyFileReaderTest,
       configFileWithPathToFileWithApiKeyExists_filePathWithApiKeyNotExists_shouldReturnNone)
{
    EXPECT_CALL(*fileAccess, exists(filePathWithPathToFileWithApiKey)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, readContent(filePathWithPathToFileWithApiKey))
        .WillOnce(Return(invalidFilePathWithApiKey));
    EXPECT_CALL(*fileAccess, exists(invalidFilePathWithApiKey)).WillOnce(Return(false));

    const auto actualApiKey = apiKeyFileReader.readApiKey();

    ASSERT_EQ(actualApiKey, boost::none);
}

TEST_F(TranslateApiKeyFileReaderTest,
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