#include "DefaultApiKeyLocationUpdater.h"

#include "utils/FileAccessMock.h"

#include "utils/GetProjectPath.h"
#include <boost/optional/optional_io.hpp>

using namespace ::testing;
using namespace glossary::wordDescriptionService;

namespace
{
const std::string filePathWithPathToFileWithApiKey{utils::getProjectPath("glossary") +
                                                   "config/wordsApiKeyLocation.txt"};
const std::string exampleApiKey{"apiKey"};
const std::string apiKeyLocation{"apiKeyLocation"};
}

class DefaultApiKeyLocationUpdaterTest : public Test
{
public:
    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    DefaultApiKeyLocationUpdater apiKeyLocationUpdater{fileAccess};
};

TEST_F(DefaultApiKeyLocationUpdaterTest, configFileWithPathToFileWithApiKeyNotExists_shouldDoNothing)
{
    EXPECT_CALL(*fileAccess, exists(filePathWithPathToFileWithApiKey)).WillOnce(Return(false));

    apiKeyLocationUpdater.updateApiKeyLocation(apiKeyLocation);
}

TEST_F(DefaultApiKeyLocationUpdaterTest,
       configFileWithPathToFileWithApiKeyExists_shouldOverwriteContentOfFileWithWordsApiKeyLocation)
{
    EXPECT_CALL(*fileAccess, exists(filePathWithPathToFileWithApiKey)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, write(filePathWithPathToFileWithApiKey, apiKeyLocation));

    apiKeyLocationUpdater.updateApiKeyLocation(apiKeyLocation);
}
