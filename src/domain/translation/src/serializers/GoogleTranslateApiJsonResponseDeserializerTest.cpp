#include "GoogleTranslateApiJsonResponseDeserializer.h"

#include "gtest/gtest.h"

#include "exceptions/GoogleTranslateApiJsonResponseMissingRequiredFieldsError.h"
#include "exceptions/InvalidJsonError.h"

using namespace ::testing;
using namespace glossary::translation;

namespace
{
const std::string googleApiJsonResponse = R"({
  "data": {
    "translations": [
      {
        "translatedText": "poduszka",
        "detectedSourceLanguage": "en"
      }
    ]
  }
})";
const std::string googleApiJsonResponseWithoutDataField = R"({
  "missing": {
    "translations": [
      {
        "translatedText": "poduszka",
        "detectedSourceLanguage": "en"
      }
    ]
  }
})";
const std::string googleApiJsonResponseWithoutTranslationsField = R"({
  "data": {
    "missing": [
      {
        "translatedText": "poduszka",
        "detectedSourceLanguage": "en"
      }
    ]
  }
})";
const std::string googleApiJsonResponseWithoutTranslatedTextField = R"({
  "data": {
    "translations": [
      {
        "missing": "poduszka",
        "detectedSourceLanguage": "en"
      }
    ]
  }
})";
const std::string googleApiJsonResponseWithoutDetectedSourceLanguageField = R"({
  "data": {
    "translations": [
      {
        "translatedText": "poduszka",
        "missing": "en"
      }
    ]
  }
})";
const auto invalidJson{"{:"};
const auto emptyJson = "{}";
}

class GoogleTranslateApiJsonResponseDeserializerTest : public Test
{
public:
    GoogleTranslateApiJsonResponseDeserializer deserializer;
};

TEST_F(GoogleTranslateApiJsonResponseDeserializerTest, givenInvalidJson_shouldThrowInvalidJsonError)
{
    ASSERT_THROW(deserializer.deserialize(invalidJson), exceptions::InvalidJsonError);
}

TEST_F(GoogleTranslateApiJsonResponseDeserializerTest, givenJsonWithoutDataField_shouldThrowError)
{
    ASSERT_THROW(deserializer.deserialize(googleApiJsonResponseWithoutDataField),
                 exceptions::GoogleTranslateApiJsonResponseMissingRequiredFieldsError);
}

TEST_F(GoogleTranslateApiJsonResponseDeserializerTest, givenJsonWithoutTranslationsField_shouldThrowError)
{
    ASSERT_THROW(deserializer.deserialize(googleApiJsonResponseWithoutTranslationsField),
                 exceptions::GoogleTranslateApiJsonResponseMissingRequiredFieldsError);
}

TEST_F(GoogleTranslateApiJsonResponseDeserializerTest, givenJsonWithoutTranslatedTextField_shouldThrowError)
{
    ASSERT_THROW(deserializer.deserialize(googleApiJsonResponseWithoutTranslatedTextField),
                 exceptions::GoogleTranslateApiJsonResponseMissingRequiredFieldsError);
}

TEST_F(GoogleTranslateApiJsonResponseDeserializerTest,
       givenJsonWithoutDetectedSourceLanguageField_shouldThrowError)
{
    ASSERT_THROW(deserializer.deserialize(googleApiJsonResponseWithoutDetectedSourceLanguageField),
                 exceptions::GoogleTranslateApiJsonResponseMissingRequiredFieldsError);
}

TEST_F(GoogleTranslateApiJsonResponseDeserializerTest, givenEmptyJson_shouldReturnNoTranslations)
{
    const auto result = deserializer.deserialize(emptyJson);

    ASSERT_TRUE(result.data.translations.empty());
}

TEST_F(GoogleTranslateApiJsonResponseDeserializerTest,
       givenCorrectlyFormattedJsonResponse_shouldReturnTranslationsTranslationsObject)
{
    const auto result = deserializer.deserialize(googleApiJsonResponse);

    const auto expectedTranslation = GoogleTranslateApiResponseDataTranslation{"poduszka", "en"};

    ASSERT_EQ(result.data.translations.size(), 1);
    ASSERT_EQ(result.data.translations[0], expectedTranslation);
}
