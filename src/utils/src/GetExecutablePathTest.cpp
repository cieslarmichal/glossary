#include "ProjectAbsolutePath.h"

#include "gtest/gtest.h"
#include "boost/algorithm/string/predicate.hpp"

using namespace ::testing;
using namespace utils;

class ProjectAbsolutePathTest : public Test
{
public:
    const std::string projectName{"glossary/"};
};

TEST_F(ProjectAbsolutePathTest, shouldReturnAbsolutePathToProject)
{
    const auto actualPath = getExecutablePath();
    std::cerr<<actualPath;
//    ASSERT_TRUE(boost::algorithm::ends_with(actualPath, projectName));
}