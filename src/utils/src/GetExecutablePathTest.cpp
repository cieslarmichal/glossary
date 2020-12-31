#include "GetExecutablePath.h"

#include "boost/algorithm/string/predicate.hpp"
#include "gtest/gtest.h"

using namespace ::testing;
using namespace utils;

namespace
{
#ifdef _WIN32
const std::string utilsExecutableName{"utilsUT.exe"};
#else
const std::string utilsExecutableName{"utilsUT"};
#endif
}

TEST(GetExecutablePathTest, shouldReturnAbsolutePathToProject)
{
    const auto actualPath = getExecutablePath();
    std::cerr << actualPath;
    ASSERT_TRUE(boost::algorithm::ends_with(actualPath, utilsExecutableName));
}