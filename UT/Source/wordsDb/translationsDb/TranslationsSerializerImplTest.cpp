#include "wordsDb/translationsDb/TranslationsSerializerImpl.h"

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
const Translations translationsWithOneTranslation{translation1};
const Translations emptyTranslations{};
const std::string serializedTranslations{
    R"({"translations":[{"englishWord":"cat","polishWord":"kot"},{"englishWord":"dog","polishWord":"pies"}]})"};
const std::string twoSerializedTranslationsOneWithoutRequiredField{
    R"({"translations":[{"correctAnswers":7,"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"incorrectAnswers":1}]})"};
const std::string serializedTranslationsWithoutRequiredFields{
    R"({"translations":[{"englishWord":"cat","incorrectAnswers":0},{"correctAnswers":2,"incorrectAnswers":1}]})"};
const std::string emptySerializedStatistics{};
}

class TranslationsSerializerImplTest : public Test
{
public:
    TranslationsSerializerImpl serializer;
};

//TEST_F(TranslationsSerializerImplTest,
//       givenNoTranslations_shouldReturnEmptyString)
//{
//    const auto actualSerializedTranslations =
//        serializer.serialize(emptyTranslations);
//
//    EXPECT_TRUE(actualSerializedTranslations.empty());
//}
//
//TEST_F(TranslationsSerializerImplTest,
//       givenTranslations_shouldReturnSerializedTranslations)
//{
//    const auto actualSerializedTranslations =
//        serializer.serialize(translations);
//
//    EXPECT_EQ(actualSerializedTranslations, serializedTranslations);
//}
//
//TEST_F(TranslationsSerializerImplTest,
//       givenSerializedTranslations_shouldReturnTranslations)
//{
//    const auto actualTranslations =
//        serializer.deserialize(serializedTranslations);
//
//    EXPECT_EQ(actualTranslations, translations);
//}
//
//TEST_F(TranslationsSerializerImplTest,
//       givenEmptySerializedTranslationsString_shouldReturnNoTranslations)
//{
//    const auto actualTranslations =
//        serializer.deserialize(emptySerializedStatistics);
//
//    EXPECT_TRUE(actualTranslations.empty());
//}
//
//TEST_F(
//    TranslationsSerializerImplTest,
//    givenSerializedTranslationsWithoutRequiredFields_shouldReturnEmptyTranslations)
//{
//    const auto actualTranslations =
//        serializer.deserialize(serializedTranslationsWithoutRequiredFields);
//
//    EXPECT_TRUE(actualTranslations.empty());
//}
//
//TEST_F(
//    TranslationsSerializerImplTest,
//    givenTwoSerializedTranslationsAndOneOfThemWithoutRequiredFields_shouldReturnTranslationForOneWord)
//{
//    const auto actualTranslations =
//        serializer.deserialize(twoSerializedTranslationsOneWithoutRequiredField);
//
//    EXPECT_EQ(actualTranslations, translationsWithOneTranslation);
//}
