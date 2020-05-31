#include "DefaultWordDescriptionServiceFactory.h"

#include "DefaultApiKeyLocationUpdater.h"
#include "DefaultWordDescriptionService.h"
#include "DefaultWordsApiConnectionChecker.h"
#include "WordsApiKeyFileReader.h"

namespace glossary::wordDescriptionService
{

DefaultWordDescriptionServiceFactory::DefaultWordDescriptionServiceFactory(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<WordDescriptionService> DefaultWordDescriptionServiceFactory::createWordDescriptionService(
    const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>& wordDescriptionDownloader,
    const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>& wordDescriptionRepository)
    const
{
    return std::make_unique<DefaultWordDescriptionService>(
        wordDescriptionDownloader, wordDescriptionRepository,
        std::make_unique<DefaultWordsApiConnectionChecker>(wordDescriptionDownloader),
        std::make_unique<WordsApiKeyFileReader>(fileAccess),
        std::make_unique<DefaultApiKeyLocationUpdater>(fileAccess));
}

}