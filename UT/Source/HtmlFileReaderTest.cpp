#include "HtmlFileReader.h"

#include "gtest/gtest.h"

using namespace ::testing;

class HtmlFileReaderTest : public Test
{
public:
    HtmlFileReader htmlFileReader;
};

TEST_F(HtmlFileReaderTest, givenCorrectUrlAddress_shouldReturnContentOfTheHtmlFile)
{
    const std::string correctUrlAddress = "https://www.merriam-webster.com";

    std::string htmlContent = htmlFileReader.read(correctUrlAddress);

    ASSERT_TRUE(htmlContent.find("<!DOCTYPE html>") || htmlContent.find("<!doctype html>"));
}

TEST_F(HtmlFileReaderTest, givenIncorrectUrlAddress_shouldThrowConnectionFailed)
{
    std::string inaccessibleUrlAddress = "xh111ttps://aazzz.com";

    ASSERT_THROW(htmlFileReader.read(inaccessibleUrlAddress), HtmlFileReader::ConnectionFailed);
}

TEST_F(HtmlFileReaderTest, givenInaccessibleUrlAddress_shouldThrowFileNotFound)
{
    std::string inaccessibleUrlAddress = "https://www.facebook.com";

    ASSERT_THROW(htmlFileReader.read(inaccessibleUrlAddress), HtmlFileReader::FileNotFound);
}
