#include "DatabaseImpl.h"

#include "gtest/gtest.h"
#include "FileAccessMock.h"
#include "StringHelper.h"
#include <iostream>

using namespace ::testing;

namespace
{
const std::string wordTranslationsFilePath{"../database/dictionary.txt"};
const std::string wordDescriptionsFilePath{"../database/glossary.txt"};
const std::string wordExistenceInformationsFilePath{"../database/list.txt"};
const std::string existingInFileEnglishWord{"blanket"};
const std::string existingInFilePolishTranslation{"koc"};
const std::string translationsFromFile{existingInFileEnglishWord + " " + existingInFilePolishTranslation};
bool hasDescription{true};
const std::string existenceFromFile{existingInFileEnglishWord + " " + std::to_string(hasDescription)};
const std::string nonExistingInFileEnglishWord{"pillow"};

const std::string definitionMark{":"};
const std::string exampleMark{"//"};
const std::string sentenceMark{"\""};
const std::string definition{definitionMark + "definition"};
const std::string example{exampleMark + "example"};
const std::string sentence{sentenceMark + "some sentence" + sentenceMark};
const std::string descriptionFromFile{
     existingInFileEnglishWord + "\n"+
     "{" + "\n" +
     definition + "\n"+
     example +"\n" +
     sentence +"\n" +
     "}"
};
}


class DatabaseImplSetup : public Test
{
public:
    DatabaseImplSetup()
    {
        EXPECT_CALL(fileAccess, readContent(wordTranslationsFilePath)).WillOnce(Return(translationsFromFile));
    }

    StrictMock<FileAccessMock> fileAccess;
};

class DatabaseImplTest : public DatabaseImplSetup
{
public:
    WordDescription createWordDescription()
    {
        WordDescription wordDescription;
        std::vector<std::string> wordSentences{sentence};
        std::vector<DefinitionWIthExample> wordDefinitionsAndExamples{{definition, example}};
        wordDescription.definitionsWithExamples = wordDefinitionsAndExamples;
        wordDescription.sentences = wordSentences;
        return wordDescription;
    }

    DatabaseImpl database{fileAccess};
};

TEST_F(DatabaseImplTest, givenRemainingWords_shouldReturnNextWord)
{
    WordWithTranslation expectedNextWord{existingInFileEnglishWord, existingInFilePolishTranslation};

    auto actualNextWord = database.readNextWord();

    ASSERT_TRUE(actualNextWord.is_initialized());
    ASSERT_TRUE(*actualNextWord == expectedNextWord);
}

TEST_F(DatabaseImplTest, givenNoMoreRemainingWords_shouldNotReturnNextWord)
{
    database.readNextWord();

    auto actualNextWord = database.readNextWord();

    ASSERT_TRUE(actualNextWord == boost::none);
}

TEST_F(DatabaseImplTest, givenExistingWord_shouldReturnWordExistenceInfo)
{
    WordAvailability expectedExistenceInfo{existingInFileEnglishWord, hasDescription};
    EXPECT_CALL(fileAccess, readContent(wordExistenceInformationsFilePath)).WillOnce(Return(existenceFromFile));

    auto actualWordExistenceInfo = database.getWordExistenceInfo(existingInFileEnglishWord);

    ASSERT_TRUE(actualWordExistenceInfo.is_initialized());
    ASSERT_TRUE(*actualWordExistenceInfo == expectedExistenceInfo);
}

TEST_F(DatabaseImplTest, givenNotExistingWord_shouldNotReturnWordExistenceInfo)
{
    EXPECT_CALL(fileAccess, readContent(wordExistenceInformationsFilePath)).WillOnce(Return(existenceFromFile));

    auto actualWordExistenceInfo = database.getWordExistenceInfo(nonExistingInFileEnglishWord);

    ASSERT_TRUE(actualWordExistenceInfo == boost::none);
}

TEST_F(DatabaseImplTest, givenExistingWord_shouldReturnWordDescription)
{
    auto wordDescription = createWordDescription();
    EXPECT_CALL(fileAccess, readContent(wordDescriptionsFilePath)).WillOnce(Return(descriptionFromFile));

    auto actualWordDescription = database.getWordDescription(existingInFileEnglishWord);

    ASSERT_TRUE(actualWordDescription.is_initialized());
    std::cout<< *actualWordDescription<<"\n";
    std::cerr<<wordDescription;
    ASSERT_TRUE(*actualWordDescription == wordDescription);
}

TEST_F(DatabaseImplTest, givenNotExistingWord_shouldNotReturnWordDescription)
{
    EXPECT_CALL(fileAccess, readContent(wordDescriptionsFilePath)).WillOnce(Return(descriptionFromFile));

    auto actualWordDescription = database.getWordDescription(nonExistingInFileEnglishWord);

    ASSERT_TRUE(actualWordDescription == boost::none);
}

TEST_F(DatabaseImplTest, givenWordExistenceInfo_shouldWriteIntoFile)
{
    WordAvailability existenceInfo{existingInFileEnglishWord, hasDescription};
    EXPECT_CALL(fileAccess, append(wordExistenceInformationsFilePath, existenceInfo.toString()));

    database.saveWordExistenceInfo(existenceInfo);
}

TEST_F(DatabaseImplTest, givenWordDescription_shouldWriteIntoFile)
{
    auto wordDescription = createWordDescription();
    auto word = EnglishWordWithDescription{existingInFileEnglishWord, wordDescription};
    std::string expectedWordWithDescription = existingInFileEnglishWord+"\n{\n"+wordDescription.toString()+"}\n";
    EXPECT_CALL(fileAccess, append(wordDescriptionsFilePath, expectedWordWithDescription));

    database.writeWordWithDescription(word);
}

