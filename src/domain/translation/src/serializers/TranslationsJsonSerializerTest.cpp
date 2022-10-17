#include "TranslationsJsonSerializer.h"

#include "gtest/gtest.h"

#include "exceptions/InvalidJsonError.h"
#include "exceptions/TranslationJsonMissingRequiredFieldsError.h"

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
const std::vector<Translation> translationsWithOneTranslation{translation1};
const std::vector<Translation> emptyTranslations{};
const std::string invalidJson{"{."};
const std::string jsonTranslations{
    R"({"translations":[{"englishWord":"englishWord1","polishWord":"polishWord1"},{"englishWord":"englishWord2","polishWord":"polishWord2"}]})"};
const std::string jsonTranslationsWithoutTranslationsField{
    R"({"missing":[{"englishWord":"englishWord1","polishWord":"polishWord1"},{"englishWord":"englishWord2","polishWord":"polishWord2"}]})"};
const std::string jsonTranslationsWithoutEnglishWordFields{
    R"({"translations":[{"missing":"englishWord1","polishWord":"polishWord1"},{"missing":"englishWord2","polishWord":"polishWord2"}]})"};
const std::string jsonTranslationsWithoutPolishWordFields{
    R"({"translations":[{"englishWord":"englishWord1","missing":"polishWord1"},{"englishWord":"englishWord2","missing":"polishWord2"}]})"};
const std::string emptySerializedTranslations{"{}"};
}

class TranslationsJsonSerializerTest : public Test
{
public:
    TranslationsJsonSerializer serializer;
};

TEST_F(TranslationsJsonSerializerTest, givenNoTranslations_shouldReturnEmptyJson)
{
    const auto actualSerializedTranslations = serializer.serialize(emptyTranslations);

    ASSERT_EQ(actualSerializedTranslations, emptySerializedTranslations);
}

TEST_F(TranslationsJsonSerializerTest, givenTranslations_shouldReturnSerializedTranslations)
{
    const auto actualSerializedTranslations = serializer.serialize(translations);

    ASSERT_EQ(actualSerializedTranslations, jsonTranslations);
}

TEST_F(TranslationsJsonSerializerTest, givenInvalidJson_shouldThrowInvalidJsonError)
{
    ASSERT_THROW(serializer.deserialize(invalidJson), exceptions::InvalidJsonError);
}

TEST_F(TranslationsJsonSerializerTest, givenSerializedTranslations_shouldReturnTranslations)
{
    const auto actualTranslations = serializer.deserialize(jsonTranslations);

    EXPECT_EQ(actualTranslations, translations);
}

TEST_F(TranslationsJsonSerializerTest, givenEmptySerializedTranslationsString_shouldReturnNoTranslations)
{
    const auto actualTranslations = serializer.deserialize(emptySerializedTranslations);

    EXPECT_TRUE(actualTranslations.empty());
}

TEST_F(TranslationsJsonSerializerTest,
       givenJsonWithoutTranslationsField_shouldThrowTranslationJsonMissingRequiredFieldsError)
{
    ASSERT_THROW(serializer.deserialize(jsonTranslationsWithoutTranslationsField),
                 exceptions::TranslationJsonMissingRequiredFieldsError);
}

TEST_F(TranslationsJsonSerializerTest,
       givenJsonWithoutPolishWordField_shouldThrowTranslationJsonMissingRequiredFieldsError)
{
    ASSERT_THROW(serializer.deserialize(jsonTranslationsWithoutPolishWordFields),
                 exceptions::TranslationJsonMissingRequiredFieldsError);
}

TEST_F(TranslationsJsonSerializerTest,
       givenJsonWithoutEnglishWordField_shouldThrowTranslationJsonMissingRequiredFieldsError)
{
    ASSERT_THROW(serializer.deserialize(jsonTranslationsWithoutEnglishWordFields),
                 exceptions::TranslationJsonMissingRequiredFieldsError);
}
