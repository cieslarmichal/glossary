#include "FileAccessImpl.h"

#include "boost/algorithm/cxx11/all_of.hpp"
#include "boost/algorithm/cxx11/any_of.hpp"
#include "boost/algorithm/string/predicate.hpp"
#include "gtest/gtest.h"

#include "exceptions/DirectoryNotFound.h"
#include "exceptions/FileNotFound.h"

using namespace ::testing;
using namespace utils;
using namespace boost::algorithm;

namespace
{
const std::string textToWrite{"Hello this text should be written\nby write method"};
const std::string textToAppend{"\nand this text should be written\nby append method"};
const std::string textAfterWriteAndAppend{textToWrite + textToAppend};
const std::string exampleContent{"this is example file created\nin order to check readContent\nmethod"};
const std::string testDirectory = "src/utils/src/testDirectory/testFiles/";
const std::string testExperimentalDirectory = "src/utils/src/testDirectory/testExperimental/";
const std::string filenameForReading = "testFileForReading.txt";
const std::string filenameForWriting = "testFileForWriting.txt";
const std::string pathForReading{testDirectory + filenameForReading};
const std::string pathForWriting{testDirectory + filenameForWriting};
const std::string jpgFile{"jpgFile.jpg"};
const std::string pdfFile{"pdfFile.pdf"};
const std::string incorrectPath = "433\\UTzxxxx/fi123xtF";
const std::vector<std::string> filenamesWithoutFiltering{filenameForReading, pdfFile, filenameForWriting,
                                                         jpgFile};
const std::vector<std::string> filenamesAfterFiltering{filenameForReading, pdfFile, filenameForWriting};
const std::vector<std::string> noExtensionsToFilter{};
const std::vector<std::string> extensionsToFilter{".txt", ".pdf"};
const std::string newDirectoryPath{testExperimentalDirectory + "xxx/"};
const std::string newFileInDirectoryPath{newDirectoryPath + "aaaa.txt"};
const std::string newDirectoryChangedPath{testExperimentalDirectory + "yyy/"};
const std::string newFilePath{testExperimentalDirectory + "xxx.txt"};
const std::string newFileChangedPath{testExperimentalDirectory + "yyy.txt"};
}

class FileAccessImplTest : public Test
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

    FileAccessImpl fileAccess{"glossary"};
};

TEST_F(FileAccessImplTest, givenCorrectPath_shouldWriteToFile)
{
    fileAccess.write(pathForWriting, textToWrite);

    const auto actualFileContent = fileAccess.readContent(pathForWriting);

    ASSERT_EQ(actualFileContent, textToWrite);
}

TEST_F(FileAccessImplTest, givenIncorrectPath_shouldThrowFileNotFoundForWritingAppendingAndReading)
{
    ASSERT_THROW(fileAccess.write(incorrectPath, textToWrite), utils::exceptions::FileNotFound);
    ASSERT_THROW(fileAccess.append(incorrectPath, textToWrite), utils::exceptions::FileNotFound);
    ASSERT_THROW(fileAccess.readContent(incorrectPath), utils::exceptions::FileNotFound);
}

TEST_F(FileAccessImplTest, givenCorrectPath_shouldAppendToFile)
{
    fileAccess.write(pathForWriting, textToWrite);
    fileAccess.append(pathForWriting, textToAppend);

    const auto actualFileContent = fileAccess.readContent(pathForWriting);

    ASSERT_EQ(actualFileContent, textAfterWriteAndAppend);
}

TEST_F(FileAccessImplTest, givenCorrectPath_shouldReturnContentOfFile)
{
    const auto actualFileContent = fileAccess.readContent(pathForReading);

    ASSERT_EQ(actualFileContent, exampleContent);
}

TEST_F(FileAccessImplTest, givenCorrectDirectoryPath_shouldReturnDirectoryFilepaths)
{
    const auto actualFilepaths = fileAccess.getDirectoryFilepaths(testDirectory);

    ASSERT_TRUE(all_of(actualFilepaths, [&](const std::string& filepath) {
        return any_of(filenamesWithoutFiltering,
                      [&](const std::string& filename) { return ends_with(filepath, filename); });
    }));
}

TEST_F(FileAccessImplTest, givenIncorrectPath_shouldThrowDirectoryNotFound)
{
    ASSERT_THROW(fileAccess.getDirectoryFilepaths(incorrectPath), exceptions::DirectoryNotFound);
}

TEST_F(FileAccessImplTest,
       givenDirectoryPathWithoutFileExtensionsToFilter_shouldReturnAllFilenamesFromDirectory)
{
    const auto actualFilenames = fileAccess.getDirectoryFilenames(testDirectory, noExtensionsToFilter);

    ASSERT_TRUE(all_of(actualFilenames, [&](const std::string& filepath) {
      return any_of(filenamesWithoutFiltering,
                    [&](const std::string& filename) { return ends_with(filepath, filename); });
    }));
}

TEST_F(FileAccessImplTest,
       givenDirectoryPathWithFileExtensionsToFilter_shouldReturnFilteredFilenamesFromDirectory)
{
    const auto actualFilenames = fileAccess.getDirectoryFilenames(testDirectory, extensionsToFilter);

    ASSERT_TRUE(all_of(actualFilenames, [&](const std::string& filepath) {
      return any_of(filenamesAfterFiltering,
                    [&](const std::string& filename) { return ends_with(filepath, filename); });
    }));
}

TEST_F(FileAccessImplTest, givenExistingPath_shouldReturnTrue)
{
    ASSERT_TRUE(fileAccess.exists(testDirectory));
}

TEST_F(FileAccessImplTest, givenCorrectPath_shouldCreateNewDirectory)
{
    prepareDeletedPath(newDirectoryPath);

    fileAccess.createDirectory(newDirectoryPath);

    ASSERT_TRUE(fileAccess.exists(newDirectoryPath));
    prepareDeletedPath(newDirectoryPath);
}

TEST_F(FileAccessImplTest, givenExistingDirectory_shouldRemoveDirectory)
{
    prepareCreatedDirectory(newDirectoryPath);

    fileAccess.remove(newDirectoryPath);

    ASSERT_FALSE(fileAccess.exists(newDirectoryPath));
}

TEST_F(FileAccessImplTest, givenExistingDirectoryWithFiles_shouldRemoveDirectoryWithFiles)
{
    prepareCreatedDirectory(newDirectoryPath);
    prepareCreatedFile(newFileInDirectoryPath);

    fileAccess.remove(newDirectoryPath);

    ASSERT_FALSE(fileAccess.exists(newDirectoryPath));
    ASSERT_FALSE(fileAccess.exists(newFileInDirectoryPath));
}

TEST_F(FileAccessImplTest, givenExistingFile_shouldRemoveFile)
{
    prepareCreatedFile(newFilePath);

    fileAccess.remove(newFilePath);

    ASSERT_FALSE(fileAccess.exists(newFilePath));
}

TEST_F(FileAccessImplTest, givenExistingDirectory_shouldRenameDirectory)
{
    prepareCreatedDirectory(newDirectoryPath);

    fileAccess.rename(newDirectoryPath, newDirectoryChangedPath);

    ASSERT_TRUE(fileAccess.exists(newDirectoryChangedPath));
    prepareDeletedPath(newDirectoryChangedPath);
}

TEST_F(FileAccessImplTest, givenExistingFile_shouldRenameFile)
{
    prepareCreatedDirectory(newFilePath);

    fileAccess.rename(newFilePath, newFileChangedPath);

    ASSERT_TRUE(fileAccess.exists(newFileChangedPath));
    prepareDeletedPath(newFileChangedPath);
}
