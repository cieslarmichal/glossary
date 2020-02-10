#include "utils/FileAccessImpl.h"

#include "exceptions/FileNotFound.h"
#include "gtest/gtest.h"

using namespace ::testing;
using namespace utils;

namespace
{
const std::string textToWrite{
    "Hello this text should be written\nby write method"};
const std::string textToAppend{
    "\nand this text should be written\nby append method"};
const std::string textAfterWriteAndAppend{textToWrite + textToAppend};
const std::string correctPathForWriting =
    "../UT/TestTextFiles/testFileForWriting.txt";
const std::string correctPathForReading =
    "../UT/TestTextFiles/testFileForReading.txt";
const std::string incorrectPath = "433\\UTzxxxx/fi123xtF";
const std::string exampleContent{
    "this is example file created\nin order to check readContent\nmethod"};

}

class FileAccessImplTest : public Test
{
public:
    FileAccessImpl fileAccess;
};

TEST_F(FileAccessImplTest, givenCorrectPath_shouldWriteToFile)
{
    fileAccess.write(correctPathForWriting, textToWrite);

    const auto fileContent = fileAccess.readContent(correctPathForWriting);

    ASSERT_EQ(textToWrite, fileContent);
}

TEST_F(FileAccessImplTest,
       givenIncorrectPath_shouldThrowFileNotFoundForWritingAppendingAndReading)
{
    ASSERT_THROW(fileAccess.write(incorrectPath, textToWrite),
                 exceptions::FileNotFound);
    ASSERT_THROW(fileAccess.append(incorrectPath, textToWrite),
                 exceptions::FileNotFound);
    ASSERT_THROW(fileAccess.readContent(incorrectPath),
                 exceptions::FileNotFound);
}

TEST_F(FileAccessImplTest, givenCorrectPath_shouldAppendToFile)
{
    fileAccess.write(correctPathForWriting, textToWrite);
    fileAccess.append(correctPathForWriting, textToAppend);

    const auto fileContent = fileAccess.readContent(correctPathForWriting);

    ASSERT_EQ(textAfterWriteAndAppend, fileContent);
}

TEST_F(FileAccessImplTest, givenCorrectPath_shouldReturnContentOfFile)
{
    const auto fileContent = fileAccess.readContent(correctPathForReading);

    ASSERT_EQ(fileContent, exampleContent);
}
