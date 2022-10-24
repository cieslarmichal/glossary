#pragma once

#include "WordDescriptionDownloaderFactory.h"

namespace glossary::dictionary
{
class DefaultWordDescriptionDownloaderFactory : public WordDescriptionDownloaderFactory
{
public:
    explicit DefaultWordDescriptionDownloaderFactory(std::shared_ptr<const common::httpClient::HttpClient>);

    std::unique_ptr<WordDescriptionDownloader> createWordDescriptionDownloader() const override;

private:
    std::shared_ptr<const common::httpClient::HttpClient> httpClient;
};
}