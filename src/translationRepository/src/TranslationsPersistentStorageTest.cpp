#include "TranslationsPersistentStorage.h"

#include "gtest/gtest.h"

#include "TranslationsSerializerMock.h"
#include "utils/include/utils/FileAccessMock.h"

#include "utils/GetProjectPath.h"
#include "utils/exceptions/FileNotFound.h"

using namespace ::testing;
using namespace glossary::translationRepository;

namespace
{
const std::string filePath{utils::getProjectPath("glossary") + "repositoryFiles/translations.txt"};
const SourceText polishWord1{"polishWord1"};
const SourceText polishWord2{"polishWord2"};
const SourceText nonExistingPolishWord{"nonExisting"};
const TranslatedText englishWord1{"englishWord1"};
const TranslatedText englishWord2{"englishWord2"};
const Translation translation1{polishWord1, englishWord1};
const Translation translation2{polishWord2, englishWord2};
const Translations translationsWithOneTranslation{translation1};
const Translations translationsWithTwoTranslations{translation1, translation2};
const Translations emptyTranslations{};
}

class TranslationsPersistentStorageTest : public Test
{
public:
    void expectTwoTranslationsLoad()
    {
        EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return("some content"));
        EXPECT_CALL(*serializer, deserialize("some content"))
            .WillOnce(Return(translationsWithTwoTranslations));
    }

    void expectNoTranslationsLoad()
    {
        EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return("some content"));
        EXPECT_CALL(*serializer, deserialize("some content")).WillOnce(Return(emptyTranslations));
    }

    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    std::shared_ptr<TranslationsSerializerMock> serializer =
        std::make_shared<StrictMock<TranslationsSerializerMock>>();
};

TEST_F(TranslationsPersistentStorageTest, givenPersistentStorageWithEmptyFile_shouldBeEmpty)
{
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return(""));
    EXPECT_CALL(*serializer, deserialize("")).WillOnce(Return(emptyTranslations));
    TranslationsPersistentStorage persistentStorage{fileAccess, serializer};

    ASSERT_TRUE(persistentStorage.empty());
}

TEST_F(TranslationsPersistentStorageTest, givenPersistentStorageWithFileWithStatistics_shouldLoadTranslations)
{
    expectTwoTranslationsLoad();
    TranslationsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualTranslations = persistentStorage.getTranslations();

    ASSERT_EQ(actualTranslations, translationsWithTwoTranslations);
}

TEST_F(TranslationsPersistentStorageTest, givenInvalidFile_shouldReturnNoTranslations)
{
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Throw(utils::exceptions::FileNotFound{""}));
    TranslationsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualTranslations = persistentStorage.getTranslations();

    EXPECT_TRUE(actualTranslations.empty());
}

TEST_F(TranslationsPersistentStorageTest, givenTranslationAddition_shouldAddWordTranslationAndSerialize)
{
    expectNoTranslationsLoad();
    TranslationsPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, write(filePath, "words"));
    EXPECT_CALL(*serializer, serialize(translationsWithOneTranslation)).WillOnce(Return("words"));

    persistentStorage.addTranslation(translation1);

    ASSERT_TRUE(persistentStorage.contains(translation1.sourceText));
}

TEST_F(TranslationsPersistentStorageTest,
       givenTranslationAdditionAndNonExistingFIle_shouldAddWordTranslationAndNotSerialize)
{
    expectNoTranslationsLoad();
    TranslationsPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, write(filePath, "words")).WillOnce(Throw(utils::exceptions::FileNotFound{""}));
    EXPECT_CALL(*serializer, serialize(translationsWithOneTranslation)).WillOnce(Return("words"));

    persistentStorage.addTranslation(translation1);

    ASSERT_TRUE(persistentStorage.contains(translation1.sourceText));
}

TEST_F(TranslationsPersistentStorageTest, givenTwoSameTranslations_shouldAddAndSerializeOnlyOne)
{
    expectNoTranslationsLoad();
    TranslationsPersistentStorage persistentStorage{fileAccess, serializer};

    EXPECT_CALL(*fileAccess, write(filePath, "words"));
    EXPECT_CALL(*serializer, serialize(translationsWithOneTranslation)).WillOnce(Return("words"));

    persistentStorage.addTranslation(translation1);
    persistentStorage.addTranslation(translation1);

    ASSERT_EQ(persistentStorage.size(), 1);
}

TEST_F(TranslationsPersistentStorageTest, addTwoDifferentTranslations_shouldAddAndSerializeBoth)
{
    expectNoTranslationsLoad();
    TranslationsPersistentStorage persistentStorage{fileAccess, serializer};

    EXPECT_CALL(*fileAccess, write(filePath, "words"));
    EXPECT_CALL(*serializer, serialize(translationsWithOneTranslation)).WillOnce(Return("words"));

    persistentStorage.addTranslation(translation1);

    EXPECT_CALL(*fileAccess, write(filePath, "words"));
    EXPECT_CALL(*serializer, serialize(translationsWithTwoTranslations)).WillOnce(Return("words"));

    persistentStorage.addTranslation(translation2);

    ASSERT_EQ(persistentStorage.size(), 2);
}

TEST_F(TranslationsPersistentStorageTest, givenExistingInStoragePolishWord_shouldReturnThisWordsTranslation)
{
    expectTwoTranslationsLoad();
    TranslationsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWordStats = persistentStorage.getTranslation(polishWord1);

    ASSERT_EQ(*actualWordStats, translation1);
}

TEST_F(TranslationsPersistentStorageTest, givenTwoTranslations_shouldContainsThoseTwoTranslations)
{
    expectTwoTranslationsLoad();
    TranslationsPersistentStorage persistentStorage{fileAccess, serializer};

    ASSERT_TRUE(persistentStorage.contains(polishWord1));
    ASSERT_TRUE(persistentStorage.contains(polishWord2));
    ASSERT_FALSE(persistentStorage.contains(nonExistingPolishWord));
}
