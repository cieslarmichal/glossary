#include "GetSyslogPath.h"

#include "boost/algorithm/string/predicate.hpp"
#include "gtest/gtest.h"

using namespace ::testing;
using namespace utils;

class GetSyslogPathTest : public Test
{
public:
    const std::string validSyslogPathEnd{"glossary/syslog.log"};
};

TEST_F(GetSyslogPathTest, shouldReturnSyslogPath)
{
    const auto actualSyslogPath = getSyslogPath();

    ASSERT_TRUE(boost::algorithm::ends_with(actualSyslogPath, validSyslogPathEnd));
}
