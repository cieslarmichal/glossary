#include "WordsDatabase.h"

#include "gtest/gtest.h"
#include "FileAccessMock.h"
#include "StringHelper.h"
#include "StorageMock.h"

using namespace ::testing;

namespace
{
const std::string wordDescriptionsFilePath{"../database/words.txt"};
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

class DatabaseImplTest : public Test
{
public:
    WordDescription createWordDescription()
    {
        WordDescription wordDescription;
        std::vector<std::string> wordSentences{sentence};
        std::vector<DefinitionWithExample> wordDefinitionsAndExamples{{definition, example}};
        wordDescription.definitionsWithExamples = wordDefinitionsAndExamples;
        wordDescription.sentences = wordSentences;
        return wordDescription;
    }

    StrictMock<FileAccessMock> fileAccess;
    StorageMock storage;
    WordsDatabase database{fileAccess, storage};
};

TEST_F(DatabaseImplTest, givenWordDescription_shouldWriteIntoFile)
{
    auto wordDescription = createWordDescription();
    auto word = EnglishWordWithDescription{existingInFileEnglishWord, wordDescription};
    std::string expectedWordWithDescription = existingInFileEnglishWord+"\n{\n"+wordDescription.toString()+"}\n";
    EXPECT_CALL(fileAccess, append(wordDescriptionsFilePath, expectedWordWithDescription));

    database.saveWord(word);
}

