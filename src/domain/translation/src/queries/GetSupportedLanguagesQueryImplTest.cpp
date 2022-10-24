#include "GetSupportedLanguagesQueryImpl.h"

#include "gtest/gtest.h"

#include "collection/StlOperators.h"
#include "Language.h"

using namespace ::testing;
using namespace glossary::translation;

class GetSupportedLanguagesQueryImplTest : public Test
{
public:
    GetSupportedLanguagesQueryImpl query;
};

TEST_F(GetSupportedLanguagesQueryImplTest, getSupportedLanguages)
{
    const std::vector<Language> expectedLanguages = {Language::English, Language::Polish};

    const auto actualLanguages = query.getSupportedLanguages();

    ASSERT_TRUE(compareVectors(actualLanguages, expectedLanguages));
}
