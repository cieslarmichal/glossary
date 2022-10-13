#include "FileExtensionsFilter.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace common::fileSystem;

namespace
{
constexpr auto filename1{"file1.txt"};
constexpr auto filename2{"file2.jpg"};
constexpr auto filename3{"file3.pdf"};
constexpr auto filename4{"file4.h"};
const std::vector<std::string> filenames{filename1, filename2, filename3, filename4};
const std::vector<std::string> filenamesAfterFiltering{filename1, filename4};
const std::vector<std::string> noExtensions{};
const std::vector<std::string> extensions{".txt", ".h"};
}

class FileExtensionsFilterTest : public Test
{
public:
    FileExtensionsFilter fileExtensionsFilter;
};

TEST_F(FileExtensionsFilterTest, givenFilenamesAndEmptyExtensionsListShouldNotFilter)
{
    const auto filteredFilenames = fileExtensionsFilter.filterByExtensions(filenames, noExtensions);

    ASSERT_EQ(filteredFilenames, filenames);
}

TEST_F(FileExtensionsFilterTest, givenFilenamesAndExtensionsListShouldFilter)
{
    const auto filteredFilenames = fileExtensionsFilter.filterByExtensions(filenames, extensions);

    ASSERT_EQ(filteredFilenames, filenamesAfterFiltering);
}