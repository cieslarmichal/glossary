#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionDownloader.h"

namespace wordDescriptionDownloader
{
class WordDescriptionDownloaderMock : public WordDescriptionDownloader
{
public:
    MOCK_CONST_METHOD1(downloadWordDescription, boost::optional<wordDescriptionRepository::WordDescription>(
                                                    const wordDescriptionRepository::EnglishWord&));
};
}