#include "GlossaryApplication.h"

#include "GlossaryFactory.h"

namespace glossary
{
GlossaryApplication::GlossaryApplication()
    : glossary{GlossaryFactory::createGlossaryFactory()->createGlossary()}
{
}

void GlossaryApplication::run()
{
    glossary->run();
}
}