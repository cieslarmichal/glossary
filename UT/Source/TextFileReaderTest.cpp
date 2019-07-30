#include "TextFileReader.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const std::string correctFilePath = "../UT/Source/fileToTestTextFileReader.txt";
const std::string exampleContent{"this is example file created\nin order to check TextFileReader\nclass"};
const std::vector<std::string> exampleSplittedContent{"this is example file created",
                                                      "in order to check TextFileReader", "class"};
}

class TextFileReaderTest : public Test
{
public:
    TextFileReader textFileReader;
};

TEST_F(TextFileReaderTest, givenCorrectFilePath_shouldReturnContentOfTheFile)
{
    auto fileContent = textFileReader.read(correctFilePath);
    ASSERT_EQ(fileContent, exampleContent);
}

TEST_F(TextFileReaderTest, givenIncorrectFilePath_shouldThrowFileNotFound)
{
    std::string incorrectFilePath = "a/c/d.txt";
    ASSERT_THROW(textFileReader.read(incorrectFilePath), TextFileReader::FileNotFound);
}

TEST_F(TextFileReaderTest, givenCorrectFilePath_shouldReturnSplittedContentOfTheFile)
{
    auto fileContent = textFileReader.readAndSplitLines(correctFilePath);
    ASSERT_EQ(fileContent, exampleSplittedContent);
}
