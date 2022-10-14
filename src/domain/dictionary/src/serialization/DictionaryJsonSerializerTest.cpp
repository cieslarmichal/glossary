#include "DictionaryJsonSerializer.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::dictionary;
using namespace serialization;

namespace
{
const std::string dictionaryName1{"dictionaryName1"};
const std::string dictionaryName2{"dictionaryName2"};
const std::string dictionaryName3{"dictionaryName3"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWordWithoutTranslation{"englishWord3", std::nullopt};
const Dictionary dictionary1{dictionaryName1, std::vector<DictionaryWord>{dictionaryWord1}};
const Dictionary dictionary2{dictionaryName2, std::vector<DictionaryWord>{dictionaryWord1, dictionaryWord2}};
const Dictionary dictionaryWithSomeWordsWithoutTranslation{
    dictionaryName3,
    std::vector<DictionaryWord>{dictionaryWord1, dictionaryWord2, dictionaryWordWithoutTranslation}};
const Dictionary emptyDictionary{dictionaryName1, {}};
const std::vector<Dictionary> noDictionaries{};
const std::vector<Dictionary> dictionaries{dictionary1, dictionary2};
const std::vector<Dictionary> dictionariesWithDictionaryWithOneWOrd{dictionary1};
const std::vector<Dictionary> dictionariesWithDictionaryWithSomeWordsWithoutTranslation{
    dictionaryWithSomeWordsWithoutTranslation};
const std::string invalidJson{"{."};
const std::string emptyDictionariesJson;
const nlohmann::json serializedDictionaries = {
    {{"dictionaryName", "dictionaryName1"},
     {"dictionaryWords", {{{"englishWord", "englishWord1"}, {"translation", "translation1"}}}}},
    {{"dictionaryName", "dictionaryName2"},
     {"dictionaryWords",
      {{{"englishWord", "englishWord1"}, {"translation", "translation1"}},
       {{"englishWord", "englishWord2"}, {"translation", "translation2"}}}}}};
const nlohmann::json dictionariesWithoutDictionaryNameJson = {{{"dictionaryWords", {}}}};
const nlohmann::json dictionariesWithoutDictionaryWordsJson = {{{"dictionaryName", "dictionaryName1"}}};
const nlohmann::json serializedDictionariesWithSomeMissingEnglishWordField = {
    {{"dictionaryName", "dictionaryName1"},
     {"dictionaryWords",
      {{{"englishWord", "englishWord1"}, {"translation", "translation1"}},
       {{"translation", "translation2"}}}}}};
const nlohmann::json serializedDictionariesWithMissingTranslationField = {
    {{"dictionaryName", "dictionaryName3"},
     {"dictionaryWords",
      {{{"englishWord", "englishWord1"}, {"translation", "translation1"}},
       {{"englishWord", "englishWord2"}, {"translation", "translation2"}},
       {{"englishWord", "englishWord3"}}}}}};
}

class DictionaryJsonSerializerTest : public Test
{
public:
    DictionaryJsonSerializer serializer;
};

TEST_F(DictionaryJsonSerializerTest, giveNoDictionaries_shouldReturnEmptyString)
{
    const auto actualSerializedDictionaries = serializer.serialize(noDictionaries);

    EXPECT_TRUE(actualSerializedDictionaries.empty());
}

TEST_F(DictionaryJsonSerializerTest, givenDictionaries_shouldReturnSerializedDictionaries)
{
    const auto actualSerializedDictionaries = serializer.serialize(dictionaries);

    EXPECT_EQ(actualSerializedDictionaries, serializedDictionaries.dump());
}

TEST_F(DictionaryJsonSerializerTest, givenInvalidJson_shouldReturnNoDictionaries)
{
    const auto actualDictionaries = serializer.deserialize(invalidJson);

    EXPECT_TRUE(actualDictionaries.empty());
}

TEST_F(DictionaryJsonSerializerTest, givenEmptyJson_shouldReturnNoDictionaries)
{
    const auto actualDictionaries = serializer.deserialize(emptyDictionariesJson);

    EXPECT_TRUE(actualDictionaries.empty());
}

TEST_F(DictionaryJsonSerializerTest,
       givenJsonWithOneDictionaryWithoutDictionaryNameField_shouldReturnNoDictionaries)
{
    const auto actualDictionaries = serializer.deserialize(dictionariesWithoutDictionaryNameJson.dump());

    EXPECT_TRUE(actualDictionaries.empty());
}

TEST_F(DictionaryJsonSerializerTest,
       givenJsonWithOneDictionaryWithoutDictionaryWordsField_shouldReturnNoDictionaries)
{
    const auto actualDictionaries = serializer.deserialize(dictionariesWithoutDictionaryWordsJson.dump());

    EXPECT_TRUE(actualDictionaries.empty());
}

TEST_F(
    DictionaryJsonSerializerTest,
    givenJsonDictionaryWithDictionaryWordsWithoutEnglishWordField_shouldReturnDictionaryWithWordWhichHadEnglishWord)
{
    const auto actualDictionaries =
        serializer.deserialize(serializedDictionariesWithSomeMissingEnglishWordField.dump());

    EXPECT_EQ(actualDictionaries, dictionariesWithDictionaryWithOneWOrd);
}

TEST_F(
    DictionaryJsonSerializerTest,
    givenJsonDictionaryWithDictionaryWordsWithoutTranslationField_shouldReturnDictionaryWithWordsWithNoneTranslation)
{
    const auto actualDictionaries =
        serializer.deserialize(serializedDictionariesWithMissingTranslationField.dump());

    EXPECT_EQ(actualDictionaries, dictionariesWithDictionaryWithSomeWordsWithoutTranslation);
}

TEST_F(DictionaryJsonSerializerTest, givenSerializedDictionaries_shouldReturnDictionaries)
{
    const auto actualDictionaries = serializer.deserialize(serializedDictionaries.dump());

    EXPECT_EQ(actualDictionaries, dictionaries);
}
