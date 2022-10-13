#include "DefaultFileAccess.h"

#include "gtest/gtest.h"

#include "GetProjectPath.h"
#include "StlOperators.h"
#include "exceptions/DirectoryNotFound.h"
#include "exceptions/FileNotFound.h"

using namespace ::testing;
using namespace common::fileSystem;

namespace
{
const std::string projectPath{getProjectPath("glossary")};
const std::string testDirectory = projectPath + "src/common/fileSystem/src/testDirectory/";
const std::string testFilesDirectory = testDirectory + "testFiles/";
const std::string testExperimentalDirectory = testDirectory + "testExperimental/";
const std::string slashDelimiter = "/";
const std::string textToWrite{"Hello this text should be written\nby write method"};
const std::string textToAppend{"\nand this text should be written\nby append method"};
const std::string textAfterWriteAndAppend{textToWrite + textToAppend};
const std::string exampleContent{"this is example file created\nin order to check readContent\nmethod"};
const std::string filenameForReading = "testFileForReading.txt";
const std::string filenameForWriting = "testFileForWriting.txt";
const std::string dummyDirectoryName{"dummyDir"};
const std::string fileInsideDummyDir{"fileInsideDir.txt"};
const std::string jpgFile{"jpgFile.jpg"};
const std::string pdfFile{"pdfFile.pdf"};
const std::string pathForReading{testFilesDirectory + filenameForReading};
const std::string pathForWriting{testFilesDirectory + filenameForWriting};
const std::string dummyDirectoryPath{testFilesDirectory + dummyDirectoryName};
const std::string fileInsideDummyDirPath{dummyDirectoryPath + slashDelimiter + fileInsideDummyDir};
const std::string jpgPath{testFilesDirectory + jpgFile};
const std::string pdfPath{testFilesDirectory + pdfFile};
const std::vector<std::string> filenamesAfterFileFiltering{filenameForReading, jpgFile, pdfFile,
                                                           filenameForWriting, fileInsideDummyDir};
const std::vector<std::string> filenamesAfterTxtAndFileFiltering{filenameForReading, filenameForWriting,
                                                                 fileInsideDummyDir};
const std::vector<std::string> expectedFilePaths{pathForReading,         pathForWriting, dummyDirectoryPath,
                                                 fileInsideDummyDirPath, jpgPath,        pdfPath};
const std::vector<std::string> noExtensionsToFilter{};
const std::vector<std::string> txtExtensionsToFilter{".txt"};
const std::string newDirectoryPath{testExperimentalDirectory + "xxx/"};
const std::string newFileInDirectoryPath{newDirectoryPath + "aaaa.txt"};
const std::string newDirectoryChangedPath{testExperimentalDirectory + "yyy/"};
const std::string newFilePath{testExperimentalDirectory + "xxx.txt"};
const std::string newFileChangedPath{testExperimentalDirectory + "yyy.txt"};
const std::string incorrectPath = "433\\UTzxxxx/fi123xtF";
}

class DefaultFileAccessTest : public Test
{
public:
    void prepareCreatedFile(const std::string& path) const
    {
        fileAccess.write(path, "");
    }

    void prepareCreatedDirectory(const std::string& path) const
    {
        fileAccess.createDirectory(path);
    }

    void prepareDeletedPath(const std::string& path) const
    {
        fileAccess.remove(path);
    }

    DefaultFileAccess fileAccess;
};

TEST_F(DefaultFileAccessTest, givenCorrectPath_shouldWriteToFile)
{
    fileAccess.write(pathForWriting, textToWrite);

    const auto actualFileContent = fileAccess.readContent(pathForWriting);

    ASSERT_EQ(actualFileContent, textToWrite);
}

TEST_F(DefaultFileAccessTest, givenIncorrectPath_shouldThrowFileNotFoundForWritingAppendingAndReading)
{
    ASSERT_THROW(fileAccess.write(incorrectPath, textToWrite), exceptions::FileNotFound);
    ASSERT_THROW(fileAccess.append(incorrectPath, textToWrite), exceptions::FileNotFound);
    ASSERT_THROW(fileAccess.readContent(incorrectPath), exceptions::FileNotFound);
}

TEST_F(DefaultFileAccessTest, givenCorrectPath_shouldAppendToFile)
{
    fileAccess.write(pathForWriting, textToWrite);
    fileAccess.append(pathForWriting, textToAppend);

    const auto actualFileContent = fileAccess.readContent(pathForWriting);

    ASSERT_EQ(actualFileContent, textAfterWriteAndAppend);
}

TEST_F(DefaultFileAccessTest, givenCorrectPath_shouldReturnContentOfFile)
{
    const auto actualFileContent = fileAccess.readContent(pathForReading);

    ASSERT_EQ(actualFileContent, exampleContent);
}

TEST_F(DefaultFileAccessTest, givenCorrectPath_shouldCreateNewDirectory)
{
    prepareDeletedPath(newDirectoryPath);

    fileAccess.createDirectory(newDirectoryPath);

    ASSERT_TRUE(fileAccess.exists(newDirectoryPath));
    prepareDeletedPath(newDirectoryPath);
}

TEST_F(DefaultFileAccessTest, givenExistingDirectory_shouldRemoveDirectory)
{
    prepareCreatedDirectory(newDirectoryPath);

    fileAccess.remove(newDirectoryPath);

    ASSERT_FALSE(fileAccess.exists(newDirectoryPath));
}

TEST_F(DefaultFileAccessTest, givenExistingDirectoryWithFiles_shouldRemoveDirectoryWithFiles)
{
    prepareCreatedDirectory(newDirectoryPath);
    prepareCreatedFile(newFileInDirectoryPath);

    fileAccess.remove(newDirectoryPath);

    ASSERT_FALSE(fileAccess.exists(newDirectoryPath));
    ASSERT_FALSE(fileAccess.exists(newFileInDirectoryPath));
}

TEST_F(DefaultFileAccessTest, givenExistingFile_shouldRemoveFile)
{
    prepareCreatedFile(newFilePath);

    fileAccess.remove(newFilePath);

    ASSERT_FALSE(fileAccess.exists(newFilePath));
}

TEST_F(DefaultFileAccessTest, givenNonexistingDirectory_shouldNotRenameDirectory)
{
    fileAccess.rename(newDirectoryPath, newDirectoryChangedPath);

    ASSERT_FALSE(fileAccess.exists(newDirectoryPath));
    ASSERT_FALSE(fileAccess.exists(newDirectoryChangedPath));
}

TEST_F(DefaultFileAccessTest, givenExistingDirectory_shouldRenameDirectory)
{
    prepareCreatedDirectory(newDirectoryPath);

    fileAccess.rename(newDirectoryPath, newDirectoryChangedPath);

    ASSERT_TRUE(fileAccess.exists(newDirectoryChangedPath));
    prepareDeletedPath(newDirectoryChangedPath);
}

TEST_F(DefaultFileAccessTest, givenExistingFile_shouldRenameFile)
{
    prepareCreatedDirectory(newFilePath);

    fileAccess.rename(newFilePath, newFileChangedPath);

    ASSERT_TRUE(fileAccess.exists(newFileChangedPath));
    prepareDeletedPath(newFileChangedPath);
}

TEST_F(DefaultFileAccessTest, givenExistingPath_shouldReturnTrue)
{
    ASSERT_TRUE(fileAccess.exists(testFilesDirectory));
}

TEST_F(DefaultFileAccessTest, givenRegularFilePath_whenCheckingForRegularFile_shouldReturnTrue)
{
    ASSERT_TRUE(fileAccess.isRegularFile(pathForReading));
}

TEST_F(DefaultFileAccessTest, givenDirectoryPath_whenCheckingForRegularFile_shouldReturnFalse)
{
    ASSERT_FALSE(fileAccess.isRegularFile(dummyDirectoryPath));
}

TEST_F(DefaultFileAccessTest, givenDirectoryPath_whenCheckingForDirectory_shouldReturnTrue)
{
    ASSERT_TRUE(fileAccess.isDirectory(dummyDirectoryPath));
}

TEST_F(DefaultFileAccessTest, givenRegularFilePath_whenCheckingForDirectory_shouldReturnFalse)
{
    ASSERT_FALSE(fileAccess.isDirectory(pathForReading));
}

TEST_F(DefaultFileAccessTest, givenIncorrectPath_shouldThrowDirectoryNotFound)
{
    ASSERT_THROW(fileAccess.getAllPathsFromDirectory(incorrectPath), exceptions::DirectoryNotFound);
}

TEST_F(DefaultFileAccessTest, givenCorrectDirectoryPath_shouldReturnDirectoryFilePaths)
{
    const auto actualFilePaths = fileAccess.getAllPathsFromDirectory(testFilesDirectory);

    ASSERT_TRUE(compareVectors(actualFilePaths, expectedFilePaths));
}

TEST_F(DefaultFileAccessTest, givenDirectoryPath_shouldReturnAllFilenamesFromDirectory)
{
    const auto actualFilenames = fileAccess.getAllFilenamesFromDirectory(testFilesDirectory);

    ASSERT_TRUE(compareVectors(actualFilenames, filenamesAfterFileFiltering));
}

TEST_F(DefaultFileAccessTest,
       givenDirectoryPathWithoutFileExtensionsToFilter_shouldReturnAllFilenamesFromDirectory)
{
    const auto actualFilenames =
        fileAccess.getFilteredFilenamesFromDirectory(testFilesDirectory, noExtensionsToFilter);

    ASSERT_TRUE(compareVectors(actualFilenames, filenamesAfterFileFiltering));
}

TEST_F(DefaultFileAccessTest,
       givenDirectoryPathWithFileExtensionsToFilter_shouldReturnFilteredFilenamesFromDirectory)
{
    const auto actualFilenames =
        fileAccess.getFilteredFilenamesFromDirectory(testFilesDirectory, txtExtensionsToFilter);

    ASSERT_TRUE(compareVectors(actualFilenames, filenamesAfterTxtAndFileFiltering));
}