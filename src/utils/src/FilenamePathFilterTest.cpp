#include "FilenamePathFilter.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace utils;

namespace
{
const std::string filename1{"file1.txt"};
const std::string filename2{"file2.pdf"};
const std::string filename3{"file3.h"};
const std::string filename4{"x"};
const std::string filepath1{"/home/michal/" + filename1};
const std::string filepath2{"/home/michal/" + filename2};
const std::string filepath3{filename3};
const std::string filepath4{"/home/michal/" + filename4};
const std::vector<std::string> filepaths{filepath1, filepath2, filepath3, filepath4};
const std::vector<std::string> filenamesAfterFiltering{filename1, filename2, filename3, filename4};
}

class FilenamePathFilterTest : public Test
{
public:
    FilenamePathFilter filenamePathFilter;
};

TEST_F(FilenamePathFilterTest, givenFilenamesAndEmptyExtensionsListShouldNotFilter)
{
    const auto filteredFilenames = filenamePathFilter.filter(filepaths);

    ASSERT_EQ(filteredFilenames, filenamesAfterFiltering);
}
