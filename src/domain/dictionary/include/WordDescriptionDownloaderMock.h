#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionDownloader.h"

namespace glossary::dictionary
{
class WordDescriptionDownloaderMock : public WordDescriptionDownloader
{
public:
    MOCK_CONST_METHOD2(tryDownloadWordDescription,
                       dictionary::WordDescription(
                           const std::string&, const std::string& wordsApiKey));
};
}