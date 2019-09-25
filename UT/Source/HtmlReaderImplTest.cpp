#include "HtmlReaderImpl.h"

#include "gtest/gtest.h"

#include "Exceptions/ConnectionFailed.h"

using namespace ::testing;

class HtmlReaderImplTest : public Test
{
public:
    HtmlReaderImpl htmlReader;
};

TEST_F(HtmlReaderImplTest, givenCorrectUrlAddress_shouldReturnContentOfTheHtmlFile)
{
    const std::string correctUrlAddress = "https://www.merriam-webster.com";

    std::string htmlContent = htmlReader.read(correctUrlAddress);

    ASSERT_TRUE(htmlContent.find("<!DOCTYPE html>") || htmlContent.find("<!doctype html>"));
}

TEST_F(HtmlReaderImplTest, givenIncorrectUrlAddress_shouldThrowConnectionFailed)
{
    std::string inaccessibleUrlAddress = ".xh111ttps://aazzz.com";

    ASSERT_THROW(htmlReader.read(inaccessibleUrlAddress), exceptions::ConnectionFailed);
}
