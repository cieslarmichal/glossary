#pragma once

#include <memory>

#include "WordDescriptionDownloader.h"
#include "webConnection/HttpHandler.h"

namespace glossary::wordDescriptionDownloader
{
class WordDescriptionDownloaderFactory
{
public:
    virtual ~WordDescriptionDownloaderFactory() = default;

    virtual std::unique_ptr<WordDescriptionDownloader> createWordDescriptionDownloader() const = 0;

    static std::unique_ptr<WordDescriptionDownloaderFactory>
    createWordDescriptionDownloaderFactory(const std::shared_ptr<const webConnection::HttpHandler>&);
};
}