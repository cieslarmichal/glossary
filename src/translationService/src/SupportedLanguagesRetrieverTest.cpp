#include "SupportedLanguagesRetriever.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary;
using namespace translationService;
using namespace translator;

namespace
{
const std::vector<std::string> supportedLanguages{"Polish", "English"};
}

class SupportedLanguagesRetrieverTest : public Test
{
public:
    SupportedLanguagesRetriever retriever;
};

TEST_F(SupportedLanguagesRetrieverTest, shouldReturnSupportedLanguages)
{
    const auto actualSupportedLanguages = retriever.retrieveSupportedLanguages();

    ASSERT_EQ(actualSupportedLanguages, supportedLanguages);
}