#include "DefaultTranslationRepository.h"

#include "gtest/gtest.h"

#include "TranslationsStorageMock.h"

using namespace ::testing;
using namespace glossary::translation;

namespace
{
const std::string polishWord1{"polishWord1"};
const std::string polishWord2{"polishWord2"};
const std::string englishWord1{"englishWord1"};
const std::string englishWord2{"englishWord2"};
const Translation translation1{polishWord1, englishWord1};
const Translation translation2{polishWord2, englishWord2};
const std::vector<Translation> translations{translation1, translation2};
}

class DefaultTranslationRepositoryTest : public Test
{
public:
    std::unique_ptr<TranslationsStorageMock> storageInit =
        std::make_unique<StrictMock<TranslationsStorageMock>>();
    TranslationsStorageMock* storage = storageInit.get();
    DefaultTranslationRepository repository{std::move(storageInit)};
};

TEST_F(DefaultTranslationRepositoryTest, addTranslation)
{
    EXPECT_CALL(*storage, addTranslation(translation1));

    repository.addTranslation(translation1);
}

TEST_F(DefaultTranslationRepositoryTest, getTranslation)
{
    EXPECT_CALL(*storage, getTranslation(polishWord1)).WillOnce(Return(translation1));

    const auto actualTranslation = repository.getTranslation(polishWord1);

    ASSERT_EQ(actualTranslation, translation1);
}

TEST_F(DefaultTranslationRepositoryTest, givenTranslationForTextExistingInStorage_shouldContainTranslation)
{
    EXPECT_CALL(*storage, contains(polishWord1)).WillOnce(Return(true));

    ASSERT_TRUE(repository.containsTranslation(polishWord1));
}

TEST_F(DefaultTranslationRepositoryTest,
       givenTranslationForTextNonExistingInStorage_shouldNotContainTranslation)
{
    EXPECT_CALL(*storage, contains(polishWord1)).WillOnce(Return(false));

    ASSERT_FALSE(repository.containsTranslation(polishWord1));
}