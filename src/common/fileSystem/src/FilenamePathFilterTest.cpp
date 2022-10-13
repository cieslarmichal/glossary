#include "FilenamePathFilter.h"

#include "gtest/gtest.h"

#include "GetProjectPath.h"

using namespace ::testing;
using namespace common::fileSystem;

namespace
{
const std::string projectPath{getProjectPath("glossary")};
const std::string testDirectory = projectPath + "src/common/fileSystem/src/testDirectory/testFiles/";
const std::string filenameForReading = "testFileForReading.txt";
const std::string filenameForWriting = "testFileForWriting.txt";
const std::string jpgFilename{"jpgFile.jpg"};
const std::string pdfFilename{"pdfFile.pdf"};
const std::string fileInsideDirFilename{"fileInsideDir.txt"};
const std::string pathForReading{testDirectory + filenameForReading};
const std::string pathForWriting{testDirectory + filenameForWriting};
const std::string jpgFilePath{testDirectory + jpgFilename};
const std::string pdfFilePath{testDirectory + pdfFilename};
const std::string dummyDirectoryName{testDirectory + "dummyDir/"};
const std::string fileInsideDummyDir{dummyDirectoryName + fileInsideDirFilename};
const std::vector<std::string> filePaths{pathForReading, pathForWriting,     jpgFilePath,
                                         pdfFilePath,    dummyDirectoryName, fileInsideDummyDir};
const std::vector<std::string> filenamesAfterFiltering{filenameForReading, filenameForWriting, jpgFilename,
                                                       pdfFilename, fileInsideDirFilename};
}

class FilenamePathFilterTest : public Test
{
public:
    FilenamePathFilter filenamePathFilter;
};

TEST_F(FilenamePathFilterTest, givenFilenamesAndEmptyExtensionsListShouldNotFilter)
{
    const auto filteredFilenames = filenamePathFilter.filterFilenames(filePaths);

    ASSERT_EQ(filteredFilenames, filenamesAfterFiltering);
}
