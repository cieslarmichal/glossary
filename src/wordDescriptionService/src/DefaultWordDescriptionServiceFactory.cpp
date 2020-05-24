#include "DefaultWordDescriptionServiceFactory.h"

#include "DefaultWordDescriptionRetrieverService.h"
#include "DefaultWordsApiConnectionChecker.h"

namespace glossary::wordDescriptionService
{

std::unique_ptr<WordDescriptionRetrieverService>
DefaultWordDescriptionServiceFactory::createWordDescriptionService(
    const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>& wordDescriptionDownloader,
    const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>& wordDescriptionRepository)
    const
{
    return std::make_unique<DefaultWordDescriptionRetrieverService>(
        wordDescriptionDownloader, wordDescriptionRepository,
        std::make_unique<DefaultWordsApiConnectionChecker>(wordDescriptionDownloader));
}

}