#include "HtmlReaderImpl.h"

#include "Exceptions/ConnectionFailed.h"
#include "gtest/gtest.h"

using namespace ::testing;

class HtmlReaderImplTest : public Test
{
public:
    HtmlReaderImpl htmlReader;
};

TEST_F(HtmlReaderImplTest,
       givenCorrectUrlAddress_shouldReturnContentOfTheHtmlFile)
{
    const std::string correctUrlAddress = "https://www.merriam-webster.com";

    const auto htmlContent = htmlReader.read(correctUrlAddress);

    ASSERT_TRUE(htmlContent.find("<!DOCTYPE html>") ||
                htmlContent.find("<!doctype html>"));
}

TEST_F(HtmlReaderImplTest, givenIncorrectUrlAddress_shouldThrowConnectionFailed)
{
    const auto inaccessibleUrlAddress = ".xh111ttps://aazzz.com";

    ASSERT_THROW(htmlReader.read(inaccessibleUrlAddress),
                 exceptions::ConnectionFailed);
}
