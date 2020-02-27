#include "GetExecutablePath.h"
#include "boost/algorithm/string/predicate.hpp"
#include "gtest/gtest.h"

using namespace ::testing;
using namespace utils;

class GetExecutablePathTest : public Test
{
public:
    const std::string utilsExecutableName{"utilsUT"};
};

TEST_F(GetExecutablePathTest, shouldReturnAbsolutePathToProject)
{
    const auto actualPath = getExecutablePath();

    ASSERT_TRUE(boost::algorithm::ends_with(actualPath, utilsExecutableName));
}