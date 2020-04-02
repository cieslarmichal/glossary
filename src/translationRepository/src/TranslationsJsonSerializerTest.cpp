#include "TranslationsJsonSerializer.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::translationRepository;

namespace
{
const SourceText polishWord1{"polishWord1"};
const SourceText polishWord2{"polishWord2"};
const TranslatedText englishWord1{"englishWord1"};
const TranslatedText englishWord2{"englishWord2"};
const Translation translation1{polishWord1, englishWord1};
const Translation translation2{polishWord2, englishWord2};
const Translations translations{translation1, translation2};
const Translations translationsWithOneTranslation{translation1};
const Translations emptyTranslations{};
const std::string invalidJson{"{."};
const std::string serializedTranslations{
    R"({"translations":[{"englishWord":"englishWord1","polishWord":"polishWord1"},{"englishWord":"englishWord2","polishWord":"polishWord2"}]})"};
const std::string twoSerializedTranslationsOneWithoutRequiredField{
    R"({"translations":[{"englishWord":"englishWord1", "polishWord":"polishWord1"},{"polishWord":"polishWord2"}]})"};
const std::string serializedTranslationsWithoutRequiredFields{
    R"({"translations":[{"polishWord":"polishWord1"},{"polishWord":"polishWord2"}]})"};
const std::string serializedTranslationsWithoutTranslationsField{
    R"({"xxxx":[{"polishWord":"polishWord1"},{"polishWord":"polishWord2"}]})"};
const std::string emptySerializedStatistics{};
}

class TranslationsJsonSerializerTest : public Test
{
public:
    TranslationsJsonSerializer serializer;
};

TEST_F(TranslationsJsonSerializerTest, givenNoTranslations_shouldReturnEmptyString)
{
    const auto actualSerializedTranslations = serializer.serialize(emptyTranslations);

    EXPECT_TRUE(actualSerializedTranslations.empty());
}

TEST_F(TranslationsJsonSerializerTest, givenTranslations_shouldReturnSerializedTranslations)
{
    const auto actualSerializedTranslations = serializer.serialize(translations);

    EXPECT_EQ(actualSerializedTranslations, serializedTranslations);
}

TEST_F(TranslationsJsonSerializerTest, givenInvalidJson_shouldReturnNoTranslations)
{
    const auto actualTranslations = serializer.deserialize(invalidJson);

    EXPECT_TRUE(actualTranslations.empty());
}

TEST_F(TranslationsJsonSerializerTest, givenJsonWithoutTranslationsField_shouldReturnNoTranslations)
{
    const auto actualTranslations = serializer.deserialize(serializedTranslationsWithoutTranslationsField);

    EXPECT_TRUE(actualTranslations.empty());
}

TEST_F(TranslationsJsonSerializerTest, givenSerializedTranslations_shouldReturnTranslations)
{
    const auto actualTranslations = serializer.deserialize(serializedTranslations);

    EXPECT_EQ(actualTranslations, translations);
}

TEST_F(TranslationsJsonSerializerTest, givenEmptySerializedTranslationsString_shouldReturnNoTranslations)
{
    const auto actualTranslations = serializer.deserialize(emptySerializedStatistics);

    EXPECT_TRUE(actualTranslations.empty());
}

TEST_F(TranslationsJsonSerializerTest,
       givenSerializedTranslationsWithoutRequiredFields_shouldReturnEmptyTranslations)
{
    const auto actualTranslations = serializer.deserialize(serializedTranslationsWithoutRequiredFields);

    EXPECT_TRUE(actualTranslations.empty());
}

TEST_F(TranslationsJsonSerializerTest,
       givenTwoSerializedTranslationsAndOneOfThemWithoutRequiredFields_shouldReturnTranslationForOneWord)
{
    const auto actualTranslations = serializer.deserialize(twoSerializedTranslationsOneWithoutRequiredField);

    EXPECT_EQ(actualTranslations, translationsWithOneTranslation);
}
