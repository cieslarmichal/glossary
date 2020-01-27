#include "wordsDb/translationsDb/TranslationsMemoryStorage.h"

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
const Translations translations{translation1, translation2};
}

class TranslationsMemoryStorageTest : public Test
{
public:
    TranslationsMemoryStorage storage;
};

TEST_F(TranslationsMemoryStorageTest,
       givenTranslationNotExistingInStorage_shouldAddTranslation)
{
    ASSERT_TRUE(storage.empty());

    storage.addTranslation(translation1);

    ASSERT_FALSE(storage.empty());
    ASSERT_EQ(storage.size(), 1);
}

TEST_F(TranslationsMemoryStorageTest,
       givenTranslationExistingInStorage_shouldNotAddTranslation)
{
    storage.addTranslation(translation1);
    storage.addTranslation(translation1);

    ASSERT_EQ(storage.size(), 1);
}

TEST_F(TranslationsMemoryStorageTest,
       givenTwoTranslations_shouldReturnTranslations)
{
    storage.addTranslation(translation1);
    storage.addTranslation(translation2);

    const auto actualTranslations = storage.getTranslations();

    ASSERT_EQ(actualTranslations, translations);
}

TEST_F(TranslationsMemoryStorageTest,
       givenExistingInStoragePolishWordsTranslation_shouldReturnTranslation)
{
    storage.addTranslation(translation1);

    const auto actualTranslation = storage.getTranslation(polishWord1);

    ASSERT_EQ(*actualTranslation, translation1);
}

TEST_F(TranslationsMemoryStorageTest,
       givenNonExistingInStoragePolishWordsTranslation_shouldReturnNone)
{
    const auto actualTranslation = storage.getTranslation(polishWord1);

    ASSERT_EQ(actualTranslation, boost::none);
}

TEST_F(TranslationsMemoryStorageTest,
       givenTwoTranslations_shouldReturnTwoElementsBasingOnBeginEnd)
{
    storage.addTranslation(translation1);
    storage.addTranslation(translation2);

    const auto amountOfTranslations =
        std::distance(storage.begin(), storage.end());

    ASSERT_EQ(amountOfTranslations, 2);
}

TEST_F(TranslationsMemoryStorageTest, givenInitStorage_shouldBeEmpty)
{
    ASSERT_TRUE(storage.empty());
}
