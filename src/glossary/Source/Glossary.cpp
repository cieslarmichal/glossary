#include "Glossary.h"

#include "GlossaryApplication.h"
#include "utils/FileAccessFactory.h"

namespace glossary
{
Glossary::Glossary()
    : application{std::make_unique<GlossaryApplication>(
          utils::FileAccessFactory::createFileAccessFactory()->createDefaultFileAccess())}
{
}

void Glossary::run()
{
    application->run();
}
}