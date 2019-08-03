#include "TextFileWriter.h"

#include "gtest/gtest.h"

#include "TextFileReader.h"

using namespace ::testing;

namespace
{
const std::string textToWrite{"Hello this text should be written\nby write method"};
const std::string textToAppend{"\nand this text should be written\nby append method"};
const std::string textAfterWriteAndAppend{textToWrite + textToAppend};
const std::string correctFilePath = "../UT/Source/fileToTestTextFileWriter";
const std::string incorrectFilePath = "UTzxxxx/fi123xtFileWriter";

}

class TextFileWriterTest : public Test
{
public:
    TextFileReader textFileReader;
};

TEST_F(TextFileWriterTest, givenCorrectFilePath_shouldWriteThisStringIntoTextFile)
{
    TextFileWriter textFileWriter{correctFilePath};
    textFileWriter.write(textToWrite);

    auto fileContent = textFileReader.read(correctFilePath);
    ASSERT_EQ(textToWrite, fileContent);
}

TEST_F(TextFileWriterTest, givenIncorrectFilePath_shouldThrowFileNotFoundForWritingAndAppending)
{
    TextFileWriter textFileWriter{incorrectFilePath};

    ASSERT_THROW(textFileWriter.write(textToWrite), TextFileWriter::FileNotFound);
    ASSERT_THROW(textFileWriter.append(textToWrite), TextFileWriter::FileNotFound);
}

TEST_F(TextFileWriterTest, givenCorrectFilePath_shouldAppendThisStringToTheTextFile)
{
    TextFileWriter textFileWriter{correctFilePath};
    textFileWriter.write(textToWrite);
    textFileWriter.append(textToAppend);
    auto fileContent = textFileReader.read(correctFilePath);

    ASSERT_EQ(textAfterWriteAndAppend, fileContent);
}

