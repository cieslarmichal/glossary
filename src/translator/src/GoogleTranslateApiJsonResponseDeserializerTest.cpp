#include "gtest/gtest.h"

#include "GoogleTranslateApiJsonResponseDeserializer.h"

using namespace ::testing;
using namespace glossary::translator;

namespace
{
const std::string exampleGoogleApiJsonResponse = R"({
  "data": {
    "translations": [
      {
        "translatedText": "kostka",
        "detectedSourceLanguage": "en"
      }
    ]
  }
})";
const std::string translatedText = "kostka";
const auto invalidJson{"{:"};
const auto emptyJson = "";
}

class GoogleTranslateApiJsonResponseDeserializerTest : public Test
{
public:
    GoogleTranslateApiJsonResponseDeserializer deserializer;
};

TEST_F(GoogleTranslateApiJsonResponseDeserializerTest, givenEmpyJson_shouldReturnEmptyText)
{
    const auto actualText = deserializer.deserialize(emptyJson);

    ASSERT_TRUE(actualText.empty());
}

TEST_F(GoogleTranslateApiJsonResponseDeserializerTest, givenInvalidJson_shouldReturnEmptyText)
{
    const auto actualText = deserializer.deserialize(invalidJson);

    ASSERT_TRUE(actualText.empty());
}

TEST_F(GoogleTranslateApiJsonResponseDeserializerTest, givenJsonWithTranslation_shouldReturnText)
{
    const auto actualText = deserializer.deserialize(exampleGoogleApiJsonResponse);

    ASSERT_EQ(actualText, translatedText);
}
