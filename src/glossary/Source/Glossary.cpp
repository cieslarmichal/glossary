#include "Glossary.h"

#include "GlossaryApplication.h"
#include "utils/FileAccessFactory.h"

Glossary::Glossary()
    : application{std::make_unique<GlossaryApplication>(
          utils::FileAccessFactory::createFileAccessFactory()->createFileAccess("glossary"))}
{
}

void Glossary::run()
{
    application->run();
}