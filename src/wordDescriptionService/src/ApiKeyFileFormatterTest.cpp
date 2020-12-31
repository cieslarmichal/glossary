#include "ApiKeyFileFormatter.h"

#include "gtest/gtest.h"
#include <boost/optional/optional_io.hpp>

using namespace ::testing;
using namespace glossary::wordDescriptionService;

namespace
{
const std::string fileContentWithWhiteSpaces{" \n\n       apiKey\n\n\n "};
const std::string fileContentWithoutWhiteSpaces{"apiKey"};
const std::string expectedApiKey{"apiKey"};
}

class ApiKeyFromFileContentRetrieverTest : public Test
{
public:
    ApiKeyFileFormatter formatter;
};

TEST_F(ApiKeyFromFileContentRetrieverTest, givenFileContentWithWhiteSpaces_shouldIgnoreThemAndReturnApiKey)
{
    const auto actualApiKey = formatter.getFormattedApiKey(fileContentWithWhiteSpaces);

    ASSERT_EQ(actualApiKey, expectedApiKey);
}

TEST_F(ApiKeyFromFileContentRetrieverTest, givenFileContentWithotWhiteSpaces_shouldReturnApiKey)
{
    const auto actualApiKey = formatter.getFormattedApiKey(fileContentWithoutWhiteSpaces);

    ASSERT_EQ(actualApiKey, expectedApiKey);
}
