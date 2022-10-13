#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionDownloader.h"

namespace glossary::wordDescriptionDownloader
{
class WordDescriptionDownloaderMock : public WordDescriptionDownloader
{
public:
    MOCK_CONST_METHOD2(tryDownloadWordDescription,
                       wordDescriptionRepository::WordDescription(
                           const wordDescriptionRepository::std::string&, const std::string& wordsApiKey));
};
}