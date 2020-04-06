#include "ApplicationFactory.h"

#include "GlossaryApplicationFactory.h"

namespace glossary
{
std::unique_ptr<ApplicationFactory> ApplicationFactory::createApplicationFactory()
{
    return std::make_unique<GlossaryApplicationFactory>();
}
}