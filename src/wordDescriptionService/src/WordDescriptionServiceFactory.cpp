#include "WordDescriptionServiceFactory.h"

#include "DefaultWordDescriptionServiceFactory.h"

namespace glossary::wordDescriptionService
{

std::unique_ptr<WordDescriptionServiceFactory>
WordDescriptionServiceFactory::createWordDescriptionServiceFactory()
{
    return std::make_unique<DefaultWordDescriptionServiceFactory>();
}
}