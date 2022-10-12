#pragma once

#include <memory>

#include "WordDescriptionDownloader.h"
#include "WordDescriptionDownloaderApi.h"
#include "httpClient/HttpClient.h"
#include "utils/FileAccess.h"

namespace glossary::wordDescriptionDownloader
{
class WORD_DESCRIPTION_DOWNLOADER_API WordDescriptionDownloaderFactory
{
public:
    virtual ~WordDescriptionDownloaderFactory() = default;

    virtual std::unique_ptr<WordDescriptionDownloader> createWordDescriptionDownloader() const = 0;

    static std::unique_ptr<WordDescriptionDownloaderFactory>
    createWordDescriptionDownloaderFactory(const std::shared_ptr<const httpClient::HttpClient>&);
};
}