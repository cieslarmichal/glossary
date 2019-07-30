#include "TextFileWriter.h"

#include "gtest/gtest.h"

#include "TextFileReader.h"

using namespace ::testing;

namespace
{
const std::string textToWrite{"this is example text written to check/n/n TextFileWriter class"};
}

class TextFileWriterTest : public Test
{
public:
    TextFileWriter textFileWriter;
    TextFileReader textFileReader;
};

TEST_F(TextFileWriterTest, givenCorrectFilePath_shouldWriteThisStringIntoTextFile)
{
    const std::string correctFilePath = "../UT/Source/fileToTestTextFileWriter";

    textFileWriter.write(correctFilePath, textToWrite);

    auto fileContent = textFileReader.read(correctFilePath);
    ASSERT_EQ(textToWrite, fileContent);
}

TEST_F(TextFileWriterTest, givenIncorrectFilePath_shouldThrowFileNotFound)
{
    const std::string incorrectFilePath = "UTzxxxx/fi123xtFileWriter";

    ASSERT_THROW(textFileWriter.write(incorrectFilePath,textToWrite), TextFileWriter::FileNotFound);
}
