#include "DictionaryJsonSerializer.h"

#include "gtest/gtest.h"

#include "exceptions/DictionaryJsonMissingRequiredFieldsError.h"
#include "exceptions/InvalidJsonError.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string dictionaryName{"dictionaryName"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWordWithoutTranslation{"englishWord1", std::nullopt};
const Dictionary dictionary{dictionaryName, std::vector<DictionaryWord>{dictionaryWord1, dictionaryWord2}};
const Dictionary dictionaryWithSomeWordsWithoutTranslation{
    dictionaryName, std::vector<DictionaryWord>{dictionaryWordWithoutTranslation, dictionaryWord2}};
const std::vector<Dictionary> noDictionaries{};
const std::vector<Dictionary> dictionaries{dictionary};
const std::vector<Dictionary> dictionariesWithDictionaryWithSomeWordsWithoutTranslation{
    dictionaryWithSomeWordsWithoutTranslation};
const std::string invalidJson{"{."};
const std::string emptyDictionariesJson{"{}"};
const std::string jsonDictionaries{
    R"([{"dictionaryName":"dictionaryName","dictionaryWords":[{"englishWord":"englishWord1","translation":"translation1"},{"englishWord":"englishWord2","translation":"translation2"}]}])"};
const std::string jsonDictionariesWithoutDictionaryNameField{
    R"([{"missing":"dictionaryName","dictionaryWords":[{"englishWord":"englishWord1","translation":"translation1"},{"englishWord":"englishWord2","translation":"translation2"}]}])"};
const std::string jsonDictionariesWithoutDictionaryWordsField{
    R"([{"dictionaryName":"dictionaryName","missing":[{"englishWord":"englishWord1","translation":"translation1"},{"englishWord":"englishWord2","translation":"translation2"}]}])"};
const std::string jsonDictionariesWithMissingEnglishWordField{
    R"([{"dictionaryName":"dictionaryName","dictionaryWords":[{"missing":"englishWord1","translation":"translation1"},{"englishWord":"englishWord2","translation":"translation2"}]}])"};
const std::string jsonDictionariesWithMissingTranslationField{
    R"([{"dictionaryName":"dictionaryName","dictionaryWords":[{"englishWord":"englishWord1","missing":"translation1"},{"englishWord":"englishWord2","translation":"translation2"}]}])"};
}

class DictionaryJsonSerializerTest : public Test
{
public:
    DictionaryJsonSerializer serializer;
};

TEST_F(DictionaryJsonSerializerTest, giveNoDictionaries_shouldReturnEmptyJson)
{
    const auto actualSerializedDictionaries = serializer.serialize(noDictionaries);

    EXPECT_EQ(actualSerializedDictionaries, "{}");
}

TEST_F(DictionaryJsonSerializerTest, givenDictionaries_shouldReturnSerializedDictionaries)
{
    const auto actualSerializedDictionaries = serializer.serialize(dictionaries);

    EXPECT_EQ(actualSerializedDictionaries, jsonDictionaries);
}

TEST_F(DictionaryJsonSerializerTest, givenInvalidJson_shouldThrowError)
{
    ASSERT_THROW(serializer.deserialize(invalidJson), exceptions::InvalidJsonError);
}

TEST_F(DictionaryJsonSerializerTest, givenEmptyJson_shouldReturnNoDictionaries)
{
    const auto actualDictionaries = serializer.deserialize(emptyDictionariesJson);

    EXPECT_TRUE(actualDictionaries.empty());
}

TEST_F(DictionaryJsonSerializerTest, givenJsonWithOneDictionaryWithoutDictionaryNameField_shouldThrow)
{
    ASSERT_THROW(serializer.deserialize(jsonDictionariesWithoutDictionaryNameField),
                 exceptions::DictionaryJsonMissingRequiredFieldsError);
}

TEST_F(DictionaryJsonSerializerTest, givenJsonWithOneDictionaryWithoutDictionaryWordsField_shouldThrow)
{
    ASSERT_THROW(serializer.deserialize(jsonDictionariesWithoutDictionaryWordsField),
                 exceptions::DictionaryJsonMissingRequiredFieldsError);
}

TEST_F(DictionaryJsonSerializerTest, givenJsonDictionaryWithDictionaryWordsWithoutEnglishWordField_shouldThrow)
{
    ASSERT_THROW(serializer.deserialize(jsonDictionariesWithMissingEnglishWordField),
                 exceptions::DictionaryJsonMissingRequiredFieldsError);
}

TEST_F(DictionaryJsonSerializerTest,
       givenJsonDictionaryWithDictionaryWordsWithoutTranslationField_shouldReturnDictionaryWithWordsWithNoneTranslation)
{
    const auto actualDictionaries = serializer.deserialize(jsonDictionariesWithMissingTranslationField);

    EXPECT_EQ(actualDictionaries, dictionariesWithDictionaryWithSomeWordsWithoutTranslation);
}

TEST_F(DictionaryJsonSerializerTest, givenSerializedDictionaries_shouldReturnDictionaries)
{
    const auto actualDictionaries = serializer.deserialize(jsonDictionaries);

    EXPECT_EQ(actualDictionaries, dictionaries);
}
