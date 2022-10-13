#include "GetExecutablePath.h"

#include "boost/algorithm/string/predicate.hpp"
#include "gtest/gtest.h"

using namespace ::testing;
using namespace common::fileSystem;

namespace
{
const std::string fileSystemExecutableName{"fileSystemUT"};
}

TEST(GetExecutablePathTest, shouldReturnAbsolutePathToProject)
{
    const auto actualPath = getExecutablePath();

    ASSERT_TRUE(boost::algorithm::ends_with(actualPath, fileSystemExecutableName));
}