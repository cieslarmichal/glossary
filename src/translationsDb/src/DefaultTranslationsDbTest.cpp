#include "gtest/gtest.h"

#include "TranslationsStorageMock.h"

#include "DefaultTranslationsDb.h"

using namespace ::testing;
using namespace translationsDb;

namespace
{
const SourceText polishWord1{"polishWord1"};
const SourceText polishWord2{"polishWord2"};
const TranslatedText englishWord1{"englishWord1"};
const TranslatedText englishWord2{"englishWord2"};
const Translation translation1{polishWord1, englishWord1};
const Translation translation2{polishWord2, englishWord2};
const Translations translations{translation1, translation2};
}

class DefaultTranslationsDbTest : public Test
{
public:
    std::unique_ptr<TranslationsStorageMock> storageInit =
        std::make_unique<StrictMock<TranslationsStorageMock>>();
    TranslationsStorageMock* storage = storageInit.get();
    DefaultTranslationsDb database{std::move(storageInit)};
};

TEST_F(DefaultTranslationsDbTest, addTranslation)
{
    EXPECT_CALL(*storage, addTranslation(translation1));

    database.addTranslation(translation1);
}

TEST_F(DefaultTranslationsDbTest, getTranslation)
{
    EXPECT_CALL(*storage, getTranslation(polishWord1)).WillOnce(Return(translation1));

    const auto actualTranslation = database.getTranslation(polishWord1);

    ASSERT_EQ(actualTranslation, translation1);
}

TEST_F(DefaultTranslationsDbTest, getTranslations)
{
    EXPECT_CALL(*storage, getTranslations()).WillOnce(Return(translations));

    const auto actualTranslations = database.getTranslations();

    ASSERT_EQ(actualTranslations, translations);
}
