#include "Glossary.h"

#include "GlossaryApplication.h"
#include "utils/FileAccessImpl.h"

Glossary::Glossary()
    : fileAccess{std::make_shared<utils::FileAccessImpl>("glossary")},
      application{std::make_unique<GlossaryApplication>(fileAccess)}
{
}

void Glossary::run()
{
    application->run();
}