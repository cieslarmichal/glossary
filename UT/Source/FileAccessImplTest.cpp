#include "FileAccessImpl.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const std::string textToWrite{"Hello this text should be written\nby write method"};
const std::string textToAppend{"\nand this text should be written\nby append method"};
const std::string textAfterWriteAndAppend{textToWrite + textToAppend};
const std::string correctPathForWriting = "../UT/Source/testFileForWriting.txt";
const std::string correctPathForReading = "../UT/Source/testFileForReading.txt";
const std::string incorrectPath = "433\\UTzxxxx/fi123xtF";
const std::string exampleContent{"this is example file created\nin order to check readContent\nmethod"};

}

class FileAccessImplTest : public Test
{
public:
    FileAccessImpl fileAccess;
};

TEST_F(FileAccessImplTest, givenCorrectPath_shouldWriteToFile)
{
    fileAccess.write(correctPathForWriting, textToWrite);

    auto fileContent = fileAccess.readContent(correctPathForWriting);
    ASSERT_EQ(textToWrite, fileContent);

}

TEST_F(FileAccessImplTest, givenIncorrectPath_shouldThrowFileNotFoundForWritingAppendingAndReading)
{
    ASSERT_THROW(fileAccess.write(incorrectPath, textToWrite), FileAccessImpl::FileNotFound);
    ASSERT_THROW(fileAccess.append(incorrectPath, textToWrite), FileAccessImpl::FileNotFound);
    ASSERT_THROW(fileAccess.readContent(incorrectPath), FileAccessImpl::FileNotFound);
}

TEST_F(FileAccessImplTest, givenCorrectPath_shouldAppendToFile)
{
    fileAccess.write(correctPathForWriting, textToWrite);
    fileAccess.append(correctPathForWriting, textToAppend);
    auto fileContent = fileAccess.readContent(correctPathForWriting);

    ASSERT_EQ(textAfterWriteAndAppend, fileContent);
}

TEST_F(FileAccessImplTest, givenCorrectPath_shouldReturnContentOfFile)
{
    auto fileContent = fileAccess.readContent(correctPathForReading);

    ASSERT_EQ(fileContent, exampleContent);
}
