#include "Glossary.h"

#include "GlossaryApplication.h"
#include "utils/FileAccessFactory.h"

Glossary::Glossary()
    : application{std::make_unique<GlossaryApplication>(
          utils::FileAccessFactory::createFileAccessFactory()->createDefaultFileAccess())}
{
}

void Glossary::run()
{
    application->run();
}