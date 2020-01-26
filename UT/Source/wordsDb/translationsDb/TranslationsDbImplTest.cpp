#include "wordsDb/translationsDb/TranslationsDbImpl.h"

#include "wordsDb/translationsDb/TranslationsStorageMock.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace wordsDb::translationsDb;

namespace
{
const PolishWord polishWord1{"polishWord1"};
const PolishWord polishWord2{"polishWord2"};
const EnglishWord englishWord1{"englishWord1"};
const EnglishWord englishWord2{"englishWord2"};
const Translation translation1{polishWord1, englishWord1};
const Translation translation2{polishWord2, englishWord2};
const Translations translations{translation1,translation2};
}

class TranslationsDbImplTest : public Test
{
public:
    std::unique_ptr<TranslationsStorageMock> storageInit =
        std::make_unique<StrictMock<TranslationsStorageMock>>();
    TranslationsStorageMock* storage = storageInit.get();
    TranslationsDbImpl database{std::move(storageInit)};
};

TEST_F(TranslationsDbImplTest, addTranslation)
{
    EXPECT_CALL(*storage, addTranslation(translation1));

    database.addTranslation(translation1);
}

TEST_F(TranslationsDbImplTest,
       getTranslation)
{
    EXPECT_CALL(*storage, getTranslation(polishWord1))
        .WillOnce(Return(translation1));

    const auto actualTranslation = database.getTranslation(polishWord1);

    ASSERT_EQ(actualTranslation, translation1);
}

TEST_F(TranslationsDbImplTest, getTranslations)
{
    EXPECT_CALL(*storage, getTranslations())
        .WillOnce(Return(translations));

    const auto actualTranslations = database.getTranslations();

    ASSERT_EQ(actualTranslations, translations);
}
