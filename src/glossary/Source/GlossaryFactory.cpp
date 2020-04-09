#include "GlossaryFactory.h"

#include "DefaultGlossaryFactory.h"

namespace glossary
{
std::unique_ptr<GlossaryFactory> GlossaryFactory::createGlossaryFactory()
{
    return std::make_unique<DefaultGlossaryFactory>();
}
}