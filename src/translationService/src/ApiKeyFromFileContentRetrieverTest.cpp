#include "ApiKeyFromFileContentRetriever.h"

#include "gtest/gtest.h"
#include <boost/optional/optional_io.hpp>

using namespace ::testing;
using namespace glossary::translationService;

namespace
{
const std::string fileContentWithWhiteSpaces{" \n\n       apiKey\n\n\n "};
const std::string fileContentWithoutWhiteSpaces{"apiKey"};
const std::string expectedApiKey{"apiKey"};
}

class ApiKeyFromFileContentRetrieverTest : public Test
{
public:
    ApiKeyFromFileContentRetriever retriever;
};

TEST_F(ApiKeyFromFileContentRetrieverTest, givenFileContentWithWhiteSpaces_shouldIgnoreThemAndReturnApiKey)
{
    const auto actualApiKey = retriever.retrieveApiKeyFromFileContent(fileContentWithWhiteSpaces);

    ASSERT_EQ(actualApiKey, expectedApiKey);
}

TEST_F(ApiKeyFromFileContentRetrieverTest, givenFileContentWithotWhiteSpaces_shouldReturnApiKey)
{
    const auto actualApiKey = retriever.retrieveApiKeyFromFileContent(fileContentWithoutWhiteSpaces);

    ASSERT_EQ(actualApiKey, expectedApiKey);
}
