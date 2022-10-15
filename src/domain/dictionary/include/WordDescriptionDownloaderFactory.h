#pragma once

#include <memory>

#include "FileAccess.h"
#include "WordDescriptionDownloader.h"
#include "httpClient/HttpClient.h"

namespace glossary::dictionary
{
class WordDescriptionDownloaderFactory
{
public:
    virtual ~WordDescriptionDownloaderFactory() = default;

    virtual std::unique_ptr<WordDescriptionDownloader> createWordDescriptionDownloader() const = 0;

    static std::unique_ptr<WordDescriptionDownloaderFactory>
    createWordDescriptionDownloaderFactory(const std::shared_ptr<const common::httpClient::HttpClient>&);
};
}