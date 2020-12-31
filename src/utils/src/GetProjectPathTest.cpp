#include "GetProjectPath.h"

#include "boost/algorithm/string/predicate.hpp"
#include "gtest/gtest.h"

#include "exceptions/FileNotFound.h"

using namespace ::testing;
using namespace utils;

namespace
{
#ifdef _WIN32
const std::string validPathEnd{"glossary\\"};
#else
const std::string validPathEnd{"glossary/"};
#endif

const std::string validProjectName{"glossary"};
const std::string invalidProjectName{"nasjxanxjqq"};
}

TEST(GetProjectPathTest, givenValidProjectName_shouldReturnProjectPath)
{
    const auto actualProjectPath = getProjectPath(validProjectName);

    ASSERT_TRUE(boost::algorithm::ends_with(actualProjectPath, validPathEnd));
}

TEST(GetProjectPathTest, givenInvalidProjectName_shouldThrowFileNotFound)
{
    ASSERT_THROW(getProjectPath(invalidProjectName), exceptions::FileNotFound);
}