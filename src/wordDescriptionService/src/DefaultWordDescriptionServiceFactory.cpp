#include "DefaultWordDescriptionServiceFactory.h"

#include "DefaultWordDescriptionRetrieverService.h"

namespace glossary::wordDescriptionService
{

std::unique_ptr<WordDescriptionRetrieverService>
DefaultWordDescriptionServiceFactory::createWordDescriptionService(
    const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>& wordDescriptionDownlaoder,
    const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>& wordDescriptionRepository)
    const
{
    return std::make_unique<DefaultWordDescriptionRetrieverService>(wordDescriptionDownlaoder,
                                                                    wordDescriptionRepository);
}

}